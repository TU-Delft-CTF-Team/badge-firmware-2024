#!/bin/bash

flag='.-- .... ----- ..--.- .--. ..- - ..--.- -- .---- ..... -.-. ..--.- .---- -. ..--.- .... .--'
output='morse_flag.hpp'

cat > $output <<EOF
#pragma once
#include "pico/stdlib.h"

uint dit = 2 * (clock_get_hz(clk_sys) / (2 * 4));
uint dah = 3 * dit;
uint short_gap = 2 * dit;
uint gap = 6 * dit;

uint32_t morse_flag[] = {
EOF

for (( i=0; i<${#flag}; i++ )); do
    c=${flag:$i:1}
  
    case $c in
        '.')
            echo "    dit, dit," >> $output
            ;;
        '-')
            echo "    dah, dit," >> $output
            ;;
        ' ')
            echo "    0, short_gap," >> $output
            ;;
    esac
done

cat >> $output <<EOF
    0, gap
};

uint transfer_count = sizeof(morse_flag)/sizeof(uint32_t);
EOF