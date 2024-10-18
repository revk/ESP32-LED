// Simple audio color

#include "app.h"

const char *
appaudio (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->colourset = a->rainbow = 1;
      if (!a->data)
         a->data = malloc (AUDIOBANDS);
   }
   uint8_t *c = a->data;
   for (int i = 0; i < AUDIOBANDS; i++)
   {
      int v = a->fader * audioband[i];
      if (v >= 255)
         v = 255;
      c[i] = v;
   }
   for (int i = 0; i < a->len; i++)
   {
      float p = (float) i * AUDIOBANDS / a->len;
      int x = p;
      p -= x;
      int v = c[x] * (1.0 - p) + c[x + 1] * p;
      setl (a->start + i, a, v);
   }
   return NULL;
}
