cmake_minimum_required(VERSION 3.20)
project(sfml_rb C)

set(CMAKE_C_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        sfml_headers
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
)
FetchContent_Populate(sfml_headers)

FetchContent_Declare(
        csfml_headers
        GIT_REPOSITORY https://github.com/SFML/CSFML.git
        GIT_TAG master
)
FetchContent_Populate(csfml_headers)

FetchContent_Declare(
        ruby_headers
        GIT_REPOSITORY https://github.com/ruby/ruby.git
        GIT_TAG v3_3_0
)
FetchContent_Populate(ruby_headers)

add_library(headers_indexing INTERFACE)

target_include_directories(
        headers_indexing
        INTERFACE
        ext
        ${sfml_headers_SOURCE_DIR}/include
        ${csfml_headers_SOURCE_DIR}/include
        ${ruby_headers_SOURCE_DIR}/include
)

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

target_link_libraries(sfml_rb PRIVATE headers_indexing)

find_package(Ruby REQUIRED)
target_include_directories(sfml_rb PRIVATE ${RUBY_INCLUDE_DIRS})
target_link_libraries(sfml_rb PRIVATE ${RUBY_LIBRARIES})