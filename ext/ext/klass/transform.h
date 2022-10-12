#ifndef CANDY2D_EXT_TRANSFORM_H
#define CANDY2D_EXT_TRANSFORM_H

#include <ruby.h>

#define MATRIX_LENGTH       9   // 3x3
#define MATRIX_GL_LENGTH    16  // 4x4

static VALUE rb_cTransform;

void Init_Transform(VALUE rb_module);

void *Get_Transform_Struct(VALUE self);

VALUE To_Transform_Struct(void *ptr);

#endif //CANDY2D_EXT_TRANSFORM_H
