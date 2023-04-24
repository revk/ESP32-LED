// Countdown

#include "app.h"

const char *
appcountdown (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->cycling = 1;
      if (!a->limit)
         a->limit = 60 * cps;
   }
   uint32_t n = (uint32_t) 256 * a->len * (a->limit - a->cycle) / a->limit;
   uint8_t f = n & 255;
   n /= 256;
   for (unsigned int i = 0; i < n; i++)
      setl (a->start + i, a, 255);
   setl (a->start + n, a, f);
   return NULL;
}
