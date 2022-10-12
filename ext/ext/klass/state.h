#ifndef CANDY2D_EXT_STATE_H
#define CANDY2D_EXT_STATE_H

#include <ruby.h>

#define DefaultMatrix3x3() {1, 0, 0, 0, 1, 0, 0, 0, 1}

void Init_State(VALUE rb_module);

void *Get_State_Struct(VALUE self);

VALUE Get_Klass_State(void);

VALUE Get_New_State(void);

#endif //CANDY2D_EXT_STATE_H
