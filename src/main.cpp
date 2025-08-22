#include <GL/freeglut.h>
#include "obj_container.hpp"

void init(void);
void display(void);
void capturarCliqueMouse(int button, int state, int x, int y);

ObjContainer obj_container = ObjContainer();

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(250, 50);
    glutCreateWindow("Paint_CG");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(capturarCliqueMouse);

    // for�a redesenho logo que a janela abre
    glutPostRedisplay();

    glutMainLoop();
    return 0;
}

void capturarCliqueMouse(int button, int state, int x, int y) {
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){

        int largura = glutGet(GLUT_WINDOW_WIDTH);
        int altura = glutGet(GLUT_WINDOW_HEIGHT);

        float glX=(2.0f*x/largura)-1.0f;
        float glY=1.0f-(2.0f*y/altura);

        obj_container.addPoint(Point(glX, glY));

        glutPostRedisplay();
    }
};

void init(void) {

    //definindo cor de fundo como branco
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);


    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);

    glBegin(GL_POINTS);
    for (auto &p : obj_container.get_points()) {
        glVertex2f(p.getX(), p.getY());
    }

    glEnd();

    glFlush();
    //trocando buffers
    glutSwapBuffers();
}
