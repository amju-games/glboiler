// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <cmath>
#include <string.h> // memcpy
#include "vec3.h"

class mat4
{
public:
  mat4() { load_identity(); }

  mat4(const float f[16])
  {
    memcpy(m, f, 16 * sizeof(float));
  }

  mat4(
    float f0,
    float f1,
    float f2,
    float f3,
    float f4,
    float f5,
    float f6,
    float f7,
    float f8,
    float f9,
    float f10,
    float f11,
    float f12,
    float f13,
    float f14,
    float f15)
  {
    m[0]  = f0;
    m[1]  = f1;
    m[2]  = f2;
    m[3]  = f3;
    m[4]  = f4;
    m[5]  = f5;
    m[6]  = f6;
    m[7]  = f7;
    m[8]  = f8;
    m[9]  = f9;
    m[10] = f10;
    m[11] = f11;
    m[12] = f12;
    m[13] = f13;
    m[14] = f14;
    m[15] = f15;
  }

  const float* data() const { return m; }
  float operator[] (int i) const { return m[i]; }
  float& operator[] (int i) { return m[i]; }

  const mat4& load_identity();
  const mat4& translate(const vec3& tr);

  const mat4& rotate_x_radians(float radians);
  const mat4& rotate_y_radians(float radians);
  const mat4& rotate_z_radians(float radians);

  const mat4& scale(float x, float y, float z);

private:
  float m[16];
  friend mat4 mult(const mat4& m1, const mat4& m2);
};

inline const mat4& mat4::load_identity()
{
  m[0]  = 1; 
  m[1]  = 0; 
  m[2]  = 0; 
  m[3]  = 0; 

  m[4]  = 0; 
  m[5]  = 1; 
  m[6]  = 0; 
  m[7]  = 0; 

  m[8]  = 0; 
  m[9]  = 0; 
  m[10] = 1; 
  m[11] = 0; 

  m[12] = 0; 
  m[13] = 0; 
  m[14] = 0; 
  m[15] = 1; 

  return *this;
}

inline const mat4& mat4::translate(const vec3& tr)
{
  load_identity();
  m[12] = tr.x;  
  m[13] = tr.y;  
  m[14] = tr.z;  

  return *this;
}

inline const mat4& mat4::rotate_x_radians(float radians)
{
  float c = cos(radians);
  float s = sin(radians);

  m[0] = 1;
  m[1] = 0;
  m[2] = 0;

  m[4] = 0;
  m[5] = c;
  m[6] = s;

  m[8] = 0;
  m[9] = -s;
  m[10] = c;

  return *this;
}

inline const mat4& mat4::rotate_y_radians(float radians)
{
  float c = cos(radians);
  float s = sin(radians);
 
  m[0]  = c; 
  m[1]  = 0; 
  m[2]  = -s; 

  m[4]  = 0; 
  m[5]  = 1; 
  m[6]  = 0; 

  m[8]  = s; 
  m[9]  = 0; 
  m[10] = c; 

  return *this;
}

inline const mat4& mat4::rotate_z_radians(float radians)
{
  float c = cos(radians);
  float s = sin(radians);

  m[0] = c;
  m[1] = s;
  m[2] = 0;

  m[4] = -s;
  m[5] = c;
  m[6] = 0;

  m[8] = 0;
  m[9] = 0;
  m[10] = 1;

  return *this;
}

inline const mat4& mat4::scale(float x, float y, float z)
{
  m[0] = x;
  m[1] = 0;
  m[2] = 0;
  m[3] = 0;

  m[4] = 0;
  m[5] = y;
  m[6] = 0;
  m[7] = 0;

  m[8] = 0;
  m[9] = 0;
  m[10] = z;
  m[11] = 0;

  m[12] = 0;
  m[13] = 0;
  m[14] = 0;
  m[15] = 1;

  return *this;
}

inline mat4 mult(const mat4& m1, const mat4& m2)
{
  mat4 res;
  res.m[ 0] = m1[ 0] * m2[ 0] + m1[ 1] * m2[ 4] + m1[ 2] * m2[ 8] + m1[ 3] * m2[12];
  res.m[ 1] = m1[ 0] * m2[ 1] + m1[ 1] * m2[ 5] + m1[ 2] * m2[ 9] + m1[ 3] * m2[13];
  res.m[ 2] = m1[ 0] * m2[ 2] + m1[ 1] * m2[ 6] + m1[ 2] * m2[10] + m1[ 3] * m2[14];
  res.m[ 3] = m1[ 0] * m2[ 3] + m1[ 1] * m2[ 7] + m1[ 2] * m2[11] + m1[ 3] * m2[15];

  res.m[ 4] = m1[ 4] * m2[ 0] + m1[ 5] * m2[ 4] + m1[ 6] * m2[ 8] + m1[ 7] * m2[12];
  res.m[ 5] = m1[ 4] * m2[ 1] + m1[ 5] * m2[ 5] + m1[ 6] * m2[ 9] + m1[ 7] * m2[13];
  res.m[ 6] = m1[ 4] * m2[ 2] + m1[ 5] * m2[ 6] + m1[ 6] * m2[10] + m1[ 7] * m2[14];
  res.m[ 7] = m1[ 4] * m2[ 3] + m1[ 5] * m2[ 7] + m1[ 6] * m2[11] + m1[ 7] * m2[15];

  res.m[ 8] = m1[ 8] * m2[ 0] + m1[ 9] * m2[ 4] + m1[10] * m2[ 8] + m1[11] * m2[12];
  res.m[ 9] = m1[ 8] * m2[ 1] + m1[ 9] * m2[ 5] + m1[10] * m2[ 9] + m1[11] * m2[13];
  res.m[10] = m1[ 8] * m2[ 2] + m1[ 9] * m2[ 6] + m1[10] * m2[10] + m1[11] * m2[14];
  res.m[11] = m1[ 8] * m2[ 3] + m1[ 9] * m2[ 7] + m1[10] * m2[11] + m1[11] * m2[15];

  res.m[12] = m1[12] * m2[ 0] + m1[13] * m2[ 4] + m1[14] * m2[ 8] + m1[15] * m2[12];
  res.m[13] = m1[12] * m2[ 1] + m1[13] * m2[ 5] + m1[14] * m2[ 9] + m1[15] * m2[13];
  res.m[14] = m1[12] * m2[ 2] + m1[13] * m2[ 6] + m1[14] * m2[10] + m1[15] * m2[14];
  res.m[15] = m1[12] * m2[ 3] + m1[13] * m2[ 7] + m1[14] * m2[11] + m1[15] * m2[15];
  return res;
}

