// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "log.h"
#include "render_to_texture.h"

// Thanks: http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/

render_to_texture::render_to_texture()
{
  m_tex[0] = -1;
  m_tex[1] = -1;
  m_old_fbo = -1;
  m_framebuffer = -1;
}
  
render_to_texture::~render_to_texture()
{
}

void render_to_texture::destroy_on_gl_thread()
{
  // TODO clean up framebuffer etc

  for (int i = 0; i < 2; i++)
  {
    if (m_tex[i] > 0)
    {
      GL_CHECK(glDeleteTextures(1, &m_tex[i]));
    }
  }
}

void render_to_texture::set_render_flags(int renderFlags)
{
  m_flags = renderFlags;
}

void render_to_texture::set_size(int w, int h)
{
  m_width = w;
  m_height = h;
}
 
void render_to_texture::use_texture_on_gl_thread()
{
  GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

  GL_CHECK(glEnable(GL_TEXTURE_2D));

  if (m_flags == RENDER_DEPTH)
  {
    // Only 1 texture, so use texture0, right?
    // TODO Set this
    GL_CHECK(glActiveTexture(GL_TEXTURE1));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_tex[1]));
  }
  else if (m_flags == RENDER_COLOUR)
  {
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_tex[0]));
  }
  else
  {
    // Depth and colour buffers
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_tex[0]));

    GL_CHECK(glActiveTexture(GL_TEXTURE1));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_tex[1]));

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
  }
}
  
bool render_to_texture::init_depth()
{
  // Render depth buffer to texture
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_tex[1]));

  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
    m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0));

  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

  // we won't bind a color texture with the currently binded FBO
  GL_CHECK(glDrawBuffer(GL_NONE));
  GL_CHECK(glReadBuffer(GL_NONE));
  
  // attach the texture to FBO depth attachment point
  GL_CHECK(glFramebufferTexture2D(
    GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, m_tex[1], 0));

  return true;
}

bool render_to_texture::init_depth_and_colour()
{
  for (int i = 0; i < 2; i++)
  {
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_tex[i]));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  }

  // parameters for color buffer texture
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_tex[0]));
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, 0));

  // parameters for depth texture
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_tex[1]));
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0,
                 GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, 0));
    
  // attach the texture to FBO color attachment point
  GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_TEXTURE_2D, m_tex[0], 0));
    
  // Attach the texture to FBO depth attachment point  
  GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_TEXTURE_2D, m_tex[1], 0));

  return true;
}

bool render_to_texture::init_colour()
{
  // Render colour buffer to texture (with depth buffering)
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_tex[0]));

  // Give an empty image to OpenGL ( the last "0" )
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
    m_width, m_height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, NULL));

  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GLuint depthRenderbuffer;
  GL_CHECK(glGenRenderbuffers(1, &depthRenderbuffer));
  GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer));
  GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_width, m_height));
  GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
    GL_RENDERBUFFER, depthRenderbuffer));

  GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tex[0], 0));

  return true;
}

bool render_to_texture::init_on_gl_thread()
{
  // This line gives GL errors!!
  GL_CHECK(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_old_fbo));
  
  GL_CHECK(glGenFramebuffers(1, &m_framebuffer));
  GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer));

  // create the texture
  GL_CHECK(glGenTextures(2, m_tex));

  if (m_flags == RENDER_DEPTH)
  { 
    init_depth();
  }
  else if (m_flags == RENDER_COLOUR)
  {
    init_colour();
  }
  else
  {
    init_depth_and_colour();
  }
  
  GL_CHECK(GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER));
  if (status != GL_FRAMEBUFFER_COMPLETE) 
  {
    log(msg() << status);
  }
  
  GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_old_fbo));

  return true;
}

bool render_to_texture::begin_on_gl_thread()
{
  GL_CHECK(glViewport(0, 0, m_width, m_height)); // same as size in Init
  
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

  GL_CHECK(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_old_fbo));
  GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer));

  GL_CHECK(glClear(  ///GL_COLOR_BUFFER_BIT | 
    GL_DEPTH_BUFFER_BIT));
  
  return true;
}

bool render_to_texture::end_on_gl_thread()
{
  GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_old_fbo));
  
  return true;
}

void render_to_texture::debug_draw_on_gl_thread()
{
  glUseProgram(0); // back to fixed function
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor4f(1,1,1,1);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_tex[1]);
  glTranslated(0,0,-1);
  glBegin(GL_QUADS);
  float x1 = 0.5f;
  float x2 = 1.0f;
  float y1 = 0.5f;
  float y2 = 1.0f;
  glTexCoord2d(0,0);glVertex2f(x1, y1);
  glTexCoord2d(1,0);glVertex2f(x2, y1);
  glTexCoord2d(1,1);glVertex2f(x2, y2);
  glTexCoord2d(0,1);glVertex2f(x1, y2);
  glEnd();
}


