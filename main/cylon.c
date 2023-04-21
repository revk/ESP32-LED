// Simple cylon color

#include "app.h"

const char *
cylon (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      if (!a->colourset)
         a->r = 255;
      if (a->len < 3)
         return "Len min 3";
   }
   // Not speed based, one step per

   if (a->t1)
   {
      if (a->step == a->len - 1)
      {
         a->t1 = 0;
         a->step--;
      } else
         a->step++;
   } else
   {
      if (!a->step)
      {
         a->step++;
         a->t1 = 1;
      } else
         a->step--;
   }

   clear (a->start, a->len);
   if (a->step > 0)
      setl (a->start + a->step - 1, a, 127);
   setl (a->start + a->step, a, 255);
   if (a->step + 1 < a->len)
      setl (a->start + a->step + 1, a, 127);
   return NULL;
}
