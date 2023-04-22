// Stargate

#include "app.h"

const char *
appstargate (app_t * a)
{
   if (!a->data)
      a->data = malloc (a->len * 2 + 1);
   uint8_t *old = a->data,
      *new = old + a->len,
      *posp = new + a->len,
      pos = *posp;
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
      if (!a->limit)
         a->limit = 60 * cps;
   }

   if (!a->cycle)
   {
      a->step = a->fade;
      pos = esp_random ();
   }

   void ring (uint8_t l)
   {
      for (unsigned int i = 0; i < a->len; i++)
         setl (a->start + i, a, (int) l * cos8[(256 * i / a->len + pos) & 255] / 255);
   }
   void chevron (uint8_t n, uint8_t l)
   {

   }

   if (!a->stage)
   {                            // Fade up
      ring (255 * a->step / a->fade);
      if (!--a->fade)
      {
         a->stage = 10;
         a->step = a->speed + esp_random () % (a->speed * 2);
      }
   } else if (a->stage < 100)
   {                            // Dialling

   } else
   {                            // Twinkling

   }
   *posp = pos;
   return "No stargate yet";
}
