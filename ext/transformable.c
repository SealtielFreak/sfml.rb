#include "ext/klass/transformable.h"

#include <ruby.h>
#include <stdio.h>

#include "ext/module/transform.h"
#include "ext/vec2.h"
#include "ext/rect.h"
#include "ext/module.h"
#include "ext/sfml.h"

static VALUE rb_cTransformable;

static sfTransformable *Transformable_create() {
    return sfTransformable_create();
}

static void Transformable_free(void *ptr) {
    sfTransformable_destroy((sfTransformable *) ptr);
    free(ptr);
}

static VALUE Transformable_new(VALUE klass) {
    VALUE self;
    sfTransformable *transformable;

    transformable = Transformable_create();
    self = Data_Wrap_Struct(klass, 0, Transformable_free, transformable);

    rb_obj_call_init(self, 0, NULL);

    return self;
}

static VALUE Transformable_init(VALUE self) {
    return self;
}

static VALUE Transformable_set_position(VALUE self, VALUE rb_position) {
    sfVector2f position = VEC2_RB2C(rb_position);
    sfTransformable_setPosition(Get_Transformable_Struct(self), position);

    return self;
}

static VALUE Transformable_set_rotation(VALUE self, VALUE rb_angle) {
    sfTransformable_setRotation(Get_Transformable_Struct(self), NUM2DBL(rb_angle));

    return self;
}

static VALUE Transformable_set_scale(VALUE self, VALUE rb_scale) {
    sfVector2f scale = VEC2_RB2C(rb_scale);
    sfTransformable_setScale(Get_Transformable_Struct(self), scale);

    return self;
}

static VALUE Transformable_set_origin(VALUE self, VALUE rb_origin) {
    sfVector2f origin = VEC2_RB2C(rb_origin);
    sfTransformable_setOrigin(Get_Transformable_Struct(self), origin);

    return self;
}

static VALUE Transformable_get_position(VALUE self) {
    sfVector2f position = sfTransformable_getPosition(Get_Transformable_Struct(self));

    return VEC2_C2RB(position);
}

static VALUE Transformable_get_rotation(VALUE self) {
    return DBL2NUM(sfTransformable_getRotation(Get_Transformable_Struct(self)));
}

static VALUE Transformable_get_scale(VALUE self) {
    sfVector2f scale = sfTransformable_getScale(Get_Transformable_Struct(self));

    return VEC2_C2RB(scale);
}

static VALUE Transformable_get_origin(VALUE self) {
    sfVector2f origin = sfTransformable_getOrigin(Get_Transformable_Struct(self));

    return VEC2_C2RB(origin);
}

static VALUE Transformable_move(VALUE self, VALUE rb_move) {
    sfVector2f move = VEC2_RB2C(rb_move);
    sfTransformable_move(Get_Transformable_Struct(self), move);

    return self;
}

static VALUE Transformable_rotate(VALUE self, VALUE rb_angle) {
    sfTransformable_rotate(Get_Transformable_Struct(self), NUM2DBL(rb_angle));

    return self;
}

static VALUE Transformable_scale(VALUE self, VALUE rb_scale) {
    sfVector2f scale = VEC2_RB2C(rb_scale);
    sfTransformable_scale(Get_Transformable_Struct(self), scale);

    return self;
}

static VALUE Transformable_get_matrix(VALUE self) {
    sfTransformable *transformable = Get_Transformable_Struct(self);
    sfTransform transform = sfTransformable_getTransform(transformable);

    return Transform_MatrixToArray(transform.matrix);
}

void Init_Transformable(VALUE rb_module) {
    rb_cTransformable = rb_define_class_under(rb_module, "Transformable", rb_cObject);

    rb_define_singleton_method(rb_cTransformable, "new", Transformable_new, 0);
    rb_define_method(rb_cTransformable, "initialize", Transformable_init, 0);

    rb_define_method(rb_cTransformable, "position=", Transformable_set_position, 1);
    rb_define_method(rb_cTransformable, "angle=", Transformable_set_rotation, 1);
    rb_define_method(rb_cTransformable, "scale=", Transformable_set_scale, 1);
    rb_define_method(rb_cTransformable, "origin=", Transformable_set_origin, 1);

    rb_define_method(rb_cTransformable, "position", Transformable_get_position, 0);
    rb_define_method(rb_cTransformable, "angle", Transformable_get_rotation, 0);
    rb_define_method(rb_cTransformable, "scale", Transformable_get_scale, 0);
    rb_define_method(rb_cTransformable, "origin", Transformable_get_origin, 0);

    rb_define_method(rb_cTransformable, "move", Transformable_move, 1);
    rb_define_method(rb_cTransformable, "rotate", Transformable_rotate, 1);
    rb_define_method(rb_cTransformable, "escalate", Transformable_scale, 1);

    rb_define_method(rb_cTransformable, "matrix", Transformable_get_matrix, 0);
}

void *Get_Transformable_Struct(VALUE self) {
    sfTransformable *transform;
    Data_Get_Struct(self, sfTransformable, transform);
    return transform;
}

VALUE Get_Klass_Transformable() {
    return rb_cTransformable;
}