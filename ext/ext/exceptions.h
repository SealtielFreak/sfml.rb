#ifndef CANDY2D_EXT_EXCEPTIONS_H
#define CANDY2D_EXT_EXCEPTIONS_H

#include <ruby.h>

void raise_invalid_argument_type(const char* type);

void raise_invalid_argument_class(VALUE rb_cKlass);

void raise_invalid_arguments_excepted(int expected, size_t given);

void raise_invalid_array_length(size_t length);

void raise_method_no_implemented(const char *method);

#endif //CANDY2D_EXT_EXCEPTIONS_H
