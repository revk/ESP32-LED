// Random

#include "app.h"

const char *
apprandom (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      free (a->data);
      a->data = malloc (8 * a->len);
      memset (a->data, 0, 8 * a->len);
      if (!a->colourset)
         a->cycling = 1;
      a->stage = 1;
   }
   uint8_t *r0 = a->data,
      *g0 = r0 + a->len,
      *b0 = g0 + a->len,
      *w0 = b0 + a->len,
      *r1 = w0 + a->len,
      *g1 = r1 + a->len,
      *b1 = g1 + a->len,
      *w1 = b1 + a->len;
   if (!--a->stage)
   {
      a->stage = a->speed;
      memcpy (r0, r1, a->len * 3);
      if (a->stop)
         memset (r1, 0, a->len * 3);
      else
         esp_fill_random (r1, a->len * 3);
   }
   uint8_t q = a->fader;
   uint8_t l = 255 * a->stage / a->speed;
   for (int i = 0; i < a->len; i++)
      setRGBWl (a->start + i,   //
                (l * r0[i] + (255 - l) * r1[i]) / 255,  //
                (l * g0[i] + (255 - l) * g1[i]) / 255,  //
                (l * b0[i] + (255 - l) * b1[i]) / 255,  //
                (l * w0[i] + (255 - l) * w1[i]) / 255,  //
                q);
   return NULL;
}
