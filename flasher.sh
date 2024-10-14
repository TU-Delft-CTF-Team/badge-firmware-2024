#!/bin/bash

PICOTOOL=$(which picotool) # replace with the path to your picotool
FIRMWARE=./firmware.uf2 # replace with the actual path to the firmware

remove_device_shown=0
flashed=0
while true; do
    found=0
    for dev in /sys/bus/usb/devices/*-*; do
        if [ -f $dev/idVendor ]; then
            if [[ "$(cat $dev/idVendor)" == "2e8a" && "$(cat $dev/idProduct)" == "0003" ]]; then
                found=1
                if [[ "$flashed" == "0" ]]; then
                    echo "Found a Pico! Invoking picotool..."
                    $PICOTOOL load $FIRMWARE -f
                    echo "Done!"
                    flashed=1
                elif [[ "$remove_device_shown" == "0" ]]; then
                    echo "Please detach the device"
                    remove_device_shown=1
                fi
                break
            fi
        fi
    done
    if [[ "$found" == "0" ]]; then
        flashed=0
        remove_device_shown=0
    fi
    sleep 1
done