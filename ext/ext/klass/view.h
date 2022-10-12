#ifndef CANDY2D_EXT_VIEW_H
#define CANDY2D_EXT_VIEW_H

#include <ruby.h>

void Init_View(VALUE rb_module);

void *Get_View_Struct(VALUE self);

VALUE Get_Klass_View();

VALUE Get_Casting_View(void *ptr);

#endif //CANDY2D_EXT_VIEW_H
