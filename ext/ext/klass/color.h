#ifndef SFML_RB_COLOR_H
#define SFML_RB_COLOR_H

#include <ruby.h>

#include "ext/sfml.h"

#define VALID_LENGTH_COLOR      4

#define UNPACK_COLOR(c_color) (unsigned char) c_color.r, (unsigned char) c_color.g, (unsigned char) c_color.b, (unsigned char) c_color.a

#define COLOR_C2RB(c_color) color_new(c_color.r, c_color.g, c_color.b, c_color.a)

#define COLOR_RB2C(rb_arr) { NUM2INT(rb_ary_entry(rb_arr, 0)), NUM2INT(rb_ary_entry(rb_arr, 1)), NUM2INT(rb_ary_entry(rb_arr, 2)), NUM2INT(rb_ary_entry(rb_arr, 3)) }

VALUE color_new(int r, int g, int b, int a);

void color_check(VALUE rb_arr);

void color_swap(sfColor *color_a, sfColor *color_b);

sfColor color_new_from_rb(VALUE rb_arr);

VALUE color_new_from_c(sfColor color);

#endif //SFML_RB_COLOR_H
