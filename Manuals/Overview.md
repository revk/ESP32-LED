# LED Strip controller

This software, designed to run on any PCb, but particularly the defined PCB with one output data pin, is intended to work with common RGB LED strips. These allow a series of individual LEDs, each capable of full colour, to be individually addressed and controlled.

## Output command

Sending `command/LED/id` with an argument can set the specific output pattern required.

- The argument can be simply the name of one app, e.g. `rainbow`.
- The argument can be an array of strings, naming a stacked list of apps. 
- The argument can be an object with each field in order being an app, named for the app, which is an object with the app arguments

e.g. `{"rainbow":{"time":10},"cylon":{"color":"F00"}}`

Note: Unlike valid JSON the same app can appear more than once in the object if needed.

The app list is replaced with those specified, and each app in turn is applied to the LED strip on top of the previous one, and they run concurrently. This means you can have different apps covering different parts of the LED strip, or have a time limited app over writing part of an underlying app, and then showing it once the time limited app stops, etc.

The command `add` can be used to add new apps on existing ones without replacing the existing ones - this is idea for time limited apps and reverting to previous working.

You can also use an app name as a command where the payload is the parameters. This replaces the list of apps with this one app.

Whilst app parameters are normally an object with one or more parameters, if it is just a string, that sets `colour`, and if a number, that sets `limit`. E.g. `command/LED/whatever/spin red`.

The `stop` command sets the limit on all active apps to be `fade` from now. For most apps this is a controlled stop, e.g. fade out.

## Power and wiring

The PCB passes on the USB supplied power. Each LED could use something like 60mA when on full, so consider total power. A USB port only has to provide 0.5A which would be only 8 LEDs, but obviously the LEDs may not all be on full white usually.

However, most USB charger ports can do more, e.g. 2A or even 3A, allowing perhaps 50 LEDs fully on.

If, however, you need more LEDs that your USB port can supply, then use a separate power supply. This should be connected to the power on the LED strip and to the PCB. The USB would then not be connected.

The LEDs are all connected to power (GND and 5V), usually daisy chained, also a DATA line is connected, in to DIN and from DOUT to the next DIN, in a chain. The physical layout may be mroe complex.

## Key settings

The main settings are :-

|Setting|Meaning|
|-------|-------|
|`ledgpio`|The GPIO for output, prefix `-` for inverted.|
|`leds`|This is how many LEDs in the chain. This defaults to `1` so if only the first LED does something, you have failed to set this.|
|`maxr` `maxg` `maxb`|This is the top value for brightness (before applying gamma). Output is scaled to this.|
|`app`|The default app name, using default arguments|

Important, the settings and commands that take an LED position all start from LED `1` as the first LED. This is not as one would internally address an array, and is done deliberately to make `0` mean *unset* rather than the *first LED*.

### Default arguments

Apps take arguments of various sorts, but you can also set defaults which apply.

For example, some apps are designed to work on an LED ring - this may be the whole LED strip, in which case you may not need any special settings, but it could also be part of a chain of LEDs with other things. To constrain the working of a ring based app to the ring, these settings are useful. If not set it is assumed the entire chain is one ring.

|Setting|Meaning|
|-------|-------|
|`ringstart`|Number of first LED in the ring, electrically, numbered as 1st LED in chain as LED `1`.|
|`ringlen`|How many LEDs in the ring, starting at `ringstart` (or 1st LED if not set).|
|`ringtop`|For ring apps that need to know the orientation (e.g. `clock` and `stargate`) this is the LED number of the LED at the top of the ring. If not set then `ringstart` is assumed to be at the top. This can be set negative meaning reverse the ring.|

## "Apps"

You can command one or more apps in order. There operation is stacked, e.g. `rainbow`,`clock` would do a `clock` on a defined `ring` but all LEDs not in that are `rainbow`. Some apps stop after a time, e.g. `stargate` and revert to whatever app is before them.

Each app can have arguments.

### Common arguments

|Argument|Meaning|
|--------|-------|
|`time`|How long to run the app for. Some apps go forever if not set to a limited time.|
|`colour`|The main colour argument for the app - this is specified as a string of single digit hex, e.g. `f00` is full red. Also allowed is `randbow` and `cycle`|
|`start`|The first LED|
|`len`|The number of LEDs|

### Simple apps

|App|Meaning|
|---|-------|
|`idle`|This simply displays all LEDs with defined colour, which by default is black (off). If a colour set `fade` can be set to fade up at start and down at `limit`|
|`cylon`|This runs an LED of colour specified (default is red) backwards and forwards, Cylon/Knightrider style|
|`pulse`|This fades up and down the specified colour (default `cycle`) on all LEDs constantly.|
|`countdown`|Count LEDs until limit (default 60 seconds)|

### Ring apps

|App|Meaning|
|---|-------|
|`spin`|This is intended for a ring but can work on a strip quite well - it rotates the specified colour (default `cycle`) around the ring|
|`clock`|This operates a clock on the ring, red for hour, green for minute, blue for second, obviously a ring with 60 LEDs is best|
|`stargate`|This dials a stargate, setting each chevron, and then opens the gate. Gate closes after a period even if `limit` is not set|

### Text apps

|App|Meaning|
|---|-------|
|`text`|Show text|
|`kern`|Show text with kernin|
|`time`|Show time as text|
