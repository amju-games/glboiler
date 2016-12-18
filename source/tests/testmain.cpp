// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

// Unit tests 
// To build on Mac:
// First build gtest.a in googletest (only needs doing once):
//   cd source/thirdparty/googletest/make
//   make gtest.a
// Then back in source/tests
//   clang++ *.cpp ../*.cpp -I .. -I ../thirdparty/googletest/include  -std=c++11  ../thirdparty/googletest/make/gtest.a

#include <gtest/gtest.h>

int main(int argc, char * argv[])
{
  //setup tests
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


