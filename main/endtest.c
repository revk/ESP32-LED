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
   if (a->top)
      setRGBW (a->top, 255, 255, 255, 255);
   setRGBW (a->start + a->len - 1, 255, 255, 255, 255);
   return NULL;
}
