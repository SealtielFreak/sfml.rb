#include "ext/klass/keyboard.h"

#include <stdlib.h>
#include <string.h>

#define LENGTH_KEYS        102

static const char *keys[LENGTH_KEYS] = {
        "a",
        "b",
        "c",
        "d",
        "e",
        "f",
        "g",
        "h",
        "i",
        "j",
        "k",
        "l",
        "m",
        "n",
        "o",
        "p",
        "q",
        "r",
        "s",
        "t",
        "u",
        "v",
        "w",
        "x",
        "y",
        "z",
        "num0", "num1", "num2", "num3", "num4",
        "num5", "num6", "num7", "num8",
        "num9", "escape", "LControl", "LShift",
        "LAlt", "LSystem", "RControl", "RShift",
        "RAlt", "RSystem", "Menu", "LBracket",
        "RBracket", "Semicolon", "Comma", "Period",
        "Quote", "Slash", "Backslash", "Tilde",
        "Equal", "Hyphen", "Space", "Enter",
        "Backspace", "Tab", "PageUp", "PageDown",
        "End", "Home", "Insert", "Delete",
        "Add", "Subtract", "Multiply", "Divide",
        "Left", "Right", "Up", "Down",
        "Numpad0", "Numpad1", "Numpad2", "Numpad3",
        "Numpad4", "Numpad5", "Numpad6", "Numpad7",
        "Numpad8", "Numpad9", "f1", "f2",
        "f3", "f4", "f5", "f6",
        "f7", "f8", "f9", "f10",
        "f11", "f12", "f13", "f14",
        "f15", "pause", "keycount"
};

int find_key(const char *name) {
    int i;

    for (i = 0; i < LENGTH_KEYS; i++) {
        if (strcmp(keys[i], name) == 0) {
            return i;
        }
    }

    return -1;
}

const char *get_key_event(unsigned int key) {
    if (key < LENGTH_KEYS) {
        return keys[key];
    } else {
        return "";
    }
}