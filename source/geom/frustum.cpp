// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <cmath>
#include "frustum.h"

frustum::frustum()
{
}

plane frustum::get_plane(frustum_plane fpl)
{
  return m_planes[fpl];
}

void frustum::set_from_matrix(mat4 m)
{
  // Wait. This is treating matrix as row major, shurrely
  /*
Row major

0	1	2	3
4	5	6	7
8	9	10	11
12	13	14	15

Column major

0	4	8	12
1	5	9	13
2	6	10	14
3	7	11	15

  */

  m_planes[FRUSTUM_PLANE_RIGHT]  = plane(m[3] - m[0], m[7] - m[4], m[11] - m[8],  m[15] - m[12]).normalise();
  m_planes[FRUSTUM_PLANE_LEFT]   = plane(m[3] + m[0], m[7] + m[4], m[11] + m[8],  m[15] + m[12]).normalise();
  m_planes[FRUSTUM_PLANE_TOP]    = plane(m[3] - m[1], m[7] - m[5], m[11] - m[9],  m[15] - m[13]).normalise();
  m_planes[FRUSTUM_PLANE_BOTTOM] = plane(m[3] + m[1], m[7] + m[5], m[11] + m[9],  m[15] + m[13]).normalise();
  m_planes[FRUSTUM_PLANE_FAR]    = plane(m[3] - m[2], m[7] - m[6], m[11] - m[10], m[15] - m[14]).normalise();
  m_planes[FRUSTUM_PLANE_NEAR]   = plane(m[3] + m[2], m[7] + m[6], m[11] + m[10], m[15] + m[14]).normalise();

  /*
  // Extract the RIGHT mping plane
  m_planes[0][0] = m[ 3] - m[ 0];
  m_planes[0][1] = m[ 7] - m[ 4];
  m_planes[0][2] = m[11] - m[ 8];
  m_planes[0][3] = m[15] - m[12];

  // Normalize it
  float t = (float) sqrtf( m_planes[0][0] * m_planes[0][0] + m_planes[0][1] * m_planes[0][1] + m_planes[0][2] * m_planes[0][2] );
  m_planes[0][0] /= t;
  m_planes[0][1] /= t;
  m_planes[0][2] /= t;
  m_planes[0][3] /= t;

  // Extract the LEFT mping plane
  m_planes[1][0] = m[ 3] + m[ 0];
  m_planes[1][1] = m[ 7] + m[ 4];
  m_planes[1][2] = m[11] + m[ 8];
  m_planes[1][3] = m[15] + m[12];

  // Normalize it
  t = (float) sqrtf( m_planes[1][0] * m_planes[1][0] + m_planes[1][1] * m_planes[1][1] + m_planes[1][2] * m_planes[1][2] );
  m_planes[1][0] /= t;
  m_planes[1][1] /= t;
  m_planes[1][2] /= t;
  m_planes[1][3] /= t;

  // Extract the BOTTOM mping plane
  m_planes[2][0] = m[ 3] + m[ 1];
  m_planes[2][1] = m[ 7] + m[ 5];
  m_planes[2][2] = m[11] + m[ 9];
  m_planes[2][3] = m[15] + m[13];

  // Normalize it
  t = (float) sqrtf( m_planes[2][0] * m_planes[2][0] + m_planes[2][1] * m_planes[2][1] + m_planes[2][2] * m_planes[2][2] );
  m_planes[2][0] /= t;
  m_planes[2][1] /= t;
  m_planes[2][2] /= t;
  m_planes[2][3] /= t;

  // Extract the TOP mping plane
  m_planes[3][0] = m[ 3] - m[ 1];
  m_planes[3][1] = m[ 7] - m[ 5];
  m_planes[3][2] = m[11] - m[ 9];
  m_planes[3][3] = m[15] - m[13];

  // Normalize it
  t = (float) sqrtf( m_planes[3][0] * m_planes[3][0] + m_planes[3][1] * m_planes[3][1] + m_planes[3][2] * m_planes[3][2] );
  m_planes[3][0] /= t;
  m_planes[3][1] /= t;
  m_planes[3][2] /= t;
  m_planes[3][3] /= t;

  // Extract the FAR mping plane
  m_planes[4][0] = m[ 3] - m[ 2];
  m_planes[4][1] = m[ 7] - m[ 6];
  m_planes[4][2] = m[11] - m[10];
  m_planes[4][3] = m[15] - m[14];

  // Normalize it
  t = (float) sqrtf( m_planes[4][0] * m_planes[4][0] + m_planes[4][1] * m_planes[4][1] + m_planes[4][2] * m_planes[4][2] );
  m_planes[4][0] /= t;
  m_planes[4][1] /= t;
  m_planes[4][2] /= t;
  m_planes[4][3] /= t;

  // Extract the NEAR mping plane.  This is last on purpose (see pointinm_planes() for reason)
  m_planes[5][0] = m[ 3] + m[ 2];
  m_planes[5][1] = m[ 7] + m[ 6];
  m_planes[5][2] = m[11] + m[10];
  m_planes[5][3] = m[15] + m[14];

  // Normalize it
  t = (float) sqrtf( m_planes[5][0] * m_planes[5][0] + m_planes[5][1] * m_planes[5][1] + m_planes[5][2] * m_planes[5][2] );
  m_planes[5][0] /= t;
  m_planes[5][1] /= t;
  m_planes[5][2] /= t;
  m_planes[5][3] /= t;
  */
}

