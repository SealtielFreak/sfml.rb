#include "ext/klass/color.h"

#include <ruby.h>
#include <stdio.h>

#include "ext/exceptions.h"

VALUE color_new(int r, int g, int b, int a) {
    VALUE rb_arr;

    rb_arr = rb_ary_new();

    rb_ary_push(rb_arr, INT2NUM(r));
    rb_ary_push(rb_arr, INT2NUM(g));
    rb_ary_push(rb_arr, INT2NUM(b));
    rb_ary_push(rb_arr, INT2NUM(a));

    return rb_arr;
}

void color_check(VALUE rb_arr) {
    if (rb_array_len(rb_arr) != VALID_LENGTH_COLOR) {
        raise_invalid_array_length(VALID_LENGTH_COLOR);
    }
}

void color_swap(sfColor *color_a, sfColor *color_b) {
    sfColor c;

    c = *color_b;
    *color_b = *color_a;
    *color_a = c;
}

sfColor color_new_from_rb(VALUE rb_arr) {
    sfColor color = COLOR_RB2C(rb_arr);

    return color;
}

VALUE color_new_from_c(sfColor color) {
    return COLOR_C2RB(color);
}