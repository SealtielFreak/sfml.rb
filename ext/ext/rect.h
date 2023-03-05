#ifndef SFML_RB_EXT_RECT_H
#define SFML_RB_EXT_RECT_H

#include <ruby.h>

#define RECT_UNPACK(c_rect) c_rect.width, c_rect.height, c_rect.top, c_rect.left

#define RECT_C2RB(c_rect) Rect_new(RECT_UNPACK(c_rect))

#define RECT_RB2C(rb_arr) { NUM2DBL(rb_ary_entry(rb_arr, 0)), NUM2DBL(rb_ary_entry(rb_arr, 1)), NUM2DBL(rb_ary_entry(rb_arr, 2)), NUM2DBL(rb_ary_entry(rb_arr, 3)) }

VALUE Rect_new(float width, float height, float top, float bottom);

void Rect_check(VALUE rb_arr);

#endif //SFML_RB_EXT_RECT_H
