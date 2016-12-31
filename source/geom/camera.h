// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "frustum.h"
#include "look_at.h"
#include "vec3.h"

class camera 
{
public:
  void set_look_at(const look_at&);

  void set_perspective_projection(
    float fovy, float aspect_ratio, float near_dist, float far_dist);

  frustum calc_frustum() const;

//private: TODO TEMP TEST
  mat4 m_proj;
  mat4 m_look_at;
};

struct stereo_camera_setup
{
  look_at look;
  float viewport_aspect_ratio = 1;
  float focal_length = 1; 
  float eye_separation_distance = 1; 
};

void set_stereo_cameras(
  camera& left, camera& right, const stereo_camera_setup& setup); 

