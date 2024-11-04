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
      memset (a->data = mallocspi (a->len * 3 + sizeof (config_t)), 0, a->len * 3 + sizeof (config_t));
      if (!a->colourset || a->palette)
         setcolour (a, "white");
   }
   config_t *c = a->data + a->len * 3;
   if (!a->cycle)
   {
      if (a->config)
      {
         jo_t j = jo_parse_str (a->config);
         if (jo_here (j) == JO_OBJECT)
         {
            uint8_t band (void)
            {
               int v = jo_read_int (j);
               if (v >= AUDIOBANDS)
                  v = audiohz2band (v);
               return v;
            }
            void set (band_t * b, const char *tag)
            {
               jo_type_t t = jo_find (j, tag);
               if (!t)
                  return;
               b->len = AUDIOBANDS / 3;
               if (t == JO_NUMBER)
                  b->start = band ();
               else if (t == JO_ARRAY)
               {
                  if (jo_next (j) != JO_NUMBER)
                     return;
                  b->start = band ();
                  if (jo_next (j) != JO_NUMBER)
                     return;
                  b->len = band () - b->start;
               }
            }
            set (&c->r, "r");
            set (&c->g, "g");
            set (&c->b, "b");
         }
         jo_free (&j);
      }
      if (!c->b.len && !c->r.len && !c->g.len)
      {                         // No r/g/b config - set defaults
         c->b.start = 0;
         c->b.len = AUDIOBANDS / 3;
         c->g.start = AUDIOBANDS / 3;
         c->g.len = AUDIOBANDS / 3;
         c->r.start = 2 * AUDIOBANDS / 3;
         c->r.len = AUDIOBANDS / 3;
      }
      // Report config
      jo_t n = jo_object_alloc ();
      if (c->b.len)
      {
         jo_array (n, "b");
         jo_int (n, NULL, audioband2hz (c->b.start));
         jo_int (n, NULL, audioband2hz (c->b.start + c->b.len));
         jo_close (n);
      }
      if (c->g.len)
      {
         jo_array (n, "g");
         jo_int (n, NULL, audioband2hz (c->g.start));
         jo_int (n, NULL, audioband2hz (c->g.start + c->g.len));
         jo_close (n);
      }
      if (c->r.len)
      {
         jo_array (n, "r");
         jo_int (n, NULL, audioband2hz (c->r.start));
         jo_int (n, NULL, audioband2hz (c->r.start + c->r.len));
         jo_close (n);
      }
      char *was = a->config;
      a->config = jo_finisha (&n);
      free (was);
   }
   if (c->b.len)
   {                            // Low 1/4
      float m = 0;
      for (uint8_t i = c->b.start; i < c->b.start + c->b.len && i < AUDIOBANDS; i++)
         m += audioband[i];
      int v = m * 65536 / c->b.len;
      if (m < 0)
         v = 0;
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
      if (m < 0)
         v = 0;
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
      if (m < 0)
         v = 0;
      if (v > 65535)
         v = 65535;
      bargraph (a, pixelr, v, 65535, a->fader);
   }
   return NULL;
}
