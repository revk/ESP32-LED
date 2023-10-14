# Stargate

The `stargate` app has some special features.

It is typically just a *ring* style gate dial sequence - dialling a randon 7 chevron address. However, if the `len` of the *ring* is `210`, `372` or `507` it operates a special gate sequence for some complex gate rings.

## Dialling the gate

<img src=Gate372.jpg width=25% align=right>

If the `app` is set to `stargate` then the gate dials a random address on power up. The address is usually 7 chevron but can occasionally be 8 or 9 chevron.

However you can start a dialling sequence via MQTT, as you would expect, `command/LED/Gate/stargate` (where `Gate` is the `hostname`).

You can pass paramters as JSON, or just a string. If a string (that is not a colour) this is passed as `data`.

The `data` sequence can be either `*` for an incoming gate, or a sequence of up to 9 characters for the gate dial sequence. The characters are from the set `@ABCDEFGHIJKLMNOPQRSTUVWXYZ&-0123456789` where `@` is the home symbol and the following characters are glyphs (clockwise) from that. The sequence should normally be non repeating, and end in `@` and be 7, 8, or 9 characters. However, the app will allow any sequence, from 1 to 9 glyphs and allow repeats, if you want.

You can also instruct dialling via `http`, e.g. `http://192.168.1.2/?app=stargate&data=ABCDEF@`

Note that `colour` can be set as well, and this changes the glypth colour, `black` or `000` would disable showing these.