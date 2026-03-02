#include "channel_config.h"

Channel channels[MAX_CHANNELS];

void channel_config_init() {

    uint8_t pins[MAX_CHANNELS] = {5, 18, 19, 21, 22, 23, 25, 26};

    for (int i = 0; i < MAX_CHANNELS; i++) {
        channels[i].pin = pins[i];
        channels[i].state = false;
        channels[i].duration = 0;
        channels[i].startTime = 0;

        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], LOW);
    }
}

Channel* get_channel(uint8_t id) {
    if (id >= MAX_CHANNELS) return NULL;
    return &channels[id];
}
