// Simple cylon color

#include "app.h"

const char *
appcylon (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
      {
         a->r = 255;
         a->colourset = 1;
      }
      if (a->len < 3)
         return "Len min 3";
   }
   // Not speed based, one step per

   if (a->stage)
   {
      if (a->step == a->len - 1)
      {
         a->stage = 0;
         a->step--;
      } else
         a->step++;
   } else
   {
      if (!a->step)
      {
         a->step++;
         a->stage = 1;
      } else
         a->step--;
   }
   uint8_t l = a->fader;
   clear (a->start, a->len);
   if (a->step > 0)
      setl (a->start + a->step - 1, a, (int) 255 * (a->step - 1) / a->len, l / 2);
   setl (a->start + a->step, a, (int) 255 * a->step / a->len, l);
   if (a->step + 1 < a->len)
      setl (a->start + a->step + 1, a, (int) 255 * (a->step + 1) / a->len, l / 2);
   return NULL;
}
