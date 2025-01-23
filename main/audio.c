// Simple audio color

#include "app.h"
#include <math.h>

typedef struct
{
   uint8_t min;
   uint8_t max;
   uint8_t damp[0];
} config_t;

const char *
appaudio (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         setcolour (a, "spin");
      free (a->data);
      memset (a->data = mallocspi (sizeof (config_t)), 0, sizeof (config_t));
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
   void setled (int i, float v)
   {
      uint8_t c = 0,
         w = 0;
      v *= a->fader;
      if (v < 0)
         v = 0;
      if (v > 255)
      {
         v -= 255;
         v *= 2;
         if (v > 255)
            v = 255;
         w = v;
         c = 255;
      } else
      {
         w = 0;
         c = v;
      }
      setl (a->start + i, a, i, a->len, c);
      if (!a->w)
         setW (a->start + i, w);
   }
   uint8_t bands = c->max - c->min;
   xSemaphoreTake (mic_mutex, portMAX_DELAY);
   if (bands > a->len)
      for (int i = 0; i < a->len; i++)
      {                         // More bands, pack in to LEDs
         float p1 = c->min + (float) i * bands / a->len;
         float p2 = c->min + (float) (i + 1) * bands / a->len;
         float v = 0;
         while (p1 < p2)
         {
            float q = ceil (p1);
            if (q <= p1)
               q = p1 + 1;
            if (q > p2)
               q = p2;
            float f = q - p1;
            v += micband[(int) p1] * f;
            p1 = q;
         }
         v = v * a->len / bands;
         setled (i, v);
   } else
      for (int i = 0; i < a->len; i++)
      {                         // more LEDs, interpolate to bands
         float p = c->min + (float) i * bands / a->len;
         int x = p;
         p -= x;
         float v = micband[x] * (1.0 - p) + micband[x + 1] * p;
         setled (i, v);
      }
   xSemaphoreGive (mic_mutex);
   return NULL;
}
