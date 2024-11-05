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
   }
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
      if (rgbw && !a->w)
         setW (a->start + i, w);
   }
   xSemaphoreTake (audio_mutex, portMAX_DELAY);
   if (AUDIOBANDS > a->len)
      for (int i = 0; i < a->len; i++)
      {                         // More bands, pack in to LEDs
         float p1 = (float) i * AUDIOBANDS / a->len;
         float p2 = (float) (i + 1) * AUDIOBANDS / a->len;
         float v = 0;
         while (p1 < p2)
         {
            float q = ceil (p1);
            if (q <= p1)
               q = p1 + 1;
            if (q > p2)
               q = p2;
            float f = q - p1;
            v += audioband[(int) p1] * f;
            p1 = q;
         }
         v = v * a->len / AUDIOBANDS;
         setled (i, v);
   } else
      for (int i = 0; i < a->len; i++)
      {                         // more LEDs, interpolate to bands
         float p = (float) i * AUDIOBANDS / a->len;
         int x = p;
         p -= x;
         float v = audioband[x] * (1.0 - p) + audioband[x + 1] * p;
         setled (i, v);
      }
   xSemaphoreGive (audio_mutex);
   return NULL;
}
