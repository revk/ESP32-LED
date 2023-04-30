// Simple idle color

#include "app.h"

const char *
appidle (app_t * a)
{
   uint8_t l = 255;
   if (a->stop)
      l = 255 * a->stop / a->fade;
   else if (a->fade && a->cycle < a->fade)
      l = 255 * a->cycle / a->fade;
   for (int i = 0; i < a->len; i++)
      setl (a->start + i, a, l);
   return NULL;
}
