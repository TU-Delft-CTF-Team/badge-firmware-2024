#pragma once

namespace Flagstore {
    void init();
    extern const char** flags;

    enum Challenge {
        HELLO_HARDWARE,
        ENTROPY_ENCRYPTER,
        WEARY_WATCHDOG
    };
}