#ifndef MODULE_H
#define MODULE_H

#include <ruby.h>

#define BOOL2RB(value) value? Qtrue: Qfalse

static VALUE rb_mExt;

#endif //MODULE_H
