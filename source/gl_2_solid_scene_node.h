// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "scene_node.h"

class gl_2_plane_scene_node : public scene_node
{
public:
  gl_2_plane_scene_node();
  virtual void render_on_gl_thread() const override;
};

class gl_2_sphere_scene_node : public scene_node
{
public:
  gl_2_sphere_scene_node();
  virtual void render_on_gl_thread() const override;
};

class gl_2_teapot_scene_node : public scene_node
{
public:
  gl_2_teapot_scene_node();
  virtual void render_on_gl_thread() const override;
};

