// Stargate

#include "app.h"

const char *
stargate (app_t * a)
{
      uint8_t top;
   int8_t dir = 1;
   if (a->top < 0)
   {
      top = (leds + a->start + a->top) % leds;
      dir = -1;
   } else
      top = (leds + a->top - a->start) % leds;
   if (!a->cycle)
   {                            // Sanity checks, etc
	   if(!a->limit)a->limit=60*cps;
   }

   return "No stargate yet";
}
