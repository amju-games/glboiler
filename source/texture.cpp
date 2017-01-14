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
  assert(m_destroy_called);
}

bool texture::load(const std::string& filename)
{
  m_filename = filename;
  m_data = load_png(filename, &m_w, &m_h, &m_bytes_per_pixel);
  if (m_data)
  {
    log(msg() << "Loaded texture " << filename << " w: " << m_w << " h: " << m_h << " bpp: " << m_bytes_per_pixel);
  }
  else
  {
    log(msg() << "Failed to load texture " << filename);
  }
  return m_data != nullptr;
}

void texture::upload_on_gl_thread()
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

  if (m_delete_data_after_upload)
  {
    free_data();
  }

  m_has_been_uploaded = true;
}

void texture::destroy_on_gl_thread()
{
  free_data();

  if (m_bind_texture_id > 0)
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
  }
}

void texture::use_on_gl_thread()
{
  assert(m_has_been_uploaded);

  GL_CHECK(glEnable(GL_TEXTURE_2D));
  GL_CHECK(glActiveTexture(GL_TEXTURE0 + m_active_texture_id));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_bind_texture_id));
}

