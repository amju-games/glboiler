// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "scene_node.h"

class gl_1_1_plane_scene_node : public scene_node
{
public:
  gl_1_1_plane_scene_node();
  virtual void render() const override;
};

class gl_1_1_sphere_scene_node : public scene_node
{
public:
  gl_1_1_sphere_scene_node();
  virtual void render() const override;
};

class gl_1_1_teapot_scene_node : public scene_node
{
public:
  gl_1_1_teapot_scene_node();
  virtual void render() const override;
};

