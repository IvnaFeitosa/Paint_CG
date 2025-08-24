#include "object.hpp"

unsigned int Object::id_gen = 0;

Object::Object(): id(id_gen++){}

unsigned int Object::get_id() {
    return this->id;
}

bool Object::equals(Object* obj) {
    return this->id == obj->id;
}
