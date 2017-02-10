all:glboiler_tests_exe

clean:
	rm glboiler_tests *.o ../*.o geom/*.o ../geom/*.o ../macosx/*.o utils/*.o ../md3/*.o

run:
	cp glboiler_tests ../../assets/; cd ../../assets/; ./glboiler_tests; cd -
# NB run tests from assets/ dir, so we can load assets within the tests


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I.. \
  -I../thirdparty/googletest/include \
  -I../thirdparty/lodepng \
  -I../geom \
  -I../macosx \
  -I../md3 \
  -Igeom \
  -I../utils

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++11   -DMACOSX

LDFLAGS=../thirdparty/googletest/make/gtest.a -framework OpenGL -framework GLUT

SOURCES=test_main.cpp \
colour_tests.cpp \
int_graph_tests.cpp \
light_tests.cpp \
scene_graph_tests.cpp \
scene_node_tests.cpp \
texture_tests.cpp \
vertex_tests.cpp \
viewport_tests.cpp \
geom/aabb_tests.cpp \
geom/frustum_tests.cpp \
geom/mat4_tests.cpp \
geom/mat4_test_utils.cpp \
geom/vec2_tests.cpp \
geom/vec3_tests.cpp \
utils/file_tests.cpp \
utils/string_utils_tests.cpp \
../gl_1_1_renderer.cpp \
../gl_2_renderer.cpp \
../gl_1_1_solid_scene_node.cpp \
../gl_2_solid_scene_node.cpp \
../gl_system.cpp \
../gl_shader.cpp \
../int_graph.cpp \
../light.cpp \
../load_png.cpp \
../log.cpp \
../material.cpp \
../md3_node.cpp \
../md3_state.cpp \
../renderer.cpp \
../render_pass.cpp \
../render_to_texture.cpp \
../resource_manager.cpp \
../scene_description.cpp \
../scene_graph.cpp \
../scene_node.cpp \
../shadow_depth_pass.cpp \
../shadow_opaque_pass.cpp \
../simple_forward_pass.cpp \
../state.cpp \
../texture.cpp \
../view.cpp \
../geom/aabb.cpp \
../geom/camera.cpp \
../geom/frustum.cpp \
../geom/look_at.cpp \
../geom/projection.cpp \
../geom/quat.cpp \
../macosx/timer.cpp \
../md3/md3.cpp \
../utils/file.cpp \
../utils/string_utils.cpp \
../thirdparty/lodepng/lodepng.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=glboiler_tests

glboiler_tests_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

