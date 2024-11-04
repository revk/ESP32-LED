// Simple audio color

#include "app.h"

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
   xSemaphoreGive (audio_mutex);
   // TODO if AUDIOBANDS is more than a->len, different logic
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
