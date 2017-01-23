// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>

bool load_png(
  const std::string& filename, 
  std::vector<unsigned char>* data,
  unsigned int* pWidth, 
  unsigned int* pHeight,
  unsigned int* bytesPerPixel);

void flip_image_data(
  unsigned char* data, 
  unsigned int w, 
  unsigned int h, 
  unsigned int bytes_per_pixel);

