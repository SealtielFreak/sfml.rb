#include "ext/klass/display.h"

#include <stdio.h>

#include "ext/klass/state.h"
#include "ext/module/drawable/drawable.h"
#include "ext/klass/drawable/circle.h"
#include "ext/klass/target.h"
#include "ext/klass/view.h"
#include "ext/klass/mode.h"
#include "ext/klass/event.h"
#include "ext/klass/color.h"
#include "ext/exceptions.h"
#include "ext/style_name.h"
#include "ext/vec2.h"
#include "ext/module.h"
#include "ext/sfml.h"

static VALUE rb_cDisplay;

static sfRenderWindow *Window_create(sfVideoMode *mode, const char *title) {
    return sfRenderWindow_create(*mode, title, sfDefaultStyle, NULL);
}

static void Window_free(void *ptr) {
    sfRenderWindow_destroy((sfRenderWindow *) ptr);
    free(ptr);
}

static VALUE Window_new(int argc, VALUE *argv, VALUE klass) {
    VALUE self, rb_video_mode, rb_title;
    sfRenderWindow *window;

    if (argc > 2) {
        raise_invalid_arguments_excepted(2, argc);
    }

    rb_video_mode = argv[0];
    rb_title = argv[1];

    if (!rb_obj_is_kind_of(rb_video_mode, Get_Klass_Mode())) {
        raise_invalid_argument_class(Get_Klass_Mode());
        rb_raise(rb_eArgError, "wrong object, expected a VideoMode");
    }

    window = Window_create(Get_Mode_Struct(rb_video_mode), RSTRING_PTR(rb_title));
    self = Data_Wrap_Struct(klass, 0, Window_free, window);

    rb_obj_call_init(self, argc, argv);

    return self;
}

static VALUE Window_init(int argc, VALUE *argv, VALUE self) {
    return self;
}

static VALUE Window_is_open(VALUE self) {
    return BOOL2RB(sfRenderWindow_isOpen(Get_Display_Struct(self)));
}

static VALUE Window_close(VALUE self) {
    sfRenderWindow_close(Get_Display_Struct(self));
    return self;
}

static VALUE Window_clear(int argc, VALUE *argv, VALUE self) {
    sfColor color = sfBlack;
    VALUE rb_color;

    if (argc != 3 && argc != 0) {
        raise_invalid_arguments_excepted(argc, 3);
    }

    if (argc == 3) {
        rb_color = rb_ary_new();

        rb_ary_push(rb_color, argv[0]);
        rb_ary_push(rb_color, argv[1]);
        rb_ary_push(rb_color, argv[2]);

        color = color_new_from_rb(rb_color);
    }

    sfRenderWindow_clear(Get_Display_Struct(self), color);

    return self;
}

static VALUE Window_display(VALUE self) {
    sfRenderWindow_display(Get_Display_Struct(self));
    return self;
}

static VALUE Window_poll_event(VALUE self, VALUE rb_event) {
    if (!rb_obj_is_kind_of(rb_event, Get_Klass_Event())) {
        raise_invalid_argument_class(Get_Klass_Event());
    }

    return BOOL2RB(sfRenderWindow_pollEvent(Get_Display_Struct(self), Get_Event_Struct(rb_event)));
}

static VALUE Window_wait_event(VALUE self, VALUE rb_event) {
    if (!rb_obj_is_kind_of(rb_event, Get_Klass_Event())) {
        raise_invalid_argument_class(Get_Klass_Event());
    }

    return BOOL2RB(sfRenderWindow_waitEvent(Get_Display_Struct(self), Get_Event_Struct(rb_event)));
}

static VALUE Window_get_position(VALUE self) {
    return VEC2_C2RB(sfRenderWindow_getPosition(Get_Display_Struct(self)));
}

static VALUE Window_set_position(VALUE self, VALUE rb_arr) {
    sfRenderWindow_setPosition(Get_Display_Struct(self), vec2i_new_from_ruby(rb_arr));
    return self;
}

static VALUE Window_set_frame_rate(VALUE self, VALUE rb_limit) {
    sfRenderWindow_setFramerateLimit(Get_Display_Struct(self), NUM2INT(rb_limit));
    return self;
}

static VALUE Window_set_size(VALUE self, VALUE rb_size) {
    sfRenderWindow_setSize(Get_Display_Struct(self), vec2u_new_from_ruby(rb_size));
    return self;
}

static VALUE Window_set_title(VALUE self, VALUE rb_title) {
    sfRenderWindow_setTitle(Get_Display_Struct(self), RSTRING_PTR(rb_title));
    return self;
}

static VALUE Window_set_icon(VALUE self, VALUE rb_icon) {
    return self;
}

static VALUE Window_set_visible(VALUE self, VALUE rb_visible) {
    sfRenderWindow_setVisible(Get_Display_Struct(self), RTEST(rb_visible));
    return self;

}

static VALUE Window_set_vertical_sync_enabled(VALUE self, VALUE rb_enable) {
    sfRenderWindow_setVerticalSyncEnabled(Get_Display_Struct(self), RTEST(rb_enable));
    return self;
}

static VALUE Window_set_mouse_cursor_visible(VALUE self, VALUE rb_visible) {
    sfRenderWindow_setMouseCursorVisible(Get_Display_Struct(self), RTEST(rb_visible));
    return self;
}

static VALUE Window_set_mouse_cursor_grabbed(VALUE self, VALUE rb_grabbed) {
    sfRenderWindow_setMouseCursorGrabbed(Get_Display_Struct(self), RTEST(rb_grabbed));
    return self;
}

static VALUE Window_set_mouse_cursor(VALUE self, VALUE rb_cursor) {
    raise_method_no_implemented(NULL);
    return self;
}

static VALUE Window_set_key_repeat_enabled(VALUE self, VALUE rb_enabled) {
    sfRenderWindow_setKeyRepeatEnabled(Get_Display_Struct(self), RTEST(rb_enabled));
    return self;
}

static VALUE Window_set_joystick_threshold(VALUE self, VALUE rb_threshold) {
    sfRenderWindow_setJoystickThreshold(Get_Display_Struct(self), RTEST(rb_threshold));
    return self;
}

static VALUE Window_request_focus(VALUE self) {
    sfRenderWindow_requestFocus(Get_Display_Struct(self));
    return self;
}


static VALUE Window_has_focus(VALUE self) {
    return BOOL2RB(sfRenderWindow_hasFocus(Get_Display_Struct(self)));
}

static VALUE Window_draw(int argc, VALUE *argv, VALUE self) {
    VALUE rb_drawable;
    sfRenderStates *states;
    sfRenderWindow *window;

    if (argc == 0 || argc > 2) {
        raise_invalid_arguments_excepted(-1, argc);
    }

    rb_drawable = argv[0];
    window = Get_Display_Struct(self);
    states = NULL;

    if (argc == 2) {
        VALUE rb_state = argv[1];

        if (rb_obj_is_kind_of(rb_state, Get_Klass_State())) {
            states = Get_State_Struct(rb_state);
        } else {
            raise_invalid_argument_class(Get_Klass_State());
        }
    }

    if (rb_obj_is_kind_of(rb_drawable, Get_Klass_Circle())) {
        sfRenderWindow_drawCircleShape(window, Get_Circle_Struct(rb_drawable), states);
    } else {
        rb_funcall(rb_drawable, rb_intern("draw"), 2, Get_New_Target(self), Get_New_State());
    }

    return self;
}

static VALUE Window_set_view(VALUE self, VALUE rb_view) {
    if (!rb_obj_is_kind_of(rb_view, Get_Klass_View())) {
        rb_raise(rb_eArgError, "invalid object, expected a View object");
    }

    sfRenderWindow_setView(Get_Display_Struct(self), Get_View_Struct(rb_view));

    return self;
}

static VALUE Window_get_view(VALUE self) {
    return Get_Casting_View(sfView_copy(sfRenderWindow_getView(Get_Display_Struct(self))));
}

static VALUE Window_get_default_view(VALUE self) {
    return Get_Casting_View(sfView_copy((sfRenderWindow_getDefaultView(Get_Display_Struct(self)))));
}

void Init_Display(VALUE rb_module) {
    rb_cDisplay = rb_define_class_under(rb_module, "Display", rb_cObject);

    rb_define_singleton_method(rb_cDisplay, "new", Window_new, -1);

    // methods
    rb_define_method(rb_cDisplay, "initialize", Window_init, -1);
    rb_define_method(rb_cDisplay, "is_open?", Window_is_open, 0);
    rb_define_method(rb_cDisplay, "close!", Window_close, 0);
    rb_define_method(rb_cDisplay, "clear", Window_clear, -1);
    rb_define_method(rb_cDisplay, "display", Window_display, 0);
    rb_define_method(rb_cDisplay, "poll_event!", Window_poll_event, 1);
    rb_define_method(rb_cDisplay, "wait_event!", Window_wait_event, 1);

    // setters
    rb_define_method(rb_cDisplay, "frame_rate=", Window_set_frame_rate, 1);
    rb_define_method(rb_cDisplay, "size=", Window_set_size, 1);
    rb_define_method(rb_cDisplay, "title=", Window_set_title, 1);
    rb_define_method(rb_cDisplay, "icon=", Window_set_icon, 1);
    rb_define_method(rb_cDisplay, "visible=", Window_set_visible, 1);
    rb_define_method(rb_cDisplay, "vertical_sync_enabled=", Window_set_vertical_sync_enabled, 1);
    rb_define_method(rb_cDisplay, "cursor_visible=", Window_set_mouse_cursor_visible, 1);
    rb_define_method(rb_cDisplay, "cursor_grabbed=", Window_set_mouse_cursor_grabbed, 1);
    rb_define_method(rb_cDisplay, "mouse_cursor=", Window_set_mouse_cursor, 1);
    rb_define_method(rb_cDisplay, "key_repeat_enabled=", Window_set_key_repeat_enabled, 1);
    rb_define_method(rb_cDisplay, "joystick_threshold=", Window_set_joystick_threshold, 1);
    rb_define_method(rb_cDisplay, "position=", Window_set_position, 1);
    //rb_define_method(rb_cDisplay, "view=", Window_set_view, 1);

    // getters
    rb_define_method(rb_cDisplay, "request_focus", Window_request_focus, 0);
    rb_define_method(rb_cDisplay, "focus?", Window_has_focus, 0);
    rb_define_method(rb_cDisplay, "draw", Window_draw, -1);
    rb_define_method(rb_cDisplay, "position", Window_get_position, 0);
    //rb_define_method(rb_cDisplay, "view", Window_get_view, 0);
    //rb_define_method(rb_cDisplay, "default_view", Window_get_default_view, 0);
}

void *Get_Display_Struct(VALUE self) {
    sfRenderWindow *ptr;
    Data_Get_Struct(self, sfRenderWindow, ptr);
    return ptr;
}

VALUE Get_Klass_Display() {
    return rb_cDisplay;
}