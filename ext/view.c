#include "ext/klass/view.h"

#include <stdio.h>

#include "ext/module/transform.h"
#include "ext/klass/transformable.h"
#include "ext/klass/color.h"
#include "ext/vec2.h"
#include "ext/rect.h"
#include "ext/module.h"
#include "ext/sfml.h"

static VALUE rb_cView;

static sfView *View_create() {
    return sfView_create();
}

static void View_free(void *ptr) {
    sfView_destroy(ptr);
}

static VALUE View_new_from(VALUE klass, sfView *c_view) {
    VALUE self;
    sfView *view;

    if (c_view != NULL) {
        view = c_view;
    } else {
        view = View_create();
    }

    self = Data_Wrap_Struct(klass, 0, View_free, view);

    rb_obj_call_init(self, 0, NULL);

    return self;
}

static VALUE View_new(VALUE klass) {
    return View_new_from(klass, NULL);
}

static VALUE View_init(VALUE self) {
    return self;
}

static VALUE View_set_position(VALUE self, VALUE rb_position) {
    sfView *view = Get_View_Struct(self);
    sfVector2f position = VEC2_RB2C(rb_position);
    sfVector2f size = sfView_getSize(view);

    sfFloatRect rect = {position.x, position.y, size.x, size.y};

    sfView_setViewport(Get_View_Struct(self), rect);

    return self;
}


static VALUE View_set_rotation(VALUE self, VALUE rb_rotation) {
    sfView_setRotation(Get_View_Struct(self), NUM2DBL(rb_rotation));
    return self;
}


static VALUE View_set_size(VALUE self, VALUE rb_scale) {
    sfView_setSize(Get_View_Struct(self), vec2f_new_from_ruby(rb_scale));
    return self;
}


static VALUE View_set_center(VALUE self, VALUE rb_origin) {
    sfVector2f origin = VEC2_RB2C(rb_origin);
    sfView_setCenter(Get_View_Struct(self), origin);
    return self;
}

static VALUE View_set_viewport(VALUE self, VALUE rb_viewport) {
    sfFloatRect viewport = RECT_RB2C(rb_viewport);
    sfView_setViewport(Get_View_Struct(self), viewport);

    return self;
}

static VALUE View_get_position(VALUE self) {
    sfFloatRect viewport = sfView_getViewport(Get_View_Struct(self));
    return vec2_new(viewport.top, viewport.left);
}


static VALUE View_get_rotation(VALUE self) {
    DBL2NUM(sfView_getRotation(Get_View_Struct(self)));
}


static VALUE View_get_size(VALUE self) {
    return vec2f_new_from_c(sfView_getSize(Get_View_Struct(self)));
}


static VALUE View_get_center(VALUE self) {
    return vec2f_new_from_c(sfView_getCenter(Get_View_Struct(self)));
}

static VALUE View_get_viewport(VALUE self) {
    return RECT_C2RB(sfView_getViewport(Get_View_Struct(self)));
}

static VALUE View_move(VALUE self, VALUE rb_move) {
    sfView_move(Get_View_Struct(self), vec2f_new_from_ruby(rb_move));
    return self;
}

static VALUE View_rotate(VALUE self, VALUE rb_angle) {
    sfView_rotate(Get_View_Struct(self), NUM2DBL(rb_angle));

    return self;
}

static VALUE View_zoom(VALUE self, VALUE rb_zoom) {
    sfView_zoom(Get_View_Struct(self), NUM2DBL(rb_zoom));

    return self;
}

static VALUE View_copy(VALUE self) {
    return Get_Casting_View(sfView_copy(Get_View_Struct(self)));
}

void Init_View(VALUE rb_module) {
    rb_cView = rb_define_class_under(rb_module, "View", rb_cObject);

    rb_define_singleton_method(rb_cView, "new", View_new, 0);

    // methods
    rb_define_method(rb_cView, "initialize", View_init, 0);
    rb_define_method(rb_cView, "move", View_move, 1);
    rb_define_method(rb_cView, "rotate", View_rotate, 1);
    rb_define_method(rb_cView, "zoom", View_zoom, 1);
    rb_define_method(rb_cView, "copy", View_copy, 0);

    // setters
    rb_define_method(rb_cView, "position=", View_set_position, 1);
    rb_define_method(rb_cView, "angle=", View_set_rotation, 1);
    rb_define_method(rb_cView, "size=", View_set_size, 1);
    rb_define_method(rb_cView, "center=", View_set_center, 1);
    rb_define_method(rb_cView, "viewport=", View_set_viewport, 1);

    // getters
    rb_define_method(rb_cView, "position", View_get_position, 0);
    rb_define_method(rb_cView, "angle", View_get_rotation, 0);
    rb_define_method(rb_cView, "size", View_get_size, 0);
    rb_define_method(rb_cView, "center", View_get_center, 0);
    rb_define_method(rb_cView, "viewport", View_get_viewport, 0);
}

void *Get_View_Struct(VALUE self) {
    sfView *ptr;
    Data_Get_Struct(self, sfView, ptr);
    return ptr;
}

VALUE Get_Klass_View() {
    return rb_cView;
}

VALUE Get_Casting_View(void *ptr) {
    return View_new_from(Get_Klass_View(), ptr);
}