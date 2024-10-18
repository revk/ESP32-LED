 // Bargraph (uses brightness as level)

#include "app.h"

static void
pixel (app_t * a, int pos, uint8_t l)
{
   setl (pos, a, l);
}

const char *
appbargraph (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->colourset = a->cycling = 1;
   }
   bargraph (a, pixel, a->fader, 255);
   return NULL;
}
