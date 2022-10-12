#ifndef CANDY2D_EXT_CIRCLE_H
#define CANDY2D_EXT_CIRCLE_H

#include <ruby.h>

void Init_Circle(VALUE rb_module);

void *Get_Circle_Struct(VALUE self);

VALUE Get_Klass_Circle();

#endif //CANDY2D_EXT_CIRCLE_H
