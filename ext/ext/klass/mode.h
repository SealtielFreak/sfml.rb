#ifndef CANDY2D_EXT_MODE_H
#define CANDY2D_EXT_MODE_H

#include <ruby.h>

void Init_Mode(VALUE rb_module);

void *Get_Mode_Struct(VALUE self);

VALUE Get_Klass_Mode();

#endif //CANDY2D_EXT_MODE_H
