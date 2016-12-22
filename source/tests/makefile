all: glboiler_tests

glboiler_tests:
	clang++  -I .. -I ../thirdparty/googletest/include  -std=c++11   -I../geom -DMACOSX ../*.cpp *.cpp -I ../thirdparty/lpng1626/ -framework OpenGL -framework GLUT -Wno-deprecated-declarations ../thirdparty/lpng1626/libpng.a -lz -o glboiler_tests ../thirdparty/googletest/make/gtest.a

