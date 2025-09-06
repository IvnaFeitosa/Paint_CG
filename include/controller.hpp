#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "point.hpp"
#include <GL/freeglut.h>

void init(void);
void display(void);
void capturarCliqueMouse(int button, int state, int x, int y);
void capturarTeclaPressionada(unsigned char key, int x, int y);
Point get_mouse_point(int mousex, int mousey);
void capturarMovimentoMouse(int mousex, int mousey);

#endif