// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <cmath>
#include "boiler_assert.h"

struct vec3
{
  vec3() : x(0), y(0), z(0) {}
  vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
  float x, y, z;
};

inline bool operator==(const vec3& v1, const vec3& v2)
{
  return    v1.x == v2.x 
         && v1.y == v2.y
         && v1.z == v2.z;
} 

inline float dot(const vec3& v1, const vec3& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float squared_length(const vec3& v)
{
  return dot(v, v);
}

inline float length(const vec3& v)
{
  return sqrtf(squared_length(v));
}

inline vec3 cross(const vec3& v1, const vec3& v2)
{
  return vec3(
    v1.y * v2.z - v2.y * v1.z,
    v2.x * v1.z - v1.x * v2.z,
    v1.x * v2.y - v2.x * v1.y);
}

inline vec3 operator*(const vec3& v, float f)
{
  return vec3(v.x * f, v.y * f, v.z * f);
}

inline vec3 operator*(float f, const vec3& v)
{
  return v * f;
}

inline vec3 operator+(const vec3& v1, const vec3& v2)
{
  return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline vec3 operator-(const vec3& v1, const vec3& v2)
{
  return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline vec3 operator-(const vec3& v)
{
  return vec3(-v.x, -v.y, -v.z);
}

inline vec3 normalise(const vec3& v)
{
  float len = length(v);
  gl_boiler_assert(len > 0);
  float one_over = 1.0f / len;
  return v * one_over;
}


