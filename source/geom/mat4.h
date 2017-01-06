// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <math.h>
#include <string.h> // memcpy
#include "vec3.h"

using mat4 = float[16];

inline void copy_matrix(const mat4& src, mat4& dest)
{
  memcpy(dest, src, 16 * sizeof(float));
}

inline void load_identity(mat4 m)
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
}

inline void translate(mat4 m, const vec3& tr)
{
  load_identity(m);
  m[12] = tr.x;  
  m[13] = tr.y;  
  m[14] = tr.z;  
}

inline void rotate_y_radians(mat4 m, float radians)
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
}

inline void mult(const mat4 m1, const mat4 m2, mat4 res)
{
  res[ 0] = m1[ 0] * m2[ 0] + m1[ 1] * m2[ 4] + m1[ 2] * m2[ 8] + m1[ 3] * m2[12];
  res[ 1] = m1[ 0] * m2[ 1] + m1[ 1] * m2[ 5] + m1[ 2] * m2[ 9] + m1[ 3] * m2[13];
  res[ 2] = m1[ 0] * m2[ 2] + m1[ 1] * m2[ 6] + m1[ 2] * m2[10] + m1[ 3] * m2[14];
  res[ 3] = m1[ 0] * m2[ 3] + m1[ 1] * m2[ 7] + m1[ 2] * m2[11] + m1[ 3] * m2[15];

  res[ 4] = m1[ 4] * m2[ 0] + m1[ 5] * m2[ 4] + m1[ 6] * m2[ 8] + m1[ 7] * m2[12];
  res[ 5] = m1[ 4] * m2[ 1] + m1[ 5] * m2[ 5] + m1[ 6] * m2[ 9] + m1[ 7] * m2[13];
  res[ 6] = m1[ 4] * m2[ 2] + m1[ 5] * m2[ 6] + m1[ 6] * m2[10] + m1[ 7] * m2[14];
  res[ 7] = m1[ 4] * m2[ 3] + m1[ 5] * m2[ 7] + m1[ 6] * m2[11] + m1[ 7] * m2[15];

  res[ 8] = m1[ 8] * m2[ 0] + m1[ 9] * m2[ 4] + m1[10] * m2[ 8] + m1[11] * m2[12];
  res[ 9] = m1[ 8] * m2[ 1] + m1[ 9] * m2[ 5] + m1[10] * m2[ 9] + m1[11] * m2[13];
  res[10] = m1[ 8] * m2[ 2] + m1[ 9] * m2[ 6] + m1[10] * m2[10] + m1[11] * m2[14];
  res[11] = m1[ 8] * m2[ 3] + m1[ 9] * m2[ 7] + m1[10] * m2[11] + m1[11] * m2[15];

  res[12] = m1[12] * m2[ 0] + m1[13] * m2[ 4] + m1[14] * m2[ 8] + m1[15] * m2[12];
  res[13] = m1[12] * m2[ 1] + m1[13] * m2[ 5] + m1[14] * m2[ 9] + m1[15] * m2[13];
  res[14] = m1[12] * m2[ 2] + m1[13] * m2[ 6] + m1[14] * m2[10] + m1[15] * m2[14];
  res[15] = m1[12] * m2[ 3] + m1[13] * m2[ 7] + m1[14] * m2[11] + m1[15] * m2[15];
}

