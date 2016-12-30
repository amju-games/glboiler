// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <memory>
#include "bounding_vol.h"
#include "frustum.h"
#include "object.h"

class scene_node : public object
{
public:
  virtual const bounding_vol& get_bounding_vol() const
  {
    return *m_bounding_vol;
  }

  virtual void render() const = 0;

protected:
  std::unique_ptr<bounding_vol> m_bounding_vol;
};

using p_scene_node = std::shared_ptr<scene_node>;

