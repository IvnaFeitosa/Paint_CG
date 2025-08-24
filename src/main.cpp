#include <GL/freeglut.h>
#include "obj_container.hpp"
#include "transformations.hpp"

void init(void);
void display(void);
void capturarCliqueMouse(int button, int state, int x, int y);
void capturarTeclaPressionada(unsigned char key, int x, int y);
Point get_mouse_point(int mousex, int mousey);
void capturarMovimentoMouse(int mousex, int mousey);

ObjContainer obj_container = ObjContainer();

//variáveis de controle de modo
const int nenhum = 0;
const int modoCriacaoPonto = 1;
const int modoCriacaoLinha = 2;
const int modoCriacaoPoligono = 3;

int modoAtual = nenhum;

// seleção e dragging
Object* objetoSelecionado = nullptr;
bool dragging = false;
float startX, startY;

//variável contadora para 2 cliques esperados de linha
bool aguardandoPrimeiroClique = false;
Point primeiroPontoLinha(0, 0);

//vetor para armazenar pontos do poligono durante modo criação
list<Point> verticesPoly;

// posição do mouse
int ultimoMouseX = 0, ultimoMouseY = 0;


// ---------- FUNÇÕES ----------
void capturarTeclaPressionada(unsigned char key, int x, int y){
    if(modoAtual == nenhum){
        if(key=='1'){
            modoAtual = modoCriacaoPonto;
            printf("modo de criacao de ponto ativado\n");
        }else if(key=='2'){
            modoAtual = modoCriacaoLinha;
            printf("modo de criacao de linha ativado\n");
        }else if(key=='3'){
            modoAtual = modoCriacaoPoligono;
            printf("modo de criacao de poligono ativado\n");
        }
    }else{
        if(key==13){ // ENTER
            if(modoAtual == modoCriacaoPoligono){
                obj_container.addPoly(Poly(verticesPoly));
                verticesPoly.clear();
            }
            printf("retornando ao modo padrao\n");
            modoAtual = nenhum;
        }
    }

    // tecla 'i' -> tentar selecionar objeto
    if(key=='i' && modoAtual==nenhum){
        float largura = (float)glutGet(GLUT_WINDOW_WIDTH);
        float altura  = (float)glutGet(GLUT_WINDOW_HEIGHT);

        float x_mundo = ((float)ultimoMouseX/largura)*800.0f;
        float y_mundo = ((altura-(float)ultimoMouseY)/altura)*600.0f;

        objetoSelecionado = nullptr;

        for (auto &linha : obj_container.get_lines()) {
            if (linha.detection(x_mundo, y_mundo)) {
                objetoSelecionado = &linha;
                printf("Linha selecionada!\n");
                break;
            }
        }
        if (!objetoSelecionado) {
            for (auto &poly : obj_container.get_polygons()) {
                if (poly.detection(x_mundo, y_mundo)) {
                    objetoSelecionado = &poly;
                    printf("Polígono selecionado!\n");
                    break;
                }
            }
        }
        if (!objetoSelecionado) {
            for (auto &p : obj_container.get_points()) {
                if (p.detection(x_mundo, y_mundo)) {
                    objetoSelecionado = &p;
                    printf("Ponto selecionado!\n");
                    break;
                }
            }
        }

        if(!objetoSelecionado){
            printf("Nenhum objeto sob o mouse\n");
        }
    }

    // TRANSFORMAÇÕES POR TECLA
    if(objetoSelecionado != nullptr){
        switch(key){
            case 't': // Transladar
                Transform::translade(50, 30);
                Transform::aply_transformations(objetoSelecionado);
                printf("Transladação aplicada\n");
                break;
            case 'r': // Rotacionar
                Transform::rotate(45, Point(0,0));
                Transform::aply_transformations(objetoSelecionado);
                printf("Rotação aplicada\n");
                break;
            case 's': // Escalar
                Transform::scale(2, 2, Point(0,0));
                Transform::aply_transformations(objetoSelecionado);
                printf("Escala aplicada\n");
                break;
            case 'x': // Reflexão X
                Transform::reflect(true, false);
                Transform::aply_transformations(objetoSelecionado);
                printf("Reflexão em X aplicada\n");
                break;
            case 'y': // Reflexão Y
                Transform::reflect(false, true);
                Transform::aply_transformations(objetoSelecionado);
                printf("Reflexão em Y aplicada\n");
                break;
            case 'h': // Shear X
                Transform::shear_x(1.0f, Point(0,0));
                Transform::aply_transformations(objetoSelecionado);
                printf("Shear em X aplicado\n");
                break;
            case 'v': // Shear Y
                Transform::shear_y(1.0f, Point(0,0));
                Transform::aply_transformations(objetoSelecionado);
                printf("Shear em Y aplicado\n");
                break;
        }
        glutPostRedisplay();
    }
}


Point get_mouse_point(int mousex, int mousey) {
    float largura = (float) glutGet(GLUT_WINDOW_WIDTH);
    float altura  = (float) glutGet(GLUT_WINDOW_HEIGHT);

    float x = ((float) mousex / largura) * 800.0f;
    float y = ((altura - (float) mousey) / altura) * 600.0f;

    return Point(x, y);
}


void capturarCliqueMouse(int button, int state, int mousex, int mousey) {
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
        }else{
            // clique em modo normal: tentar arrastar
            objetoSelecionado = obj_container.search_detection(mouse_pos.getX(), mouse_pos.getY());
            if (objetoSelecionado) {
                dragging = true;
                startX = mouse_pos.getX();
                startY = mouse_pos.getY();
                printf("Objeto selecionado para dragging\n");
            }
        }
        glutPostRedisplay();
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && dragging) {
        dragging = false;
        objetoSelecionado = nullptr;
        printf("Soltei\n");
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


void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800.0, 0, 600.0);
    glMatrixMode(GL_MODELVIEW);
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);

    // pontos
    glBegin(GL_POINTS);
    for (auto &p : obj_container.get_points()) {
        glVertex2f(p.getX(), p.getY());
    }
    glEnd();

    // linhas
    glBegin(GL_LINES);
    for(auto &linha: obj_container.get_lines()){
        glVertex2f(linha.getp1().getX(), linha.getp1().getY());
        glVertex2f(linha.getp2().getX(), linha.getp2().getY());
    }
    glEnd();

    // pontos temporários do polígono
    glBegin(GL_POINTS);
    for (auto &p : verticesPoly) {
        glVertex2f(p.getX(), p.getY());
    }
    glEnd();

    // polígonos finalizados
    glColor3f(0.0f, 0.0f, 0.0f);
    for (auto &poly : obj_container.get_polygons()) {
        glBegin(GL_POLYGON);
        for (auto &vertice : poly.get_verticies()) {
            glVertex2f(vertice.getX(), vertice.getY());
        }
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}


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
