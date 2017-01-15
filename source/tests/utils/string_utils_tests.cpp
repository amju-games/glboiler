// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "string_utils.h"

TEST(string_utils, split_empty_string)
{
  strings strs = split("", '.');
  // Empty string means split result is empty vector.
  ASSERT_TRUE(strs.empty());
}

TEST(string_utils, split_1_string)
{
  strings strs = split("abc", '.');
  ASSERT_EQ(strs.size(), 1);
  ASSERT_EQ(strs[0], "abc");
}

TEST(string_utils, split_2_strings)
{
  strings strs = split("abc.defg", '.');
  ASSERT_EQ(strs.size(), 2);
  ASSERT_EQ(strs[0], "abc");
  ASSERT_EQ(strs[1], "defg");
}

TEST(string_utils, split_with_empty_strings)
{
  strings strs = split(".abc..defg..", '.');
  ASSERT_EQ(strs.size(), 2);
  ASSERT_EQ(strs[0], "abc");
  ASSERT_EQ(strs[1], "defg");
}

TEST(string_utils, trim_1)
{
  ASSERT_EQ(trim(" a"), "a");
  ASSERT_EQ(trim("    \t  \n   \ra"), "a");
}

TEST(string_utils, trim_2)
{
  ASSERT_EQ(trim("a "), "a");
  ASSERT_EQ(trim("a  \t  \r \n "), "a");
}

TEST(string_utils, trim_3)
{
  ASSERT_EQ(trim(" a "), "a");
  ASSERT_EQ(trim("  \t \r \n  a \t\n\r  "), "a");
}

TEST(string_utils, trim_4)
{
  ASSERT_EQ(trim(" a b "), "a b");
}

TEST(string_utils, replace_1)
{
  ASSERT_EQ(replace("", "",  ""),  "");
  ASSERT_EQ(replace("", "",  "y"), "");
  ASSERT_EQ(replace("", "x", "y"), "");
  ASSERT_EQ(replace("", "x", ""),  "");
}

TEST(string_utils, replace_2)
{
  ASSERT_EQ(replace("abc", "x", "y"), "abc");
  ASSERT_EQ(replace("abc", "a", "a"), "abc");
  ASSERT_EQ(replace("abc", "a", "y"), "ybc");
  ASSERT_EQ(replace("abc", "a", "ya"), "yabc");
  ASSERT_EQ(replace("abc", "a", "ay"), "aybc");
}

TEST(string_utils, replace_3)
{
  ASSERT_EQ(replace("abcdefg", "bcd", ""), "aefg");
  ASSERT_EQ(replace("abcdefg", "bcd", "dcb"), "adcbefg");
}

TEST(string_utils, contains_1)
{
  ASSERT_FALSE(contains("", "a"));

  // Strings do not contain ""
  ASSERT_FALSE(contains("", ""));
  ASSERT_FALSE(contains("abc", ""));
}

TEST(string_utils, contains_2)
{
  ASSERT_TRUE(contains("abc", "bc"));
  ASSERT_TRUE(contains("abc", "abc"));
  ASSERT_FALSE(contains("abc", "abcd"));
}

TEST(string_utils, to_int)
{
  ASSERT_EQ(to_int("0"), 0);
  ASSERT_EQ(to_int("-0"), 0);
  ASSERT_EQ(to_int("1"), 1);
  ASSERT_EQ(to_int("-1"), -1);
  ASSERT_EQ(to_int("abc"), 0);
}

