// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <vector>
#include "vec2.h"
#include "vec3.h"

// * vertex *
// Vertex buffer element type
struct vertex
{
  vertex() = default;
  vertex(const vec3& pos_, const vec3& normal_, const vec2& uv_, const vec3& tangent_) :
    pos(pos_), normal(normal_), uv(uv_), tangent(tangent_) {}

  vec3 pos;
  vec2 uv;
  vec3 normal;
  vec3 tangent;
};

struct tri
{
  vertex m_verts[3];

  void calc_tangents();
};

typedef std::vector<tri> tris;


