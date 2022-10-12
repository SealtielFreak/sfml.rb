#include "ext/klass/state.h"

#include <ruby.h>
#include <stdio.h>

#include "ext/module/transform.h"
#include "ext/klass/transformable.h"
#include "ext/vec2.h"
#include "ext/rect.h"
#include "ext/module.h"
#include "ext/sfml.h"

static VALUE rb_cRenderState;

static sfRenderStates *RenderStates_create(sfTransform transform) {
    sfRenderStates *states = malloc(sizeof(sfRenderStates));

    states->transform = transform;
    states->blendMode = sfBlendAlpha;
    states->texture = NULL;
    states->shader = NULL;

    return states;
}

static void RenderStates_free(void *ptr) {
    free(ptr);
}

static VALUE RenderStates_new(int argc, VALUE *argv, VALUE klass) {
    float c_matrix[MATRIX_LENGTH] = DefaultMatrix3x3();
    sfRenderStates *states;
    sfTransform transform;
    VALUE self;

    if (argc > 1) {
        rb_raise(rb_eArgError, "invalid number of arguments");
    }

    if (argc == 1) {
        VALUE rb_arr = argv[0];

        if (TYPE(rb_arr) == T_ARRAY) {
            if (rb_array_len(rb_arr) != 9) {
                rb_raise(rb_eArgError, "invalid length array");
            }

            Transform_ArrayToMatrix(rb_arr, c_matrix);
        }
    }

    Transform_SwapMatrix(c_matrix, transform.matrix);

    states = RenderStates_create(transform);
    self = Data_Wrap_Struct(klass, 0, RenderStates_free, states);

    rb_obj_call_init(self, argc, argv);

    return self;
}

static VALUE RenderStates_init(int argc, VALUE *argv, VALUE self) {
    return self;
}

static VALUE RenderStates_set_matrix(VALUE self, VALUE rb_matrix) {
    float c_matrix[MATRIX_LENGTH];
    sfRenderStates *states;

    states = Get_State_Struct(self);

    Transform_ArrayToMatrix(rb_matrix, c_matrix);
    Transform_SwapMatrix(c_matrix, states->transform.matrix);

    return self;
}

static VALUE RenderStates_get_matrix(VALUE self) {
    return Transform_MatrixToArray(((sfRenderStates *) Get_State_Struct(self))->transform.matrix);
}

void Init_State(VALUE rb_module) {
    rb_cRenderState = rb_define_class_under(rb_module, "State", rb_cObject);

    rb_define_singleton_method(rb_cRenderState, "new", RenderStates_new, -1);

    // methods
    rb_define_method(rb_cRenderState, "initialize", RenderStates_init, -1);

    // setters
    rb_define_method(rb_cRenderState, "matrix=", RenderStates_set_matrix, 1);

    // getters
    rb_define_method(rb_cRenderState, "matrix", RenderStates_get_matrix, 0);
}

void *Get_State_Struct(VALUE self) {
    sfRenderStates *states;
    Data_Get_Struct(self, sfRenderStates, states);
    return states;
}

VALUE Get_Klass_State(void) {
    return rb_cRenderState;
}

VALUE Get_New_State(void) {
    return RenderStates_new(0, NULL, Get_Klass_State());
}