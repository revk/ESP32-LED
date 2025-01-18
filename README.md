# ESP32-LED (WS2812/etc) Project


## Trademark

This is an open source project, but bear in mind you cannot sell boards bearing the Andrews & Arnold Ltd name, the A&A logo, the registered trademark AJK logo, or the GS1 allocated EANs assigned to Andrews & Arnold Ltd.

## Summary

A system to drive common RGB and RGBW LED strips such as those based on the
WS2812 or SK6812 chips, as well as others.

This is a hardware and software project. The software is much like WLED, but my library and style, though without as many effects (yet). The hardware is designed to be compact and flexible, but also to be able to run WLED.

Note boards are branded A&A, AJK, and HIWTSI.

## Full spec (USB-C)

<img src=PCB/LEDR/LED.png align=right width=50%>

This is the full specification module, with a lot of features.

* Small: 46mm x 25mm (including antenna).
* USB-C connection - functional for flashing and debug as well as 5V power.
* Powerful ESP32-S3-MINI-1-N4-R2 dual CPU processor with 4MB Flash and 2MB SPI RAM, WiFi, Bluetooth, etc.
* 3 pin WAGO connector for the LED strip, for simple and easy connection.
* 2 pin WAGO connector to solid state relay, 3.5A
* Switch mode power supply working from 4V to 35V (5V only when USB connected).
* TDK ICS 43434 I2S digital microphone.
* MAX98357A I2S digital amplifier.
* 2 pin WAGO connector for 4Ω speaker.
* Single-sided design with flat base to allow easy fixing under a shelf, etc.
* Simple potential divide to ADC pin to allow input voltage monitoring.
* Pads allowing a 6x6 surface mount contact switch to be soldered on the back.
* 38kHz IR receiver module.
* PCB marked with all GPIO numbers

The power supply means you can run the board from USB and it will power the LED strip from that same 5V USB, or power the board from the strip, e.g. a 12V strip and external 12V supply (even at the other end of strip). Do not connect USB at the same time as a higher voltage supply. The solid state relay can be used to power control the strip, whether using the USB/5V supply or external supply.

## In-line USB-C

<img src=PCB/LEDC/LED.png align=right width=50%>

The USB-C module is designed to be small and work in-line between a USB-C cable and an LED strip.

* Tiny, 46mm x 16mm PCB (46mm x 21mm including antenna).
* Powerful ESP32-S3-MINI-1-N4-R2 dual CPU processor with 4MB Flash and 2MB SPI RAM, WiFi, Bluetooth, etc.
* 3 pin WAGO connector for the LED strip, for simple and easy connection.
* Switch mode power supply working from 4V to 35V (5V only when USB connected).
* On board WS2812 style LED for status (separte to LED strip).
* TDK ICS 43434 I2S digital microphone.
* Single-sided design with flat base to allow easy fixing under a shelf, etc.
* Functional USB for flashing and debug to ESP32.
* Simple potential divide to ADC pin to allow input voltage monitoring.
* The USB-C module also has pads allowing a 6x6 surface mount contact switch to be soldered on the back.
* PCB marked with all GPIO numbers

The power supply means you can run the board from USB and it will power the LED strip from that same 5V USB, or power the board from the strip, e.g. a 12V strip and external 12V supply (even at the other end of strip). Do not connect USB at the same time as a higher voltage supply.

### What it does not have, and why...

* No level shifter. The data line for LED strip is 3.3V. This is because LED strtips we have tested, 5V and 12V, all seem very happy working from 3.3V. We also cannot be sure of 5V being available for level convertor as we can run off the strip up to 35V, and level shifting to the supply voltage is not likely to be sensible. Adding an additional 5V supply and level shifter would add a lot to the size.
* No relay. Many boards have a relay to power off the strip, which is sensible. But the current usage of some long strips is not insignificant. A relay or larger FET and heatsink would add a lot to the size of the board, and also need a separate power supply connection when not powering from USB 5V.

## Plug-in USB-A

<img src=PCB/LEDA/LED.png align=right width=48%><img src=PCB/LEDA/LED-bottom.png width=48%>

The USB-A module is designed to plug in directly to a USB-A socket and connector to an LED strip.

* Very tiny 33.1mm x 15.4mm (38.2mm x 15.4mm including antenna), but bear in mind that 10mm disappears in to the USB-A socket.
* All the same features as the USB-C, except double-sided to make it even smaller.
* Very easy to fit directly on to end of LED strip allowing direct plug in to USB-A.

<img src=Manuals/USB-A-Attached.jpg>

## Non USB, tiny board

<img src=PCB/LEDX/LED.png width=48%><img src=PCB/LEDX/LED-bottom.png width=48%>

* Even smaller, but no USB connector (USB can be accessed via TC2030 lead or solder pads if needed)
* Designed for power from strip, e.g. 5V, 12V, 24V

## Other designs

Well, quite a few other PCBs...

<img src=https://github.com/user-attachments/assets/d5e7e25f-a918-4311-868a-3e9b72b282fa width=48%><img src=PCB/Coaster2/Coaster.png width=48%>
<img src=PCB/LED32/LED.png width=48%>

## Software

The boards are designed so they can run WLED code and esphome. The code included here is different, but offers a number of useful features.

* Handles various formats, RGB, RGBW, and some with other sequences like GRB.
* Sound reactive using microphone.
* Links in to Home Assistant.
* Allows a set of HA "lights" which can be various sections of the strip(s), even overlapping.
* Range of effects, which is constantly being extended.
* Range of palettes, to use with effects.

There is even a special Stargate mode for a 504 LED gate design!
