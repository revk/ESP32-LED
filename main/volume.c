 // Bargraph (uses brightness as level)

#include "app.h"

void
pixel (app_t * a, int pos, uint8_t p, uint8_t l)
{
   uint8_t *c = a->data;
   pos -= a->start;
   if (pos < 0 || pos >= a->len)
      return;
   if (l > c[pos])
      c[pos] = l;
   else
      c[pos] = ((uint16_t) c[pos] * 15 + l) / 16;
   setl (pos + a->start, a, p, c[pos]);
}

const char *
appvolume (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         setcolour (a, "cycling");
      if (!a->data)
         memset (a->data = malloc (a->len), 0, a->len);
   }

   int v = audiomag * 255 * 2;  // this is average, and we auto gain on peak, so this may make sense...
   if (v > 255)
      v = 255;
   bargraph (a, pixel, v, a->fader);
   return NULL;
}
