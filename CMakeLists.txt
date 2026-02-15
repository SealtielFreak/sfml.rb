cmake_minimum_required(VERSION 3.20)
project(sfml_rb C)

set(CMAKE_C_STANDARD 11)

find_package(Ruby 3.3.0 REQUIRED)
find_package(CSFML 3.0.0 REQUIRED COMPONENTS graphics window system)

add_library(sfml_rb SHARED
        ext/ext.c
        ext/window.c
        ext/video_mode.c
        ext/event.c
        ext/event_name.c
        ext/keyboard.c
        ext/color.c
        ext/vec2.c
        ext/rect.c
        ext/circle.c
        ext/render_state.c
        ext/transformable.c
        ext/transform.c
        ext/drawable.c
        ext/view.c
        ext/clock.c
        ext/style_name.c
        ext/exceptions.c
        ext/target.c
        ext/image.c
        ext/texture.c
        ext/sprite.c
        ext/rectangle.c
        ext/polygon.c
)

target_include_directories(sfml_rb PRIVATE
        include
        ext
        ${RUBY_INCLUDE_DIRS}
        ${csfml_SOURCE_DIR}/include
)

target_link_libraries(sfml_rb
        PRIVATE
        ${RUBY_LIBRARIES}
        csfml-graphics
        csfml-window
        csfml-system
)

set_target_properties(sfml_rb PROPERTIES PREFIX "")