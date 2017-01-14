// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "mat4.h"

struct perspective
{
  perspective(float fovy_, float aspect_ratio_, float near_distance_, float far_distance_) : 
    fov_y_degs(fovy_), aspect_ratio(aspect_ratio_), near_distance(near_distance_), far_distance(far_distance_) {}

  void set_matrix(mat4&) const;

  float fov_y_degs = 45.0f;
  float aspect_ratio = 1.5f;
  float near_distance = 1.0f;
  float far_distance = 100.0f;
};

struct ortho
{
  ortho(float left_, float right_, float bottom_, float top_, float near_distance_, float far_distance_) :
    left(left_), right(right_), bottom(bottom_), top(top_), near_distance(near_distance_), far_distance(far_distance_) {}

  void set_matrix(mat4&) const;

  float left, right, bottom, top, near_distance, far_distance;
};

