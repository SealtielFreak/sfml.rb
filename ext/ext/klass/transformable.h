#ifndef SFML_RB_TRANSFORMABLE_H
#define SFML_RB_TRANSFORMABLE_H

#include <ruby.h>

void Init_Transformable(VALUE rb_module);

void *Get_Transformable_Struct(VALUE self);


VALUE Get_Klass_Transformable();

#endif //SFML_RB_TRANSFORMABLE_H
