#include <cstdio>
#include <exception>
#include <iostream>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/watchdog.h"


#include "hello_hardware/hello_hardware.hpp"
#include "weary_watchdog/weary_watchdog.hpp"
#include "black_box/black_box.hpp"
#include "entropy_encrypter/entropy_encrypter.hpp"
#include "flagstore/flagstore.hpp"


void init() {
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    sleep_ms(1000);
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    sleep_ms(1000);

    Flagstore::init();
    EntropyEncrypter::init();
    
    while (!stdio_usb_connected()) {}
    WearyWatchdog::init();
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    BlackBox::init();
}

int main() {
    init();

    std:: cout << "\033[32m" << R"(
####################################################
#   ____                                     _     #
#  |  _ \ __ _ ___ _____      _____  _ __ __| |    #
#  | |_) / _` / __/ __\ \ /\ / / _ \| '__/ _` |    #
#  |  __/ (_| \__ \__ \\ V  V / (_) | | | (_| |    #
#  |_|   \__,_|___/___/ \_/\_/ \___/|_|  \__,_|    #
#    __ _  ___ _ __   ___ _ __ __ _| |_ ___  _ __  #
#   / _` |/ _ \ '_ \ / _ \ '__/ _` | __/ _ \| '__| #
#  | (_| |  __/ | | |  __/ | | (_| | || (_) | |    #
#   \__, |\___|_| |_|\___|_|  \__,_|\__\___/|_|    #
#   |___/                                          #
####################################################
)";

    HelloHardware::entrypoint();
    std::cout << R"(Welcome to our cryptographically secure password generator!
It uses the bleeding edge technology of generating randomness via entropy
sampled from quantum fluctuations using a flux capacitor.
)" << std::flush;

    char buffer[4];
    while(true) {
        int length = -797979;
        std::string buf;
        while (length == -797979) {
            std::cout << "\nPlease select the desired length (8~100) of your new and secure password\n> " << std::flush;

            std::getline(std::cin, buf, '\r');
            try {
                length = std::stoi(buf);
            } catch(std::exception& ex) {
                std::cout << "\033[31mERROR:\033[32m Invalid input!" << std::endl;
            }
        }

        if (length < 0) {
            std::cout << "\033[31mERROR:\033[32m Password length can not be negative!" << std::endl;
        } else if (length < 8) {
            std::cout << "\033[31mERROR:\033[32m Password length is too short to be secure!" << std::endl;
        } else if (length > 100) {
            std::cout << "\033[31mERROR:\033[32m Password length too long!" << std::endl;
        } else {
            EntropyEncrypter::generate(length);
        }
    }
}
