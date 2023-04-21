// Simple spin color

#include "app.h"

const char *
spin (app_t * a)
{
   if (!a->cycle)
   {                            // Any defaults or sanity checks
      if (!a->len)
         a->len = leds;
      if (!a->start)
         a->start = 1;
   }
   a->step += 256 / a->len;
   for (unsigned int i = 1; i <= a->len; i++)
      setl (i, a, cos256[(256 * i / a->len + a->step) & 255]);
   return NULL;
}
