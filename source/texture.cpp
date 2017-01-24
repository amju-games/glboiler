// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <assert.h>
#include "gl_includes.h"
#include "load_png.h"
#include "log.h"
#include "texture.h"

texture::~texture()
{
  if (has_been_uploaded())
  {
    gl_boiler_assert(m_destroy_called);
  }
  free_data();
}

colour texture::get_texel_colour(const vec2& uv) const
{
  gl_boiler_assert(m_data);
  gl_boiler_assert(m_w > 0);
  gl_boiler_assert(m_h > 0);
  gl_boiler_assert(m_bytes_per_pixel > 0);

  int x = static_cast<int>(uv.x * static_cast<float>(m_w - 1));
  int y = static_cast<int>(uv.y * static_cast<float>(m_h - 1));
  gl_boiler_assert(x >= 0);
  gl_boiler_assert(x < static_cast<int>(m_w));
  gl_boiler_assert(y >= 0);
  gl_boiler_assert(y < static_cast<int>(m_h));
 
  // TODO stride ?
  unsigned char* addr = m_data + y * m_w * m_bytes_per_pixel + x; 
  gl_boiler_assert(addr < (m_data + m_w * m_h * m_bytes_per_pixel));

  unsigned char c[4] = { 0, 0, 0, 0xff };

  switch (m_bytes_per_pixel)
  {
  case 1:
    c[0] = c[1] = c[2] = *addr;
    break;
  case 4:
    c[3] = *(addr + 3);
    // fall through
  case 3:
    c[0] = *addr;
    c[1] = *(addr + 1);
    c[2] = *(addr + 2);
    break;
  default:
    gl_boiler_stop; // unexpected bytes per pixel
  }
  
  return colour(
    static_cast<float>(c[0]) / 255.0f, 
    static_cast<float>(c[1]) / 255.0f, 
    static_cast<float>(c[2]) / 255.0f, 
    static_cast<float>(c[3]) / 255.0f );
}

bool texture::load(const std::string& filename)
{
  m_filename = filename;
  m_data = load_png(filename, &m_w, &m_h, &m_bytes_per_pixel);
  if (m_data)
  {
    flip_image_data(m_data, m_w, m_h, m_bytes_per_pixel);

    log(msg() << "Loaded texture \"" << filename 
      << "\" w: " << m_w << " h: " << m_h 
      << " bpp: " << m_bytes_per_pixel);
  }
  else
  {
    log(msg() << "Failed to load texture \"" << filename << "\"");
  }
  return m_data != nullptr;
}

void texture::upload_on_gl_thread()
{
  glGenTextures(1, &m_bind_texture_id);
  glBindTexture(GL_TEXTURE_2D, m_bind_texture_id);

  // TODO GL 1.1 only - move into gl_1_1_renderer/material
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  int format = GL_RGB;
  if (m_bytes_per_pixel == 4)
  {
    format = GL_RGBA;
  }
  
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D,
           0,
           format,
           m_w,
           m_h,
           0,
           format,
           GL_UNSIGNED_BYTE,
           m_data));

  if (m_use_mipmaps)
  {
    GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D)); // GL v.3.0+
  
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  }
  else
  {
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  }

  if (m_delete_data_after_upload)
  {
    free_data();
  }

  m_has_been_uploaded = true;
}

void texture::destroy_on_gl_thread()
{
  free_data();

  if (has_been_uploaded())
  {
    GL_CHECK(glDeleteTextures(1, &m_bind_texture_id));
  }
  m_destroy_called = true;
}

void texture::free_data()
{
  if (m_data)
  {
    free(m_data);
    m_data = nullptr;
    log(msg() << "Deleted data for texture \"" << m_filename << "\"");
  }
}

void texture::use_on_gl_thread()
{
  gl_boiler_assert(m_has_been_uploaded);

  GL_CHECK(glEnable(GL_TEXTURE_2D));
  GL_CHECK(glActiveTexture(GL_TEXTURE0 + m_active_texture_id));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_bind_texture_id));
}

