#include "object.hpp"

unsigned int Object::id_gen = 0;
ColorPalet Object::colors = {{
    {{0.00f, 0.00f, 0.00f}},  // Preto
    {{0.91f, 0.30f, 0.24f}},  // vermelho vibrante
    {{0.18f, 0.80f, 0.44f}},  // verde limão
    {{0.20f, 0.60f, 0.86f}},  // azul celeste
    {{0.95f, 0.77f, 0.06f}},  // amarelo ouro
    {{0.84f, 0.15f, 0.60f}},  // magenta
    {{1.00f, 0.50f, 0.00f}},  // laranja
    {{0.55f, 0.34f, 0.29f}},  // marrom
    {{0.40f, 0.75f, 0.64f}},  // verde água
    {{0.60f, 0.40f, 0.80f}},  // roxo
    {{0.25f, 0.25f, 0.25f}}   // cinza escuro
}};

Object::Object(): id(id_gen++), color_id(0) {
    color[0] = 0.0f;
    color[1] = 0.0f;
    color[2] = 0.0f;
}

unsigned int Object::get_id() {
    return this->id;
}

bool Object::equals(Object* obj) {
    return this->id == obj->id;
}

void Object::get_color(float &r, float &g, float &b) {
    r = color[0]; g = color[1]; b = color[2];
}

void Object::set_color(float r, float g, float b) {
    color[0] = r; 
    color[1] = g; 
    color[2] = b;
}

void Object::next_color() {
    if (color_id >= colors.size())
        color_id = 0;
    color[0] = colors[++color_id][0]; 
    color[1] = colors[color_id][1]; 
    color[2] = colors[color_id][2];
}
