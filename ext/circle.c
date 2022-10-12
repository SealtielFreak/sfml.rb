#include "ext/klass/drawable/circle.h"

#include <stdio.h>

#include "ext/module/drawable/drawable.h"
#include "ext/klass/target.h"
#include "ext/klass/state.h"
#include "ext/exceptions.h"
#include "ext/module/transform.h"
#include "ext/klass/transformable.h"
#include "ext/klass/color.h"
#include "ext/vec2.h"
#include "ext/rect.h"
#include "ext/module.h"
#include "ext/sfml.h"


static VALUE rb_cCircle;

static sfCircleShape *Circle_create(float r) {
    sfCircleShape *circle = sfCircleShape_create();

    sfCircleShape_setRadius(circle, r);

    return circle;
}

static void Circle_free(void *ptr) {
    sfCircleShape_destroy(ptr);
    free(ptr);
}

static VALUE Circle_new(int argc, VALUE *argv, VALUE klass) {
    sfCircleShape *circle;
    float radius;
    VALUE self;

    if (argc > 1) {
        raise_invalid_arguments_excepted(1, argc);
    }

    radius = 0;

    if (argc == 1) {
        radius = NUM2DBL(argv[0]);
    }

    circle = Circle_create(radius);

    self = Data_Wrap_Struct(klass, 0, Circle_free, circle);

    rb_obj_call_init(self, argc, argv);

    return self;
}

static VALUE Circle_init(int argc, VALUE *argv, VALUE self) {
    return self;
}

static VALUE Circle_set_fill_color(VALUE self, VALUE rb_color) {
    color_check(rb_color);

    sfCircleShape_setFillColor(Get_Circle_Struct(self), color_new_from_rb(rb_color));

    return self;
}

static VALUE Circle_get_fill_color(VALUE self) {
    sfColor color = sfCircleShape_getFillColor(Get_Circle_Struct(self));

    return color_new_from_c(color);
}

static VALUE Circle_set_radius(VALUE self, VALUE rb_radius) {
    sfCircleShape_setRadius(Get_Circle_Struct(self), NUM2DBL(rb_radius));

    return self;
}

static VALUE Circle_set_position(VALUE self, VALUE rb_position) {
    sfCircleShape_setPosition(Get_Circle_Struct(self), vec2f_new_from_ruby(rb_position));

    return self;
}

static VALUE Circle_set_rotation(VALUE self, VALUE rb_angle) {
    sfCircleShape_setRotation(Get_Circle_Struct(self), NUM2DBL(rb_angle));

    return self;
}

static VALUE Circle_set_origin(VALUE self, VALUE rb_origin) {
    sfCircleShape_setOrigin(Get_Circle_Struct(self), vec2f_new_from_ruby(rb_origin));

    return self;
}

static VALUE Circle_set_scale(VALUE self, VALUE rb_scale) {
    sfCircleShape_setScale(Get_Circle_Struct(self), vec2f_new_from_ruby(rb_scale));

    return self;
}

static VALUE Circle_get_radius(VALUE self) {
    return DBL2NUM(sfCircleShape_getRadius(Get_Circle_Struct(self)));
}

static VALUE Circle_get_position(VALUE self) {
    return vec2f_new_from_c(sfCircleShape_getPosition(Get_Circle_Struct(self)));
}

static VALUE Circle_get_rotation(VALUE self) {
    return DBL2NUM(sfCircleShape_getRotation(Get_Circle_Struct(self)));
}

static VALUE Circle_get_scale(VALUE self) {
    return vec2f_new_from_c(sfCircleShape_getPosition(Get_Circle_Struct(self)));
}

static VALUE Circle_get_origin(VALUE self) {
    return vec2f_new_from_c(sfCircleShape_getOrigin(Get_Circle_Struct(self)));
}

static VALUE Circle_move(VALUE self, VALUE rb_move) {
    sfCircleShape_move(Get_Circle_Struct(self), vec2f_new_from_ruby(rb_move));
    return self;
}

static VALUE Circle_rotate(VALUE self, VALUE rb_angle) {
    sfCircleShape_rotate(Get_Circle_Struct(self), NUM2DBL(rb_angle));
    return self;
}

static VALUE Circle_scale(VALUE self, VALUE rb_scale) {
    sfCircleShape_scale(Get_Circle_Struct(self), vec2f_new_from_ruby(rb_scale));
    return self;
}

static VALUE Circle_get_matrix(VALUE self) {
    return Transform_MatrixToArray(sfCircleShape_getTransform(Get_Circle_Struct(self)).matrix);
}

static VALUE Circle_draw(VALUE self, VALUE rb_target, VALUE rb_state) {
    if (!rb_obj_is_kind_of(rb_target, Get_Klass_Target())) {
        raise_invalid_argument_class(Get_Klass_Target());
    }

    if (!rb_obj_is_kind_of(rb_target, Get_Klass_State())) {
        raise_invalid_argument_class(Get_Klass_State());
    }

    sfRenderWindow_drawCircleShape(((Target *) Get_Target_Struct(rb_target))->window, Get_Circle_Struct(self),
                                   Get_State_Struct(rb_state));
    return Qnil;
}

void Init_Circle(VALUE rb_module) {
    rb_cCircle = rb_define_class_under(rb_module, "Circle", rb_cObject);

    rb_include_module(rb_cCircle, Get_Module_Drawable());

    rb_define_singleton_method(rb_cCircle, "new", Circle_new, -1);

    // methods
    rb_define_method(rb_cCircle, "initialize", Circle_init, -1);
    rb_define_method(rb_cCircle, "move", Circle_move, 1);
    rb_define_method(rb_cCircle, "rotate", Circle_rotate, 1);
    rb_define_method(rb_cCircle, "escalate", Circle_scale, 1);
    rb_define_method(rb_cCircle, "draw", Circle_draw, 2);

    // setters
    rb_define_method(rb_cCircle, "radius=", Circle_set_radius, 1);
    rb_define_method(rb_cCircle, "position=", Circle_set_position, 1);
    rb_define_method(rb_cCircle, "angle=", Circle_set_rotation, 1);
    rb_define_method(rb_cCircle, "scale=", Circle_set_scale, 1);
    rb_define_method(rb_cCircle, "origin=", Circle_set_origin, 1);
    rb_define_method(rb_cCircle, "fill_color=", Circle_set_fill_color, 1);

    // getters
    rb_define_method(rb_cCircle, "radius", Circle_get_radius, 0);
    rb_define_method(rb_cCircle, "position", Circle_get_position, 0);
    rb_define_method(rb_cCircle, "angle", Circle_get_rotation, 0);
    rb_define_method(rb_cCircle, "scale", Circle_get_scale, 0);
    rb_define_method(rb_cCircle, "origin", Circle_get_origin, 0);
    rb_define_method(rb_cCircle, "fill_color", Circle_get_fill_color, 0);
    rb_define_method(rb_cCircle, "matrix", Circle_get_matrix, 0);

}

void *Get_Circle_Struct(VALUE self) {
    sfCircleShape *ptr;
    Data_Get_Struct(self, sfCircleShape, ptr);
    return ptr;
}

VALUE Get_Klass_Circle() {
    return rb_cCircle;
}