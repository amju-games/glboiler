// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "camera.h"

void look_at::set_matrix(mat4 m) const
{
  // up and dir are normalised in ctor
  vec3 right = normalise(cross(dir, up)); // so this normalise unnecessary?
  vec3 up = normalise(cross(right, dir)); // new orthogonal up vec
 
  load_identity(m);
  m[0] = right.x;  
  m[1] = right.y;  
  m[2] = right.z;  

  m[4] = up.x;
  m[5] = up.y;
  m[6] = up.z;

  m[8]  = -dir.x;
  m[9]  = -dir.y;
  m[10] = -dir.z;

  m[12] = -eye.x;
  m[13] = -eye.y;
  m[14] = -eye.z;
}

frustum camera::calc_frustum() const
{
  return frustum();
}

void camera::set_look_at(const look_at& look)
{
  look.set_matrix(m_look_at);    
}

void camera::set_perspective_projection(
    float fovy, float aspect_ratio, float near_dist, float far_dist)
{
}

/*          
struct stereo_camera_setup
{       
  look_at look;
  float viewport_aspect_ratio = 1;
  float focal_length = 1; 
  float eye_separation_distance = 1;
};
*/

void set_stereo_cameras(
  camera& left, camera& right, const stereo_camera_setup& setup)
{
  
}

