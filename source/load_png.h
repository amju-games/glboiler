// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>

unsigned char* load_png(
  const std::string& filename, 
  unsigned int* pWidth, 
  unsigned int* pHeight,
  unsigned int* bytesPerPixel);

void flip_image_data(
  unsigned char* data, 
  unsigned int w, 
  unsigned int h, 
  unsigned int bytes_per_pixel);

