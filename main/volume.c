 // Bargraph (uses brightness as level)

#include "app.h"

void
pixel (app_t * a, int pos, int p, int n, uint8_t l)
{
   uint8_t *c = a->data;
   pos -= a->start;
   if (pos < 0 || pos >= a->len)
      return;
   if (l > c[pos])
      c[pos] = l;
   else
      c[pos] = ((uint16_t) c[pos] * 15 + l) / 16;
   setl (pos + a->start, a, p, n, c[pos]);
}

const char *
appvolume (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         setcolour (a, "cycling");
      free (a->data);
      memset (a->data = malloc (a->len), 0, a->len);
   }


   float m = 0;
   for (uint8_t i = 0; i < AUDIOBANDS; i++)
      m += audioband[i];
   int v = m * 65536 / AUDIOBANDS * 2;
   if (m < 0)
      v = 0;
   if (v > 65535)
      v = 65535;
   bargraph (a, pixel, v, 65535, a->fader);
   return NULL;
}
