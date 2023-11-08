// Simple rainbow color

#include "app.h"

const char *
apprainbow (app_t * a)
{
   uint8_t l = 255;
   if (a->stop)
      l = 255 * a->stop / a->fade;
   else if (a->fade && a->cycle < a->fade)
      l = 255 * a->cycle / a->fade;
   for (int i = 0; i < a->len; i++)
      setrgbl (a->start + i,
               wheel[(256 * i / a->len + 85) & 255], wheel[(256 * i / a->len + 0) & 255], wheel[(256 * i / a->len + 170) & 255], l);
   return NULL;
}
