// Simple spin color

#include "app.h"

const char *
spin (app_t * a)
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
   for (unsigned int i = 0; i < a->len; i++)
      setl (a->start + i, a, cos8[(256 * i / a->len + a->step) & 255]);
   return NULL;
}
