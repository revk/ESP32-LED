 // Bargraph (uses brightness as level)

#include "app.h"

static void
pixel (app_t * a, int pos, uint8_t p, uint8_t l)
{
   setl (pos, a, p, l);
}

const char *
appbargraph (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         setcolour (a, "cycling");
   }
   bargraph (a, pixel, a->fader, 255);
   return NULL;
}
