// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <memory>
#include "bounding_vol.h"
#include "frustum.h"
#include "mat4.h"
#include "material.h"
#include "object.h"
#include "render_pass_type.h"

class scene_node : public object
{
public:
  scene_node() : m_id(-1)
  {
    m_has_changed = false;
  }

  void set_id(int id_) { m_id = id_; }
  int get_id() const { return m_id; }

  bool has_changed() const { return m_has_changed; }

  virtual const bounding_vol& get_bounding_vol() const
  {
    return *m_bounding_vol;
  }

  virtual void render_on_gl_thread() const {}

  const mat4& get_xform() const { return m_xform; }
  mat4& get_xform() { m_has_changed = true; return m_xform; }

  virtual void update() {}

  void set_material(std::shared_ptr<material> material);
  void use_material_on_gl_thread() const;

  // Set render passes for which we should render this node
  void add_render_pass(render_pass_type rpt);
  bool yes_render_in_pass(render_pass_type rpt) const;

protected:
  // Bit field: each bit position corresponds to a render pass
  unsigned int m_render_passes = 0;
  int m_id;
  mat4 m_xform;
  std::shared_ptr<material> m_material;
  std::unique_ptr<bounding_vol> m_bounding_vol;
  bool m_has_changed;
};

using p_scene_node = std::shared_ptr<scene_node>;

