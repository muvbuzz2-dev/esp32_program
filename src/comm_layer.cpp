#include "comm_layer.h"
#include "valve_engine.h"
#include <cstring>
#include <cstdlib>

void comm_handle_message(char* topic, char* payload) {

    // Example payload:
    // "CH1_ON"
    // "CH2_OFF"
    // "CH3_5000" (timed 5 sec)

    if (strncmp(payload, "CH", 2) == 0) {

        uint8_t channel = payload[2] - '1';  // CH1 -> index 0

        if (strstr(payload, "_ON")) {
            valve_set(channel, true);
        }
        else if (strstr(payload, "_OFF")) {
            valve_set(channel, false);
        }
        else {
            unsigned long duration = atol(&payload[4]);
            valve_set_timed(channel, duration);
        }
    }
}
