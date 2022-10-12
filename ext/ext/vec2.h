#ifndef CANDY2D_EXT_VEC2_H
#define CANDY2D_EXT_VEC2_H

#include <ruby.h>

#include "ext/sfml.h"

#define UNPACK_VEC2(c_type, c_vec) (c_type) c_vec.x, (c_type) c_vec.y

#define VEC2_C2RB(c_vec) vec2_new((float) c_vec.x, (float) c_vec.y)

#define VEC2_C2RB_T(c_type, c_vec) vec2_new((c_type) c_vec.x, (c_type) c_vec.y)

#define VEC2_RB2C(rb_arr) { NUM2DBL(rb_ary_entry(rb_arr, 0)), NUM2DBL(rb_ary_entry(rb_arr, 1)) }

#define VEC2_RB2C_T(c_type, rb_arr) { (c_type) NUM2DBL(rb_ary_entry(rb_arr, 0)), (c_type) NUM2DBL(rb_ary_entry(rb_arr, 1)) }

#define VEC2_SET_X(rb_arr, x) rb_ary_store(rb_arr, 0, DBL2NUM(x))

#define VEC2_SET_Y(rb_arr, x) rb_ary_store(rb_arr, 1, DBL2NUM(y))

#define VEC2_GET_X(rb_arr) NUM2DBL(rb_ary_entry(rb_arr, 0))

#define VEC2_GET_Y(rb_arr) NUM2DBL(rb_ary_entry(rb_arr, 1))

VALUE vec2_new(float x, float y);

void vec2_check(VALUE rb_arr);

VALUE vec2f_new_from_c(sfVector2f c_vec);

sfVector2i vec2i_new_from_ruby(VALUE rb_arr);

sfVector2u vec2u_new_from_ruby(VALUE rb_arr);

sfVector2f vec2f_new_from_ruby(VALUE rb_arr);

#endif //CANDY2D_EXT_VEC2_H
