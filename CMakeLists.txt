cmake_minimum_required(VERSION 3.20)
project(sfml_rb C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(include/ruby)
include_directories(include/SFML)

include_directories(ext)

add_library(sfml_rb ext/ext.c ext/window.c ext/ext/klass/window.h ext/ext/sfml.h ext/video_mode.c ext/ext/klass/video_mode.h ext/ext/module.h ext/event.c ext/ext/klass/event.h ext/event_name.c ext/ext/klass/event/event_name.h ext/keyboard.c ext/ext/klass/keyboard.h ext/color.c ext/ext/klass/color.h ext/vec2.c ext/ext/vec2.h ext/rect.c ext/ext/rect.h ext/circle.c ext/ext/klass/drawable/circle.h ext/render_state.c ext/ext/klass/render_state.h ext/transformable.c ext/ext/klass/transformable.h ext/transform.c ext/ext/module/transform.h ext/drawable.c ext/ext/module/drawable/drawable.h ext/view.c ext/ext/klass/view.h ext/clock.c ext/ext/klass/clock.h ext/style_name.c ext/ext/style_name.h ext/exceptions.c ext/ext/exceptions.h ext/target.c ext/ext/klass/target.h ext/image.c ext/ext/klass/drawable/image.h ext/texture.c ext/ext/klass/drawable/texture.h ext/sprite.c ext/ext/klass/drawable/sprite.h ext/rectangle.c ext/ext/klass/drawable/rectangle.h ext/polygon.c ext/ext/klass/drawable/polygon.h)
