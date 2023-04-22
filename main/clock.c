// Simple clock

#include "app.h"

struct clock_s
{
   uint8_t h0,
     m0,
     s0;
   uint8_t h1,
     m1,
     s1;
};

const char *
appclock (app_t * a)
{
   if (!a->data)
      a->data = malloc (sizeof (struct clock_s));
   struct clock_s *c = a->data;
   uint8_t top;
   int8_t dir = 1;
   if (a->top < 0)
   {
      top = -a->top - a->start;
      dir = -1;
   } else
      top = a->top - a->start;

   if (!a->cycle)
   {                            // Sanity checks, etc
      c->h0 = a->start + top;
      c->m0 = a->start + top;
      c->s0 = a->start + top;
      c->h1 = a->start + top;
      c->m1 = a->start + top;
      c->s1 = a->start + top;
      a->step = cps * 3;        // Start at 12:00
   }

   clear (a->start, a->len);
   if (a->step)
   {                            // Second fade from one to another
      uint8_t l = 255 * a->step / a->fade;
      if (a->step > a->fade)
         l = 255;

      if (c->h0 == c->h1)
         setr (c->h0, 255);
      else
      {
         setr (c->h0, 255 - l);
         setr (c->h1, l);
      }
      if (c->m0 == c->m1)
         setg (c->m0, 255);
      else
      {
         setg (c->m0, 255 - l);
         setg (c->m1, l);
      }
      if (c->s0 == c->s1)
         setb (c->s0, 255);
      else
      {
         setb (c->s0, 255 - l);
         setb (c->s1, l);
      }

      if (!--a->step)
      {
         c->h1 = c->h0;
         c->m1 = c->m0;
         c->s1 = c->s0;
         a->step = 0;
      }
      return NULL;
   }

   struct timeval tv;
   gettimeofday (&tv, NULL);
   struct tm t;
   localtime_r (&tv.tv_sec, &t);
   uint32_t s = t.tm_hour * 3600000 + t.tm_min * 60000 + t.tm_sec * 1000 + tv.tv_usec / 1000;;

   c->h0 = a->start + (a->len + top + dir * (a->len * (s % 43200000) / 43200000)) % a->len;
   c->m0 = a->start + (a->len + top + dir * (a->len * (s % 3600000) / 3600000)) % a->len;
   c->s0 = a->start + (a->len + top + dir * (a->len * (s % 60000) / 60000)) % a->len;

   setr (c->h1, 255);
   setg (c->m1, 255);
   setb (c->s1, 255);

   if (c->h0 != c->h1 || c->m0 != c->m1 || c->s0 != c->s1)
      a->step = (a->fade - 1) ? : 1;    // -1 because a fade default of cps means we can be out of step
   return NULL;
}
