// Simple idle color

#include "app.h"

const char *
appidle (app_t * a)
{
   if (!a->cycle)
   {
      if (!a->colourset)
         setcolour (a, "blue");
   }
   uint8_t l = a->fader;
   for (int i = 0; i < a->len; i++)
      setl (a->start + i, a, (int) 25 * i / a->len, l);
   return NULL;
}
