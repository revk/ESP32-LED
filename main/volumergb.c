 // Bargraph (uses brightness as level)

#include "app.h"

void
pixelr (app_t * a, int pos, uint8_t l)
{
   uint8_t *c = a->data;
   pos -= a->start;
   if (pos < 0 || pos >= a->len)
      return;
   if (l > c[pos])
      c[pos] = l;
   else
      c[pos] = ((uint16_t) c[pos] * 15 + l) / 16;
   setR (pos + a->start, c[pos]);
}

void
pixelg (app_t * a, int pos, uint8_t l)
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
   setG (pos + a->start, c[pos]);
}

void
pixelb (app_t * a, int pos, uint8_t l)
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
   setB (pos + a->start, c[pos]);
}

const char *
appvolumergb (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->data)
         memset (a->data = malloc (a->len * 3), 0, a->len * 3);
   }

   {                            // Low
      float m = 0;
      for (int i = 0 * AUDIOBANDS / 3; i < 1 * AUDIOBANDS / 3; i++)
         m += audioband[i];
      int v = m * 255 / (AUDIOBANDS / 3);
      if (v > 255)
         v = 255;
      bargraph (a, pixelg, v, a->fader);
   }
   {                            // Mid
      float m = 0;
      for (int i = 1 * AUDIOBANDS / 3; i < 2 * AUDIOBANDS / 3; i++)
         m += audioband[i];
      int v = m * 255 / (AUDIOBANDS / 3);
      if (v > 255)
         v = 255;
      bargraph (a, pixelb, v, a->fader);
   }
   {                            // High
      float m = 0;
      for (int i = 2 * AUDIOBANDS / 3; i < 3 * AUDIOBANDS / 3; i++)
         m += audioband[i];
      int v = m * 255 / (AUDIOBANDS / 3);
      if (v > 255)
         v = 255;
      bargraph (a, pixelr, v, a->fader);
   }
   return NULL;
}
