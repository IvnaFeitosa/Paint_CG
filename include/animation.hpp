#ifndef ANIMATION_HPP
#define ANIMATION_HPP

extern float pacy;
extern float pacx;

void desenharPac(float x, float y, float r, float anguloAbertura);
void desenharBolinhas(float x, float y, float r);
void movimentarPac(int value);
void display_animation(void);
void reset();

#endif