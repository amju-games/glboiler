// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "file_string_utils.h"

TEST(file_string_utils, just_path)
{
  ASSERT_EQ(just_path(""), "");
  ASSERT_EQ(just_path("/a"), "/");
  ASSERT_EQ(just_path("a/b"), "a/");
  ASSERT_EQ(just_path("a/b/"), "a/b/");
  ASSERT_EQ(just_path("a/b/c.ext"), "a/b/");
}

TEST(file_string_utils, just_filename)
{
  ASSERT_EQ(just_filename(""), "");
  ASSERT_EQ(just_filename("a"), "a");
  ASSERT_EQ(just_filename("a/b"), "b");
  ASSERT_EQ(just_filename("a/b/"), "");
}

TEST(file_string_utils, just_extension)
{
  ASSERT_EQ(just_extension(""), "");
  ASSERT_EQ(just_extension("a"), "");
  ASSERT_EQ(just_extension("a/b"), "");
  ASSERT_EQ(just_extension("a/b/c.ext"), "ext");
  ASSERT_EQ(just_extension("a/b/c.fgh.ijk"), "ijk");
}

TEST(file_string_utils, without_extension)
{
  ASSERT_EQ(without_extension(""), "");
  ASSERT_EQ(without_extension("a"), "a");
  ASSERT_EQ(without_extension("a/b"), "b");
  ASSERT_EQ(without_extension("a/b/c.ext"), "a/b/c");
  ASSERT_EQ(without_extension("a/b/c.fgh.ijk"), "a/b/c.fgh");
}

