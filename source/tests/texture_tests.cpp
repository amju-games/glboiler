// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "gl_texture.h"

// Load testing: these tests expect that we are running in the assets/ dir.
// These values depend on the asset of course.
static const std::string TEX_FILENAME = "textures/white.png";
static const unsigned int EXPECTED_WIDTH = 8;
static const unsigned int EXPECTED_HEIGHT = 8;
// Because we set png image format to RGBA, we always get 4 bytes per pixel
static const unsigned int EXPECTED_BYTES_PER_PIXEL = 4;
static const colour EXPECTED_COLOUR(1, 1, 1, 1); // i.e. white

TEST(gl_texture, create)
{
  gl_texture tex;
  ASSERT_FALSE(tex.has_been_uploaded());
  ASSERT_EQ(tex.get_width(), 0);  
  ASSERT_EQ(tex.get_height(), 0);  
}

TEST(gl_texture, load)
{
  gl_texture tex;
  bool loaded = tex.load(TEX_FILENAME);
  ASSERT_TRUE(loaded);
  ASSERT_EQ(tex.get_width(), EXPECTED_WIDTH);
  ASSERT_EQ(tex.get_height(), EXPECTED_HEIGHT);
  ASSERT_EQ(tex.get_bytes_per_pixel(), EXPECTED_BYTES_PER_PIXEL);
}

TEST(gl_texture, get_texel_colour)
{
  gl_texture tex;
  bool loaded = tex.load(TEX_FILENAME);
  ASSERT_TRUE(loaded);
  // Get the colour of a texel. As the entire image is white, any texel 
  //  should be white.
  ASSERT_EQ(tex.get_texel_colour(vec2(0.5f, 0.5f)), EXPECTED_COLOUR);
}


