// Simple drop color

#include "app.h"

typedef struct
{
   float position;              // m
   float speed;                 // m/s
   uint8_t pos;                 // used for colour pick, random
   uint8_t running:1;           // Ball running
} ball_t;

typedef struct
{
   float height;                // m, can be negative for other way
   float gravity;               // m/s/s
   float drag;                  // 0-1
   float bounce;                // 0-1
   float size;                  // m
   uint8_t balls;
   uint8_t backwards:1;
   ball_t ball[0];
} config_t;

const char *
appdrop (app_t * a)
{
   if (!a->cycle)
   {
      if (!a->colourset)
         setcolour (a, "rainbow");
      free (a->data);
      memset (a->data = malloc (sizeof (config_t)), 0, sizeof (config_t));
   }
   config_t *c = a->data;
   if (!a->cycle)
   {
      // Defaults
      c->height = 1;
      c->drag = 0.01;
      c->gravity = 1;           // 9.8;
      c->bounce = 0.3;
      c->balls = 3;
      if (a->preset && *config[a->preset - 1])
      {
         jo_t j = jo_parse_str (config[a->preset - 1]);
         if (jo_here (j) == JO_OBJECT)
         {
            void setf (const char *tag, float *fp)
            {
               if (jo_find (j, tag) == JO_NUMBER)
                  *fp = jo_read_float (j);
            }
            setf ("height", &c->height);
            setf ("gravity", &c->gravity);
            setf ("drag", &c->drag);
            setf ("bounce", &c->bounce);
            setf ("size", &c->size);
            if (jo_find (j, "balls") == JO_NUMBER)
               c->balls = jo_read_int (j);
         }
         jo_free (&j);
      }
      if (c->balls < 1)
         c->balls = 1;
      if (c->balls > 10)
         c->balls = 10;
      if (c->height == 0)
         c->height = 1;
      if (c->height < 0)
      {
         c->height = 0 - c->height;
         c->backwards = 1;
      }
      if (!c->size)
         c->size = c->height * 7 / a->len;
      c = a->data = realloc (c, sizeof (config_t) + c->balls * sizeof (ball_t));
      memset (c->ball, 0, c->balls * sizeof (ball_t));
   }
   // Start a new ball?
   for (int i = 0; i < c->balls; i++)
   {
      ball_t *b = &c->ball[i];
      if (b->running)
         continue;
      if (esp_random () % cps)
         continue;
      b->pos = esp_random ();
      if ((b->position = c->height) < 0)
         b->position = -c->height;
      b->speed = -c->gravity * (esp_random () & 255) / 256 / cps;
      b->running = 1;
      break;
   }
   // Draw and move balls
   for (int i = 0; i < c->balls; i++)
   {
      ball_t *b = &c->ball[i];
      if (!b->running)
         continue;
      int p = a->len * b->position / c->height;
      int n = a->len * c->size / c->height / 2;
      if (c->backwards)
         p = a->len - 1 - p;
      if (!n)
         n = 1;
      for (int i = 0; i < n; i++)
      {
         uint8_t l = cos8[128 * i / n];
         if (p - i >= 0)
            setl (a->start + p - i, a, b->pos, 255, l);
         if (i && p + i < a->len)
            setl (a->start + p + i, a, b->pos, 255, l);
      }
      // Move
      b->position += b->speed / cps;
      b->speed -= c->gravity / cps;
      b->speed *= (1 - c->drag / cps);
      if (b->position <= 0)
      {
         b->position = (-b->position * c->bounce);
         b->speed = (-b->speed * c->bounce);
      }
      if (b->position > c->height || (b->speed >= 0 && b->speed < c->gravity / cps && b->position < c->size))
         b->running = 0;
   }
   return NULL;
}
