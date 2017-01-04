// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "mat4.h"
#include "vec3.h"

class light
{
public:
  virtual ~light() {}

  const mat4& get_matrix() const { return m_matrix; }

  const vec3& get_pos() const { return m_pos; }
  const vec3& get_dir() const { return m_dir; }

protected:
  mat4 m_matrix;
  vec3 m_pos;
  vec3 m_dir;
};

class directional_light : public light
{
public:
  directional_light(const vec3& pos_, const vec3& dir_) 
  {
    m_pos = pos_;
    m_dir = dir_;
  } 

  void calc_matrix(float frustum_size, float near_dist, float far_dist);
};

