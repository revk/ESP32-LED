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

   uint8_t l = a->fader;

   if (++a->step >= a->speed * 2)
      a->step = 0;
   int d = ((cps / 10) ? : 1);
   uint8_t r = ((a->step / d) & 1) && a->step < a->speed ? 255 : 0;
   uint8_t b = ((a->step / d) & 1) && a->step >= a->speed ? 255 : 0;
   for (unsigned int i = 0; i < a->len; i++)
      setRGBl (a->start + i, r, 0, b, l);
   return NULL;
}
