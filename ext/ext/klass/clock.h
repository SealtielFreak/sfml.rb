#ifndef CANDY2D_EXT_CLOCK_H
#define CANDY2D_EXT_CLOCK_H

#include <ruby.h>

void Init_Clock(VALUE rb_module);

void *Get_Clock_Struct(VALUE self);

VALUE Get_Klass_Clock();

#endif //CANDY2D_EXT_CLOCK_H
