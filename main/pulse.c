// Simple pulse color

#include "app.h"

const char *
apppulse (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         setcolour (a, "cycling");
   }

   uint8_t l = a->fader * (255 - cos8[a->step & 255]) / 255;
   for (unsigned int i = 0; i < a->len; i++)
      setl (a->start + i, a, i, a->len, l);
   a->step += 256 / a->speed;
   return NULL;
}
