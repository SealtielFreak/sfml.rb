#ifndef CANDY2D_EXT_EVENT_H
#define CANDY2D_EXT_EVENT_H

#include <ruby.h>

void Init_Event(VALUE rb_module);

void *Get_Event_Struct(VALUE self);

VALUE Get_Klass_Event();

#endif //CANDY2D_EXT_EVENT_H
