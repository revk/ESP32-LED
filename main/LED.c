/* LED app */
/* Copyright ©2019 - 23 Adrian Kennard, Andrews & Arnold Ltd.See LICENCE file for details .GPL 3.0 */

static const char TAG[] = "LED";

#include "revk.h"
#include "esp_sleep.h"
#include "esp_task_wdt.h"
#include <driver/gpio.h>
#include <driver/uart.h>
#include <driver/i2c.h>
#include <driver/i2s_pdm.h>
#include "led_strip.h"
#include "app.h"
#include <esp_http_server.h>
#include "fft.h"
#include "math.h"

#define a(a,d)	extern const char* app##a(app_t*);
#include "apps.h"

struct applist_s
{
   const char *name;
   app_f *app;
   uint8_t ring:1;              // Is a ring based app
   uint8_t text:1;              // Is a text based app
} applist[] = {
#define a(a,d)	{#a,&app##a,0,0},
#define r(a,d)	{#a,&app##a,1,0},
#define t(a,d)	{#a,&app##a,0,1},
#include "apps.h"
};

struct
{
   uint8_t haconfig:1;          // Send config
   uint8_t hacheck:1;           // Check presets
} b;

static httpd_handle_t webserver = NULL;

int ledmax = 0;                 // Total LEDs
#define	STRIPS	(sizeof(leds)/sizeof(leds[0]))

uint8_t *ledr = NULL;
uint8_t *ledg = NULL;
uint8_t *ledb = NULL;
uint8_t *ledw = NULL;

uint8_t gatedial = 0;

const uint8_t cos8[256] =
   { 255, 255, 255, 255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 249, 248, 247, 246, 245, 243, 242, 240, 239, 237, 236, 234,
   232, 230, 228, 226, 224, 222, 220, 218, 216, 213, 211, 209, 206, 204, 201, 199, 196, 193, 191, 188, 185, 182, 179, 176, 174, 171,
   168, 165, 162, 159,
   156, 152, 149, 146, 143, 140, 137, 134, 131, 127, 124, 121, 118, 115, 112, 109, 106, 103, 99, 96, 93, 90, 87, 84, 81, 79, 76, 73,
   70, 67, 64, 62, 59,
   56, 54, 51, 49, 46, 44, 42, 39, 37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1,
   0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 15, 16, 18, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 42, 44, 46, 49,
   51, 54, 56, 59, 62,
   64, 67, 70, 73, 76, 79, 81, 84, 87, 90, 93, 96, 99, 103, 106, 109, 112, 115, 118, 121, 124, 127, 131, 134, 137, 140, 143, 146,
   149, 152, 156, 159, 162,
   165, 168, 171, 174, 176, 179, 182, 185, 188, 191, 193, 196, 199, 201, 204, 206, 209, 211, 213, 216, 218, 220, 222, 224, 226, 228,
   230, 232, 234, 236,
   237, 239, 240, 242, 243, 245, 246, 247, 248, 249, 250, 251, 252, 252, 253, 254, 254, 255, 255, 255, 255, 255
};

const uint8_t wheel[256] =
   { 0, 0, 0, 0, 1, 2, 3, 4, 5, 7, 8, 10, 12, 14, 16, 19, 21, 24, 27, 30, 33, 36, 40, 43, 47, 50, 54, 58, 62, 66, 70, 75, 79, 83,
   88, 92, 97, 102, 106, 111, 116, 120, 125, 130, 135, 139, 144, 149, 153, 158, 163, 167, 172, 176, 180, 185, 189, 193, 197, 201,
   205, 208, 212, 215,
   219, 222, 225, 228, 231, 234, 236, 239, 241, 243, 245, 247, 248, 250, 251, 252, 253, 254, 255, 255, 255, 255, 255, 255, 255, 254,
   253, 252, 251, 250,
   248, 247, 245, 243, 241, 239, 236, 234, 231, 228, 225, 222, 219, 215, 212, 208, 205, 201, 197, 193, 189, 185, 180, 176, 172, 167,
   163, 158, 153, 149,
   144, 139, 135, 130, 125, 120, 116, 111, 106, 102, 97, 92, 88, 83, 79, 75, 70, 66, 62, 58, 54, 50, 47, 43, 40, 36, 33, 30, 27, 24,
   21, 19, 16, 14, 12,
   10, 8, 7, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0
};

const uint8_t zig[256] =
   { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64,
   66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122,
   124, 126, 128, 130,
   132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182,
   184, 186, 188,
   190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 238, 240,
   242, 244, 246,
   248, 250, 252, 255, 253, 251, 249, 247, 245, 243, 241, 239, 237, 235, 233, 231, 229, 227, 225, 223, 221, 219, 217, 215, 213, 211,
   209, 207, 205,
   203, 201, 199, 197, 195, 193, 191, 189, 187, 185, 183, 181, 179, 177, 175, 173, 171, 169, 167, 165, 163, 161, 159, 157, 155, 153,
   151, 149, 147,
   145, 143, 141, 139, 137, 135, 133, 131, 129, 127, 125, 123, 121, 119, 117, 115, 113, 111, 109, 107, 105, 103, 101, 99, 97, 95,
   93, 91, 89, 87, 85,
   83, 81, 79, 77, 75, 73, 71, 69, 67, 65, 63, 61, 59, 57, 55, 53, 51, 49, 47, 45, 43, 41, 39, 37, 35, 33, 31, 29, 27, 25, 23, 21,
   19, 17, 15, 13, 11,
   9, 7, 5, 3, 1
};

app_t active[MAXAPPS] = { 0 };

uint64_t haon = 0;              // Bits, which are on
uint64_t hachanged = 0;         // Bits, which are changed and need updating to active[]
uint64_t hastatus = 0;          // Bits, which need status report
uint64_t hargb = 0;             // Bits, if rgb set from HA
uint64_t habrightset = 0;       // Bits, if bright set from HA
// Bits, HA sent a colour
uint8_t har[CONFIG_REVK_WEB_EXTRA_PAGES] = { 0 };       // Colour
uint8_t hag[CONFIG_REVK_WEB_EXTRA_PAGES] = { 0 };
uint8_t hab[CONFIG_REVK_WEB_EXTRA_PAGES] = { 0 };
uint8_t haw[CONFIG_REVK_WEB_EXTRA_PAGES] = { 0 };
uint8_t habright[CONFIG_REVK_WEB_EXTRA_PAGES] = { 0 };  // Brightness
const char *haeffect[CONFIG_REVK_WEB_EXTRA_PAGES] = { 0 };      // Selected effect from HA

static SemaphoreHandle_t app_mutex = NULL;

void
appzap (app_t * a)
{                               // Assumes mutex, Delete an app
   free (a->data);
   memset (a, 0, sizeof (*a));
}

app_t *
addapp (int index, int preset, const char *name, jo_t j)
{                               // Assumes mutex, store an app
   if (index >= MAXAPPS)
      return NULL;
   if (!strcmp (name, "*") && preset && haeffect[preset - 1] && *haeffect[preset - 1])
      name = haeffect[preset - 1];
   app_t *a = &active[index];
   if (!name || !*name)
   {
      appzap (a);
      return NULL;
   }
   for (int i = 0; i < sizeof (applist) / sizeof (*applist); i++)
      if (!strcasecmp (name, applist[i].name))
      {
         uint8_t setcolourstr (char *temp)
         {
            if (!strcasecmp (temp, "rainbow"))
               a->colourset = a->rainbow = 1;
            else if (!strcasecmp (temp, "cycling"))
               a->colourset = a->cycling = 1;
            else if (!strcasecmp (temp, "wheel"))
               a->colourset = a->wheel = 1;
            else if (rgbw && !strcasecmp (temp, "white"))
               strcpy (temp, "#000F");
#define	c(h,c)	else if(!strcasecmp(temp,#c))strcpy(temp,#h);
            colours
#undef c
            char *c = temp;
            if (*c == '#')
               c++;
#define x(n)((c[n] & 0xF) + (isalpha ((uint8_t)c[n]) ? 9 : 0))
            if (isxdigit ((int) c[0]) && isxdigit ((int) c[1]) && isxdigit ((int) c[2]))
            {
               if (!c[3])
               {                // RGB
                  a->colourset = 1;
                  a->r = x (0) * 17;
                  a->g = x (1) * 17;
                  a->b = x (2) * 17;
                  a->w = 0;
               } else if (isxdigit ((int) c[3]))
               {
                  if (!c[4])
                  {             // # RGBW
                     a->colourset = 1;
                     a->r = x (0) * 17;
                     a->g = x (1) * 17;
                     a->b = x (2) * 17;
                     a->w = x (3) * 17;
                  } else if (isxdigit ((int) c[4]) && isxdigit ((int) c[5]))
                  {
                     if (!c[6])
                     {          // # RRGGBB
                        a->colourset = 1;
                        a->r = x (0) * 16 + x (1);
                        a->g = x (2) * 16 + x (3);
                        a->b = x (4) * 16 + x (5);
                        a->w = 0;
                     } else if (isxdigit ((int) c[6]) && isxdigit ((int) c[7]))
                     {          // # RRGGBBWW
                        if (!c[8])
                        {
                           a->colourset = 1;
                           a->r = x (0) * 16 + x (1);
                           a->g = x (2) * 16 + x (3);
                           a->b = x (4) * 16 + x (5);
                           a->w = x (6) * 16 + x (7);
                        } else
                           return 0;
                     }
                  }

               }
            } else
               return 0;
            return 1;
#undef x
         }
         uint8_t setcolour (jo_t j)
         {
            char temp[20];
            jo_strncpy (j, temp, sizeof (temp));
            return setcolourstr (temp);
         }
         if (!a->app || a->name != applist[i].name || a->stop)
            appzap (a);
         a->name = applist[i].name;
         if (*colour[preset ? preset - 1 : 0])
            setcolourstr (colour[preset ? preset - 1 : 0]);
#define u8(s,n,d)         a->n=n[preset?preset-1:0];
#define u8d(s,n,d)        u8(s,n,d)
#define u8r(s,n,d)        u8(s,n,d)
#define u16(s,n,d)         u8(s,n,d)
#define u16r(s,n,d)        u8r(s,n,d)
#define s8(s,n,d)        u8(s,n,d)
#define s8r(s,n,d)        u8r(s,n,d)
#define s16r(s,n,d)        u16r(s,n,d)
#define u32(s,n,d)        u8(s,n,d)
#define u32d(s,n,d)        u8(s,n,d)
         params
#undef  u8
#undef  u8d
#undef  u8r
#undef  u16
#undef  u16r
#undef  s8
#undef  s8r
#undef  s16r
#undef  u32
#undef  u32d
            if (j && jo_here (j) == JO_OBJECT)
         {                      // Expects to be at start of object
            while (jo_next (j) == JO_TAG)
            {
#define u8(s,n,d)         if(!jo_strcmp(j,#n)||!jo_strcmp(j,#s)){if(jo_next(j)==JO_NUMBER)a->n=jo_read_int(j);continue;}
#define u8d(s,n,d)         if(!jo_strcmp(j,#n)||!jo_strcmp(j,#s)){if(jo_next(j)==JO_NUMBER)a->n=0.5+speed_scale*jo_read_float(j);continue;}
#define u8r(s,n,d)        u8(s,n,d)
#define u16(s,n,d)        u8(s,n,d)
#define u16r(s,n,d)        u8(s,n,d)
#define s8(s,n,d)        u8(s,n,d)
#define s8r(s,n,d)        u8(s,n,d)
#define s16r(s,n,d)        u8(s,n,d)
#define u32(s,n,d)        u8(s,n,d)
#define u32d(s,n,d)        u8d(s,n,d)
               params
#undef  u8
#undef  u8d
#undef  u8r
#undef  u16
#undef  u16r
#undef  s8
#undef  s8r
#undef  s16r
#undef  u32
#undef  u32d
                  if (!jo_strcmp (j, "colour") || !jo_strcmp (j, "#"))
               {
                  if (jo_next (j) == JO_STRING)
                     setcolour (j);
                  continue;
               }
               if (!jo_strcmp (j, "data"))
               {
                  if (jo_next (j) == JO_STRING)
                  {
                     free (a->data);
                     int l = jo_strlen (j);
                     if (l)
                        jo_strncpy (j, a->data = malloc (l + 1), l + 1);
                  }
                  continue;
               }
               jo_next (j);     // Skip
            }
         } else if (j && jo_here (j) == JO_STRING)
         {
            if (!setcolour (j))
            {                   // data
               free (a->data);
               int l = jo_strlen (j);
               if (l)
                  jo_strncpy (j, a->data = malloc (l + 1), l + 1);
            }
         } else if (j && jo_here (j) == JO_NUMBER)
            a->limit = limit_scale * jo_read_float (j); // Defaults
         if (preset && preset <= CONFIG_REVK_WEB_EXTRA_PAGES)
         {                      // preset based settings
            if (!a->colourset && (hargb & (1ULL << (preset - 1))))
            {
               a->r = har[preset - 1];
               a->g = hag[preset - 1];
               a->b = hab[preset - 1];
               a->w = haw[preset - 1];
               if (a->r || a->g || a->b || a->w)
                  a->colourset = 1;
            }
            if (!a->bright && (habrightset & (1ULL << (preset - 1))))
               a->bright = habright[preset - 1];
         }
         if (!a->start)
            a->start = 1;
         if (!a->top)
            a->top = a->start;
         if (!a->len)
            a->len = ledmax + 1 - a->start;
         if (!a->speed)
            a->speed = speed_scale;     //  1.0 s
         if (!a->fadein)
            a->fadein = fadein_scale;   //  1.0 s
         if (!a->fadeout)
            a->fadeout = fadeout_scale; //  1.0 s
         if (!a->bright)
            a->bright = 255;
         if (!a->height)
            a->height = 8;      //  Adjust for scale and cps
         a->delay = cps * a->delay / delay_scale;
         a->limit = cps * a->limit / limit_scale;
         a->speed = cps * a->speed / speed_scale ? : 1;
         a->fadein = cps * a->fadein / fadein_scale ? : 1;
         a->fadeout = cps * a->fadeout / fadeout_scale ? : 1;
         a->app = applist[i].app;
         a->preset = preset;
         ESP_LOGI (TAG, "Adding app %d: %s (%lu)", index, name, a->cycle);
         return a;
      }
   appzap (a);
   ESP_LOGE (TAG, "App not found %s", name);
   jo_t e = jo_object_alloc ();
   jo_int (j, "level", index);
   jo_string (e, "app", name);
   revk_error ("not-found", &e);
   return NULL;
}

void
appzapall (int index)
{                               // Assumes mutex, clears all apps at index to end(except preset)
   while (index < MAXAPPS)
   {
      if (!active[index].preset)
         appzap (&active[index]);
      index++;
   }
}

int
apptidy (uint8_t stop)
{                               // Assumes mutex, packs all apps to start, if stop set then stops active (non preset) apps, returns first unused app (must be checked against MAXAPPS)
   int i = 0,
      o = 0;
   while (i < MAXAPPS)
   {
      app_t *a = &active[i];
      if (stop && a->delay)
         appzap (a);            // Not started, so simply zap
      if (stop && a->app && !a->stop && !a->preset)
         a->stop = a->fadeout;  // Running, so controlled stop
      if (a->app)
      {                         // Copy down running apps
         if (i != o)
         {
            active[o++] = *a;
            memset (a, 0, sizeof (*a)); // Does not free stuff in it as moved down.
         }
         o++;
      }
      i++;
   }
   return o;
}

const char *
led_stop (void)
{
   ESP_LOGE (TAG, "Stop");
   xSemaphoreTake (app_mutex, portMAX_DELAY);
   apptidy (1);
   xSemaphoreGive (app_mutex);
   return "";
}

const char *
led_add (const char *tag, int preset, jo_t j)
{
   if (!strcmp (tag, "*") && preset && haeffect[preset - 1] && *haeffect[preset - 1])
      tag = haeffect[preset - 1];
   for (int i = 0; i < sizeof (applist) / sizeof (*applist); i++)
      if (!strcasecmp (tag, applist[i].name))
      {                         // Direct command
         xSemaphoreTake (app_mutex, portMAX_DELAY);
         int index = apptidy (1);
         addapp (index++, preset, tag, j);
         xSemaphoreGive (app_mutex);
         return "";
      }
   return NULL;
}

int
app_json (int index, int preset, jo_t j)
{                               // Add apps from JSON
   jo_type_t t = jo_here (j);
   if (t == JO_STRING)
   {                            // Simple add app
      char temp[20];
      jo_strncpy (j, temp, sizeof (temp));
      if (!strcasecmp (temp, "stop"))
         led_stop ();
      else
         addapp (index++, preset, temp, NULL);
   } else if (t == JO_ARRAY)
   {
      while ((t = jo_next (j)) == JO_STRING)
      {
         char temp[20];
         jo_strncpy (j, temp, sizeof (temp));
         addapp (index++, preset, temp, NULL);
      }
   } else if (t == JO_OBJECT)
   {
      while ((t = jo_next (j)) == JO_TAG)
      {
         char temp[20];
         jo_strncpy (j, temp, sizeof (temp));
         t = jo_next (j);
         if (t != JO_OBJECT)
            break;
         addapp (index++, preset, temp, j);
      }
   }
   appzapall (index);
   return index;
}

void
presetcheck (void)
{                               // Check presets are off
   xSemaphoreTake (app_mutex, portMAX_DELAY);
   b.hacheck = 0;
   uint64_t found = 0;
   uint64_t changed = hachanged;
   hachanged = 0;
   for (int index = 0; index < MAXAPPS; index++)
   {
      app_t *a = &active[index];
      if (!a->preset || a->stop)
         continue;
      if (haon & (1ULL << (a->preset - 1)))
      {                         // Update in situe
         found |= (1ULL << (a->preset - 1));
         if (changed & (1ULL << (a->preset - 1)))
         {                      // Update settings
            a->r = har[a->preset - 1];
            a->g = hag[a->preset - 1];
            a->b = hab[a->preset - 1];
            a->w = haw[a->preset - 1];
            a->bright = habright[a->preset - 1];
            hastatus |= (1ULL << (a->preset - 1));
         }
         continue;
      }
      a->stop = a->fadeout;
      hastatus |= (1ULL << (a->preset - 1));
   }
   found = (haon & ~found);     // Which should be on and not
   if (found)
   {                            // add missing
      int index = apptidy (0);
      for (int preset = 0; preset < CONFIG_REVK_WEB_EXTRA_PAGES; preset++)
         if (found & (1ULL << preset))
         {
            jo_t j = jo_parse_str (config[preset]);
            if (haeffect[preset])
               addapp (index++, preset + 1, haeffect[preset], j);       // Effect based, set via HA
            else if (*effect[preset])
               addapp (index++, preset + 1, effect[preset], j); // Effect based based, preset
            else if (*config[preset])
               index = app_json (index, preset + 1, j); // Config based
            else
               addapp (index++, preset + 1, "idle", j); // Effect based, default idle as not set
            jo_free (&j);
            hastatus |= (1ULL << preset);
         }
   }
   xSemaphoreGive (app_mutex);
}

const char *
app_callback (int client, const char *prefix, const char *target, const char *suffix, jo_t j)
{
   if (client || !prefix || target || strcmp (prefix, topiccommand))
      return NULL;              // Not for us or not a command from main MQTTS
   if (suffix && ((haenable && (!strcmp (suffix, "connect") || !strcmp (suffix, "status"))) || !strcmp (suffix, "setting")))
   {
      b.haconfig = 1;
      b.hacheck = 1;
      hastatus = -1;
   }
   if (poweron && suffix && !strcmp (suffix, "init") && *effect[0])
   {                            // Power on init
      haon |= 1;
      hachanged |= 1;
      return NULL;
   }
   if (suffix && isdigit ((int) (uint8_t) * suffix))
   {                            // HA command or web button
      char val[20];
      int preset = atoi (suffix);
      if (!preset || preset > CONFIG_REVK_WEB_EXTRA_PAGES)
         return "Unknown preset number";
      if (!j || jo_find (j, "app"))
         haon ^= (1ULL << (preset - 1));        // Just toggle
      else
      {
         if (jo_find (j, "state"))
         {                      // ON / OFF
            jo_strncpy (j, val, sizeof (val));
            if (!strcmp (val, "ON"))
               haon |= (1ULL << (preset - 1));
            else
               haon &= ~(1ULL << (preset - 1));
         }
         if (jo_find (j, "brightness"))
         {
            habright[preset - 1] = jo_read_int (j);
            habrightset |= (1ULL << (preset - 1));
         }
         if (jo_find (j, "color"))
         {                      // r / g / b
            while (jo_next (j) == JO_TAG)
            {
               jo_strncpy (j, val, sizeof (val));
               if (jo_next (j) != JO_NUMBER)
                  break;
               int v = jo_read_int (j);
               if (!strcmp (val, "r"))
                  har[preset - 1] = v;
               else if (!strcmp (val, "g"))
                  hag[preset - 1] = v;
               else if (!strcmp (val, "b"))
                  hab[preset - 1] = v;
               else if (!strcmp (val, "w"))
                  haw[preset - 1] = v;
            }
            if (har[preset - 1] || hag[preset - 1] || hab[preset - 1] || (rgbw && haw[preset - 1]))
               hargb |= (1ULL << (preset - 1));
            else
               hargb &= ~(1ULL << (preset - 1));        // Black considered unset
         }
         if (jo_find (j, "effect"))
         {                      // effect
            if (*effect[preset - 1])
               return "Effect not expected";
            jo_strncpy (j, val, sizeof (val));
            int i;
            for (i = 0; i < sizeof (applist) / sizeof (*applist); i++)
               if (!strcasecmp (val, applist[i].name))
                  break;
            if (i == sizeof (applist) / sizeof (*applist))
               return "Unknown effect";
            if (haeffect[preset - 1] != applist[i].name)
            {
               for (int index = 0; index < MAXAPPS; index++)
                  if (active[index].preset == preset && !active[index].stop)
                     active[index].stop = active[index].fadeout;        // Old effect stops
               haeffect[preset - 1] = applist[i].name;
            }
         }
      }
      hachanged |= (1ULL << (preset - 1));
      b.hacheck = 1;
      return NULL;
   }
   if (suffix && (!strcasecmp (suffix, "stop") || !strcasecmp (suffix, "upgrade")))
      return led_stop ();
   if (suffix && !strncasecmp (suffix, "power", 5))
   {                            // Like tasmota
      int preset = atoi (suffix + 5) ? : 1;
      if (!preset || preset > CONFIG_REVK_WEB_EXTRA_PAGES)
         return "Unknown preset number";
      char val[10] = "";
      jo_strncpy (j, val, sizeof (val));
      if (!strcasecmp (val, "off") || !strcmp (val, "0"))
         haon &= ~(1ULL << (preset - 1));       // Off
      else if (!strcasecmp (val, "on") || !strcmp (val, "1") || !strcasecmp (val, "blink"))
         haon |= (1ULL << (preset - 1));        // On(blink may as well be on)
      else if (!strcasecmp (val, "2"))
         haon ^= (1ULL << (preset - 1));        // Toggle
      hachanged |= (1ULL << (preset - 1));
      b.hacheck = 1;
      return NULL;
   }
   if (suffix && strcmp (suffix, "add"))
      return led_add (suffix, 0, j);    // Process command to set apps
   xSemaphoreTake (app_mutex, portMAX_DELAY);
   int index = apptidy (suffix ? 0 : 1);
   if (!suffix)
      index = 0;                // Overwrite existing
   index = app_json (index, 0, j);
   xSemaphoreGive (app_mutex);
   return NULL;
}

static void
send_ha_status (void)
{
   uint64_t send = hastatus;
   hastatus = 0;
   for (int preset = 0; preset < CONFIG_REVK_WEB_EXTRA_PAGES; preset++)
      if ((send & (1ULL << preset)) && *name[preset])
      {
         jo_t j = jo_object_alloc ();
         jo_string (j, "state", (haon & (1ULL << preset)) ? "ON" : "OFF");
         jo_int (j, "brightness", habright[preset]);
         jo_string (j, "color_mode", rgbw ? "rgbw" : "rgb");
         if (!*effect[preset] && haeffect[preset])
            jo_string (j, "effect", haeffect[preset]);
         if (hargb & (1ULL << preset))
         {
            jo_object (j, "color");
            jo_int (j, "r", har[preset]);
            jo_int (j, "g", hag[preset]);
            jo_int (j, "b", hab[preset]);
            if (rgbw)
               jo_int (j, "w", haw[preset]);
         }
         char topic[10];
         snprintf (topic, sizeof (topic), "ha%d", preset + 1);
         revk_state (topic, &j);
      }
}

static void
send_ha_config (void)
{
   b.haconfig = 0;
   char *hastatus = revk_topic (topicstate, NULL, "ha");
   char *lwt = revk_topic (topicstate, NULL, NULL);
   char *cmd = revk_topic (topiccommand, NULL, NULL);
   char *topic;
   jo_t make (int i, const char *icon)
   {
      jo_t j = jo_object_alloc ();
      jo_stringf (j, "unique_id", "%s-%d", revk_id, i + 1);
      jo_object (j, "dev");
      jo_array (j, "ids");
      jo_string (j, NULL, revk_id);
      jo_close (j);
      jo_string (j, "name", hostname);
      jo_string (j, "sw", revk_version);
      jo_string (j, "mdl", appname);
      jo_string (j, "mf", "RevK");
      jo_stringf (j, "cu", "http://%s.local/", hostname);
      jo_close (j);
      if (icon)
         jo_string (j, "icon", icon);
      jo_string (j, "avty_t", lwt);
      jo_string (j, "avty_tpl", "{{value_json.up}}");
      jo_bool (j, "pl_avail", 1);
      jo_bool (j, "pl_not_avail", 0);
      return j;
   }
   for (int i = 0; i < CONFIG_REVK_WEB_EXTRA_PAGES; i++)
      if (asprintf (&topic, "homeassistant/light/%s-%d/config", revk_id, i + 1) >= 0)
      {
         if (!haenable || !*name[i])
            revk_mqtt_send (NULL, 1, topic, NULL);
         else
         {
            jo_t j = make (i, "mdi:led-strip");
            jo_string (j, "name", name[i]);
            jo_stringf (j, "cmd_t", "%s/%d", cmd, i + 1);
            jo_stringf (j, "stat_t", "%s%d", hastatus, i + 1);
            jo_string (j, "schema", "json");
            jo_bool (j, "brightness", 1);
            jo_array (j, "supported_color_modes");
            jo_string (j, NULL, rgbw ? "rgbw" : "rgb");
            jo_close (j);
            if (!*effect[i])
            {
               jo_bool (j, "effect", 1);
               jo_array (j, "effect_list");
               for (int i = 0; i < sizeof (applist) / sizeof (*applist); i++)
                  if (!applist[i].text)
                     jo_string (j, NULL, applist[i].name);
            }
            revk_mqtt_send (NULL, 1, topic, &j);
         }
         free (topic);
      }
   free (hastatus);
   free (lwt);
   free (cmd);
}

void
led_task (void *x)
{
   if (!rgb[0].set || !(gpio_ok (rgb[0].num) & 1))
   {
      ESP_LOGE (TAG, "Bad GPIO %d", rgb[0].num);
      vTaskDelete (NULL);
      return;
   }
   uint8_t led_status = (blink[0].num == rgb[0].num ? 1 : 0);
   if (!led_status)
      revk_blink_init ();       // Library blink
   led_strip_handle_t strip[STRIPS] = { 0 };
   for (int s = 0; s < STRIPS; s++)
      if (leds[s])
      {
         ledmax += leds[s];
         ESP_LOGE (TAG, "Started using GPIO %d%s, %d LEDs%s", rgb[s].num, rgb[s].invert ? " (inverted)" : "", leds[s],
                   led_status ? dark ? " (plus status, dark)" : " (plus status)" : "");
         led_strip_config_t strip_config = {
            .strip_gpio_num = rgb[s].num,
            .max_leds = leds[s] + (s ? 0 : led_status), // The number of LEDs in the strip,
            .led_pixel_format = rgbw ? LED_PIXEL_FORMAT_GRBW : LED_PIXEL_FORMAT_GRB,    // Pixel format of your LED strip
            .led_model = sk6812 ? LED_MODEL_SK6812 : LED_MODEL_WS2812,  // LED strip model
            .flags.invert_out = rgb[s].invert,  // whether to invert the output signal(useful when your hardware has a level inverter)
         };
         led_strip_rmt_config_t rmt_config = {
            .clk_src = RMT_CLK_SRC_DEFAULT,     // different clock source can lead to different power consumption
            .resolution_hz = 10 * 1000 * 1000,  // 10 MHz
#ifdef	CONFIG_IDF_TARGET_ESP32S3
            .flags.with_dma = true,
#endif
         };
         REVK_ERR_CHECK (led_strip_new_rmt_device (&strip_config, &rmt_config, &strip[s]));
         REVK_ERR_CHECK (led_strip_clear (strip[s]));
      }
   if (!ledmax)
      ledmax = 1;
   ledr = calloc (ledmax, sizeof (*ledr));
   ledg = calloc (ledmax, sizeof (*ledg));
   ledb = calloc (ledmax, sizeof (*ledb));
   if (rgbw)
      ledw = calloc (ledmax, sizeof (*ledw));
   if (poweron && *effect[0])
   {                            // Light 1 is default
      haon = 1;
      hachanged = 1;
      b.hacheck = 1;
   }
   uint32_t tick = 1000000LL / cps;
   while (1)
   {                            // Main loop
      if (b.hacheck)
         presetcheck ();
      if (b.haconfig)
         send_ha_config ();
      if (hastatus)
         send_ha_status ();
      usleep (tick - (esp_timer_get_time () % tick));
      clear (1, ledmax);
      xSemaphoreTake (app_mutex, portMAX_DELAY);
      for (int preset = 0; preset <= CONFIG_REVK_WEB_EXTRA_PAGES; preset++)
         for (unsigned int i = 0; i < MAXAPPS; i++)
         {
            app_t *a = &active[i];
            if (a->preset == preset && a->app)
            {
               const char *name = a->name;
               if (a->delay)
               {                // Delayed start
                  a->delay--;
                  continue;
               }
               if (a->wheel)
               {                // Cycle the colour
                  a->r = wheel[(255 - a->cycle) & 255];
                  a->g = wheel[(255 - a->cycle + 85) & 255];
                  a->b = wheel[(255 - a->cycle + 170) & 255];
                  a->w = 0;
               } else if (a->cycling)
               {                // Cycle the colour
                  a->r = cos8[(255 - a->cycle) & 255];
                  a->g = cos8[(255 - a->cycle + 85) & 255];
                  a->b = cos8[(255 - a->cycle + 170) & 255];
                  a->w = 0;
               }
               if (!a->cycle)
               {                // Starting
                  jo_t j = jo_object_alloc ();
                  jo_int (j, "level", i);
                  jo_string (j, "app", a->name);
#define u8(s,n,d)         if(a->n)jo_int(j,#n,a->n);
#define u8d(s,n,d)         if(a->n)jo_litf(j,#n,"%.1f",1.0*a->n/cps);
#define u8r(s,n,d)        u8(s,n,d)
#define u16(s,n,d)         u8(s,n,d)
#define u16r(s,n,d)        u8(s,n,d)
#define s8(s,n,d)        u8(s,n,d)
#define s8r(s,n,d)        u8(s,n,d)
#define s16r(s,n,d)        u8(s,n,d)
#define u32(s,n,d)        u8(s,n,d)
#define u32d(s,n,d)        u8d(s,n,d)
                  params
#undef  u8
#undef  u8d
#undef  u8r
#undef  u16
#undef  u16r
#undef  s8
#undef  s8r
#undef  s16r
#undef  u32
#undef  u32d
                     if (a->rainbow)
                     jo_string (j, "colour", "rainbow");
                  else if (a->wheel)
                     jo_string (j, "colour", "wheel");
                  else if (a->cycling)
                     jo_string (j, "colour", "cycling");
                  else if (a->colourset)
                  {
                     if (rgbw)
                     {
                        if (!(a->r % 17) && !(a->g % 17) && !(a->b % 17) && !(a->w % 17))
                           jo_stringf (j, "colour", "%X%X%X%X", a->r / 17, a->g / 17, a->b / 17, a->w / 17);
                        else
                           jo_stringf (j, "colour", "%02X%02X%02X%02X", a->r, a->g, a->b, a->w);
                     } else
                     {
                        if (!(a->r % 17) && !(a->g % 17) && !(a->b % 17))
                           jo_stringf (j, "colour", "%X%X%X", a->r / 17, a->g / 17, a->b / 17);
                        else
                           jo_stringf (j, "colour", "%02X%02X%02X", a->r, a->g, a->b);
                     }
                  }
                  if (a->data)
                     jo_string (j, "data", (char *) a->data);
                  revk_info ("start", &j);
               }
               const char *e = a->app (a);
               if (e)
                  a->stop = 1;
               a->cycle++;
               if (a->stop && !--a->stop)
               {
                  uint8_t preset = a->preset;
                  appzap (a);
                  if (preset)
                  {             // Last one ?
                     int i;
                     for (i = 0; i < MAXAPPS; i++)
                        if (active[i].preset == preset)
                           break;
                     if (i == MAXAPPS)
                     {          // Has turned off preset
                        haon &= ~(1ULL << (preset - 1));
                        hastatus |= (1ULL << (preset - 1));
                     }
                  }
               } else if (!a->stop && a->limit && a->cycle >= a->limit)
                  a->stop = a->fadeout; // Tell app to stop
               if (a->stop)
                  a->fader = a->bright * a->stop / a->fadeout;
               else if (a->cycle < a->fadein)
                  a->fader = a->bright * a->cycle / a->fadein;
               else
                  a->fader = a->bright;
               if (!a->app)
               {                // Done
                  jo_t j = jo_object_alloc ();
                  jo_int (j, "level", i);
                  jo_string (j, "app", name);
                  if (e && *e)
                     jo_string (j, "error", e);
                  revk_info ("done", &j);
               }
            }
         }
      xSemaphoreGive (app_mutex);
      {
         uint8_t *r = ledr;
         uint8_t *g = ledg;
         uint8_t *b = ledb;
         uint8_t *w = ledw;
         if (rgswap)
         {
            uint8_t *s = r;
            r = g;
            g = s;
         }
         if (bgswap)
         {
            uint8_t *s = r;
            r = b;
            b = s;
         }
         for (int s = 0; s < STRIPS; s++)
            if (strip[s])
            {
               if (rgbw)
               {
                  for (unsigned int i = 0; i < leds[s]; i++)
                     led_strip_set_pixel_rgbw (strip[s], i + (s ? 0 : led_status),      //
                                               gamma8[(unsigned int) maxr * r[i] / 255],        //
                                               gamma8[(unsigned int) maxg * g[i] / 255],        //
                                               gamma8[(unsigned int) maxb * b[i] / 255],        //
                                               gamma8[(unsigned int) maxw * w[i] / 255]);
               } else
               {
                  for (unsigned int i = 0; i < leds[s]; i++)
                     led_strip_set_pixel (strip[s], i + (s ? 0 : led_status),   //
                                          gamma8[(unsigned int) maxr * r[i] / 255],     //
                                          gamma8[(unsigned int) maxg * g[i] / 255],     //
                                          gamma8[(unsigned int) maxb * b[i] / 255]);
               }
               r += leds[s];
               g += leds[s];
               b += leds[s];
               if (w)
                  w += leds[s];
               if (!s)
               {
                  if (led_status)
                     revk_led (strip[s], 0, 255, revk_blinker ());
                  else
                     revk_blink_do ();  // Library blink
               }
            }
         for (int s = 0; s < STRIPS; s++)
            if (strip[s])
               REVK_ERR_CHECK (led_strip_refresh (strip[s]));
      }
   }
}

void
revk_web_extra (httpd_req_t * req, int page)
{
   if (!page)
   {
      revk_web_setting (req, NULL, "dark");
      revk_web_setting (req, NULL, "leds1");
      revk_web_setting (req, NULL, "leds2");
      revk_web_setting (req, NULL, "sk6812");
      revk_web_setting (req, NULL, "rgbw");
      revk_web_setting (req, NULL, "rgswap");
      revk_web_setting (req, NULL, "poweron");
      revk_web_setting (req, NULL, "haenable");
   } else
   {
      revk_web_send (req,
                     "<tr><td colspan=3>Virtual strips are <i>lights</i> in Home Assistant. These can overlap if required.</td></tr>");
      if (!page && poweron)
         revk_web_send (req, "<tr><td colspan=3>This is the setting applied at power on.</td></tr>");
      if (!page)
         revk_web_send (req, "<tr><td colspan=3>These also define defaults for general MQTT control.</td></tr>");
      void add (const char *tag)
      {
         char name[20];
         sprintf (name, "%s%d", tag, page);
         revk_web_setting (req, NULL, name);
      }
      add ("name");
      add ("effect");
      add ("start");
      add ("colour");
      add ("len");
      add ("top");
      add ("bright");
      add ("delay");
      add ("limit");
      add ("speed");
      add ("fadein");
      add ("fadeout");
      revk_web_send (req,
                     "<tr><td colspan=3>You can also set a JSON config, either for this named effect (above), or if not a named effect, multiple effects can be set. This can cover any parts of the strip (the above are defaults).</td></tr>");
      add ("config");
   }
}

static void
register_uri (const httpd_uri_t * uri_struct)
{
   esp_err_t res = httpd_register_uri_handler (webserver, uri_struct);
   if (res != ESP_OK)
   {
      ESP_LOGE (TAG, "Failed to register %s, error code %d", uri_struct->uri, res);
   }
}

static void
register_get_uri (const char *uri, esp_err_t (*handler) (httpd_req_t * r))
{
   httpd_uri_t uri_struct = {
      .uri = uri,
      .method = HTTP_GET,
      .handler = handler,
   };
   register_uri (&uri_struct);
}

static esp_err_t
web_root (httpd_req_t * req)
{
   if (revk_link_down () && webcontrol >= 2)
      return revk_web_settings (req);   // Direct to web set up
   revk_web_head (req, "LED");
   size_t l = httpd_req_get_url_query_len (req);
   char query[200];
   if (l > 0 && l < sizeof (query))
   {
      if (!httpd_req_get_url_query_str (req, query, sizeof (query)))
      {
         jo_t j = jo_parse_query (query);
         if (jo_find (j, "app") == JO_STRING)
         {
            char app[30];
            jo_strncpy (j, app, sizeof (app));
            jo_rewind (j);
            app_callback (0, topiccommand, NULL, app, j);
            sleep (1);
         }
      }
   }
   revk_web_send (req, "<h1>LED controller: %s</h1><ul>", hostname);
   xSemaphoreTake (app_mutex, portMAX_DELAY);
   for (int preset = 0; preset <= CONFIG_REVK_WEB_EXTRA_PAGES; preset++)
      for (unsigned int i = 0; i < MAXAPPS; i++)
      {
         app_t *a = &active[i];
         if (a->preset == preset && a->app && !a->stop)
         {
            revk_web_send (req, "<li>");
            if (*a->name)
               revk_web_send (req, "<b>%s</b>", a->name);
            if (a->preset)
               revk_web_send (req, " preset=%d", a->preset);
            if (a->start && a->start != 1)
               revk_web_send (req, " start=%d", a->start);
            if (a->len && a->len != ledmax)
               revk_web_send (req, " len=%d", a->len);
            if (a->bright < 255)
               revk_web_send (req, " bright=%d", a->bright);
            if (a->delay)
               revk_web_send (req, " delay=%.1f", 1.0 * a->delay / cps);
            if (a->limit)
               revk_web_send (req, " limit=%.1f", 1.0 * a->limit / cps);
            if (a->speed != cps)
               revk_web_send (req, " speed=%.1f", 1.0 * a->speed / cps);
            if (a->fadein != cps)
               revk_web_send (req, " fadein=%.1f", 1.0 * a->fadein / cps);
            if (a->fadeout != cps)
               revk_web_send (req, " fadeout=%.1f", 1.0 * a->fadeout / cps);
            if (a->rainbow)
               revk_web_send (req, " colour=rainbow");
            else if (a->colourset)
            {
               if (rgbw)
                  revk_web_send (req, " colour=#%02X%02X%02X%02X", a->r, a->g, a->b, a->w);
               else
                  revk_web_send (req, " colour=#%02X%02X%02X", a->r, a->g, a->b);
            }
            if (a->cycling)
               revk_web_send (req, "(cycling)");
            if (a->wheel)
               revk_web_send (req, "(wheel)");
            revk_web_send (req, "</li>");
         }
      }
   xSemaphoreGive (app_mutex);
   revk_web_send (req,
                  "</ul><p><a href=/>Reload</a></p><form method=get><fieldset><legend>Effect</legend><p>Colour:<input name='colour' placeholder='#%s' size=6> or <tt>rainbow</tt> or <tt>wheel</tt> or <tt>cycling</tt>.</p><p>",
                  rgbw ? "RGBW" : "RGB");
   void button (const char *tag)
   {
      revk_web_send (req, "<input type=submit name='app' value='%s'/>", tag);
   }
   if (*config[0])
      button ("init");
#define a(x,d) button(#x);
#include "apps.h"
   button ("stop");
   revk_web_send (req, "</p></fieldset><fieldset><legend>Preset</legend><p>");
   for (int p = 1; p <= CONFIG_REVK_WEB_EXTRA_PAGES; p++)
   {
      if (!*config[p - 1] && !*effect[p - 1] && !*name[p - 1])
         continue;
      char temp[10];
      sprintf (temp, "%d", p);
      revk_web_send (req, "<div style='display:inline-block;text-align:center;'>");
      button (temp);
      if (*name[p - 1])
         revk_web_send (req, "<br>%s", name[p - 1]);
      revk_web_send (req, "</div>");
   }
   revk_web_send (req, "</p></fieldset></form>");
   return revk_web_foot (req, 0, webcontrol >= 2 ? 1 : 0, NULL);
}

void
i2c_task (void *arg)
{
   jo_t e (uint8_t a, uint8_t cmd, const char *tag, esp_err_t err)
   {                            // Error
      jo_t j = jo_object_alloc ();
      if (tag)
         jo_string (j, "error", tag);
      if (err)
         jo_string (j, "description", esp_err_to_name (err));
      if (cmd)
         jo_int (j, "cmd", cmd);
      if (sda.set)
         jo_int (j, "sda", sda.num);
      if (scl.set)
         jo_int (j, "scl", scl.num);
      if (a)
         jo_int (j, "address", a);
      return j;
   }
   esp_err_t err;
   err = i2c_driver_install (i2c, I2C_MODE_MASTER, 0, 0, 0);
   if (!err)
   {
      i2c_config_t config = {
         .mode = I2C_MODE_MASTER,
         .sda_io_num = sda.num,
         .scl_io_num = scl.num,
         .sda_pullup_en = true,
         .scl_pullup_en = true,
         .master.clk_speed = 400000,
      };
      err = i2c_param_config (i2c, &config);
      if (err)
         i2c_driver_delete (i2c);
   }
   if (err)
   {
      jo_t j = e (0, 0, "Failed to start I2C", err);
      revk_error ("i2c", &j);
      vTaskDelete (NULL);
      return;
   }
   uint16_t r (uint8_t a, uint8_t cmd)
   {                            // Read
      uint8_t l,
        h;
      i2c_cmd_handle_t t = i2c_cmd_link_create ();
      i2c_master_start (t);
      i2c_master_write_byte (t, (a << 1) | I2C_MASTER_WRITE, true);
      i2c_master_write_byte (t, cmd, true);
      i2c_master_start (t);
      i2c_master_write_byte (t, (a << 1) | I2C_MASTER_READ, true);
      i2c_master_read_byte (t, &l, I2C_MASTER_ACK);
      i2c_master_read_byte (t, &h, I2C_MASTER_LAST_NACK);
      i2c_master_stop (t);
      err = i2c_master_cmd_begin (i2c, t, 10 / portTICK_PERIOD_MS);
      i2c_cmd_link_delete (t);
      if (err)
      {
         jo_t j = e (a, cmd, "Failed to ALS read", err);
         revk_error ("i2c", &j);
         return 0;
      }
      return (h << 8) + l;
   }
   void w (uint8_t a, uint8_t cmd, uint16_t val)
   {                            // Write
      i2c_cmd_handle_t t = i2c_cmd_link_create ();
      i2c_master_start (t);
      i2c_master_write_byte (t, (a << 1) | I2C_MASTER_WRITE, true);
      i2c_master_write_byte (t, cmd, true);
      i2c_master_write_byte (t, val & 0xFF, true);
      i2c_master_write_byte (t, val >> 8, true);
      i2c_master_stop (t);
      err = i2c_master_cmd_begin (i2c, t, 10 / portTICK_PERIOD_MS);
      i2c_cmd_link_delete (t);
      if (err)
      {
         jo_t j = e (a, cmd, "Failed to ALS read", err);
         revk_error ("i2c", &j);
         return;
      }
   }
   if (!als)
   {                            // No I2C work
      vTaskDelete (NULL);
      return;
   }
   if (als)
   {
      w (als, 0x00, 0x0040);
      ESP_LOGI (TAG, "ALS mode=%04X ", r (als, 0x00));
   }
   while (1)
   {
      if (als)
      {
         jo_t j = jo_object_alloc ();
         jo_litf (j, "r", "%.0f", (float) r (als, 0x08) * 1031 / 65535);
         jo_litf (j, "g", "%.0f", (float) r (als, 0x09) * 1031 / 65535);
         jo_litf (j, "b", "%.0f", (float) r (als, 0x0A) * 1031 / 65535);
         jo_litf (j, "w", "%.0f", (float) r (als, 0x0B) * 1031 / 65535);
         revk_info ("als", &j);
      }
      sleep (1);
   }
}

float audiomag = 0;
float audioband[AUDIOBANDS] = { 0 };

static float audiogain = 1.0;
static int16_t audioraw[AUDIOSAMPLES];
static float fftre[AUDIOSAMPLES];
static float fftim[AUDIOSAMPLES];
void
i2s_task (void *arg)
{
   ESP_LOGE (TAG, "I2S init CLK %d DAT %d", i2sclock.num, i2sdata.num);
   jo_t e (esp_err_t err, const char *msg)
   {                            // Error
      jo_t j = jo_object_alloc ();
      if (msg)
         jo_string (j, "message", msg);
      if (err)
         jo_string (j, "error", esp_err_to_name (err));
      if (sda.set)
         jo_int (j, "data", i2sdata.num);
      if (scl.set)
         jo_int (j, "clock", i2sclock.num);
      return j;
   }
   esp_err_t err;
   i2s_chan_handle_t i = { 0 };
   i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG (I2S_NUM_0, I2S_ROLE_MASTER);
   err = i2s_new_channel (&chan_cfg, NULL, &i);
   i2s_pdm_rx_config_t cfg = {
      .clk_cfg = I2S_PDM_RX_CLK_DEFAULT_CONFIG (AUDIORATE),
      .slot_cfg = I2S_PDM_RX_SLOT_DEFAULT_CONFIG (I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
      .gpio_cfg = {
                   .clk = i2sclock.num,
                   .din = i2sdata.num,
                   .invert_flags = {
                                    .clk_inv = i2sclock.invert}
                   }
   };
   cfg.slot_cfg.slot_mask = (i2sright ? I2S_PDM_SLOT_RIGHT : I2S_PDM_SLOT_LEFT);
   if (!err)
      err = i2s_channel_init_pdm_rx_mode (i, &cfg);
   if (!err)
      err = i2s_channel_enable (i);
   if (err)
   {
      ESP_LOGE (TAG, "I2S failed");
      jo_t j = e (err, "Failed init I2S");
      revk_error ("i2s", &j);
      return;
   }
   while (1)
   {
      size_t n = 0;
      i2s_channel_read (i, audioraw, sizeof (audioraw), &n, 100);
      // ESP_LOGE (TAG, "Bytes %d/%d %6d %6d %6d %6d", n / sizeof (*audioraw), AUDIOSAMPLES, audioraw[0], audioraw[1], audioraw[2], audioraw[3]);
      if (n < sizeof (audioraw))
         continue;
      for (int i = 0; i < AUDIOSAMPLES; i++)
      {
         fftre[i] = (float) audioraw[i] / 32768;
         fftim[i] = 0;
      }
      fft (fftre, fftim, AUDIOSAMPLES);
      float mag = 0,
         max = 0;
      float band[AUDIOBANDS] = { 0 };   // Should get main audio in first 16 or so slots
      for (int i = AUDIOMIN * AUDIOSAMPLES / AUDIORATE; i < AUDIOMAX * AUDIOSAMPLES / AUDIORATE && i < AUDIOSAMPLES / 2; i++)
         band[(i * AUDIORATE / AUDIOSAMPLES - AUDIOMIN) / AUDIOSTEP] += sqrt (fftre[i] * fftre[i] + fftim[i] * fftim[i]);
      for (int i = 0; i < AUDIOBANDS; i++)
      {
         float val = (band[i] *= audiogain / (AUDIORATE / (AUDIOMAX - AUDIOMIN)));
         if (val > max)
            max = val;
         mag += val / AUDIOBANDS;
      }
      ESP_LOGE (TAG, "FFT mag=%7.2f gain=%5.2f: %6.2f %6.2f %6.2f %6.2f %6.2f %6.2f %6.2f %6.2f %6.2f", mag,
                audiogain, band[0], band[1], band[2], band[3], band[4], band[5], band[6], band[7], band[8]);
      audiomag = mag;
      for (int i = 0; i < AUDIOBANDS; i++)
         audioband[i] = band[i];
      if (max)
      {
         audiogain = (audiogain * 99 + audiogain / max) / 100;
         if (audiogain > AUDIOGAINMAX)
            audiogain = AUDIOGAINMAX;
         else if (audiogain < AUDIOGAINMIN)
            audiogain = AUDIOGAINMIN;
      }
   }
   vTaskDelete (NULL);
}

#undef	N

void
app_main ()
{
   app_mutex = xSemaphoreCreateBinary ();
   xSemaphoreGive (app_mutex);
   revk_boot (&app_callback);
#ifdef	CONFIG_REVK_MATTER
   extern void matter_main (void);
   matter_main ();
#endif
   revk_start ();
   if (!cps)
      cps = 10;
   if (dark)
      revk_blink (0, 0, "K");
   if (sda.set && scl.set)
      revk_task ("i2c", i2c_task, NULL, 4);
   if (i2sdata.set && i2sclock.set)
      revk_task ("i2s", i2s_task, NULL, 4);
   if (webcontrol)
   {                            // Web interface
      httpd_config_t config = HTTPD_DEFAULT_CONFIG ();  // When updating the code below, make sure this is enough
      //  Note that we 're also 4 adding revk' s web config handlers
      config.max_uri_handlers = 8;
      if (!httpd_start (&webserver, &config))
      {
         if (webcontrol >= 2)
            revk_web_settings_add (webserver);
         register_get_uri ("/", web_root);
      }
   }
   if (cps < 10)
      cps = 10;                 // Safety for division
   memset (habright, 255, sizeof (habright));
   if (rgbw)
      memset (haw, 255, sizeof (hab));
   else
   {
      memset (har, 255, sizeof (har));
      memset (hag, 255, sizeof (hag));
      memset (hab, 255, sizeof (hab));
   }
   hargb = -1;
   revk_task ("LED", led_task, NULL, 4);
}
