#ifndef SFML_RB_VIDEO_MODE_H
#define SFML_RB_VIDEO_MODE_H

#include <ruby.h>

void Init_VideoMode(VALUE rb_module);

void *Get_Mode_Struct(VALUE self);

VALUE Get_Klass_Mode();

#endif //SFML_RB_VIDEO_MODE_H
