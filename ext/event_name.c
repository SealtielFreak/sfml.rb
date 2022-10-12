#include "ext/klass/event/event_name.h"

#include <stdlib.h>
#include <string.h>

#define LENGTH_EVENTS        24

static const char *events[LENGTH_EVENTS] = {
        "closed", "resized", "lost-focus", "gained-focus",
        "text-entered", "key-pressed", "key-released", "mouse-wheel-moved",
        "mouse-wheel-scrolled", "mouse-button-pressed", "mouse-button-released", "mouse-moved",
        "mouse-entered", "mouse-left", "joystick-button-pressed", "joystick-button-released",
        "joystick-moved", "joystick-connected", "joystick-disconnected", "touch-began",
        "touch-moved", "touch-ended", "sensor-changed", "count"
};

const char *get_event_name(size_t name) {
    if (name < LENGTH_EVENTS) {
        return events[name];
    }

    return "";
}