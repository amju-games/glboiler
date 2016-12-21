// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "png.h"
#include "load_png.h"

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

