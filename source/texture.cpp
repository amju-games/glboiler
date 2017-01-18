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
    assert(m_destroy_called);
  }
  free_data();
}

colour texture::get_texel_colour(const vec2& uv) const
{
  assert(m_data);
  assert(m_w > 0);
  assert(m_h > 0);
  assert(m_bytes_per_pixel > 0);

  int x = static_cast<int>(uv.x * static_cast<float>(m_w - 1));
  int y = static_cast<int>(uv.y * static_cast<float>(m_h - 1));
  assert(x >= 0);
  assert(x < m_w);
  assert(y >= 0);
  assert(y < m_h);
 
  // TODO stride ?
  unsigned char* addr = m_data + y * m_w * m_bytes_per_pixel + x; 
  assert(addr < (m_data + m_w * m_h * m_bytes_per_pixel));

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
    assert(false); // unexpected bytes per pixel
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

void texture::upload_on_gl_thread(bool delete_data_after_upload)
{
  glGenTextures(1, &m_bind_texture_id);
  glBindTexture(GL_TEXTURE_2D, m_bind_texture_id);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // ??
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

  gluBuild2DMipmaps(
           GL_TEXTURE_2D,  
           format,
           m_w,
           m_h,
           format,
           GL_UNSIGNED_BYTE,
           m_data);

  if (delete_data_after_upload)
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
  assert(m_has_been_uploaded);

  GL_CHECK(glEnable(GL_TEXTURE_2D));
  GL_CHECK(glActiveTexture(GL_TEXTURE0 + m_active_texture_id));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_bind_texture_id));
}
