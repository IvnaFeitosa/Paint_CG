#include <GL/freeglut.h>
#include "obj_container.hpp"
#include "transformations.hpp"  // <<---- IMPORTANTE

void init(void);
void display(void);
void capturarCliqueMouse(int button, int state, int x, int y);

ObjContainer obj_container = ObjContainer();
Transform transformador;   // <<---- instância do transformador

//variáveis de controle de modo
const int nenhum = 0;
const int modoCriacaoPonto = 1;
const int modoCriacaoLinha = 2;
const int modoCriacaoPoligono = 3;

int modoAtual = nenhum;

//variável global para armazenar objeto selecionado
Object* objetoSelecionado = nullptr;

//variável contadora para 2 cliques esperados de linha
bool aguardandoPrimeiroClique = false;
Point primeiroPontoLinha(0, 0);

//vetor para armazenar pontos do poligono durante modo criação
list<Point> verticesPoly;

//última posição do mouse (para seleção)
int ultimoMouseX = 0, ultimoMouseY = 0;

//função para registrar teclas
void capturarTeclaPressionada(unsigned char key, int x, int y){

    if(modoAtual == nenhum){
        if(key=='1'){
            modoAtual = modoCriacaoPonto;
            printf("modo de criacao de ponto ativado\n");
        }else if(key=='2'){
            modoAtual = modoCriacaoLinha;
            printf("modo de criacao de linha ativado \n");
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
            printf("\nretornando ao modo padrao\n");
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

        // tentar selecionar linhas
        for (auto &linha : obj_container.get_lines()) {
            if (linha.detection(x_mundo, y_mundo)) {
                objetoSelecionado = &linha;
                printf("Linha selecionada!\n");
                break;
            }
        }

        // tentar polígonos
        if (!objetoSelecionado) {
            for (auto &poly : obj_container.get_polygons()) {
                if (poly.detection(x_mundo, y_mundo)) {
                    objetoSelecionado = &poly;
                    printf("Polígono selecionado!\n");
                    break;
                }
            }
        }

        // tentar pontos
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

    // -------------------------
    // TRANSFORMAÇÕES
    // -------------------------
    if(objetoSelecionado != nullptr){
        switch(key){
            case 't': // Transladar 50 pra direita, 30 pra cima
                transformador.translade(50, 30);
                transformador.aply_transformations(objetoSelecionado);
                printf("Transladação aplicada\n");
                break;
            case 'r': // Rotacionar 45 graus em torno da origem
                transformador.rotate(45, Point(0,0));
                transformador.aply_transformations(objetoSelecionado);
                printf("Rotação aplicada\n");
                break;
            case 's': // Escalar 2x em X e 2x em Y
                transformador.scale(2, 2, Point(0,0));
                transformador.aply_transformations(objetoSelecionado);
                printf("Escala aplicada\n");
                break;
            case 'x': // Reflexão em X
                transformador.reflect(true, false);
                transformador.aply_transformations(objetoSelecionado);
                printf("Reflexão em X aplicada\n");
                break;
            case 'y': // Reflexão em Y
                transformador.reflect(false, true);
                transformador.aply_transformations(objetoSelecionado);
                printf("Reflexão em Y aplicada\n");
                break;
            case 'h': // Shear em X
                transformador.shear_x(1.0f, Point(0,0));
                transformador.aply_transformations(objetoSelecionado);
                printf("Shear em X aplicado\n");
                break;
            case 'v': // Shear em Y
                transformador.shear_y(1.0f, Point(0,0));
                transformador.aply_transformations(objetoSelecionado);
                printf("Shear em Y aplicado\n");
                break;
        }
        glutPostRedisplay(); // redesenha após transformação
    }
};

void capturarCliqueMouse(int button, int state, int mousex, int mousey) {
    ultimoMouseX = mousex;
    ultimoMouseY = mousey;

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        float largura = (float)glutGet(GLUT_WINDOW_WIDTH);
        float altura  = (float)glutGet(GLUT_WINDOW_HEIGHT);

        float x = ((float)mousex/largura)*800.0f;
        float y = ((altura-(float)mousey)/altura)*600.0f;

        if(modoAtual == modoCriacaoPonto){
            obj_container.addPoint(Point(x, y));
            glutPostRedisplay();

        }else if(modoAtual == modoCriacaoLinha){
            if(!aguardandoPrimeiroClique){
                primeiroPontoLinha.setX(x);
                primeiroPontoLinha.setY(y);
                aguardandoPrimeiroClique = true;
            }else{
                Point segundoPonto(x, y);
                Line linha(primeiroPontoLinha, segundoPonto);
                obj_container.addLine(linha);
                aguardandoPrimeiroClique = false;
            }
        }else if(modoAtual == modoCriacaoPoligono){
            verticesPoly.push_back(Point(x, y));
        }

        glutPostRedisplay();
    }
};

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
        for (auto &vertice : poly.getVertices()) {
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

    glutPostRedisplay();
    glutMainLoop();
    return 0;
}
