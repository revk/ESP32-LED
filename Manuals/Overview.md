# LED Strip controller

This software, designed to run on any PCB, but particularly the defined PCB with one output data pin, is intended to work with common RGB/RGBW LED strips. These allow a series of individual LEDs, each capable of full colour, to be individually addressed and controlled.

## Output command

Sending `command/LED/id` with an argument can set the specific output pattern required.

- The argument can be simply the name of one app, e.g. `spin`.
- The argument can be an array of strings, naming a stacked list of apps. 
- The argument can be an object with each field in order being an app, named for the app, which is an object with the app arguments

e.g. `{"rainbow":{"time":10},"cylon":{"color":"F00"}}`

Note: Unlike valid JSON the same app can appear more than once in the object if needed.

The app list is replaced with those specified, and each app in turn is applied to the LED strip on top of the previous one, and they run concurrently. This means you can have different apps covering different parts of the LED strip, or have a time limited app over writing part of an underlying app, and then showing it once the time limited app stops, etc.

The command `add` can be used to add new apps on existing ones without replacing the existing ones - this is idea for time limited apps and reverting to previous working.

You can also use an app name as a command where the payload is the parameters. This replaces the list of apps with this one app.

You can also pass the parameters for a simple single app as a form `GET` list, including `app=` for the name of the application.

## Power and wiring

The PCB passes on the USB supplied power. Each LED could use something like 60mA when on full, so consider total power. A USB port only has to provide 0.5A which would be only 8 LEDs, but obviously the LEDs may not all be on full white usually.

However, most USB charger ports can do more, e.g. 2A or even 3A, allowing perhaps 50 LEDs fully on.

If, however, you need more LEDs that your USB port can supply, then use a separate power supply. This should be connected to the power on the LED strip and to the PCB. The USB would then not be connected.

The LEDs are all connected to power (GND and 5V), usually daisy chained, also a DATA line is connected, in to DIN and from DOUT to the next DIN, in a chain. The physical layout may be mroe complex.

## Audio

If a microphone is fitted (TDM PDM I2S) set `audio.data` and `audio.clock` for audio effects.

## Key settings

The main settings are :-

|Setting|Meaning|
|-------|-------|
|`ledgpio`|The GPIO for output, prefix `-` for inverted.|
|`leds`|This is how many LEDs in the chain. This defaults to `1` so if only the first LED does something, you have failed to set this.|
|`maxr` `maxg` `maxb`|This is the top value for brightness (before applying gamma). Output is scaled to this.|
|`init`|The default initial application setting (JSON)|

Important, the settings and commands that take an LED position all start from LED `1` as the first LED. This is not as one would internally address an array, and is done deliberately to make `0` mean *unset* rather than the *first LED*.

## Common commands

There are commands as part of the library, but also basic commands for this LED application as well.

|Command|Args|Meaning|
|-------|----|-------|
|`stop`||Stop all directly set LED effects (not the presets)|
|`dark`||Stop all LED effects and turn off all presets|
|`power`*N*|`on`/`off`/`toggle`|Turn a preset *N* on or off or toggle, not `blink` also turns on|

## "Apps"

You can command one or more apps in order. There operation is stacked, e.g. `idle`,`clock` would do a `clock` on a defined `ring` but all LEDs not in that are `idle` colour. Some apps stop after a time, e.g. `stargate` and revert to whatever app is before them.

Each app can have arguments.

### Common arguments

|Short|Argument|Meaning|
|-----|--------|-------|
|`d`|`delay`|Delay before starting app. (seconds)|
|`T`|`limit`|How long to run the app for. Some apps go forever if not set to a limited time. (seconds)|
|`#`|`colour`|The main colour argument for the app - this is specified as a string of single digit hex, e.g. `f00` is full red. It can instead be the name of a palette|
|`s`|`start`|The first LED|
|`l`|`len`|The number of LEDs|
|`b`|`bright`|Main app brightness (0-255)|
||`speed`|Cycle time (seconds)|
||`fadein`|fade in time (seconds)|
||`fadeout`|fade out time (seconds)|

### Palettes

A palette is simply a way colours change, they can be based on time, or position, or value.

|Name|Type|Meaning|
|----|----|-------|
|rainbow|Position|Rainbow|
|revbow|Position|Rainbow (reversed)|
|cycling|Time|Rainbow|
|wheel|Time|Alternative colour bands like rainbow|
|fire|Value|red to white based on value|
|xmas|Position|Alternate red/green|
|neenaw|Time|Red/blue flashing sequence|

### Simple apps

|App|Meaning|
|---|-------|
|`idle`|This simply displays all LEDs with defined colour, which by default is black (off).|
|`cylon`|This runs an LED of colour specified (default is red) backwards and forwards, Cylon/Knightrider style|
|`pulse`|This fades up and down the specified colour (default `cycle`) on all LEDs constantly.|
|`bargraph`|Bargraph (based on brightness setting)|
|`countdown`|Count LEDs until limit (default 60 seconds)|
|`random`|Fading between random colours|
|`twinkle`|All lights constantly fading different random levels of selected colour|
|`endtest`|White light each end, and at `top` if set, and R/G/B next to ends, allow testing `start` and `len`|
|`drop`|Dropping balls|

Note `drop` allows config including `gravity` (m/s²), `height` (m), `size` (m), `drag` (0-1), `bounce` (0-1), and `balls`.

### Audio apps

|App|Meaning|
|---|-------|
|`audio`|Spectrum based display. Note, on RGBW, if W is not set, it is overridden with an over peak output white|
|`volume`|Volume bar graph.|
|`volumergb`|Volume RGB bar graph (red:high, green:mid, blue:base). Note, setting a *colour* causes colours to be restricted to colour set, e.g. set blue for *base*. Cannot use with a palette|

Note that `volumergb` uses blue for *base* and red for *high* by default, but a JSON config in a preset can set `"r"`/`"g"`/`"b"` as an array of *start* and *len* in the 24 frequency bins instead.

### Ring/loop apps

|App|Meaning|
|---|-------|
|`spin`|This is intended for a ring but can work on a strip quite well - it rotates the specified colour (default `cycle`) around the ring|
|`clock`|This operates a clock on the ring, red for hour, green for minute, blue for second, obviously a ring with 60 LEDs is best|
|`stargate`|This dials a stargate, setting each chevron, and then opens the gate. Gate closes after a period even if `limit` is not set. See [Stargate app](Stargate.md) for more details and special Stargate LED rings|
|`lava`|Fade up and down each of red/green/blue at random positions on the ring and random speeds.|

### Text apps

|App|Meaning|
|---|-------|
|`text`|Show text|
|`kern`|Show text with kernin|
|`time`|Show time as text|

## Virtual strips

You can configure settings for a number of virtual strips. This allows the various settings, and a config JSON. If `effect` is set, the JSON is the various parameters for the effect. If not, then the config can be a JSON set of multiple effects. The config can cover all the strip, just using the settings as a default.

## Home Assistant

You can configure Home Assistant use. For this you enable `haenable`. Each virtual strip can be a *light* if you set the HA name on the virtual strip.

If you leave `effect` not set, then HA can send an effect setting as well. If HA sets an effect, but the `config` is defined as multiple effects, `"*"` can be used as the selected effect.

The HA *lights* are layered as well as any lighting set by the web interface or MQTT, independently, based on HA turning the *lights* on or not. The MQTT/web effects first, then each *on* preset, in order.

[This YouTube video](https://www.youtube.com/watch?v=_URugM_1cDo) by [Home Is Where The Smart Is](https://www.hiwtsi.uk/) may be useful to help you getting started with integrating the LEDs with Home Assistant/MQTT.
