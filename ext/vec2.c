#include "ext/vec2.h"

#include <stdio.h>
#include <stdlib.h>

#include "ext/exceptions.h"

VALUE vec2_new(float x, float y) {
    VALUE rb_vec;

    rb_vec = rb_ary_new();

    rb_ary_store(rb_vec, 0, DBL2NUM(x));
    rb_ary_store(rb_vec, 1, DBL2NUM(y));

    return rb_vec;
}

void vec2_check(VALUE rb_arr) {
    if (rb_array_len(rb_arr) != 2) {
        raise_invalid_argument_class(rb_cArray);
    }
}

VALUE vec2f_new_from_c(sfVector2f c_vec) {
    return  VEC2_C2RB(c_vec);
}

sfVector2i vec2i_new_from_ruby(VALUE rb_arr) {
    sfVector2i vec = VEC2_RB2C_T(int, rb_arr);
    return vec;
}

sfVector2u vec2u_new_from_ruby(VALUE rb_arr) {
    sfVector2u vec = VEC2_RB2C_T(unsigned, rb_arr);
    return vec;
}

sfVector2f vec2f_new_from_ruby(VALUE rb_arr) {
    sfVector2f vec = VEC2_RB2C_T(float, rb_arr);
    return vec;
}