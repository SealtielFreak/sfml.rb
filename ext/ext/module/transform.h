#ifndef CANDY2D_EXT_TRANSFORM_H
#define CANDY2D_EXT_TRANSFORM_H

#include <ruby.h>

#include "ext/sfml.h"

#define MATRIX_LENGTH       9   // 3x3

void Init_Transform(VALUE rb_module);

VALUE Transform_MatrixToArray(float *c_matrix);

void Transform_ArrayToMatrix(VALUE rb_matrix, float *c_matrix);

void Transform_SwapMatrix(const float *c_matrix_a, float *c_matrix_b);

#endif //CANDY2D_EXT_TRANSFORM_H
