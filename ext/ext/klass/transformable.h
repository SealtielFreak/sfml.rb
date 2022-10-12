#ifndef CANDY2D_EXT_TRANSFORMABLE_H
#define CANDY2D_EXT_TRANSFORMABLE_H

#include <ruby.h>

void Init_Transformable(VALUE rb_module);

void *Get_Transformable_Struct(VALUE self);


VALUE Get_Klass_Transformable();

#endif //CANDY2D_EXT_TRANSFORMABLE_H
