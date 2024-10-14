#include "flagstore.hpp"
#include <cstdint>

namespace Flagstore {
    const char** flags;

    volatile const char* fake_flags[2];

    void init() {
        const char* key = "\x02uF.U\x19!U\x1a\xa1\xd1\x97\xd0p\xcag";
        const char key2[22] = { 38, 45, 84, 6, 65, 66, 38, 33, 61, 0, 32, 64, 102, 47, 17, 68, 94, 77, 98, 36, 122, 100 };
        flags = new const char*[3];
        uint8_t buf[32] = { 86, 32, 2, 109, 1, 95, 90, 27, 42, 245, 142, 162, 224, 47, 152, 83, 76, 49, 118, 99, 10, 87, 116, 24, 34, 146, 131, 200, 151, 67, 132, 26 };
        fake_flags[0] = "TUDCTF{n0t_s0_s3cur3_4ft3r_411!}"; // a fake flag for "Entropy Encrypter", only readable if you dump the firmware
        fake_flags[1] = "TUDCTF{th3_d0g_w45_w34ry_ind33d}"; // same, but for "Weary Watchdog"
        flags[HELLO_HARDWARE] = "TUDCTF{US1NG_U4RT_15_3553NT14L_1N_H4RDW4R3_H4CK1NG}";

        char* ee_flag = new char[33];
        for(int i = 0; i < 32; i++) {
            ee_flag[i] = buf[i] ^ key[i % 16];
        }
        ee_flag[32] = 0;
        flags[ENTROPY_ENCRYPTER] = ee_flag;

        uint8_t buf2[66] = { 114, 120, 16, 69, 21, 4, 93, 117, 85, 51, 127, 36, 86, 72, 78, 32, 110, 40, 87, 123, 20, 84, 17, 114, 56, 55, 42, 113, 121, 88, 13, 117, 127, 117, 18, 64, 97, 52, 111, 35, 5, 123, 14, 12, 21, 114, 49, 126, 53, 113, 84, 79, 9, 108, 127, 112, 21, 76, 32, 40, 50, 121, 22, 20, 8, 25 };
        char* ww_flag = new char[67];
        for(int i = 0; i < 66; i++) {
            ww_flag[i] = buf2[i] ^ key2[i % 22];
        }
        ww_flag[66] = 0;
        flags[WEARY_WATCHDOG] = ww_flag;
        //"TUDCTF{Th3 d0g d0e5 n07 l1k3 y0u 5topp1ng th3 ext3rn4l 0sc1ll4t0r}";
    }
}