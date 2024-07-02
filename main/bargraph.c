 // Bargraph (uses brightness as level)

#include "app.h"

const char *
appbargraph (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->cycling = 1;
      if (!a->limit)
         a->limit = 60 * cps;
   }
   if (a->cycle >= a->limit)
      return "";                // done straight away
   uint8_t l = 255;

   int t = a->top;
   if (t < 0)
      t = -t;
   if (t > a->start)
   {
      int N = t - a->start;
      uint32_t n = (uint32_t) 256 * N * a->fader / 255;
      uint8_t f = n & 255;
      n /= 256;
      for (unsigned int i = 0; i < n; i++)
         setl (t - i, a, l);
      if (!a->stop)
         setl (t - n, a, (int) l * f / 255);
   }
   if (t < a->start + a->len - 1)
   {
      int N = a->start + a->len - 1 - t;
      uint32_t n = (uint32_t) 256 * N * a->fader / 255;
      uint8_t f = n & 255;
      n /= 256;
      for (unsigned int i = 0; i < n; i++)
         setl (t + i, a, l);
      if (!a->stop)
         setl (t + n, a, (int) l * f / 255);
   }
   return NULL;
}
