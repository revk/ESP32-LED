// Simple test of ends

#include "app.h"

const char *
appendtest (app_t * a)
{
   setRGB (a->start - 1, 255, 0, 0);
   setRGB (a->start + 1, 255, 0, 0);
   setRGB (a->start + a->len - 1 - 1, 255, 0, 0);
   setRGB (a->start + a->len - 1 + 1, 255, 0, 0);
   setRGB (a->start - 2, 0, 255, 0);
   setRGB (a->start + 2, 0, 255, 0);
   setRGB (a->start + a->len - 1 - 2, 0, 255, 0);
   setRGB (a->start + a->len - 1 + 2, 0, 255, 0);
   setRGB (a->start - 3, 0, 0, 255);
   setRGB (a->start + 3, 0, 0, 255);
   setRGB (a->start + a->len - 1 - 3, 0, 0, 255);
   setRGB (a->start + a->len - 1 + 3, 0, 0, 255);
   setRGBW (a->start, 255, 255, 255, 255);
   setRGBW (a->start + a->len - 1, 255, 255, 255, 255);
   for (int i = a->start + 10; i < a->start + (a->len - 5) / 10 * 10; i += 10)
      setRGBW (i, 128, 128, 0, 0);
   for (int i = a->start + 100; i < a->start + (a->len - 5) / 10 * 10; i += 100)
      setRGBW (i, 255, 255, 0, 0);
   if (a->top)
      setRGBW (a->top, 255, 255, 255, 255);
   return NULL;
}
