// Simple idle color

#include "app.h"

const char *
appidle (app_t * a)
{
   uint8_t l = 255;
   if (a->limit && a->limit - a->cycle < a->fade)
      l = 255 * (a->limit - a->cycle + 1) / a->fade;
   else if (a->fade && a->cycle < a->fade)
      l = 255 * (a->cycle + 1) / a->fade;
   for (int i = 0; i < a->len; i++)
      setl (a->start + i, a, l);
   return NULL;
}
