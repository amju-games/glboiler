// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "load_png.h"
#include "lodepng.h"

void swap_row(unsigned char* row_1, unsigned char* row_2, unsigned char* temp, unsigned int row_length)
{
#ifdef WIN32
  memcpy_s(temp, row_length, row_1, row_length); // row_1 -> temp
  memcpy_s(row_1, row_length, row_2, row_length); // row_2 -> row_1
  memcpy_s(row_2, row_length, temp, row_length); // temp -> row_2
#endif

#ifdef MACOSX
  memcpy(temp, row_1, row_length); // row_1 -> temp
  memcpy(row_1, row_2, row_length); // row_2 -> row_1
  memcpy(row_2, temp, row_length); // temp -> row_2
#endif
}

void flip_image_data(
  unsigned char* data,
  unsigned int w,
  unsigned int h,
  unsigned int bytes_per_pixel)
{
  // Flip vertically in place, by swapping rows
  unsigned int row_length = w * bytes_per_pixel; // temp location for swap
  unsigned char* temp_row = new unsigned char[row_length];
  for (unsigned int y = 0; y < h / 2; y++)
  {
    swap_row(data + y * row_length, data + (h - y - 1) * row_length, temp_row, row_length);
  }
  delete [] temp_row;
}

bool load_png(
  const std::string& filename, 
  std::vector<unsigned char>* data,
  unsigned int* width, 
  unsigned int* height,
  unsigned int* bytesPerPixel)
{
  *bytesPerPixel = 4;
  unsigned nError = lodepng::decode(*data, *width, *height, filename);
  return (nError == 0);
}

