// Countdown

#include "app.h"

const char *
appcountdown (app_t * a)
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
   uint8_t l = a->bright;
   if (a->stop)
      l = a->bright * a->stop / a->fade;
   else if (a->fade && a->cycle < a->fade)
      l = a->bright * a->cycle / a->fade;

   int t = a->top;
   if (t < 0)
      t = -t;
   if (t > a->start)
   {
      int N = t - a->start;
      uint32_t n = (uint32_t) 256 * N * (a->limit - a->cycle) / a->limit;
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
      uint32_t n = (uint32_t) 256 * N * (a->limit - a->cycle) / a->limit;
      uint8_t f = n & 255;
      n /= 256;
      for (unsigned int i = 0; i < n; i++)
         setl (t + i, a, l);
      if (!a->stop)
         setl (t + n, a, (int) l * f / 255);
   }
   return NULL;
}
