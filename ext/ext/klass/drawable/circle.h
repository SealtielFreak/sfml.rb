#ifndef SFML_RB_CIRCLE_H
#define SFML_RB_CIRCLE_H

#include <ruby.h>

void Init_Circle(VALUE rb_module);

void *Get_Circle_Struct(VALUE self);

VALUE Get_Klass_Circle();

#endif //SFML_RB_CIRCLE_H
