// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

class quat
{
public:
  quat() { x = y = z = 0.0f;   w = 1.0f; }

  quat(float X, float Y, float Z, float W)
  {
    x = X;		y = Y;		z = Z;		w = W;
  }

  // This takes in an array of 16 floats to fill in a 4x4 homogeneous matrix from a quaternion
  void CreateMatrix(float *pMatrix);

  // This takes a 3x3 or 4x4 matrix and converts it to a quaternion, depending on rowColumnCount
  void CreateFromMatrix(float *pMatrix, int rowColumnCount);

  // This returns a spherical linear interpolated quaternion between q1 and q2, according to t
  quat Slerp(quat &q1, quat &q2, float t);

private:
  float x, y, z, w;
};