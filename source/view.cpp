// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "gl_includes.h"
#include "view.h"

void view::set_gl_viewport() const
{
  GL_CHECK(glViewport(m_vp.x, m_vp.y, m_vp.w, m_vp.h));
}

frustum view::calc_frustum() const
{
  return m_cam.calc_frustum();
}



