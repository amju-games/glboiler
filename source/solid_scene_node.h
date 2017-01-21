// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "scene_node.h"

class plane_scene_node : public scene_node
{
public:
  plane_scene_node();
  virtual void render() const override;
};

class sphere_scene_node : public scene_node
{
public:
  sphere_scene_node();
  virtual void render() const override;
};

class teapot_scene_node : public scene_node
{
public:
  teapot_scene_node();
  virtual void render() const override;
};

