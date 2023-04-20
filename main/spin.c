// Simple spin color

#include "app.h"

void
spin (app_t * a)
{
   if (!a->stage)
   {                            // Init
      if (!a->start)
         a->start = ringstart ? : 1;
      if (!a->len)
         a->len = ringlen ? : leds;
      if (!a->top)
         a->top = ringtop ? : 1;
      if(!a->r&&!a->g&&!a->b)
      {
	      a->r=255;// TODo dummy
      }
      if (a->start + a->len - 1 > leds || a->top > leds || a->len <= 1)
      { // Sanity checks
         a->app = NULL;
         return;
      }
      a->stage++;
      // TODO speed
      // TODO tail len
   }
   if (++a->step >= a->len)
      a->step = 0;
   for (unsigned int i = 0; i < a->len; i++)
   {
      led[a->start - 1 + ((a->step + i) % a->len)].r = (unsigned int) a->r *i / (a->len - 1);  
      led[a->start - 1 + ((a->step + i) % a->len)].g = (unsigned int) a->g *i / (a->len - 1); 
      led[a->start - 1 + ((a->step + i) % a->len)].b = (unsigned int) a->b *i / (a->len - 1);
   }
}
