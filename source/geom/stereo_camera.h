// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "camera.h"
#include "look_at.h"

#pragma once

struct stereo_camera_setup
{
  look_at look;
  float viewport_aspect_ratio = 1;
  float focal_length = 1;
  float eye_separation_distance = 1;
};

void set_stereo_cameras(
  camera& left, camera& right, const stereo_camera_setup& setup);



