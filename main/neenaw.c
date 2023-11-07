// Simple neenaw  color

#include "app.h"

const char *
appneenaw (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->cycling = 1;
   }

   uint8_t l = 255,
      q;
   if (a->stop && (q = 255 * a->stop / a->fade) < l)
      l = q;
   if (++a->step >= a->speed*2)
      a->step = 0;
   for (unsigned int i = 0; i < a->len; i++)
      setrgbl (a->start + i, (a->step & 1) && a->step < a->speed ? 255 : 0, 0, (a->step & 1) && a->step >= a->speed ? 255 : 0, l);
   return NULL;
}
