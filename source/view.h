// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "camera.h"
#include "viewport.h"

class view
{
public:
  view() = default;
  view(const viewport& vp_, const camera& cam_) : m_vp(vp_), m_cam(cam_) {}

  frustum calc_frustum() const;

  void set_gl_viewport() const;

private:
  viewport m_vp;
  camera m_cam;
};

