// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "binary_file.h"
#include "file.h"

// These tests have to be run from the assets/ dir

TEST(text_file, open_file_that_exists)
{
  text_file f;
  bool ok = f.open_for_reading("test/file_a.txt");
  ASSERT_TRUE(ok);
}

TEST(text_file, read_string)
{
  text_file f;
  // This file should contain: abc\ndef\n
  bool ok = f.open_for_reading("test/file_a.txt");
  ASSERT_TRUE(ok);
  std::string s;
  ok = f.read_string(&s);
  ASSERT_TRUE(ok);
  ASSERT_EQ(s, "abc");
  ok = f.read_string(&s);
  ASSERT_TRUE(ok);
  ASSERT_EQ(s, "def");
  ok = f.read_string(&s);
  ASSERT_FALSE(ok); 
}

TEST(text_file, close)
{
  text_file* f = new text_file;
  bool ok = f->open_for_reading("test/file_a.txt");
  ASSERT_TRUE(ok);
  f->close();
  std::string s;
  ok = f->read_string(&s);
  ASSERT_FALSE(ok);
  delete f;
}

TEST(text_file, open_file_that_doesnt_exist)
{
  text_file f;
  bool ok = f.open_for_reading("no_such_file______.no_file");
  ASSERT_FALSE(ok);
  std::string s;
  ok = f.read_string(&s);
  ASSERT_FALSE(ok);
}

TEST(binary_file, read_and_seek)
{
  binary_file f;
  // File contents: "0123456789abcdef\n"
  bool ok = f.open_for_reading("test/file_b.txt");
  ASSERT_TRUE(ok);
  char buf[100];
  size_t st = f.read_binary(1, buf); 
  ASSERT_EQ(st, 1);
  ASSERT_EQ(buf[0], '0');
  ok = f.seek(7);
  ASSERT_TRUE(ok);
  st = f.read_binary(1, buf); 
  ASSERT_EQ(st, 1);
  ASSERT_EQ(buf[0], '7');
  ok = f.seek(3);
  st = f.read_binary(1, buf); 
  ASSERT_EQ(st, 1);
  ASSERT_EQ(buf[0], '3');
  ok = f.seek(300);
  ASSERT_FALSE(ok);
}


