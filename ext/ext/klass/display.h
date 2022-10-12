#ifndef CANDY2D_EXT_DISPLAY_H
#define CANDY2D_EXT_DISPLAY_H

#include <ruby.h>

void Init_Display(VALUE rb_module);

void *Get_Display_Struct(VALUE self);

VALUE Get_Klass_Display();

#endif //CANDY2D_EXT_DISPLAY_H
