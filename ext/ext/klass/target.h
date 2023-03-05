#ifndef SFML_RB_TARGET_H
#define SFML_RB_TARGET_H

#include <ruby.h>

typedef struct {
    void *window;
} Target;

void Init_Target(VALUE rb_module);

VALUE Get_Klass_Target(void);

void *Get_Target_Struct(VALUE self);

VALUE Get_New_Target(VALUE rb_window);

#endif //SFML_RB_TARGET_H
