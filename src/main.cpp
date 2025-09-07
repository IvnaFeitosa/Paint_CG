#include <GL/freeglut.h>
#include "controller.hpp"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(250, 50);
    glutCreateWindow("Paint_CG");

    init();

    return 0;
}

