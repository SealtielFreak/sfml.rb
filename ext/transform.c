#include "ext/module/transform.h"

#include <ruby.h>
#include <stdio.h>

#include "ext/vec2.h"
#include "ext/rect.h"
#include "ext/module.h"
#include "ext/sfml.h"


static VALUE rb_mTransform;

VALUE Transform_combine(VALUE self, VALUE rb_arr_a, VALUE rb_arr_b) {
    sfTransform transform_a, transform_b;
    float matrix_a[MATRIX_LENGTH], matrix_b[MATRIX_LENGTH];

    Transform_ArrayToMatrix(rb_arr_a, matrix_a);
    Transform_ArrayToMatrix(rb_arr_b, matrix_b);

    Transform_SwapMatrix(matrix_a, transform_a.matrix);
    Transform_SwapMatrix(matrix_b, transform_b.matrix);

    sfTransform_combine(&transform_a, &transform_b);

    return Transform_MatrixToArray(transform_a.matrix);
}

VALUE Transform_inverse(VALUE self, VALUE rb_matrix) {
    sfTransform transform;
    float matrix[MATRIX_LENGTH];

    Transform_ArrayToMatrix(rb_matrix, matrix);
    Transform_SwapMatrix(matrix, transform.matrix);

    return Transform_MatrixToArray(sfTransform_getInverse(&transform).matrix);
}

void Init_Transform(VALUE rb_module) {
    rb_mTransform = rb_define_module_under(rb_module, "Transform");

    rb_define_module_function(rb_mTransform, "combine", Transform_combine, 2);
    rb_define_module_function(rb_mTransform, "inverse", Transform_combine, 1);
}

VALUE Transform_MatrixToArray(float *c_matrix) {
    VALUE rb_arr;
    size_t i;

    if (c_matrix == NULL) {
        return Qnil;
    }

    rb_arr = rb_ary_new();

    for (i = 0; i < MATRIX_LENGTH; i++) {
        rb_ary_push(rb_arr, DBL2NUM(c_matrix[i]));
    }

    return rb_arr;
}

void Transform_ArrayToMatrix(VALUE rb_matrix, float *c_matrix) {
    size_t i;

    if (c_matrix == NULL) {
        return;
    }

    if (rb_array_len(rb_matrix) != MATRIX_LENGTH) {
        return;
    }

    for (i = 0; i < MATRIX_LENGTH; i++) {
        c_matrix[i] = NUM2DBL(rb_ary_entry(rb_matrix, (long) i));
    }
}

void Transform_SwapMatrix(const float *c_matrix_a, float *c_matrix_b) {
    size_t i;

    if (c_matrix_a == NULL || c_matrix_b == NULL) {
        return;
    }

    for (i = 0; i < MATRIX_LENGTH; i++) {
        c_matrix_b[i] = c_matrix_a[i];
    }
}

sfTransform Transform_ArrayToTransform(VALUE rb_matrix) {
    float c_matrix[MATRIX_LENGTH];
    sfTransform transform;

    Transform_ArrayToMatrix(rb_matrix, c_matrix);
    Transform_SwapMatrix(c_matrix, transform.matrix);

    return transform;
}

VALUE Transform_TransformToArray(sfTransform c_transform) {
    float c_matrix[MATRIX_LENGTH];

    Transform_SwapMatrix(c_transform.matrix, c_matrix);

    return Transform_MatrixToArray(c_matrix);
}
