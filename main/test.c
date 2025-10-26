// Simple test

#include "app.h"

const char *
apptest (app_t * a)
{
   if (!a->step)
      a->step = 128 / a->speed;
   uint8_t l = a->step & 255;
   switch (a->step / 256)
   {
   case 0:
      for (int i = a->start; i < a->start + a->len; i++)
         setRGBW (i, l, 0, 0, 0);
      break;
   case 1:
      for (int i = a->start; i < a->start + a->len; i++)
         setRGBW (i, 255, 0, 0, 0);
      break;
   case 2:
      for (int i = a->start; i < a->start + a->len; i++)
         setRGBW (i, 255 - l, l, 0, 0);
      break;
   case 3:
      for (int i = a->start; i < a->start + a->len; i++)
         setRGBW (i, 0, 255, 0, 0);
      break;
   case 4:
      for (int i = a->start; i < a->start + a->len; i++)
         setRGBW (i, 0, 255 - l, l, 0);
      break;
   case 5:
      for (int i = a->start; i < a->start + a->len; i++)
         setRGBW (i, 0, 0, 255, 0);
      break;
   case 6:
      for (int i = a->start; i < a->start + a->len; i++)
         setRGBW (i, 0, 0, 255 - l, l);
      break;
   case 7:
      for (int i = a->start; i < a->start + a->len; i++)
         setRGBW (i, 0, 0, 0, 255);
      break;
   case 8:
      if (b.rgbw)
      {
         for (int i = a->start; i < a->start + a->len; i++)
            setRGBW (i, 0, 0, 0, 255 - l);
         break;
      }
      __attribute__((fallthrough));
   case 9:
      if (b.rgbw)
      {
         for (int i = a->start; i < a->start + a->len; i++)
            setRGBW (i, 0, 0, 0, 0);
         break;
      }
      __attribute__((fallthrough));
   default:
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
      for (int i = a->start + 10; i < a->start + a->len - 5; i += 10)
         setRGBW (i, 128, 128, 0, 0);
      for (int i = a->start + 100; i < a->start + a->len - 5; i += 100)
         setRGBW (i, 255, 255, 0, 0);
      if (a->top)
         setRGBW (a->top, 255, 255, 255, 255);
   }
   a->step += 256 / a->speed;
   return NULL;
}
