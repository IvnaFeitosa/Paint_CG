#include <GL/freeglut.h>
#include <fstream>
#include <iostream>
#include <string>
#include "obj_container.hpp"
#include "saveLoad.hpp"
#include "transformations.hpp"
#include "animation.hpp"
#include "convex_hull_dc.hpp"

void init(void);
void display(void);
void capturarCliqueMouse(int button, int state, int x, int y);
void capturarTeclaPressionada(unsigned char key, int x, int y);
void capturarTeclaEspecialPressionada(int key, int x, int y);
Point get_mouse_point(int mousex, int mousey);
void capturarMovimentoMouse(int mousex, int mousey);
void animation_pacman(int value);

ObjContainer obj_container = ObjContainer();

ObjContainer animation_container = ObjContainer();
bool is_animation_playing = false;

const int nenhum = 0;
const int modoCriacaoPonto = 1;
const int modoCriacaoLinha = 2;
const int modoCriacaoPoligono = 3;

int modoAtual = nenhum;

Object* objetoSelecionado = nullptr;
bool dragging = false;
float startX, startY;

bool aguardandoPrimeiroClique = false;
Point primeiroPontoLinha(0, 0);

list<Point> verticesPoly;

int ultimoMouseX = 0, ultimoMouseY = 0;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(250, 50);
    glutCreateWindow("Paint_CG");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(capturarTeclaPressionada);
    glutMouseFunc(capturarCliqueMouse);
    glutMotionFunc(capturarMovimentoMouse);

    glutPostRedisplay();
    glutMainLoop();
    return 0;
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800.0, 0, 600.0);
    glMatrixMode(GL_MODELVIEW);
}


void display(void) {
    if (is_animation_playing)
        return display_animation();

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5.0);
    float r, g, b;

    ObjContainer* draw_container = &obj_container;
        
    glBegin(GL_POINTS);
    for (auto &p : draw_container->get_points()) {
        p.get_color(r, g, b);
        glColor3f(r, g, b);
        glVertex2f(p.getX(), p.getY());
    }
    glEnd();


    glBegin(GL_LINES);
    for(auto &linha: draw_container->get_lines()){
        linha.get_color(r, g, b);
        glColor3f(r, g, b);
        glVertex2f(linha.getp1().getX(), linha.getp1().getY());
        glVertex2f(linha.getp2().getX(), linha.getp2().getY());
    }
    glEnd();


    glBegin(GL_POINTS);
    for (auto &p : verticesPoly) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(p.getX(), p.getY());
    }
    glEnd();

 
    for (auto &poly : draw_container->get_polygons()) {
        poly.get_color(r, g, b);
        glColor3f(r, g, b);
        glBegin(GL_POLYGON);
        for (auto &vertice : poly.get_verticies()) {
            glVertex2f(vertice.getX(), vertice.getY());
        }
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}

void capturarTeclaPressionada(unsigned char key, int x, int y){
    if (is_animation_playing) return;

    if (modoAtual == nenhum){
        if(key=='1'){
            modoAtual = modoCriacaoPonto;
            printf("modo de criacao de ponto ativado\n");
        }else if(key=='2'){
            modoAtual = modoCriacaoLinha;
            printf("modo de criacao de linha ativado\n");
        }else if(key=='3'){
            modoAtual = modoCriacaoPoligono;
            printf("modo de criacao de poligono ativado\n");
        } else if (key == 's'){
            printf("entrando em modo de salvamento de arquivo \n");
            salvarObjetos2D(obj_container);
        } else if (key == 'l'){
            printf("entrando em modo de carregamento de arquivo \n");
            carregarObjetos2D(obj_container);
            glutPostRedisplay();
        } else if ((key == 127 || key == 8) && objetoSelecionado) { // 127 = Delete, 8 = Backspace
            obj_container.search_for_deletion(objetoSelecionado);
            objetoSelecionado = nullptr;
            glutPostRedisplay();
        } else if (key == 'a') {
            is_animation_playing = true;
            animation_pacman(0);
            
        } else if (key == 'c') {
            if (objetoSelecionado) {
              
                Poly* polySelecionado = dynamic_cast<Poly*>(objetoSelecionado);
                if (polySelecionado) {
       
                    std::vector<Point> vertices = polySelecionado->get_verticies();

     
                    std::vector<Point> hull = divideAndConquerHull(vertices);

    
                    polySelecionado->set_vertices(hull);

                    glutPostRedisplay();
                }
            }
        }else {
            if (objetoSelecionado) {
                switch(key) {
                    case 'r': 
                        Transform::rotate(1, objetoSelecionado->get_center());
                        Transform::aply_transformations(objetoSelecionado);
                        break;
                    case 't': 
                        Transform::rotate(-1, objetoSelecionado->get_center());
                        Transform::aply_transformations(objetoSelecionado);
                        break;
                    case 'f': 
                        Transform::scale(1.1, 1.1, objetoSelecionado->get_center());
                        Transform::aply_transformations(objetoSelecionado);
                        break;
                    case 'g': 
                        Transform::scale(.9, .9, objetoSelecionado->get_center());
                        Transform::aply_transformations(objetoSelecionado);
                        break;
                    case 'z': 
                        Transform::reflect(true, false, objetoSelecionado->get_center());
                        Transform::aply_transformations(objetoSelecionado);
                        break;
                    case 'x': 
                        Transform::reflect(false, true, objetoSelecionado->get_center());
                        Transform::aply_transformations(objetoSelecionado);
                        break;
                    case 'y': 
                        Transform::shear_x(.5f, objetoSelecionado->get_center());
                        Transform::aply_transformations(objetoSelecionado);
                        break;
                    case 'u': 
                        Transform::shear_x(-.5f, objetoSelecionado->get_center());
                        Transform::aply_transformations(objetoSelecionado);
                        break;
                    case 'h': 
                        Transform::shear_y(.5f, objetoSelecionado->get_center());
                        Transform::aply_transformations(objetoSelecionado);
                        break;
                    case 'j': 
                        Transform::shear_y(-.5f, objetoSelecionado->get_center());
                        Transform::aply_transformations(objetoSelecionado);
                        break;
                    case 'n':
                        objetoSelecionado->next_color();
                }
                glutPostRedisplay();
            }
        }

    //se em qualquer modo
    //13 = tecla ENTER
    } else {
        if (key == 13) {
            if (modoAtual == modoCriacaoPoligono) {
                //montando poligono após a criação de todos os seus pontos
                obj_container.addPoly(Poly(verticesPoly));
                glutPostRedisplay();
                verticesPoly.clear();
            }
            printf("retornando ao modo padrao\n");
            modoAtual = nenhum;
        }
    }
}

void capturarTeclaEspecialPressionada(int key, int x, int y) {
    
}

Point get_mouse_point(int mousex, int mousey) {
    float largura = (float) glutGet(GLUT_WINDOW_WIDTH);
    float altura  = (float) glutGet(GLUT_WINDOW_HEIGHT);

    float x = ((float) mousex / largura) * 800.0f;
    float y = ((altura - (float) mousey) / altura) * 600.0f;

    return Point(x, y);
}


void capturarCliqueMouse(int button, int state, int mousex, int mousey) {
    if (is_animation_playing) return;
    ultimoMouseX = mousex;
    ultimoMouseY = mousey;

    Point mouse_pos = get_mouse_point(mousex, mousey);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        if(modoAtual == modoCriacaoPonto){
            obj_container.addPoint(mouse_pos);
            glutPostRedisplay();

        }else if(modoAtual == modoCriacaoLinha){
            if(!aguardandoPrimeiroClique){
                primeiroPontoLinha.setX(mouse_pos.getX());
                primeiroPontoLinha.setY(mouse_pos.getY());
                aguardandoPrimeiroClique = true;
            }else{
                Point segundoPonto(mouse_pos.getX(), mouse_pos.getY());
                Line linha(primeiroPontoLinha, segundoPonto);
                obj_container.addLine(linha);
                aguardandoPrimeiroClique = false;
            }
        }else if(modoAtual == modoCriacaoPoligono){
            verticesPoly.push_back(mouse_pos);
        } else {

            objetoSelecionado = obj_container.search_detection(mouse_pos.getX(), mouse_pos.getY());
 
            if (objetoSelecionado) {
                dragging = true;
                startX = mouse_pos.getX();
                startY = mouse_pos.getY();
            } else {
                objetoSelecionado = nullptr;
                dragging = false;
            }
        }
        glutPostRedisplay();
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && dragging) {
        dragging = false;
    }
}


void capturarMovimentoMouse(int mousex, int mousey) {
    if (dragging && objetoSelecionado) {
        Point mouse_pos = get_mouse_point(mousex, mousey);

        float dx = mouse_pos.getX() - startX;
        float dy = mouse_pos.getY() - startY;

        Transform::translade(dx, dy);
        Transform::aply_transformations(objetoSelecionado);

        startX = mouse_pos.getX();
        startY = mouse_pos.getY();

        glutPostRedisplay();
    }
}

void animation_pacman(int value) {

    movimentarPac(value);

    glutPostRedisplay();
    if (pacx < 850)
        glutTimerFunc(30, animation_pacman, 0);
    else {
        is_animation_playing = false;
        reset();
    }
}
