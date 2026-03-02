#ifndef CHANNEL_CONFIG_H
#define CHANNEL_CONFIG_H

#include <Arduino.h>

#define MAX_CHANNELS 8

typedef struct {
    uint8_t pin;
    bool state;
    unsigned long duration;
    unsigned long startTime;
} Channel;

extern Channel channels[MAX_CHANNELS];

void channel_config_init();
Channel* get_channel(uint8_t id);

#endif
