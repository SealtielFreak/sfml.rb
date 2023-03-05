#ifndef SFML_RB_DISPLAY_H
#define SFML_RB_DISPLAY_H

#include <ruby.h>

void Init_Display(VALUE rb_module);

void *Get_Display_Struct(VALUE self);

VALUE Get_Klass_Display();

#endif //SFML_RB_DISPLAY_H
