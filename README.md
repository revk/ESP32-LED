# ESP32-LED (WS2812/etc) Project

A system to drive common RGB and RGBW LED strips (WS2812/SK6812, etc).

This is a hardware and software project. The software is much like WLED, but my library and style, though without as many effects (yet). The hardware is designed to be compact and flexible, but also to be able to run WLED.

Note boards are branded A&A, AJK, and HIWTSI.

## Purchasing

* [Amazon - USB-C - This s/w pre loaded](https://www.amazon.co.uk/dp/B0C1W1XJS8) note new stock coming soon.
* [Amazon - USB-C - Pre loaded with WLED](https://www.amazon.co.uk/dp/B0CG3S8JX3) note new stock coming soon.
* [Amazon - USB-A - This s/w pre loaded](https://www.amazon.co.uk/dp/B0DGD5XPLT) note existing stock is TDM version of TDK mic.
* [Amazon - simple fairy lights](https://www.amazon.co.uk/dp/B0D1CQCLBX) works well on 5V USB up to 100 (2 strips).
* TBA for other models

## Full spec (USB-C)

<img src=Manuals/LEDR-Top.png align=right width=50%>

This is the full specification module, with a lot of features.

* Small, 46mm x 25mm (including antenna).
* USB-C connection - functional for flashing and debug as well as 5V power.
* Powerful ESP32-S3-MINI-1-N4-R2 dual CPU processor with 4MB Flash and 2MB SPI RAM, WiFi, Bluetooth, etc.
* 3 contact WAGO connector for the LED strip, for simple and easy connection.
* 2 pin WAGO connector to solid state relay, 3.5A
* Switch mode power supply working from 4V to 35V (5V only when USB connected).
* TDK ICS 43434 I2S digital microphone.
* MAX98357A I2S digital amplifier.
* 2 pin WAGO connector for 4Ω speaker.
* Single sided design with flat base to allow easy fixing under shelf, etc.
* Simple potential divide to ADC pin to allow input voltage monitoring.
* Pads allowing a 6x6 surface mount contact switch to be soldered on the back.
* 38kHz IR receiver module.
* 5V LDO to WS2812 LED as 1st LED, operating as level shifetr for LED output.
* PCB marked with all GPIO numbers

The power supply means you can run from USB and power the strip from 5V USB, or power from the strip, e.g. a 12V strip and external 12V supply (even at other end of strip). Don't connect USB at the same time as a higher voltage supply. The solid state relay can be used to power control the strip, whether using the USB/5V supply or external supply.

## In-line USB-C

<img src=Manuals/USB-C-Top.jpg align=right width=50%>

The USB-C module is designed to be small and work in-line between a USB-C cable and an LED strip.

* Tiny, 46mm x 16mm PCB (46mm x 21mm including antenna).
* Powerful ESP32-S3-MINI-1-N4-R2 dual CPU processor with 4MB Flash and 2MB SPI RAM, WiFi, Bluetooth, etc.
* 3 contact WAGO connector for the LED strip, for simple and easy connection.
* Switch mode power supply working from 4V to 35V (5V only when USB connected).
* On board WS2812 style LED for status (separte to LED strip).
* TDK ICS 43434 I2S digital microphone.
* Single sided design with flat base to allow easy fixing under shelf, etc.
* Functional USB for flashing and debug to ESP32.
* Simple potential divide to ADC pin to allow input voltage monitoring.
* The USB-C module also has pads allowing a 6x6 surface mount contact switch to be soldered on the back.
* PCB marked with all GPIO numbers

The power supply means you can run from USB and power the strip from 5V USB, or power from the strip, e.g. a 12V strip and external 12V supply (even at other end of strip). Don't connect USB at the same time as a higher voltage supply.

### What it does not have, and why...

* No level shifter. The data line for LED strip is 3.3V. This is becasue LED strtips we have tested, 5V and 12V, all seem very happy working from 3.3V. We also cannot be sure of 5V being available for level convertor as we can run off the strip up to 35V, and level shifting to the supply voltage is not likely to be sensible. Adding an additionam 5V supply and level shifter woudl add a lot to the size.
* No relay. Many boards have a relay to power off the strip, which is sensible. But the current usage of some long strips is not insignificant. A relay or larger FET and heatsink, would add a lot to the size of the board, and also need a separate power supply connection when not powering from USB 5V.

## Plug-in USB-A

<img src=Manuals/USB-A-Top.jpg align=right width=48%>
<img src=Manuals/USB-A-Bottom.jpg width=48%>

The USB-A module is designed to plug in directly to a USB-A socket and connector to an LED strip.

* Very tiny 33.1mm x 15.4mm (38.2mm x 15.4mm including antenna), but bear in mind that 10mm disappears in to the USB-A socket.
* All the same features as the USB-C, except double sided to make even smaller.
* Very easy to fit directly on to end of LED strip allowing direct plug in to USB-A.

<img src=Manuals/USB-A-Attached.jpg>

## Non USB, tiny board

<img src=https://github.com/user-attachments/assets/2eb207d0-c523-490b-9d63-5dc1c4035d60 width=48%>

* Even smaller, but SUB (can be accessed via TC2030 lead or solder pads if needed)

## Software

Both boards are designed so they can run WLED code and esphome. The code included here is different, but offers a number of useful features.

* Handles various formats, RGB, RGBW, and some with other sequences like GRB.
* Sound reactive using microphone.
* Links in to Home Assistant.
* Allows a set of HA "lights" which can be various sections of the strip(s), even overlapping.
* Range of effects, which is constantly being extended.
* Range of palettes, to use with effects.

There is even a special Stargate mode for a 504 LED gate design!
