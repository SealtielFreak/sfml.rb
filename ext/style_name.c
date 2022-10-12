#include "ext/style_name.h"

const char *styles[STYLES_LENGTH] = {"none", "titlebar", "resize", "close", "fullscreen", "default"};

int search_style_name(const char *style) {
    int i;

    for (i = 0; i < STYLES_LENGTH; i++) {
        if (strcmp(styles[i], style) != 0) {
            return i;
        }
    }

    return -1;
}