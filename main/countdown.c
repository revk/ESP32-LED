// Countdown

#include "app.h"

static void pixel(app_t *a,int pos,uint8_t l)
{
        setl(pos,a,l);
}

const char *
appcountdown (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->colourset = a->cycling = 1;
      if (!a->limit)
         a->limit = 60 * cps;
   }
   if (a->limit <= a->cycle)
      return "";
   bargraph(a,pixel,255*(a->limit - a->cycle) / a->limit,a->fader);
   return NULL;
}
