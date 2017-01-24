// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>
#include "colour.h"
#include "resource.h"
#include "vec2.h"

class texture : public gl_resource
{
public:
  ~texture();

  bool load(const std::string& filename);
  void set_active_texture_id(int i) { m_active_texture_id = i; }
  bool has_been_uploaded() const { return m_has_been_uploaded; }

  unsigned int get_width() const { return m_w; }
  unsigned int get_height() const { return m_h; }
  unsigned int get_bytes_per_pixel() const { return m_bytes_per_pixel; }

  // Look up texel colour in data: for this to work, the data must 
  //  not be deleted yet, of course! 
  colour get_texel_colour(const vec2& uv) const;

  virtual void upload_on_gl_thread() override;
  virtual void use_on_gl_thread() override;
  virtual void destroy_on_gl_thread() override;

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
  bool m_destroy_called = false;
  bool m_use_mipmaps = true;
  bool m_delete_data_after_upload = true;

  // TODO wrap/clamp, nearest/linear/aniso/etc  
};

