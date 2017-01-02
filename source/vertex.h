// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "vec2.h"
#include "vec3.h"

struct vert
{
  vert() = default;
  vert(const vec3& pos_, const vec3& normal_, const vec2& uv_, const vec3& tangent_) :
    pos(pos_), normal(normal_), uv(uv_), tangent(tangent_) {}

  vec3 pos;
  vec3 normal;
  vec2 uv;
  vec3 tangent;
};


