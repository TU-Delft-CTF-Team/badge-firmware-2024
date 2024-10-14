#include "weary_watchdog.hpp"

#include <iostream>

#include "hardware/watchdog.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"

#include "../flagstore/flagstore.hpp"

namespace WearyWatchdog {

    void watchdog() {
        watchdog_enable(500, 0);
        while (true) {
            sleep_ms(200);
            watchdog_update();
            printf("\033[32m\033[32m\033[32m\033[32m\033[32m\033[32m");
        }
    }   

    void init() {
        if (watchdog_enable_caused_reboot()) {
            std::cout << Flagstore::flags[Flagstore::WEARY_WATCHDOG] << '\n' << std::endl;
        }
        multicore_launch_core1(watchdog);
    }

}
