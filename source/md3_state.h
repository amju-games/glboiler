// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <memory>
#include "renderer.h"
#include "scene_graph.h"

class md3_state
{
public:
  virtual void on_enter() override;
  virtual void on_exit() override;
  virtual void render() const override; 
  virtual void update(float dt)  override;

private:
  std::unique_ptr<scene_graph> m_sg;
  std::unique_ptr<renderer> m_rend;
};

