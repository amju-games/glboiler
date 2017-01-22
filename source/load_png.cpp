// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memcpy
#include "png.h"
#include "load_png.h"

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
  for (int y = 0; y < h / 2; y++)
  {
    swap_row(data + y * row_length, data + (h - y - 1) * row_length, temp_row, row_length);
  }
  delete [] temp_row;
}

unsigned char* load_png(
  const std::string& filename, 
  unsigned int* width, 
  unsigned int* height,
  unsigned int* bytesPerPixel)
{
      png_image image; /* The control structure used by libpng */

      /* Initialize the 'png_image' structure. */
      memset(&image, 0, (sizeof image));
      image.version = PNG_IMAGE_VERSION;

      /* The first argument is the file to read: */
      if (png_image_begin_read_from_file(&image, filename.c_str()) != 0)
      {
         png_bytep buffer;

         /* Set the format in which to read the PNG file; this code chooses a
          * simple sRGB format with a non-associated alpha channel, adequate to
          * store most images.
          */
         image.format = PNG_FORMAT_RGBA;

         /* Now allocate enough memory to hold the image in this format; the
          * PNG_IMAGE_SIZE macro uses the information about the image (width,
          * height and format) stored in 'image'.
          */
         buffer = static_cast<png_bytep>(malloc(PNG_IMAGE_SIZE(image)));

         if (buffer != NULL &&
            png_image_finish_read(&image, NULL/*background*/, buffer,
                0/*row_stride*/, NULL/*colormap*/) != 0)
         {
            // Success, set ret values and return 
            *width = image.width;
            *height = image.height;
            *bytesPerPixel = 3;
            if (image.format & PNG_FORMAT_FLAG_ALPHA)
            {
                *bytesPerPixel = 4;
            }
            return buffer;
         }

         else
         {
            /* Calling png_free_image is optional unless the simplified API was
             * not run to completion.  In this case if there wasn't enough
             * memory for 'buffer' we didn't complete the read, so we must free
             * the image:
             */
            if (buffer)
               free(buffer);
         }
      }

      /* Something went wrong reading or writing the image.  libpng stores a
       * textual message in the 'png_image' structure:
       */
      fprintf(stderr, "pngtopng: error: %s\n", image.message);
    
      return nullptr; 

}

