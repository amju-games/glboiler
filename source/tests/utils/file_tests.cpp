
#include <gtest/gtest.h>
#include "file.h"

// These tests have to be run from the assets/ dir

TEST(file, open_file_that_exists)
{
  file f;
  bool ok = f.open_for_reading("test/file_a.txt");
  ASSERT_TRUE(ok);
}

TEST(file, read_string)
{
  file f;
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

TEST(file, close)
{
  file* f = new file;
  bool ok = f->open_for_reading("test/file_a.txt");
  ASSERT_TRUE(ok);
  f->close();
  std::string s;
  ok = f->read_string(&s);
  ASSERT_FALSE(ok);
  delete f;
}

TEST(file, open_file_that_doesnt_exist)
{
  file f;
  bool ok = f.open_for_reading("no_such_file______.no_file");
  ASSERT_FALSE(ok);
  std::string s;
  ok = f.read_string(&s);
  ASSERT_FALSE(ok);
}

TEST(file, seek)
{
  file f;
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


