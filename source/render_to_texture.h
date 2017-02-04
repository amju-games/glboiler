// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "gl_includes.h"

class render_to_texture 
{
public:
  render_to_texture();
  ~render_to_texture();

  // Set what to render, depth and/or colour. 
  static const int RENDER_COLOUR = 0x01;
  static const int RENDER_DEPTH = 0x02;
  void set_render_flags(int renderFlags);

  void set_size(int w, int h);

  // Create texture render target
  bool init_on_gl_thread();

  void destroy_on_gl_thread();

  // Draw scene between Begin() and End() calls. Then you can use the texture.
  // Switch to texture render target
  bool begin_on_gl_thread();

  // Switch back to regular render target
  bool end_on_gl_thread();
  
  void use_texture_on_gl_thread();

  void debug_draw_on_gl_thread();

protected:
  bool init_depth();
  bool init_colour();
  bool init_depth_and_colour();

protected:
  GLuint m_framebuffer;
  GLuint m_tex[2]; // 0 is colour, 1 is depth
  GLint m_old_fbo;
  int m_width, m_height; // pixels - size of texture to which we render

  // Viewport before switching to this render target, so we revert in End()
  int m_old_viewport[4];

  int m_flags;
};


