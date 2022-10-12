#include "ext/module/drawable/drawable.h"

#include <ruby.h>
#include <stdio.h>

#include "ext/module/transform.h"
#include "ext/klass/transformable.h"
#include "ext/klass/state.h"
#include "ext/klass/target.h"
#include "ext/klass/display.h"
#include <ext/exceptions.h>
#include "ext/vec2.h"
#include "ext/rect.h"
#include "ext/module.h"
#include "ext/sfml.h"

static VALUE rb_mDrawable;

static VALUE Drawable_draw(VALUE self, VALUE rb_target, VALUE rb_state) {
    if (!rb_obj_is_kind_of(rb_target, Get_Klass_Target())) {

    }

    if (!rb_obj_is_kind_of(rb_state, Get_Klass_State())) {

    }

    return Qnil;
}

void Init_Drawable(VALUE rb_module) {
    rb_mDrawable = rb_define_module_under(rb_module, "Drawable");

    rb_define_method(rb_mDrawable, "draw", Drawable_draw, 2);
}

VALUE Get_Module_Drawable() {
    return rb_mDrawable;
}