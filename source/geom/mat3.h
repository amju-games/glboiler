// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <cmath>
#include <string.h> // memcpy
#include "mat4.h"
#include "vec3.h"

class mat3
{
public:
  mat3() { load_identity(); }

  mat3(const float f[9])
  {
    memcpy(m, f, 9 * sizeof(float));
  }

  // Construct from mat4 - just take the 3*3 rotation part of the 4*4 matrix
  mat3(const mat4& m4)
  {
    m[0] = m4[0];
    m[1] = m4[1];
    m[2] = m4[2];
    m[3] = m4[4];
    m[4] = m4[5];
    m[5] = m4[6];
    m[6] = m4[8];
    m[7] = m4[9];
    m[8] = m4[10];
  }

  mat3(
    float f0,
    float f1,
    float f2,
    float f3,
    float f4,
    float f5,
    float f6,
    float f7,
    float f8)
  {
    m[0] = f0;
    m[1] = f1;
    m[2] = f2;
    m[3] = f3;
    m[4] = f4;
    m[5] = f5;
    m[6] = f6;
    m[7] = f7;
    m[8] = f8;
  }

  const float* data() const { return m; }
  float operator[] (int i) const { return m[i]; }
  float& operator[] (int i) { return m[i]; }

  const mat3& load_identity();
  const mat3& inverse_transpose();

private:
  float m[9];
};

inline const mat3& mat3::load_identity()
{
  m[0] = 1;
  m[1] = 0;
  m[2] = 0;

  m[3] = 0;
  m[4] = 1;
  m[5] = 0;

  m[6] = 0;
  m[7] = 0;
  m[8] = 1;

  return *this;
}

inline const mat3& mat3::inverse_transpose()
{
  // http://stackoverflow.com/questions/983999/simple-3x3-matrix-inverse-code-c

  float determinant =
    + m[0] * (m[4] * m[8] - m[7] * m[5])
    - m[1] * (m[3] * m[8] - m[5] * m[6])
    + m[2] * (m[3] * m[7] - m[4] * m[6]);

  if (determinant != 0)
  {
    float invdet = 1.f / determinant;

    mat3 result;
    result.m[0] =  (m[4] * m[8] - m[7] * m[5]) * invdet;
    result.m[3] = -(m[1] * m[8] - m[2] * m[7]) * invdet;
    result.m[6] =  (m[1] * m[5] - m[2] * m[4]) * invdet;
    result.m[1] = -(m[3] * m[8] - m[5] * m[6]) * invdet;
    result.m[4] =  (m[0] * m[8] - m[2] * m[6]) * invdet;
    result.m[7] = -(m[0] * m[5] - m[3] * m[2]) * invdet;
    result.m[2] =  (m[3] * m[7] - m[6] * m[4]) * invdet;
    result.m[5] = -(m[0] * m[7] - m[6] * m[1]) * invdet;
    result.m[8] =  (m[0] * m[4] - m[3] * m[1]) * invdet;

    *this = result;
  }
  return *this;
}


