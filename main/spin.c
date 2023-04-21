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

   a->step += 256 / a->len;
   for (unsigned int i = 1; i <= a->len; i++)
      setl (i, a, cos256[(256 * i / a->len + a->step) & 255]);
   return NULL;
}
