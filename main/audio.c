// Simple audio color

#include "app.h"

const char *
appaudio (app_t * a)
{
   for (int i = 0; i < a->len; i++)
   {
      int v = a->fader * audioband[i * AUDIOBANDS / a->len];
      if (v > 255)
         v = 255;
      setl (a->start + i, a, v);
   }
   return NULL;
}
