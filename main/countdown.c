// Countdown

#include "app.h"

static void
pixel (app_t * a, int pos, uint8_t p, uint8_t l)
{
   setl (pos, a, p, l);
}

const char *
appcountdown (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         setcolour (a, "cycling");
      if (!a->limit)
         a->limit = 60 * cps;
   }
   if (a->limit <= a->cycle)
      return "";
   bargraph (a, pixel, 255 * (a->limit - a->cycle) / a->limit, a->fader);
   return NULL;
}
