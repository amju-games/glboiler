// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "load_png.h"

TEST(load_png, flip_4_rows)
{
  unsigned char data[] = 
  {
    0,  1,  2,  3,
    4,  5,  6,  7,
    8,  9,  10, 11,
    12, 13, 14, 15
  };

  const unsigned int W = 4;
  const unsigned int H = 4;
  const unsigned int BYTES_PER_PIXEL = 1;
  flip_image_data(data, W, H, BYTES_PER_PIXEL);

  ASSERT_EQ(data[0], 12);
  ASSERT_EQ(data[1], 13);
  ASSERT_EQ(data[2], 14);
  ASSERT_EQ(data[3], 15);

  ASSERT_EQ(data[4], 8);
  ASSERT_EQ(data[5], 9);
  ASSERT_EQ(data[6], 10);
  ASSERT_EQ(data[7], 11);

  ASSERT_EQ(data[8],  4);
  ASSERT_EQ(data[9],  5);
  ASSERT_EQ(data[10], 6);
  ASSERT_EQ(data[11], 7);

  ASSERT_EQ(data[12], 0);
  ASSERT_EQ(data[13], 1);
  ASSERT_EQ(data[14], 2);
  ASSERT_EQ(data[15], 3);
}


