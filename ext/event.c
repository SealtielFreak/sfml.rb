#include "ext/klass/event.h"

#include <ruby.h>
#include <stdio.h>

#include "ext/klass/event/event_name.h"
#include "ext/klass/keyboard.h"
#include "ext/klass/video_mode.h"
#include "ext/vec2.h"
#include "ext/module.h"
#include "ext/sfml.h"

static VALUE rb_cEvent;

static sfEvent *Event_create() {
    return malloc(sizeof(sfEvent));
}

static void Event_free(void *ptr) {
    free(ptr);
}

static VALUE Event_new(VALUE klass) {
    VALUE self;
    sfEvent *event;

    VALUE argv[] = {};

    event = Event_create();
    self = Data_Wrap_Struct(klass, 0, Event_free, event);

    rb_obj_call_init(self, 0, argv);

    return self;
}

static VALUE Event_init(VALUE self) {
    return self;
}

static VALUE Event_type(VALUE self) {
    sfEvent *event = Get_Event_Struct(self);
    return rb_str_new2(get_event_name(event->type));
}

static VALUE Event_key(VALUE self) {
    VALUE arr;
    VALUE hash;
    sfEvent *event = Get_Event_Struct(self);

    const char *key_name = get_key_event(event->key.code);

    /*
    event->key.system;
    event->key.alt;
    event->key.control;
    event->key.shift;
    */

    arr = rb_ary_new();
    rb_ary_push(arr, rb_str_new2(key_name));
    rb_ary_push(arr, INT2NUM((int) event->key.system));
    rb_ary_push(arr, INT2NUM((int) event->key.alt));
    rb_ary_push(arr, INT2NUM((int) event->key.control));
    rb_ary_push(arr, INT2NUM((int) event->key.shift));

    return arr;
}

static VALUE Event_size(VALUE self) {
    sfEvent *event = Get_Event_Struct(self);

    return vec2_new(event->size.height, event->size.height);
}

static VALUE Event_text(VALUE self) {
    return Qnil;
}

static VALUE Event_mouse_move(VALUE self) {
    return Qnil;
}

static VALUE Event_mouse_button(VALUE self) {
    return Qnil;
}

static VALUE Event_mouse_wheel(VALUE self) {
    return Qnil;
}

static VALUE Event_mouse_wheel_scroll(VALUE self) {
    return Qnil;
}

static VALUE Event_joystick_move(VALUE self) {
    return Qnil;
}

static VALUE Event_joystick_button(VALUE self) {
    return Qnil;
}

static VALUE Event_joystick_connect(VALUE self) {
    return Qnil;
}

static VALUE Event_touch(VALUE self) {
    return Qnil;
}

static VALUE Event_sensor(VALUE self) {
    return Qnil;
}

void Init_Event(VALUE rb_module) {
    rb_cEvent = rb_define_class_under(rb_module, "Event", rb_cObject);

    rb_define_singleton_method(rb_cEvent, "new", Event_new, 0);

    // methods
    rb_define_method(rb_cEvent, "initialize", Event_init, 0);

    // getters
    rb_define_method(rb_cEvent, "type", Event_type, 0);
    rb_define_method(rb_cEvent, "key", Event_key, 0);
    rb_define_method(rb_cEvent, "size", Event_size, 0);
    rb_define_method(rb_cEvent, "text", Event_text, 0);
    rb_define_method(rb_cEvent, "mouse_move", Event_mouse_move, 0);
    rb_define_method(rb_cEvent, "mouse_button", Event_mouse_button, 0);
    rb_define_method(rb_cEvent, "mouse_wheel", Event_mouse_wheel, 0);
    rb_define_method(rb_cEvent, "mouse_wheel_scroll", Event_mouse_wheel_scroll, 0);
    rb_define_method(rb_cEvent, "joystick_move", Event_joystick_move, 0);
    rb_define_method(rb_cEvent, "joystick_button", Event_joystick_button, 0);
    rb_define_method(rb_cEvent, "joystick_connect", Event_joystick_connect, 0);
    rb_define_method(rb_cEvent, "touch", Event_touch, 0);
    rb_define_method(rb_cEvent, "sensor", Event_sensor, 0);
}

void *Get_Event_Struct(VALUE self) {
    sfEvent *ptr;
    Data_Get_Struct(self, sfEvent, ptr);
    return ptr;
}

VALUE Get_Klass_Event() {
    return rb_cEvent;
}