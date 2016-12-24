all:glboiler

clean:
	rm glboiler *.o ../*.o

run:
	cp glboiler ../../assets/; cd ../../assets/; ./glboiler; cd -

CC=clang++
CFLAGS=-c -Wall -Wno-deprecated-declarations -I .. -I ../thirdparty/googletest/include  -I ../thirdparty/lpng1626/ -I../geom -std=c++11   -DMACOSX
LDFLAGS=-framework OpenGL -framework GLUT ../thirdparty/lpng1626/libpng.a -lz
SOURCES=glut_main.cpp ../basic_renderer.cpp ../gl_shader.cpp ../load_png.cpp ../renderer.cpp ../scene_graph.cpp ../teapot_scene_node.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=glboiler

glboiler: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

