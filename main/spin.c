// Simple spin color

#include "app.h"

const char *
spin (app_t * a)
{
   if (!a->stage)
   {                            // Init
      if (!a->start)
         a->start = ringstart ? : 1;
      if (!a->len)
         a->len = ringlen ? : leds;
      if (!a->top)
         a->top = ringtop ? : 1;
      if (a->start + a->len - 1 > leds)
         return "Len wrong";
      if (a->top > leds)
         return "Top outside strip";
      if (a->len <= 1)
         return "Not a ring - TODO this can go when we sort tail";
      a->stage++;
      // TODO speed
      // TODO tail len
   }
   if (++a->step >= a->len)
      a->step = 0;
   for (unsigned int i = 0; i < a->len; i++)
   {
      ledr[a->start - 1 + ((a->step + i) % a->len)] = (unsigned int) a->colour.r * i / (a->len - 1);
      ledg[a->start - 1 + ((a->step + i) % a->len)] = (unsigned int) a->colour.g * i / (a->len - 1);
      ledb[a->start - 1 + ((a->step + i) % a->len)] = (unsigned int) a->colour.b * i / (a->len - 1);
   }
   return NULL;
}
