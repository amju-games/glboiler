// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <cmath>
#include "boiler_assert.h"

struct vec2
{
  vec2() : x(0), y(0) {}
  vec2(float x_, float y_) : x(x_), y(y_) {}
  float x, y;
};

inline bool operator==(const vec2& v1, const vec2& v2)
{
  return    v1.x == v2.x 
         && v1.y == v2.y;
} 

inline float dot(const vec2& v1, const vec2& v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}

inline float squared_length(const vec2& v)
{
  return dot(v, v);
}

inline float length(const vec2& v)
{
  return sqrtf(squared_length(v));
}

inline vec2 operator*(const vec2& v, float f)
{
  return vec2(v.x * f, v.y * f);
}

inline vec2 operator*(float f, const vec2& v)
{
  return v * f;
}

inline vec2 operator+(const vec2& v1, const vec2& v2)
{
  return vec2(v1.x + v2.x, v1.y + v2.y);
}

inline vec2 operator-(const vec2& v1, const vec2& v2)
{
  return vec2(v1.x - v2.x, v1.y - v2.y);
}

inline vec2 operator-(const vec2& v)
{
  return vec2(-v.x, -v.y);
}

inline vec2 normalise(const vec2& v)
{
  float len = length(v);
  gl_boiler_assert(len > 0);
  float one_over = 1.0f / len;
  return v * one_over;
}


