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


