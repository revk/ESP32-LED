// Simple audio color

#include "app.h"

const char *
appaudio (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         setcolour (a, "rainbow");
      if (!a->data)
         a->data = malloc (AUDIOBANDS * 2);
   }
   uint8_t *c = a->data;
   uint8_t *w = c + AUDIOBANDS;
   for (int i = 0; i < AUDIOBANDS; i++)
   {
      int v = a->fader * audioband[i];
      if (v >= 255)
      {
         v -= 255;
         v /= 4;
         if (v > 255)
            v = 255;
         w[i] = v;
         c[i] = 255;
      } else
      {
         w[i] = 0;
         c[i] = v;
      }
   }
   for (int i = 0; i < a->len; i++)
   {
      float p = (float) i * AUDIOBANDS / a->len;
      int x = p;
      p -= x;
      int vc = c[x] * (1.0 - p) + c[x + 1] * p;
      int vw = w[x] * (1.0 - p) + w[x + 1] * p;
      setl (a->start + i, a, (int) 255 * i / a->len, vc);
      if (rgbw && !a->w)
         setW (a->start + i, vw);
   }
   return NULL;
}
