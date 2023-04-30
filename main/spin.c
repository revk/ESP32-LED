// Simple spin color

#include "app.h"

const char *
appspin (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->cycling = 1;
   }
   if (a->top > 0)
      a->step -= 256 / a->speed;
   else
      a->step += 256 / a->speed;
   uint8_t l = 255;
   if (a->stop)
      l = 255 * a->stop / a->fade;
   else if (a->fade && a->cycle < a->fade)
      l = 255 * a->cycle / a->fade;
   for (unsigned int i = 0; i < a->len; i++)
      setl (a->start + i, a, l * cos8[(256 * i / a->len + a->step) & 255] / 255);
   return NULL;
}
