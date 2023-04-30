// Simple pulse color

#include "app.h"

const char *
apppulse (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->cycling = 1;
   }

   uint8_t l = 255 - cos8[a->step & 255],
      q;
   if (a->stop && (q = 255 * a->stop / a->fade) < l)
      l = q;
   for (unsigned int i = 0; i < a->len; i++)
      setl (a->start + i, a, l);
   a->step += 256 / a->speed;
   return NULL;
}
