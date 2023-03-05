#include <ruby.h>
#include <stdio.h>

#include "ext/module.h"
#include "ext/module/transform.h"
#include "ext/module/drawable/drawable.h"
#include "ext/klass/color.h"
#include "ext/klass/transformable.h"
#include <ext/klass/clock.h>
#include <ext/klass/target.h>
#include "ext/klass/state.h"
#include "ext/klass/event.h"
#include "ext/klass/window.h"
#include "ext/klass/view.h"
#include "ext/klass/video_mode.h"
#include "ext/klass/drawable/circle.h"


//  C Naming Convention:
//
//    Struct              TitleCase
//    Struct Members      lower_case or lowerCase
//
//    Enum                ETitleCase
//    Enum Members        ALL_CAPS or lowerCase
//
//    Public functions    pfx_TitleCase (pfx = two or three letter module prefix)
//    Private functions   TitleCase
//    Trivial variables   i,x,n,f etc...
//    Local variables     lower_case or lowerCase
//    Global variables    g_lowerCase or g_lower_case (searchable by g_ prefix)

void Init_ext(void) {
    rb_mExt = rb_define_module("SFML");

    Init_Drawable(rb_mExt);
    Init_Transform(rb_mExt);
    Init_Transformable(rb_mExt);
    Init_Clock(rb_mExt);
    Init_Target(rb_mExt);
    Init_State(rb_mExt);
    Init_Circle(rb_mExt);
    Init_Event(rb_mExt);
    Init_VideoMode(rb_mExt);
    Init_View(rb_mExt);
    Init_Window(rb_mExt);
}
