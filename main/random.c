// Random

#include "app.h"

const char *
apprandom (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      free (a->data);
      a->data = malloc (6 * a->len);
      memset (a->data, 0, 6 * a->len);
      if (!a->colourset)
         a->cycling = 1;
      a->stage = 1;
   }
   uint8_t *r0 = a->data,
      *g0 = r0 + a->len,
      *b0 = g0 + a->len,
      *r1 = b0 + a->len,
      *g1 = r1 + a->len,
      *b1 = g1 + a->len;
   if (!--a->stage)
   {
      a->stage = a->fade;
      memcpy (r0, r1, a->len * 3);
      if (a->limit && a->cycle + a->fade * 2 > a->limit)
         memset (r1, 0, a->len * 3);
      else
         esp_fill_random (r1, a->len * 3);
   }
   uint8_t l = 255 * a->stage / a->fade;
   for (int i = 0; i < a->len; i++)
      setrgb (a->start + i, (l * r0[i] + (255 - l) * r1[i]) / 255, (l * g0[i] + (255 - l) * g1[i]) / 255,
              (l * b0[i] + (255 - l) * b1[i]) / 255);
   return NULL;
}
