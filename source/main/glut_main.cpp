// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

// clang++  -I .. -I ../thirdparty/googletest/include  -std=c++11   -I../geom -DMACOSX ../*.cpp glut_main.cpp -I ../thirdparty/lpng1626/ -framework OpenGL -framework GLUT -Wno-deprecated-declarations ../thirdparty/lpng1626/libpng.a -lz

#include <stdio.h>
#include "opengl_includes.h"
#include "teapot_scene_node.h" // TODO TEMP TEST

static int WIN_X = 500;
static int WIN_Y = 500;

/*
void Mandel::Draw()
{
    char buf[1000];

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, m_winX, 0, m_winY);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glutSetWindowTitle(buf);
}
*/

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    teapot_scene_node tp;
    tp.render(0, frustum());
    
    glutSwapBuffers();
}

void reshape(int x, int y)
{
    WIN_X = x;
    WIN_Y = y;
    
    glViewport(0, 0, x, y);
}

void mouse(int button, int state, int x, int y)
{
}

void key(unsigned char c, int x, int y)
{
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    // https://pleiades.ucsc.edu/hyades/OpenGL_on_OS_X
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(WIN_X, WIN_Y);
    glutCreateWindow("Hello"); 

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    if (renderer)
    {
        printf("Renderer: %s\n", renderer);
    }
    else
    {
        printf("glGetString failed!\n");
    }

    if (version)
    {
        printf("OpenGL version supported: %s\n", version);
    }
    else
    {
        printf("glGetString failed!\n");
    }
  
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutMainLoop();
    return 0;
} 
