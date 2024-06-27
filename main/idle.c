// Simple idle color

#include "app.h"

const char *
appidle (app_t * a)
{
   uint8_t l = a->bright;
   if (a->stop)
      l = (int) a->bright * a->stop / a->fade;
   else if (a->fade && a->cycle < a->fade)
      l = (int) a->bright * a->cycle / a->fade;
   for (int i = 0; i < a->len; i++)
      setl (a->start + i, a, l);
   return NULL;
}
