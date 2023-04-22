// Simple clock

#include "app.h"

const char *
appclock (app_t * a)
{
   uint8_t top;
   int8_t dir = 1;
   if (a->top < 0)
   {
      top = (leds + a->start + a->top) % leds;
      dir = -1;
   } else
      top = (leds + a->top - a->start) % leds;

   if (!a->cycle)
   {                            // Sanity checks, etc
      if (a->start + a->len - 1 > leds)
         return "Bad start";
      a->t1 = a->start + top;
      a->t2 = a->start + top;
      a->t3 = a->start + top;
      a->t4 = a->start + top;
      a->t5 = a->start + top;
      a->t6 = a->start + top;
      a->step = cps * 3;        // Start at 12:00
   }

   clear (a->start, a->len);
   if (a->step)
   {                            // Second fade from one to another
      uint8_t l = 255 * a->step / (cps - 1);
      if (a->step >= cps)
         l = 255;

      if (a->t1 == a->t4)
         setr (a->t1, 255);
      else
      {
         setr (a->t1, 255 - l);
         setr (a->t4, l);
      }
      if (a->t2 == a->t5)
         setg (a->t2, 255);
      else
      {
         setg (a->t2, 255 - l);
         setg (a->t5, l);
      }
      if (a->t3 == a->t6)
         setb (a->t3, 255);
      else
      {
         setb (a->t3, 255 - l);
         setb (a->t6, l);
      }

      if (!--a->step)
      {
         a->t4 = a->t1;
         a->t5 = a->t2;
         a->t6 = a->t3;
         a->step = 0;
      }
      return NULL;
   }

   time_t now = time (0) + 1;
   struct tm t;
   localtime_r (&now, &t);
   uint32_t s = t.tm_hour * 3600 + t.tm_min * 60 + t.tm_sec;

   a->t1 = a->start + (a->len + top + dir * (a->len * (s % 43200) / 43200)) % a->len;
   a->t2 = a->start + (a->len + top + dir * (a->len * (s % 3600) / 3600)) % a->len;
   a->t3 = a->start + (a->len + top + dir * (a->len * (s % 60) / 60)) % a->len;

   setr (a->t4, 255);
   setg (a->t5, 255);
   setb (a->t6, 255);

   if (a->t1 != a->t4 || a->t2 != a->t5 || a->t3 != a->t6)
      a->step = cps - 1;
   return NULL;
}
