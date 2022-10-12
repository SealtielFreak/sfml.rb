#include "ext/klass/mode.h"

#include <ruby.h>
#include <stdio.h>

#include "ext/sfml.h"
#include "ext/module.h"

static VALUE rb_cMode;

static sfVideoMode *VideoMode_create(unsigned width, unsigned heigth, unsigned bitsPerPixel) {
    sfVideoMode *mode = malloc(sizeof(sfVideoMode));

    mode->width = width;
    mode->height = heigth;
    mode->bitsPerPixel = bitsPerPixel;

    return mode;
}

static void VideoMode_free(void *ptr) {
    free(ptr);
}

static VALUE VideoMode_new(VALUE klass, VALUE rb_width, VALUE rb_height, VALUE rb_bits) {
    VALUE self;
    sfVideoMode *ptr;

    VALUE argv[] = {rb_width, rb_height, rb_bits};

    ptr = VideoMode_create(NUM2INT(rb_width), NUM2INT(rb_height), NUM2INT(rb_bits));
    self = Data_Wrap_Struct(klass, 0, VideoMode_free, ptr);

    rb_obj_call_init(self, 3, argv);

    return self;
}

static VALUE VideoMode_init(VALUE self, VALUE rb_width, VALUE rb_height, VALUE rb_bits) {
    rb_iv_set(self, "@width", rb_width);
    rb_iv_set(self, "@height", rb_height);
    rb_iv_set(self, "@bits", rb_bits);

    return self;
}

static VALUE VideoMode_is_available(VALUE self) {
    sfVideoMode *ptr = Get_Mode_Struct(self);

    if (sfVideoMode_isValid(*ptr)) {
        return Qtrue;
    }

    return Qfalse;
}

void Init_Mode(VALUE rb_module) {
    rb_cMode = rb_define_class_under(rb_module, "Mode", rb_cObject);

    rb_define_singleton_method(rb_cMode, "new", VideoMode_new, 3);

    // methods
    rb_define_method(rb_cMode, "initialize", VideoMode_init, 3);
    rb_define_method(rb_cMode, "available?", VideoMode_is_available, 0);
}

void *Get_Mode_Struct(VALUE self) {
    sfVideoMode *ptr;
    Data_Get_Struct(self, sfVideoMode, ptr);
    return ptr;
}

VALUE Get_Klass_Mode() {
    return rb_cMode;
}