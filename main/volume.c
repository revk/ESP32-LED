 // Bargraph (uses brightness as level)

#include "app.h"

typedef struct
{
   uint8_t min;
   uint8_t max;
   uint8_t damp[0];
} config_t;

void
pixel (app_t * a, int pos, int p, int n, uint8_t l)
{
   config_t *c = a->data;
   pos -= a->start;
   if (pos < 0 || pos >= a->len)
      return;
   if (l > c->damp[pos])
      c->damp[pos] = l;
   else
      c->damp[pos] = ((uint16_t) c->damp[pos] * 15 + l) / 16;
   setl (pos + a->start, a, p, n, c->damp[pos]);
}

const char *
appvolume (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         setcolour (a, "cycling");
      free (a->data);
      memset (a->data = mallocspi (sizeof (config_t) + a->len), 0, sizeof (config_t) + a->len);
      config_t *c = a->data;
      c->max = MICBANDS;
      if (a->config)
      {
         jo_t j = jo_parse_str (a->config);
         if (jo_here (j) == JO_OBJECT)
         {
            if (jo_find (j, "min") == JO_NUMBER)
               c->min = michz2band (jo_read_int (j));
            if (jo_find (j, "max") == JO_NUMBER)
               c->max = michz2band (jo_read_int (j)) + 1;
         }
         jo_free (&j);
      }
      if (c->min > MICBANDS - 1)
         c->min = MICBANDS - 1;
      if (c->max < c->min + 1)
         c->max = c->min + 1;
      if (c->max > MICBANDS)
         c->max = MICBANDS;
      // Report config
      jo_t n = jo_object_alloc ();
      jo_int (n, "min", micband2hz (c->min));
      jo_int (n, "max", micband2hz (c->max));
      char *was = a->config;
      a->config = jo_finisha (&n);
      free (was);
   }
   config_t *c = a->data;
   float m = 0;
   for (uint8_t i = c->min; i < c->max; i++)
      m += micband[i];
   int v = m * 65536 * 2 / (c->max - c->min);
   if (m < 0)
      v = 0;
   if (v > 65535)
      v = 65535;
   bargraph (a, pixel, v, 65535, a->fader);
   return NULL;
}
