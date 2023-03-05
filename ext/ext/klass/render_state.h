#ifndef SFML_RB_RENDER_STATE_H
#define SFML_RB_RENDER_STATE_H

#include <ruby.h>

#define DefaultMatrix3x3() {1, 0, 0, 0, 1, 0, 0, 0, 1}

void Init_RenderState(VALUE rb_module);

void *Get_RenderState_Struct(VALUE self);

VALUE Get_Klass_RenderState(void);

VALUE Get_New_RenderState(void);

#endif //SFML_RB_RENDER_STATE_H
