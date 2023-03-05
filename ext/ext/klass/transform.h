#ifndef SFML_RB_TRANSFORM_H
#define SFML_RB_TRANSFORM_H

#include <ruby.h>

#define MATRIX_LENGTH       9   // 3x3
#define MATRIX_GL_LENGTH    16  // 4x4

static VALUE rb_cTransform;

void Init_Transform(VALUE rb_module);

void *Get_Transform_Struct(VALUE self);

VALUE To_Transform_Struct(void *ptr);

#endif //SFML_RB_TRANSFORM_H
