 // Bargraph (uses brightness as level)

#include "app.h"

const char *
appvolume (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->colourset = a->cycling = 1;
      if (!a->data)
         memset (a->data = malloc (a->len), 0, a->len);
   }
   uint8_t *c = a->data;
   uint8_t l = 255;

   int t = a->top;
   if (t < 0)
      t = -t;
   void pixel (int pos, uint8_t l)
   {
      pos -= a->start;
      if (pos < 0 || pos >= a->len)
         return;
      if (l > c[pos])
         c[pos] = l;
      else
         c[pos] = ((uint16_t) c[pos] * 15 + l) / 16;
      setl (pos + a->start, a, c[pos]);
   }
   int v = audiomag * 255;
   if (v > 255)
      v = 255;
   if (t > a->start)
   {
      int N = t - a->start;
      uint32_t n = (uint32_t) 256 * N * v / 255;
      uint8_t f = n & 255;
      n /= 256;
      int p = t;
      for (unsigned int i = 0; i < n; i++)
         pixel (p--, l);
      if (!a->stop)
         pixel (p--, (int) l * f / 255);
      while (p > a->start)
         pixel (p--, 0);
   }
   if (t < a->start + a->len - 1)
   {
      int N = a->start + a->len - 1 - t;
      uint32_t n = (uint32_t) 256 * N * v / 255;
      uint8_t f = n & 255;
      n /= 256;
      int p = t;
      for (unsigned int i = 0; i < n; i++)
         pixel (p++, l);
      if (!a->stop)
         pixel (p++, (int) l * f / 255);
      while (p < a->start + a->len)
         pixel (p++, 0);
   }
   return NULL;
}
