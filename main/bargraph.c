 // Bargraph (uses brightness as level)

#include "app.h"

static void
pixel (app_t * a, int pos, int p, int n, uint8_t l)
{
   setl (pos, a, p, n, l);
}

const char *
appbargraph (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         setcolour (a, "cycling");
   }
   bargraph (a, pixel, a->fader, 255, 255);
   return NULL;
}
