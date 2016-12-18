// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

// clang++ *.cpp ../*.cpp -I .. -std=c++11 -DMACOSX -framework OpenGL -framework GLUT

#include <stdio.h>
#ifdef WIN32
#include <GL/glut.h>
#endif
#ifdef MACOSX
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif

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
    
    glutPostRedisplay();
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   
    glutInitWindowSize(WIN_X, WIN_Y);
    glutCreateWindow("Hello"); 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutMainLoop();
    return 0;
} 
