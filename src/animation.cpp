#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include "transformations.hpp"
#include "animation.hpp"

//posicao inicial central do pacman
float pacy = 300.0;
float pacx = 30.0;

float anguloBoca = 30.0;
float direcaoBoca = 1.0;

//booleano para controlar o redesenho do pac
bool pacAtivo = true;

//posi��es bolinhas
float bolinhasy = 300.0;
std::vector<float> bolinhasx = {90, 150, 210, 270, 330, 390, 450, 510, 570, 630, 690, 750};

void desenharPac(float x, float y, float r, float anguloAbertura) {
    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y);
        for(float a = anguloAbertura; a<= 360 - anguloAbertura; a += 5.0){
            //covertendo medida em graus para radiano
            float rad = (a * M_PI)/180.0f;
            //usando equacao da reta para definir onde fica o ponto do tri�ngulo
            glVertex2f(x + cos(rad)*r, y+sin(rad)*r);
        }

    glEnd();
}

void desenharBolinhas(float x, float y, float r) {
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_TRIANGLE_FAN);
        //definindo centro
        glVertex2f(x, y);
        //dessa vez os triangulos daram toda a volta
        for (float a = 0; a <= 360; a += 10) {
            float rad = a * M_PI / 180.0f;
            glVertex2f(x + cos(rad) * r, y + sin(rad) * r);
        }
    glEnd();
}

void movimentarPac(int value) {
     //a cada 33ms ele anda 10 pixels pra frente
    pacx += 5;

    //verificando se pac atravessou a tela
    if(pacx > 850){
        pacAtivo = false;
    }

    //angulo da boca aumenta sempre em fator de 10,  ao atingir limite m�ximo o fator direcao torna-se negativo
    //e o angulo passa a diminuir at� atingir o limite m�nimo que � quando volta a crescer
    anguloBoca += direcaoBoca * 10.0;

    if (anguloBoca >= 40.0){ // limite m�ximo da abertura
        direcaoBoca = -1.0;
    } else if (anguloBoca <= 5.0){ // limite m�nimo
        direcaoBoca = 1.0;
    }

    //removendo coordenada x da bolinha ao ser alcan�ada para que n�o seja mais redesenhada
    //uma bolinha � alcan�ada quando est� dento do raio do pac (pacx + raio)

    //a cada itera��o sempre pegamos a refer�ncia da primeira posi��o, se a posi��o atual estiver
    //dentro do raio do pac ela pode ser removida do vetor para n�o ser redesenhada, ao remover com
    //erase o iterador j� pega a refer�ncia para o pr�ximo elem
    for (auto it = bolinhasx.begin(); it != bolinhasx.end(); ) {
        if (pacx + 50 >= *it) {
            it = bolinhasx.erase(it);
        } else {
            ++it;
        }
    }
}

void display_animation(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    if(pacAtivo){
        desenharPac(pacx, pacy, 50.0, anguloBoca);
    }


    for (auto &x : bolinhasx) {
        desenharBolinhas(x, bolinhasy, 10);
    }

    glutSwapBuffers();
}

void reset() {
    pacy = 300.0;
    pacx = 30.0;

    anguloBoca = 30.0;
    direcaoBoca = 1.0;

    bolinhasy = 300.0;
    bolinhasx = {90, 150, 210, 270, 330, 390, 450, 510, 570, 630, 690, 750};
}
