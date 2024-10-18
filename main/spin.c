// Simple spin color

#include "app.h"

const char *
appspin (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->colourset = a->cycling = 1;
   }
   if (a->top > 0)
      a->step -= 256 / a->speed;
   else
      a->step += 256 / a->speed;
   uint8_t l = a->fader;
   for (unsigned int i = 0; i < a->len; i++)
      setl (a->start + i, a, l * cos8[(256 * i / a->len + a->step) & 255] / 255);
   return NULL;
}
