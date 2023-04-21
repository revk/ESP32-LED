// Simple pulse color

#include "app.h"

const char *
pulse (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->cycling = 1;
   }

   a->step += 256 / a->speed;
   uint8_t l = cos8[a->step];
   for (unsigned int i = 0; i < a->len; i++)
      setl (a->start + i, a, l);
   return NULL;
}
