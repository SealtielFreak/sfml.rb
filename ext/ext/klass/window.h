#ifndef SFML_RB_WINDOW_H
#define SFML_RB_WINDOW_H

#include <ruby.h>

void Init_Window(VALUE rb_module);

void *Get_Window_Struct(VALUE self);

VALUE Get_Klass_Window();

#endif //SFML_RB_WINDOW_H
