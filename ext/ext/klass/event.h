#ifndef SFML_RB_EVENT_H
#define SFML_RB_EVENT_H

#include <ruby.h>

void Init_Event(VALUE rb_module);

void *Get_Event_Struct(VALUE self);

VALUE Get_Klass_Event();

#endif //SFML_RB_EVENT_H
