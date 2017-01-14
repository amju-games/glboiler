// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>

class texture
{
public:
  ~texture();

  bool load(const std::string& filename);
  void set_active_texture_id(int i) { m_active_texture_id = i; }

  void upload_on_gl_thread();
  void use_on_gl_thread();
  void destroy_on_gl_thread();

private:
  void free_data();

private:
  std::string m_filename;
  unsigned char* m_data = nullptr;
  unsigned int m_bind_texture_id = 0;
  int m_active_texture_id = 0;
  unsigned int m_w = 0;
  unsigned int m_h = 0;
  unsigned int m_bytes_per_pixel = 0;
  bool m_has_been_uploaded = false;
  bool m_delete_data_after_upload = true;
  bool m_destroy_called = false;
  bool m_use_mipmaps = false;

  // TODO wrap/clamp, nearest/linear/aniso/etc  
};

