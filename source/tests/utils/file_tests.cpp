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
  ASSERT_EQ(f.get_line(), 1);

  ok = f.read_string(&s);
  ASSERT_TRUE(ok);
  ASSERT_EQ(s, "def");
  ASSERT_EQ(f.get_line(), 2);

  ok = f.read_string(&s);
  ASSERT_FALSE(ok); 
  ASSERT_EQ(s, "");
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

  // Crazy seek offset doesn't put stream in a bad state. I suppose there must be a good reason...?!
  ok = f.seek(300);
  ASSERT_TRUE(ok);
}

TEST(binary_file, write_then_read)
{
  const std::string filename = "test/binary_file_created_by_tests.txt";
  const std::string string_val = "hello, I am string";
  const int int_val = 42;
  const int binary_val = 0x01020304;

  {
    binary_file f;

    bool ok = f.open_for_writing(filename);
    ASSERT_TRUE(ok);

    ok = f.write_string(string_val);
    ASSERT_TRUE(ok);

    ok = f.write_int(int_val);
    ASSERT_TRUE(ok);

    int i = binary_val;
    size_t n = f.write_binary(sizeof(int), &i);
    ASSERT_EQ(n, sizeof(int));

    f.close();

    ok = f.write_string("hello");
    ASSERT_FALSE(ok);
  }

  {
    binary_file f;

    bool ok = f.open_for_reading(filename);
    ASSERT_TRUE(ok);

    std::string s;
    ok = f.read_string(s);
    ASSERT_TRUE(ok);
    ASSERT_EQ(s, string_val);

    int i = 0;
    ok = f.read_int(i);
    ASSERT_TRUE(ok);
    ASSERT_EQ(i, int_val);

    size_t n = f.read_binary(sizeof(int), &i);
    ASSERT_EQ(n, sizeof(int));
    ASSERT_EQ(i, binary_val);

    f.close();

    ok = f.read_int(i);
    ASSERT_FALSE(ok);
  }
}


