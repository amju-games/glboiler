all:glboiler_tests_exe

clean:
	rm glboiler_tests *.o ../*.o ../geom/*.o ../macosx/*.o

run:
	./glboiler_tests

CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=-I.. -I../thirdparty/googletest/include  -I../thirdparty/lpng1626/ -I../geom -I../macosx -Igeom

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++11   -DMACOSX

LDFLAGS=../thirdparty/googletest/make/gtest.a -framework OpenGL -framework GLUT ../thirdparty/lpng1626/libpng.a -lz

SOURCES=test_main.cpp \
colour_tests.cpp \
light_tests.cpp \
scene_graph_tests.cpp \
scene_node_tests.cpp \
vertex_tests.cpp \
viewport_tests.cpp \
geom/aabb_tests.cpp \
geom/frustum_tests.cpp \
geom/mat4_tests.cpp \
geom/mat4_test_utils.cpp \
geom/vec2_tests.cpp \
geom/vec3_tests.cpp \
../forward_renderer.cpp \
../gl_system.cpp \
../gl_shader.cpp \
../light.cpp \
../load_png.cpp \
../log.cpp \
../renderer.cpp \
../render_to_texture.cpp \
../scene_description.cpp \
../scene_graph.cpp \
../teapot_scene_node.cpp \
../view.cpp \
../geom/aabb.cpp \
../geom/camera.cpp \
../geom/frustum.cpp \
../geom/look_at.cpp \
../geom/projection.cpp \
../macosx/timer.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=glboiler_tests

glboiler_tests_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

