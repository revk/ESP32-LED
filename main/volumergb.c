 // Bargraph (uses brightness as level)

#include "app.h"

void
pixelr (app_t * a, int pos, int p, int n, uint8_t l)
{
   uint8_t *c = a->data;
   pos -= a->start;
   if (pos < 0 || pos >= a->len)
      return;
   if (l > c[pos])
      c[pos] = l;
   else
      c[pos] = ((uint16_t) c[pos] * 15 + l) / 16;
   setR (pos + a->start, (int) a->r * c[pos] / 255);
}

void
pixelg (app_t * a, int pos, int p, int n, uint8_t l)
{
   uint8_t *c = a->data;
   c += a->len;
   pos -= a->start;
   if (pos < 0 || pos >= a->len)
      return;
   if (l > c[pos])
      c[pos] = l;
   else
      c[pos] = ((uint16_t) c[pos] * 15 + l) / 16;
   setG (pos + a->start, (int) a->g * c[pos] / 255);
}

void
pixelb (app_t * a, int pos, int p, int n, uint8_t l)
{
   uint8_t *c = a->data;
   c += a->len * 2;
   pos -= a->start;
   if (pos < 0 || pos >= a->len)
      return;
   if (l > c[pos])
      c[pos] = l;
   else
      c[pos] = ((uint16_t) c[pos] * 15 + l) / 16;
   setB (pos + a->start, (int) a->b * c[pos] / 255);
}

const char *
appvolumergb (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      free (a->data);
      memset (a->data = malloc (a->len * 3), 0, a->len * 3);
      if (!a->colourset || a->palette)
         setcolour (a, "white");
   }

   {                            // Low
      float m = 0;
      for (int i = 0 * AUDIOBANDS / 4; i < 1 * AUDIOBANDS / 4; i++)
         m += audioband[i];
      int v = m * 65536 / (AUDIOBANDS / 4);
      if (v > 65535)
         v = 65535;
      bargraph (a, pixelb, v, 65535, a->fader);
   }
   {                            // Mid
      float m = 0;
      for (int i = 1 * AUDIOBANDS / 4; i < 2 * AUDIOBANDS / 4; i++)
         m += audioband[i];
      int v = m * 65535 / (AUDIOBANDS / 4);
      if (v > 65535)
         v = 65535;
      bargraph (a, pixelg, v, 65535, a->fader);
   }
   {                            // High
      float m = 0;
      for (int i = 2 * AUDIOBANDS / 4; i < 4 * AUDIOBANDS / 4; i++)
         m += audioband[i];
      int v = m * 65535 / (AUDIOBANDS / 2);
      if (v > 65535)
         v = 65535;
      bargraph (a, pixelr, v, 65535, a->fader);
   }
   return NULL;
}
