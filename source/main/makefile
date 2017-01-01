all:glboiler_exe

clean:
	rm glboiler *.o ../*.o ../geom/*.o ../macosx/*.o ../../assets/glboiler

run:
	cp glboiler ../../assets/; cd ../../assets/; ./glboiler; cd -

CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations 

INCLUDES=-I.. -I../thirdparty/googletest/include  -I../thirdparty/lpng1626/ -I../geom -I../macosx

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++11 -O0 -g

LDFLAGS=-framework OpenGL -framework GLUT ../thirdparty/lpng1626/libpng.a -lz

SOURCES=glut_main.cpp \
../forward_renderer.cpp \
../gl_system.cpp \
../gl_shader.cpp \
../load_png.cpp \
../renderer.cpp \
../render_to_texture.cpp \
../scene_description.cpp \
../scene_graph.cpp \
../teapot_scene_node.cpp \
../view.cpp \
../macosx/timer.cpp \
../geom/aabb.cpp \
../geom/camera.cpp \
../geom/frustum.cpp \
../geom/look_at.cpp \
../geom/projection.cpp \
../log.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=glboiler

glboiler_exe: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

