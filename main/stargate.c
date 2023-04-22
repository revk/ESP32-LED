// Stargate

#include "app.h"
#define SPEED 2                 // Seconds per spin?

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
      top = (leds - a->top - a->start) % leds;
      dir = -1;
   } else
      top = (leds + a->top - a->start) % leds;

   if (!a->cycle)
   {                            // Sanity checks, etc
      if (!a->limit)
         a->limit = 60 * cps;
      a->step = a->fade;
      pos = esp_random ();
      if (!a->colourset)
         a->b = 63;             // Default ring blue
   }

   void ring (uint8_t l)
   {
      for (unsigned int i = 0; i < a->len; i++)
         setl (a->start + i, a, (int) l * cos8[(256 * i / a->len + pos) & 255] / 255);
   }
   void chevron (uint8_t n, uint8_t l)
   {
      switch (n)
      {
      case 0:
         n = top;
         break;
      case 1:
         n = (top + a->len - dir * 4 * a->len / 39) % a->len;
         break;
      case 2:
         n = (top + a->len + dir * 4 * a->len / 39) % a->len;
         break;
      case 3:
         n = (top + a->len - dir * 8 * a->len / 39) % a->len;
         break;
      case 4:
         n = (top + a->len + dir * 8 * a->len / 39) % a->len;
         break;
      case 5:
         n = (top + a->len - dir * 12 * a->len / 39) % a->len;
         break;
      case 6:
         n = (top + a->len + dir * 12 * a->len / 39) % a->len;
         break;
      case 7:
         n = top;
         break;
      default:
         return;
      }
      if (getr (a->start + n) < l)
         setr (a->start + n, l);
      if (getg (a->start + n) < l)
         setg (a->start + n, l);
   }
   void twinkle (void)
   {
      memcpy (old, new, a->len);
      esp_fill_random (new, a->len);
      for (int i = 0; i < a->len; i++)
         new[i] = new[i] / 4 + 32;
   }

   if (!a->stage)
   {                            // Fade up
      ring (255 * (a->fade - a->step) / a->fade);
      if (!--a->step)
      {
         a->stage = 10;
         a->step = a->speed + esp_random () % (a->speed * 2);
      }
   } else if (a->stage < 100)
   {                            // Dialling
      ring (255);
      for (int i = 1; i < a->stage / 10; i++)
         chevron (i, 255);
      if (!(a->stage % 10))
      {                         // Dial
         if ((a->stage / 20) % 2)
            pos += 256 / a->speed / SPEED;
         else
            pos -= 256 / a->speed / SPEED;
         if (!--a->step)
         {
            a->stage++;
            a->step = a->fade;
         }
      } else if ((a->stage % 10) == 1)
      {                         // Lock top
         chevron (0, 255 * (a->fade - a->step) / a->fade);
         if (!--a->step)
         {
            a->stage++;
            a->step = a->fade;
         }
      } else if (a->stage == 72)
      {                         // Open gate
         chevron (0, 255);
         uint8_t l = 255 * (a->fade - a->step) / a->fade;
         for (int i = 0; i < a->len; i++)
         {
            if (getr (a->start + i) < l)
               setr (a->start + i, l);
            if (getg (a->start + i) < l)
               setg (a->start + i, l);
            if (getb (a->start + i) < l)
               setb (a->start + i, l);
         }
         if (!--a->step)
         {                      // Next chevron
            a->stage = 100;
            a->step = a->fade;
            memset (new, 255, a->len);
            twinkle ();
         }
      } else if ((a->stage % 10) == 2)
      {                         // Chevron
         chevron (0, 255 * a->step / a->fade);
         chevron (a->stage / 10, 255 * (a->fade - a->step) / a->fade);
         if (!--a->step)
         {                      // Next chevron
            a->stage += 8;
            a->step = a->speed + esp_random () % (a->speed * 2);
         }
      }
   } else
   {                            // Twinkling
      for (int i = 0; i < a->len; i++)
      {
         uint8_t l = (int) (a->fade - a->step) * new[i] / a->fade + (int) a->step * old[i] / a->fade;
         if (a->limit && (a->limit - a->cycle) < a->fade)
            l = (a->limit - a->cycle) * l / a->fade;
         setrgb (a->start + i, l, l, l);
      }
      if (!--a->step)
      {                         // Next
         a->step = a->fade;
         twinkle ();
      }
   }
   *posp = pos;
   return NULL;
}
