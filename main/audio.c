// Simple audio color

#include "app.h"
#include <math.h>

const char *
appaudio (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         setcolour (a, "spin");
      free (a->data);
      a->data = mallocspi (AUDIOBANDS * 2);
   }
   uint8_t *c = a->data;
   uint8_t *w = c + AUDIOBANDS;
   xSemaphoreTake (audio_mutex, portMAX_DELAY);
   for (int i = 0; i < AUDIOBANDS; i++)
   {
      int v = a->fader * audioband[i];
      if (audioband[i] < 0)
         v = 0;
      if (v >= 255)
      {
         v -= 255;
         v *= 2;
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
   // Apportion bands to LEDs allow for more or fewer bands than LEDs
   xSemaphoreGive (audio_mutex);
   if (AUDIOBANDS > a->len)
      for (int i = 0; i < a->len; i++)
      {
         float p1 = (float) i * AUDIOBANDS / a->len;
         float p2 = (float) (i + 1) * AUDIOBANDS / a->len;
         int vc = 0,
            vw = 0;
         while (p1 < p2)
         {
            float q = ceil (p1);
            if (q <= p1)
               q = p1 + 1;
            if (q > p2)
               q = p2;
            float f = q - p1;
            vc += c[(int) p1] * f;
            vw += w[(int) p1] * f;
            p1 = q;
         }
         vc /= (float) AUDIOBANDS / a->len;
         vw /= (float) AUDIOBANDS / a->len;
         setl (a->start + i, a, i, a->len, vc);
         if (rgbw && !a->w)
            setW (a->start + i, vw);
   } else
      for (int i = 0; i < a->len; i++)
      {
         float p = (float) i * AUDIOBANDS / a->len;
         int x = p;
         p -= x;
         int vc = c[x] * (1.0 - p) + c[x + 1] * p;
         int vw = w[x] * (1.0 - p) + w[x + 1] * p;
         setl (a->start + i, a, i, a->len, vc);
         if (rgbw && !a->w)
            setW (a->start + i, vw);
      }
   return NULL;
}
