// Stargate

#include "app.h"

const char *
stargate (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity checks, etc
	   if(!a->limit)a->limit=60*cps;
   }
   uint8_t top;
   int8_t dir = 1;
   if (a->top < 0)
   {
      top = a->start - a->top;
      dir = -1;
   } else
      top = a->top - a->start;
   return "No stargate yet";
}
