// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "camera.h"

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

