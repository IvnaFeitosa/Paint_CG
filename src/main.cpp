#include <GL/freeglut.h>
#include "obj_container.hpp"

void init(void);
void display(void);
void capturarCliqueMouse(int button, int state, int x, int y);

ObjContainer obj_container = ObjContainer();

//veriáveis de controle de modo
const int nenhum = 0;
const int modoCriacaoPonto = 1;
const int modoCriacaoLinha = 2;
const int modoCriacaoPoligono = 3;

int modoAtual = nenhum;

//variável contadora para 2 cliques esperados de linha
bool aguardandoPrimeiroClique = false;
Point primeiroPontoLinha(0, 0);

//vetor para armazenar pontos do poligono durante modo criação
list<Point> verticesPoly;

//função para registrar 
void capturarTeclaPressionada(unsigned char key, int x, int y){

    //se não tiver sido selecionado nenhum modo ou um modo for finalizado com enter
    if(modoAtual == nenhum){
        if(key=='1'){
            modoAtual = modoCriacaoPonto;
            printf("modo de criacao de ponto ativado");
        }else if(key=='2'){
            modoAtual = modoCriacaoLinha;
            printf("modo de criacao de linha ativado \n");
        }else if(key=='3'){
            modoAtual = modoCriacaoPoligono;
            printf("modo de criacao de poligono ativado");
        }

    //se em qualquer modo
    //13 = tecla ENTER
    }else{
        if(key==13){

            if(modoAtual == modoCriacaoPoligono){

                //montando poligono após a criação de todos os seus pontos
                obj_container.addPoly(Poly(verticesPoly));

                //limpando vetor temporário de pontos para o próximo poligono
                verticesPoly.clear();

            }

            printf("\nretornando ao modo padrao\n");
            modoAtual = nenhum;
        }
    }

};

void capturarCliqueMouse(int button, int state, int mousex, int mousey) {

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){

        //sistema de coord da janela e da projeção são diferentes
        //janela: (0,0) no canto superior esquerdo; projeção: (0,0) no canto inferior esquerdo

        float largura = (float)glutGet(GLUT_WINDOW_WIDTH);
        float altura  = (float)glutGet(GLUT_WINDOW_HEIGHT);

        //para converter calculamos a razão da coord do mouse pela medida da projeção e multiplicamos
        //o resultado pela última

        float x = ((float)mousex/largura)*800.0f;
        float y = ((altura-(float)mousey)/altura)*600.0f;

        if(modoAtual == modoCriacaoPonto){

            obj_container.addPoint(Point(x, y));
            glutPostRedisplay();

        }else if(modoAtual == modoCriacaoLinha){

            if(aguardandoPrimeiroClique == false){

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

    //definindo cor de fundo como branco
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800.0, 0, 600.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);


    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);

    //desenhando pontos criados
    glBegin(GL_POINTS);
    for (auto &p : obj_container.get_points()) {
        glVertex2f(p.getX(), p.getY());
    }
    glEnd();


    //desenhando linhas criadas
    glBegin(GL_LINES);
        for(auto &linha: obj_container.get_lines()){
            glVertex2f(linha.getp1().getX(), linha.getp1().getY());
            glVertex2f(linha.getp2().getX(), linha.getp2().getY());
        }
    glEnd();

    //desenhando pontos do poligono antes de sua finalização
    glBegin(GL_POINTS);
    for (auto &p : verticesPoly) {
        glVertex2f(p.getX(), p.getY());
    }
    glEnd();

    //desenhando poligonos finalizados
    glColor3f(0.0f, 0.0f, 0.0f);
     for (auto &poly : obj_container.get_polygons()) {
        glBegin(GL_POLYGON);
        for (auto &vertice : poly.get_verticies()) {
            glVertex2f(vertice.getX(), vertice.getY());
        }
        glEnd();
    }

    glFlush();
    //trocando buffers
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

    // força redesenho logo que a janela abre
    glutPostRedisplay();

    glutMainLoop();
    return 0;
}
