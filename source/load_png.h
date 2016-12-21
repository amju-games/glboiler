// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>

unsigned char* load_png(
  const std::string& filename, 
  unsigned int* pWidth, 
  unsigned int* pHeight,
  unsigned int* bytesPerPixel);

