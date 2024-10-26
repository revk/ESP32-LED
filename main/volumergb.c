 // Bargraph (uses brightness as level)

#include "app.h"

void
pixelr (app_t * a, int pos, int p, int n, uint8_t l)
{
   uint8_t *c = a->data;
   pos -= a->start;
   if (pos < 0 || pos >= a->len)
      return;
   if (l > c[pos])
      c[pos] = l;
   else
      c[pos] = ((uint16_t) c[pos] * 15 + l) / 16;
   setR (pos + a->start, (int) a->r * c[pos] / 255);
}

void
pixelg (app_t * a, int pos, int p, int n, uint8_t l)
{
   uint8_t *c = a->data;
   c += a->len;
   pos -= a->start;
   if (pos < 0 || pos >= a->len)
      return;
   if (l > c[pos])
      c[pos] = l;
   else
      c[pos] = ((uint16_t) c[pos] * 15 + l) / 16;
   setG (pos + a->start, (int) a->g * c[pos] / 255);
}

void
pixelb (app_t * a, int pos, int p, int n, uint8_t l)
{
   uint8_t *c = a->data;
   c += a->len * 2;
   pos -= a->start;
   if (pos < 0 || pos >= a->len)
      return;
   if (l > c[pos])
      c[pos] = l;
   else
      c[pos] = ((uint16_t) c[pos] * 15 + l) / 16;
   setB (pos + a->start, (int) a->b * c[pos] / 255);
}

typedef struct
{
   uint8_t start;
   uint8_t len;
} band_t;

typedef struct
{
   band_t r,
     g,
     b;
} config_t;

const char *
appvolumergb (app_t * a)
{
   if (!a->cycle)
   {                            // Sanity check / defaults
      free (a->data);
      memset (a->data = malloc (a->len * 3 + sizeof (config_t)), 0, a->len * 3 + sizeof (config_t));
      if (!a->colourset || a->palette)
         setcolour (a, "white");
   }
   config_t *c = a->data + a->len * 3;
   if (!a->cycle)
   {
      if (a->preset && *config[a->preset - 1])
      {
         jo_t j = jo_parse_str (config[a->preset - 1]);
         if (jo_here (j) == JO_OBJECT)
         {
            while (jo_next (j) == JO_TAG)
            {
               band_t *b = NULL;
               if (!jo_strcmp (j, "r"))
                  b = &c->r;
               else if (!jo_strcmp (j, "g"))
                  b = &c->g;
               else if (!jo_strcmp (j, "b"))
                  b = &c->b;
               if (jo_next (j) != JO_ARRAY || !b)
               {
                  jo_skip (j);
                  continue;
               }
               if (jo_next (j) == JO_NUMBER)
               {
                  b->start = jo_read_int (j);
                  if (jo_next (j) == JO_NUMBER)
                     b->len = jo_read_int (j);
                  else
                     b->len = AUDIOBANDS / 3;
               }
               while (jo_here (j) && jo_here (j) != JO_CLOSE)
                  jo_skip (j);
            }
         }
         jo_free (&j);
      } else
      {                         // No config - set defaults
         c->b.start = 0;
         c->b.len = AUDIOBANDS / 4;
         c->g.start = AUDIOBANDS / 4;
         c->g.len = AUDIOBANDS / 4;
         c->r.start = AUDIOBANDS / 2;
         c->r.len = AUDIOBANDS / 2;
      }
   }
   if (c->b.len)
   {                            // Low 1/4
      float m = 0;
      for (uint8_t i = c->b.start; i < c->b.start + c->b.len && i < AUDIOBANDS; i++)
         m += audioband[i];
      int v = m * 65536 / c->b.len;
      if (v > 65535)
         v = 65535;
      bargraph (a, pixelb, v, 65535, a->fader);
   }
   if (c->g.len)
   {                            // Mid 1/4
      float m = 0;
      for (uint8_t i = c->g.start; i < c->g.start + c->g.len && i < AUDIOBANDS; i++)
         m += audioband[i];
      int v = m * 65535 / c->g.len;
      if (v > 65535)
         v = 65535;
      bargraph (a, pixelg, v, 65535, a->fader);
   }
   if (c->r.len)
   {                            // High 1/2
      float m = 0;
      for (uint8_t i = c->r.start; i < c->r.start + c->r.len && i < AUDIOBANDS; i++)
         m += audioband[i];
      int v = m * 65535 / c->r.len;
      if (v > 65535)
         v = 65535;
      bargraph (a, pixelr, v, 65535, a->fader);
   }
   return NULL;
}
