#ifndef SFML_RB_CLOCK_H
#define SFML_RB_CLOCK_H

#include <ruby.h>

void Init_Clock(VALUE rb_module);

void *Get_Clock_Struct(VALUE self);

VALUE Get_Klass_Clock();

#endif //SFML_RB_CLOCK_H
