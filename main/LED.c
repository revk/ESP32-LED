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
#include <driver/i2s_std.h>
#include "app.h"
#include <esp_http_server.h>
#include "fft.h"
#include "math.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "halib.h"
#include <ir.h>

struct b_str b = { 0 };

#define	typeisrgbw(x)	(((x)%12)/6)
#define	typeissk6812(x)	((x)/12==1)
#define	typeisxing(x)	((x)/12==2)
#define	typebase(x)	((x)%6)

#define a(a,d)	extern const char* app##a(app_t*);
#include "apps.h"

struct applist_s
{
   const char *name;
   const char *description;
   app_f *app;
   uint8_t ring:1;              // Is a ring based app
   uint8_t text:1;              // Is a text based app
   uint8_t sound:1;             // Is a sound based app
} applist[] = {
#define a(a,d)	{#a,#d,&app##a,0,0,0},
#define s(a,d)	{#a,#d,&app##a,0,0,1},
#define r(a,d)	{#a,#d,&app##a,1,0,0},
#define t(a,d)	{#a,#d,&app##a,0,1,0},
#include "apps.h"
};

#define	ADC_SCALE	134/10
#define	ADC_ATTEN	ADC_ATTEN_DB_12
int voltage = 0;                // current voltage (mV)

static httpd_handle_t webserver = NULL;

int ledmax = 0;                 // Total LEDs

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

const uint8_t ir4x11id[] = {
   0x5C, 0x5D, 0x41, 0x40,      //
   0x58, 0x59, 0x45, 0x44,      //
   0x54, 0x55, 0x49, 0x48,      //
   0x50, 0x51, 0x4D, 0x4C,      //
   0x1C, 0x1D, 0x1E, 0x1F,      //
   0x18, 0x19, 0x1A, 0x1B,      //
   0x14, 0x15, 0x16, 0x17,      //
   0x10, 0x11, 0x12, 0x13,      //
   0x0C, 0x0D, 0x0E, 0x0F,      //
   0x08, 0x09, 0x0A, 0x0B,      //
   0x04, 0x05, 0x06, 0x07,      //
};

const char *const ir4x11name[] = {
   "+", "-", ">", "POWER",      //
   "#F00", "#0F0", "#00F", "#FFF",      //
   "#F40", "#0F4", "#40F", "#FEE",      //
   "#F80", "#0F8", "#80F", "#FDD",      //
   "#FC0", "#0FC", "#C0F", "#EEF",      //
   "#FF0", "#0FF", "#F0F", "#DDF",      //
   "R+", "G+", "B+", "Quick",   //
   "R-", "G-", "B-", "Slow",    //
   "DIY1", "DIY2", "DIY3", "AUTO",      //
   "DIY4", "DIY5", "DIY6", "FLASH",     //
   "JUMP3", "JUMP7", "FADE3", "FADE7",  //
};

const char *const ir4x6name[] = {
   "+", "-", "OFF", "ON",       //
   "#F00", "#0F0", "#00F", "#FFF",      //
   "#F40", "#0F4", "#40F", "FLASH",     //
   "#F80", "#0F8", "#80F", "STROBE",    //
   "#FC0", "#0FC", "#C0F", "FADE",      //
   "#FF0", "#0FF", "#F0F", "SMOOTH",    //
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

uint8_t
setcolour (app_t *a, const char *colour)
{
   uint8_t colourset = 0;
   uint8_t R = 0;
   uint8_t G = 0;
   uint8_t B = 0;
   uint8_t W = 0;
   int p = 0;
   for (p = 0; palettes[p].name && strcmp (palettes[p].name, colour); p++);
   if (palettes[p].name)
   {                            // Palette (overwrites rgbw as it goes)
      a->palette = p + 1;
      a->colourset = 1;
      return 1;
   }
   // Fixed colour
   if (b.rgbw && !strcasecmp (colour, "white"))
      colour = "#000F";
#define	c(h,c)	else if(!strcasecmp(colour,#c))colour=#h;
   colours
#undef c
   const char *c = colour;
   if (*c == '#')
      c++;
#define x(n)((c[n] & 0xF) + (isalpha ((uint8_t)c[n]) ? 9 : 0))
   if (isxdigit ((int) c[0]) && isxdigit ((int) c[1]) && isxdigit ((int) c[2]))
   {
      if (!c[3])
      {                         // RGB
         colourset = 1;
         R = x (0) * 17;
         G = x (1) * 17;
         B = x (2) * 17;
         W = 0;
      } else if (isxdigit ((int) c[3]))
      {
         if (!c[4])
         {                      // # RGBW
            colourset = 1;
            R = x (0) * 17;
            G = x (1) * 17;
            B = x (2) * 17;
            W = x (3) * 17;
         } else if (isxdigit ((int) c[4]) && isxdigit ((int) c[5]))
         {
            if (!c[6])
            {                   // # RRGGBB
               colourset = 1;
               R = x (0) * 16 + x (1);
               G = x (2) * 16 + x (3);
               B = x (4) * 16 + x (5);
               W = 0;
            } else if (isxdigit ((int) c[6]) && isxdigit ((int) c[7]))
            {                   // # RRGGBBWW
               if (!c[8])
               {
                  colourset = 1;
                  R = x (0) * 16 + x (1);
                  G = x (2) * 16 + x (3);
                  B = x (4) * 16 + x (5);
                  W = x (6) * 16 + x (7);
               } else
                  return 0;
            }
         }

      }
   } else
      return 0;
   a->palette = 0;
   a->r = R;
   a->g = G;
   a->b = B;
   a->w = W;
   a->colourset = colourset;
   return 1;
#undef x
}

void
appzap (app_t *a)
{                               // Assumes mutex, Delete an app
   free (a->data);
   free (a->config);
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
      if (!strcasecmp (name, applist[i].name) || !strcasecmp (name, applist[i].description))
      {
         uint8_t setcolourj (jo_t j)
         {
            char temp[30];
            jo_strncpy (j, temp, sizeof (temp));
            if (!*temp)
               return 0;
            return setcolour (a, temp);
         }
         if (!a->app || a->name != applist[i].name || a->stop)
            appzap (a);
         a->name = applist[i].name;
         if (*colour[preset ? preset - 1 : 0])
            setcolour (a, colour[preset ? preset - 1 : 0]);     // Default colour from preset
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
            if (j)
               a->config = jo_strdupj (j);
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
                  if (!jo_strcmp (j, "colour") || !jo_strcmp (j, "#") || !jo_strcmp (j, "palette"))
               {
                  if (jo_next (j) == JO_STRING)
                     setcolourj (j);
                  continue;
               }
               if (!jo_strcmp (j, "data"))
               {
                  if (jo_next (j) == JO_STRING)
                  {
                     free (a->data);
                     int l = jo_strlen (j);
                     if (l)
                        jo_strncpy (j, a->data = mallocspi (l + 1), l + 1);
                  }
                  continue;
               }
               jo_next (j);     // Skip
            }
         } else if (j && jo_here (j) == JO_STRING)
         {
            if (!setcolourj (j))
            {                   // data
               free (a->data);
               int l = jo_strlen (j);
               if (l)
                  jo_strncpy (j, a->data = mallocspi (l + 1), l + 1);
            }
         } else if (j && jo_here (j) == JO_NUMBER)
            a->limit = limit_scale * jo_read_float (j); // Defaults
         if (preset && preset <= CONFIG_REVK_WEB_EXTRA_PAGES)
         {                      // Stored HA based settings
            if ((hargb & (1ULL << (preset - 1))) && (har[preset - 1] || hag[preset - 1] || hab[preset - 1] || haw[preset - 1]))
            {                   // If set black, we don't set as means use default, only applies at turn on
               if (habrightset & (1ULL << (preset - 1)))
                  a->bright = habright[preset - 1];
               a->r = har[preset - 1];
               a->g = hag[preset - 1];
               a->b = hab[preset - 1];
               a->w = haw[preset - 1];
               a->palette = 0;
               a->colourset = 1;
            }
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
         a->delay = cps * a->delay / delay_scale;
         a->limit = cps * a->limit / limit_scale;
         a->speed = cps * a->speed / speed_scale ? : 1;
         a->fadein = cps * a->fadein / fadein_scale ? : 1;
         a->fadeout = cps * a->fadeout / fadeout_scale ? : 1;
         a->app = applist[i].app;
         a->sound = applist[i].sound;
         a->ring = applist[i].ring;
         a->text = applist[i].text;
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
      if (!strcasecmp (tag, applist[i].name) || !strcasecmp (tag, applist[i].description))
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
      int p = a->preset - 1;
      if (haon & (1ULL << p))
      {                         // Update in situ
         found |= (1ULL << p);
         if (changed & (1ULL << p))
         {                      // Update settings
            // TODO black or 0 brightness needs to set default?
            if (hargb & (1ULL << p))
            {
               a->r = har[p];
               a->g = hag[p];
               a->b = hab[p];
               a->w = haw[p];
               a->palette = 0;
               a->colourset = 1;
            }
            if (habrightset & (1ULL << p))
               a->bright = habright[p];
            hastatus |= (1ULL << p);
         }
         continue;
      }
      a->stop = a->fadeout;
      hastatus |= (1ULL << p);
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
            hastatus |= (1ULL << (preset - 1));
         }
         if (jo_find (j, "brightness"))
         {
            hachanged |= (1ULL << (preset - 1));        // ideally only if actually changed
            habright[preset - 1] = jo_read_int (j);
            habrightset |= (1ULL << (preset - 1));
         }
         if (jo_find (j, "color"))
         {                      // r / g / b
            hachanged |= (1ULL << (preset - 1));        // ideally only if actually changed
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
            hargb |= (1ULL << (preset - 1));
         }
         if (jo_find (j, "effect"))
         {                      // effect
            if (*effect[preset - 1])
               return "Effect not expected";
            hachanged |= (1ULL << (preset - 1));        // ideally only if actually changed
            jo_strncpy (j, val, sizeof (val));
            int i;
            for (i = 0; i < sizeof (applist) / sizeof (*applist); i++)
               if (!strcasecmp (val, applist[i].name) || !strcasecmp (val, applist[i].description))
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
      b.hacheck = 1;
      return NULL;
   }
   if (suffix && !strcasecmp (suffix, "stop"))
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
      else
      {
         if (!strcasecmp (val, "on") || !strcmp (val, "1") || !strcasecmp (val, "blink"))
            haon |= (1ULL << (preset - 1));     // On(blink may as well be on)
         else if (!strcasecmp (val, "2"))
            haon ^= (1ULL << (preset - 1));     // Toggle
         hachanged |= (1ULL << (preset - 1));   // ideally only if actually changed
      }
      hastatus |= (1ULL << (preset - 1));
      b.hacheck = 1;
      return NULL;
   }
   if (suffix && (!strcasecmp (suffix, "dark") || !strcasecmp (suffix, "upgrade")))
   {
      haon = 0;                 // All off
      b.hacheck = 1;
      return led_stop ();
   }
   if (suffix && strcmp (suffix, "add"))
      return led_add (suffix, 0, j);    // Process command to set apps
   xSemaphoreTake (app_mutex, portMAX_DELAY);
   haon = 0;                    // All off
   b.hacheck = 1;
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
         jo_string (j, "color_mode", b.rgbw ? "rgbw" : "rgb");
         if (!*effect[preset] && haeffect[preset])
            jo_string (j, "effect", haeffect[preset]);
         if (hargb & (1ULL << preset))
         {
            jo_object (j, "color");
            jo_int (j, "r", har[preset]);
            jo_int (j, "g", hag[preset]);
            jo_int (j, "b", hab[preset]);
            if (b.rgbw)
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
      jo_string (j, "mdl", revk_app);
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
            jo_string (j, NULL, b.rgbw ? "rgbw" : "rgb");
            jo_close (j);
            if (!*effect[i])
            {
               jo_bool (j, "effect", 1);
               jo_array (j, "effect_list");
               for (int i = 0; i < sizeof (applist) / sizeof (*applist); i++)
                  if (!applist[i].text && ((micdata.set && micclock.set) || !applist[i].sound))
                     jo_string (j, NULL, applist[i].name);
            }
            revk_mqtt_send (NULL, 1, topic, &j);
         }
         free (topic);
      }
   free (hastatus);
   free (lwt);
   free (cmd);
   if (adc.set)
    ha_config_sensor ("voltage", name: "Voltage", type: "voltage", unit:"V");
   if (irha && irgpio.set)
   {
      if (ir4x11)
         for (int q = 0; q < sizeof (ir4x11id); q++)
            ha_config_trigger (ir4x11name[q],.info = "/ir",.subtype = ir4x11name[q],.payload = ir4x11name[q]);
      if (ir4x6)
         for (int q = 0; q < sizeof (ir4x6name) / sizeof (*ir4x6name); q++)
            ha_config_trigger (ir4x6name[q],.info = "/ir",.subtype = ir4x6name[q],.payload = ir4x6name[q]);
   }
}

void
led_task (void *x)
{
   revk_gpio_input (button);
   revk_gpio_output (relay, 0);
   if (!ledgpio[0].set || !(gpio_ok (ledgpio[0].num) & 1))
   {
      ESP_LOGE (TAG, "Bad GPIO %d", ledgpio[0].num);
      vTaskDelete (NULL);
      return;
   }
   for (int s = 0; s < STRIPS; s++)
      ledmax += ledcount[s];
#ifdef	CONFIG_REVK_LED
   const uint8_t led_status = 0;        // blink_init will make a single LED strip
#else
   uint8_t led_status = (blink[0].num == ledgpio[0].num ? 1 : 0);
#endif
   if (!led_status)
      revk_blink_init ();       // Library blink
#ifdef	CONFIG_REVK_LED
   led_strip_t strip[STRIPS] = { 0 };
   for (int s = 0; s < STRIPS; s++)
      if (ledgpio[s].set && (ledcount[s] || !ledmax))
      {
         const char *e = led_strip (&strip[s], ledgpio[s],
#ifdef	CONFIG_REVK_LED_TEST
                                    ledloop[s],
#endif
#ifdef	CONFIG_REVK_LED_FULL
                                    typeissk6812 (ledtype[s]) ? LED_SK6812 : typeisxing (ledtype[s]) ? LED_XINGLIGHT : LED_WS2812,
#endif
                                    (ledcount[s] ? : 4) + (s ? 0 : led_status), typeisrgbw (ledtype[s]) ? 4 : 3,
                                    ledtype[s] % 6);
         if (e)
            ESP_LOGE (TAG, "Fail %s", e);
      }
#ifdef  CONFIG_REVK_LED
   if (led_send ())
      revk_ate_fail ("LED fail");
#endif
#else
   led_strip_handle_t strip[STRIPS] = { 0 };
   for (int s = 0; s < STRIPS; s++)
      if (ledgpio[s].set && (ledcount[s] || !ledmax))
      {
         ESP_LOGE (TAG, "Started using GPIO %d%s, %d LEDs%s", ledgpio[s].num, ledgpio[s].invert ? " (inverted)" : "",
                   ledcount[s] ? : 4, led_status ? dark ? " (plus status, dark)" : " (plus status)" : "");
         led_strip_config_t strip_config = {
            .strip_gpio_num = ledgpio[s].num,
            .max_leds = (ledcount[s] ? : 4) + (s ? 0 : led_status),     // The number of LEDs in the strip,
            .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
            .led_model = typeissk6812 (ledtype[s]) ? LED_MODEL_SK6812 : LED_MODEL_WS2812,       // LED strip model
            .flags.invert_out = ledgpio[s].invert,      // whether to invert the output signal(useful when your hardware has a level inverter)
         };
         if (typeisrgbw (ledtype[s]))
         {
            strip_config.color_component_format.format.num_components = 4;
            b.rgbw = 1;
         }
         uint8_t t = typebase (ledtype[s]);
         if (t == REVK_SETTINGS_LEDTYPE_WS2812_RGB || t == REVK_SETTINGS_LEDTYPE_WS2812_RBG)
            strip_config.color_component_format.format.r_pos = 0;
         if (t == REVK_SETTINGS_LEDTYPE_WS2812_GRB || t == REVK_SETTINGS_LEDTYPE_WS2812_BRG)
            strip_config.color_component_format.format.r_pos = 1;
         if (t == REVK_SETTINGS_LEDTYPE_WS2812_GBR || t == REVK_SETTINGS_LEDTYPE_WS2812_BGR)
            strip_config.color_component_format.format.r_pos = 2;
         if (t == REVK_SETTINGS_LEDTYPE_WS2812_GBR || t == REVK_SETTINGS_LEDTYPE_WS2812_GRB)
            strip_config.color_component_format.format.g_pos = 0;
         if (t == REVK_SETTINGS_LEDTYPE_WS2812_RGB || t == REVK_SETTINGS_LEDTYPE_WS2812_BGR)
            strip_config.color_component_format.format.g_pos = 1;
         if (t == REVK_SETTINGS_LEDTYPE_WS2812_RBG || t == REVK_SETTINGS_LEDTYPE_WS2812_BRG)
            strip_config.color_component_format.format.g_pos = 2;
         if (t == REVK_SETTINGS_LEDTYPE_WS2812_BRG || t == REVK_SETTINGS_LEDTYPE_WS2812_BGR)
            strip_config.color_component_format.format.b_pos = 0;
         if (t == REVK_SETTINGS_LEDTYPE_WS2812_RBG || t == REVK_SETTINGS_LEDTYPE_WS2812_GBR)
            strip_config.color_component_format.format.b_pos = 1;
         if (t == REVK_SETTINGS_LEDTYPE_WS2812_RGB || t == REVK_SETTINGS_LEDTYPE_WS2812_GRB)
            strip_config.color_component_format.format.b_pos = 2;
         led_strip_rmt_config_t rmt_config = {
            .clk_src = RMT_CLK_SRC_DEFAULT,     // different clock source can lead to different power consumption
            .resolution_hz = 10 * 1000 * 1000,  // 10 MHz
         };
#ifdef	CONFIG_IDF_TARGET_ESP32S3
         if (!s)
            rmt_config.flags.with_dma = true;   // Seems can only be one, investigate more on this
#endif
         REVK_ERR_CHECK (led_strip_new_rmt_device (&strip_config, &rmt_config, &strip[s]));
         if (strip[s])
            REVK_ERR_CHECK (led_strip_clear (strip[s]));
      }
#endif
   ledr = mallocspi ((ledmax ? : STRIPS * 4) * sizeof (*ledr));
   ledg = mallocspi ((ledmax ? : STRIPS * 4) * sizeof (*ledg));
   ledb = mallocspi ((ledmax ? : STRIPS * 4) * sizeof (*ledb));
   if (b.rgbw)
      ledw = mallocspi ((ledmax ? : STRIPS * 4) * sizeof (*ledw));
   if (!ledmax)
   {                            // Preset for no LEDs set
      memset (ledr, 0, STRIPS * 4 * sizeof (*ledr));
      memset (ledg, 0, STRIPS * 4 * sizeof (*ledg));
      memset (ledb, 0, STRIPS * 4 * sizeof (*ledb));
      if (ledw)
         memset (ledw, 0, 8 * sizeof (*ledw));
      for (int s = 0; s < STRIPS; s++)
      {
         ledr[0 + 4 * s] = 255;
         ledg[1 + 4 * s] = 255;
         ledb[2 + 4 * s] = 255;
         if (ledw)
            ledw[3 + 4 * s] = 255;
      }
   }
   if (onpower && onpower <= CONFIG_REVK_WEB_EXTRA_PAGES && *effect[onpower - 1])
   {                            // Light 1 is default
      ESP_LOGD (TAG, "Power on effect %d", onpower);
      haon = (1ULL << (onpower - 1));
      b.hacheck = 1;
   }
   uint32_t tick = 1000000LL / cps;
   while (1)
   {                            // Main loop
      usleep (tick - (esp_timer_get_time () % tick));
      if (onbutton && onbutton <= CONFIG_REVK_WEB_EXTRA_PAGES)
      {
         uint8_t press = revk_gpio_get (button);
         if (press != b.press)
         {
            b.press = press;
            if (press)
            {
               if (!haon)
                  haon |= (1ULL << (onbutton - 1));
               else
                  haon &= ~(1ULL << (onbutton - 1));
               hastatus |= (1ULL << (onbutton - 1));
               b.hacheck = 1;
            }
         }
      }
      if (ledmax)
      {
         if (b.hacheck)
            presetcheck ();
         if (b.haconfig)
            send_ha_config ();
         if (hastatus)
            send_ha_status ();
         clear (1, ledmax);
         xSemaphoreTake (app_mutex, portMAX_DELAY);
         b.checksound = 0;
         uint8_t found = 0;
         for (int preset = 0; preset <= CONFIG_REVK_WEB_EXTRA_PAGES; preset++)
         {
            for (unsigned int i = 0; i < MAXAPPS; i++)
            {
               app_t *a = &active[i];
               if (a->sound)
                  b.checksound = 1;
               if ((!stack || a->preset == preset) && a->app)
               {
                  found++;
                  const char *name = a->name;
                  if (a->delay)
                  {             // Delayed start
                     a->delay--;
                     continue;
                  }
                  if (!a->cycle)
                  {             // Starting
                     jo_t j = jo_object_alloc ();
                     jo_int (j, "level", i);
                     jo_string (j, "effect", a->name);
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
                        if (a->palette)
                        jo_string (j, "colour", palettes[a->palette - 1].name);
                     else if (a->colourset)
                     {
                        if (b.rgbw)
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
                     {          // Last one ?
                        int i;
                        for (i = 0; i < MAXAPPS; i++)
                           if (active[i].preset == preset)
                              break;
                        if (i == MAXAPPS)
                        {       // Has turned off preset
                           haon &= ~(1ULL << (preset - 1));
                           hastatus |= (1ULL << (preset - 1));
                           b.hacheck = 1;
                        }
                     }
                  } else if (!a->stop && a->limit && a->cycle >= a->limit)
                     a->stop = a->fadeout;      // Tell app to stop
                  if (a->stop)
                     a->fader = a->bright * a->stop / a->fadeout;
                  else if (a->cycle < a->fadein)
                     a->fader = a->bright * a->cycle / a->fadein;
                  else
                     a->fader = a->bright;
                  if (!a->app)
                  {             // Done
                     jo_t j = jo_object_alloc ();
                     jo_int (j, "level", i);
                     jo_string (j, "app", name);
                     if (e && *e)
                        jo_string (j, "error", e);
                     revk_info ("done", &j);
                  }
               }
            }
            if (!stack)
               break;
         }
         b.micon = b.checksound;
         xSemaphoreGive (app_mutex);
         if (!b.relay && found)
         {
            revk_gpio_set (relay, b.relay = 1);
            usleep (100000);
         } else if (b.relay && !found)
            revk_gpio_set (relay, b.relay = 0);
      }
      {                         // Update display
         uint8_t *R = ledr;
         uint8_t *G = ledg;
         uint8_t *B = ledb;
         uint8_t *W = ledw;
         for (int s = 0; s < STRIPS; s++)
            if (strip[s])
            {
               int n = ledmax ? ledcount[s] : 4;
               if (usegamma)
               {
#ifdef	CONFIG_REVK_LED
                  for (unsigned int i = 0; i < n; i++)
                     led_set (strip[s], i + (s ? 0 : led_status),       //
                              gamma8[(unsigned int) maxr * R[i] / 255], //
                              gamma8[(unsigned int) maxg * G[i] / 255], //
                              gamma8[(unsigned int) maxb * B[i] / 255], //
                              W ? gamma8[(unsigned int) maxw * W[i] / 255] : 0);
#else
                  if (b.rgbw)
                  {
                     if (typeisrgbw (ledtype[s]))
                        for (unsigned int i = 0; i < n; i++)
                           led_strip_set_pixel_rgbw (strip[s], i + (s ? 0 : led_status),        //
                                                     gamma8[(unsigned int) maxr * R[i] / 255],  //
                                                     gamma8[(unsigned int) maxg * G[i] / 255],  //
                                                     gamma8[(unsigned int) maxb * B[i] / 255],  //
                                                     gamma8[(unsigned int) maxw * W[i] / 255]);
                     else
                        for (unsigned int i = 0; i < n; i++)
#define max(a,b)	((a)>(b)?(a):(b))
                           led_strip_set_pixel (strip[s], i + (s ? 0 : led_status),     //
                                                gamma8[(unsigned int) maxr * max (R[i], W[i]) / 255],   //
                                                gamma8[(unsigned int) maxg * max (G[i], W[i]) / 255],   //
                                                gamma8[(unsigned int) maxb * max (B[i], W[i]) / 255]);
#undef max
                  } else
                  {
                     for (unsigned int i = 0; i < n; i++)
                        led_strip_set_pixel (strip[s], i + (s ? 0 : led_status),        //
                                             gamma8[(unsigned int) maxr * R[i] / 255],  //
                                             gamma8[(unsigned int) maxg * G[i] / 255],  //
                                             gamma8[(unsigned int) maxb * B[i] / 255]);
                  }
#endif
               } else
               {
#ifdef	CONFIG_REVK_LED
                  for (unsigned int i = 0; i < n; i++)
                     led_set (strip[s], i + (s ? 0 : led_status),       //
                              (unsigned int) maxr * R[i] / 255, //
                              (unsigned int) maxg * G[i] / 255, //
                              (unsigned int) maxb * B[i] / 255, //
                              W ? (unsigned int) maxw * W[i] / 255 : 0);
#else
                  if (b.rgbw)
                  {
                     if (typeisrgbw (ledtype[s]))
                        for (unsigned int i = 0; i < n; i++)
                           led_strip_set_pixel_rgbw (strip[s], i + (s ? 0 : led_status),        //
                                                     (unsigned int) maxr * R[i] / 255,  //
                                                     (unsigned int) maxg * G[i] / 255,  //
                                                     (unsigned int) maxb * B[i] / 255,  //
                                                     (unsigned int) maxw * W[i] / 255);
                     else
                        for (unsigned int i = 0; i < n; i++)
#define max(a,b)	((a)>(b)?(a):(b))
                           led_strip_set_pixel (strip[s], i + (s ? 0 : led_status),     //
                                                (unsigned int) maxr * max (R[i], W[i]) / 255,   //
                                                (unsigned int) maxg * max (G[i], W[i]) / 255,   //
                                                (unsigned int) maxb * max (B[i], W[i]) / 255);
#undef max
                  } else
                  {
                     for (unsigned int i = 0; i < n; i++)
                        led_strip_set_pixel (strip[s], i + (s ? 0 : led_status),        //
                                             (unsigned int) maxr * R[i] / 255,  //
                                             (unsigned int) maxg * G[i] / 255,  //
                                             (unsigned int) maxb * B[i] / 255);
                  }
#endif
               }
               R += ledcount[s];
               G += ledcount[s];
               B += ledcount[s];
               if (W)
                  W += ledcount[s];
               if (!s)
               {
#ifndef  CONFIG_REVK_LED
                  if (led_status)
                     revk_led (strip[s], 0, 255, revk_blinker ());
                  else
                     revk_blink_do ();  // Library blink
#endif
               }
            }
#ifdef  CONFIG_REVK_LED
         revk_blink_do ();
#else
         for (int s = 0; s < STRIPS; s++)
            if (strip[s])
               REVK_ERR_CHECK (led_strip_refresh (strip[s]));
#endif
      }
   }
}

void
revk_state_extra (jo_t j)
{
   if (voltage)
      jo_litf (j, "voltage", "%d.%03d", voltage / 1000, voltage % 1000);
}

void
revk_web_extra (httpd_req_t *req, int page)
{
   if (!page)
   {
      if (blink[0].set)
         revk_web_setting (req, NULL, "dark");
      revk_web_setting (req, NULL, "onpower");
      if (b.micok)
         revk_web_setting (req, NULL, "onclap");
      if (button.set)
         revk_web_setting (req, NULL, "onbutton");
      revk_web_setting (req, NULL, "stack");
      revk_web_setting (req, NULL, "haenable");
   } else
   {
      revk_web_send (req,
                     "<tr><td colspan=3><h2>Preset %d:</h2>This preset (or <i>virtual strip</i>) appears as a <i>light</i> in Home Assistant if <tt>name</tt> is set. These can overlap if required.%s</td></tr>",
                     page, haenable ? "" : " (HA is not enabled)");
      if (b.micok)
         revk_web_send (req,
                        "<tr><td colspan=3>Audio response %dHz to %dHz in %d bins, e.g. Starting %dHz %dHz %dHz %dHz %dHz %dHz %dHz %dHz ... %dHz %dHz %dHz, but based on %dHz steps mapped to these bins.</td></tr>",
                        MICMIN, MICMAX, MICBANDS, micband2hz (0), micband2hz (1), micband2hz (2),
                        micband2hz (3), micband2hz (4), micband2hz (5), micband2hz (6), micband2hz (7),
                        micband2hz (MICBANDS - 3), micband2hz (MICBANDS - 2), micband2hz (MICBANDS - 1), cps);
      if (page == 1)
         revk_web_send (req, "<tr><td colspan=3>This is the defaults for web settings on main page.</td></tr>");
      if (onpower == page)
         revk_web_send (req, "<tr><td colspan=3>This is the setting applied at power on.</td></tr>");
      if (onclap == page)
         revk_web_send (req, "<tr><td colspan=3>This is the setting applied at loud clap.</td></tr>");
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
      add ("colour");
      add ("start");
      add ("len");
      add ("top");
      add ("bright");
      add ("delay");
      add ("timed");
      add ("limit");
      add ("speed");
      add ("fadein");
      add ("fadeout");
      add ("config");
   }
}

static void
register_uri (const httpd_uri_t *uri_struct)
{
   esp_err_t res = httpd_register_uri_handler (webserver, uri_struct);
   if (res != ESP_OK)
   {
      ESP_LOGE (TAG, "Failed to register %s, error code %d", uri_struct->uri, res);
   }
}

static void
register_ws_uri (const char *uri, esp_err_t (*handler) (httpd_req_t *r))
{
   httpd_uri_t uri_struct = {
      .uri = uri,
      .method = HTTP_GET,
      .handler = handler,
      .is_websocket = true,
   };
   register_uri (&uri_struct);
}

static void
register_get_uri (const char *uri, esp_err_t (*handler) (httpd_req_t *r))
{
   httpd_uri_t uri_struct = {
      .uri = uri,
      .method = HTTP_GET,
      .handler = handler,
   };
   register_uri (&uri_struct);
}

static esp_err_t
web_status (httpd_req_t *req)
{                               // Web socket status report
   int fd = httpd_req_to_sockfd (req);
   void wsend (jo_t * jp)
   {
      char *js = jo_finisha (jp);
      if (js)
      {
         httpd_ws_frame_t ws_pkt;
         memset (&ws_pkt, 0, sizeof (httpd_ws_frame_t));
         ws_pkt.payload = (uint8_t *) js;
         ws_pkt.len = strlen (js);
         ws_pkt.type = HTTPD_WS_TYPE_TEXT;
         httpd_ws_send_frame_async (req->handle, fd, &ws_pkt);
         free (js);
      }
   }
   esp_err_t status (void)
   {
      jo_t j = jo_object_alloc ();
      jo_array (j, "presets");
      for (int p = 0; p < CONFIG_REVK_WEB_EXTRA_PAGES; p++)
         jo_bool (j, NULL, (haon & (1ULL << p)) ? 1 : 0);
      jo_close (j);
      jo_array (j, "active");
      for (int preset = 0; preset <= CONFIG_REVK_WEB_EXTRA_PAGES; preset++)
      {
         for (unsigned int i = 0; i < MAXAPPS; i++)
         {
            app_t *a = &active[i];
            if ((!stack || a->preset == preset) && a->app && !a->stop)
            {
               jo_object (j, NULL);
               if (*a->name)
                  jo_string (j, "effect", a->name);
               if (a->start && a->start != 1)
                  jo_int (j, "start", a->start);
               if (a->len && a->len != ledmax)
                  jo_int (j, "len", a->len);
               if (a->bright < 255)
                  jo_int (j, "bright", a->bright);
               if (a->delay)
                  jo_litf (j, "delay", "%.lf", 1.0 * a->delay / cps);
               if (a->limit)
                  jo_litf (j, "limit", "%.1f", 1.0 * a->limit / cps);
               if (a->speed != cps)
                  jo_litf (j, "speed", "%.1f", 1.0 * a->speed / cps);
               if (a->fadein != cps)
                  jo_litf (j, "fadein", "%.1f", 1.0 * a->fadein / cps);
               if (a->fadeout != cps)
                  jo_litf (j, "fadeout", "%.1f", 1.0 * a->fadeout / cps);
               if (a->palette)
                  jo_string (j, "colour", palettes[a->palette - 1].name);
               else if (a->colourset)
               {
                  if (b.rgbw)
                     jo_stringf (j, "colour", "#%02X%02X%02X%02X", a->r, a->g, a->b, a->w);
                  else
                     jo_stringf (j, "colour", "#%02X%02X%02X", a->r, a->g, a->b);
               }
               if (a->preset)
               {
                  if (*name[a->preset - 1])
                     jo_string (j, "preset", name[a->preset - 1]);
                  else
                     jo_int (j, "preset", a->preset);
               }
               if (a->config && *a->config)
                  jo_lit (j, "config", a->config);      // Already validated json
               jo_int (j, "cycle", a->cycle);
               if (a->stop)
                  jo_int (j, "stop", a->stop);
               jo_close (j);
            }
         }
         if (!stack)
            break;
      }
      jo_close (j);
      const char *reason;
      int t = revk_shutting_down (&reason);
      if (t)
         jo_string (j, "shutdown", reason);
      wsend (&j);
      return ESP_OK;
   }
   if (req->method == HTTP_GET)
      return status ();         // Send status on initial connect
   // received packet
   httpd_ws_frame_t ws_pkt;
   uint8_t *buf = NULL;
   memset (&ws_pkt, 0, sizeof (httpd_ws_frame_t));
   ws_pkt.type = HTTPD_WS_TYPE_TEXT;
   esp_err_t ret = httpd_ws_recv_frame (req, &ws_pkt, 0);
   if (ret)
      return ret;
   if (!ws_pkt.len)
      return status ();         // Empty string
   buf = calloc (1, ws_pkt.len + 1);
   if (!buf)
      return ESP_ERR_NO_MEM;
   ws_pkt.payload = buf;
   ret = httpd_ws_recv_frame (req, &ws_pkt, ws_pkt.len);
   if (!ret)
   {
      jo_t j = jo_parse_mem (buf, ws_pkt.len);
      if (j && jo_here (j) == JO_OBJECT)
      {
         while (jo_next (j) == JO_TAG)
         {
            char tag[10];
            jo_strncpy (j, tag, sizeof (tag));
            jo_next (j);
            int p = atoi (tag);
            ESP_LOGD (TAG, "Setting %d=%d", p, jo_here (j));
            if (p >= 1 && p <= CONFIG_REVK_WEB_EXTRA_PAGES)
            {
               if (jo_here (j) == JO_TRUE)
                  haon |= (1ULL << (p - 1));
               else if (jo_here (j) == JO_FALSE)
                  haon &= ~(1ULL << (p - 1));
               hastatus |= (1ULL << (p - 1));
               b.hacheck = 1;
            }
            jo_skip (j);
         }
         jo_free (&j);
      }
   }
   free (buf);
   return status ();
}

static esp_err_t
web_root (httpd_req_t *req)
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
   revk_web_send (req, "<h1>LED controller: %s</h1>", hostname);
   revk_web_send (req, "<p id=shutdown style=' display:none;color:red;'></p>");
   if (!ledmax)
      revk_web_send (req, "<h2>Please go to settings and set number of LEDs.</h2>");
   else
   {
      revk_web_send (req,
                     "<form method=get><fieldset><legend>Effect</legend><p>Colour:<input name=colour placeholder='#%s or colour name' size=30> or <select name=palette><option value=''>--- Palette --- </option>",
                     b.rgbw ? "RGBW" : "RGB");
      for (int p = 0; palettes[p].name; p++)
         revk_web_send (req, "<option value='%s'>%s (%s)</option>", palettes[p].name, palettes[p].name, palettes[p].description);
      revk_web_send (req, "</select></p><p>");
      void button (const char *tag, const char *title)
      {
         revk_web_send (req,
                        "<label for='%s'><div style='display:inline-block;text-align:center;'><input style='min-width:7rem;' type=submit name='app' value='%s' id='%s'></div></label>",
                        tag, title, tag);
      }
      for (int i = 0; i < sizeof (applist) / sizeof (*applist); i++)
         if (!applist[i].ring && !applist[i].text && !applist[i].sound)
            button (applist[i].name, applist[i].description);
      revk_web_send (req, "<br>");
      for (int i = 0; i < sizeof (applist) / sizeof (*applist); i++)
         if (applist[i].ring)
            button (applist[i].name, applist[i].description);
      revk_web_send (req, "<br>");
      for (int i = 0; i < sizeof (applist) / sizeof (*applist); i++)
         if (applist[i].text)
            button (applist[i].name, applist[i].description);
      revk_web_send (req, "<div style='display:inline-block;'>Most text effects are better done as a preset or via MQTT.</div>");
      if (b.micok)
      {
         revk_web_send (req, "<br>");
         for (int i = 0; i < sizeof (applist) / sizeof (*applist); i++)
            if (applist[i].sound)
               button (applist[i].name, applist[i].description);
      }
      revk_web_send (req, "<br>");
      button ("stop", "Stop");
      button ("dark", "Dark");
      revk_web_send (req, "</p></fieldset><fieldset><legend>Preset</legend><p>");
      for (int p = 1; p <= CONFIG_REVK_WEB_EXTRA_PAGES; p++)
      {
         if (!*config[p - 1] && !*effect[p - 1] && !*name[p - 1])
            continue;
         char num[10];
         sprintf (num, "%d", p);
         revk_web_send (req,
                        "<div style='display:inline-block;text-align:center;'><label class=switch><input type=checkbox id=\"%d\" onchange=\"w('%d',this.checked);\"%s><span class=slider></span></label><br><label for=\"%d\">%s</label></div></label>",
                        p, p, haon & (1ULL << (p - 1)) ? " checked" : "", p, *name[p - 1] ? name[p - 1] : num);
      }
      revk_web_send (req, "</p></fieldset></form>");
   }
   if (ledmax)
      revk_web_send (req, "<fieldset><legend>Active</legend><ul id=active></ul></fieldset>"     //
                     "<script>" //
                     "var ws=0;"        //
                     "var reboot=0;"    //
                     "function g(n){return document.getElementById(n);};"       //
                     "function b(n,v){var d=g(n);if(d)d.checked=v;}"    //
                     "function h(n,v){var d=g(n);if(d)d.style.display=v?'block':'none';}"       //
                     "function s(n,v){var d=g(n);if(d)d.textContent=v;}"        //
                     "function w(n,v){var m=new Object();m[n]=v;ws.send(JSON.stringify(m));}"   //
                     "function c(){"    //
                     "ws=new WebSocket((location.protocol=='https:'?'wss:':'ws:')+'//'+window.location.host+'/status');"        //
                     "ws.onclose=function(v){ws=undefined;if(reboot)location.reload();};"       //
                     "ws.onerror=function(v){ws.close();};"     //
                     "ws.onmessage=function(v){"        //
                     "o=JSON.parse(v.data);"    //
                     "o.presets.forEach(function(e,i,a){b(i+1,e);});"   //
                     "var a=document.createElement('ul');a.id='active';"        //
                     "o.active.forEach(function(e,i,ar){l=document.createElement('li');l.textContent=JSON.stringify(e);a.appendChild(l);});"    //
                     "g('active').replaceWith(a);"      //
                     "if(o.shutdown){reboot=true;s('shutdown','Restarting: '+o.shutdown);h('shutdown',true);};" //
                     "};};c();" //
                     "setInterval(function() {if(!ws)c();else ws.send('');},1000);"     //
                     "</script>");
   if (!ledmax)
      revk_web_send (req,
                     "<fieldset><legend>Software</legend>More information on this software is available at <a href='https://led.revk.uk/'>led.revk.uk</a>.");
#ifdef  CONFIG_IDF_TARGET_ESP32S3
   if (!ledmax)
      revk_web_send (req,
                     " If you would rather run WLED, it is important to realise this is an <b>ESP32-S3</b>. Please visit <a href='https://hiwtsi.uk/LED/#setup'>Home Is Where The Smart Is</a> for instructions on reflashing, otherwise you could break things. That site also has details on LED strips and other controllers.");
#endif
   revk_web_send (req, "</fieldset>");
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
      if (lssda.set)
         jo_int (j, "sda", lssda.num);
      if (lsscl.set)
         jo_int (j, "scl", lsscl.num);
      if (a)
         jo_int (j, "address", a);
      return j;
   }
   esp_err_t err;
   err = i2c_driver_install (0, I2C_MODE_MASTER, 0, 0, 0);
   if (!err)
   {
      i2c_config_t config = {
         .mode = I2C_MODE_MASTER,
         .sda_io_num = lssda.num,
         .scl_io_num = lsscl.num,
         .sda_pullup_en = true,
         .scl_pullup_en = true,
         .master.clk_speed = 400000,
      };
      err = i2c_param_config (0, &config);
      if (err)
         i2c_driver_delete (0);
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
      err = i2c_master_cmd_begin (0, t, 10 / portTICK_PERIOD_MS);
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
      err = i2c_master_cmd_begin (0, t, 10 / portTICK_PERIOD_MS);
      i2c_cmd_link_delete (t);
      if (err)
      {
         jo_t j = e (a, cmd, "Failed to ALS read", err);
         revk_error ("i2c", &j);
         return;
      }
   }
   if (!lsals)
   {                            // No I2C work
      vTaskDelete (NULL);
      return;
   }
   w (lsals, 0x00, 0x0040);
   ESP_LOGI (TAG, "ALS mode=%04X ", r (lsals, 0x00));
   while (1)
   {
      jo_t j = jo_object_alloc ();
      jo_litf (j, "r", "%.0f", (float) r (lsals, 0x08) * 1031 / 65535);
      jo_litf (j, "g", "%.0f", (float) r (lsals, 0x09) * 1031 / 65535);
      jo_litf (j, "b", "%.0f", (float) r (lsals, 0x0A) * 1031 / 65535);
      jo_litf (j, "w", "%.0f", (float) r (lsals, 0x0B) * 1031 / 65535);
      revk_info ("als", &j);
      sleep (1);
   }
   vTaskDelete (NULL);
}

void
adc_task (void *arg)
{
   adc_unit_t adc_unit = 0;
   adc_channel_t adc_channel = 0;
   adc_oneshot_unit_handle_t adc_handle;
   adc_cali_handle_t adc_cali_handle = NULL;
   adc_oneshot_io_to_channel (adc.num, &adc_unit, &adc_channel);
   ESP_LOGE (TAG, "ADC %d unit %d channel %d", adc.num, adc_unit, adc_channel);
   adc_oneshot_unit_init_cfg_t init_config1 = {
      .unit_id = adc_unit,
      .ulp_mode = ADC_ULP_MODE_DISABLE,
   };
   adc_oneshot_new_unit (&init_config1, &adc_handle);
   ESP_LOGE (TAG, "Init done");
   adc_oneshot_chan_cfg_t config = {
      .bitwidth = ADC_BITWIDTH_DEFAULT,
      .atten = ADC_ATTEN,
   };
   adc_oneshot_config_channel (adc_handle, adc_channel, &config);
   ESP_LOGE (TAG, "Config done");
#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
   adc_cali_curve_fitting_config_t cali_config = {
      .unit_id = adc_unit,
      .chan = adc_channel,
      .atten = ADC_ATTEN,
      .bitwidth = ADC_BITWIDTH_DEFAULT,
   };
   adc_cali_create_scheme_curve_fitting (&cali_config, &adc_cali_handle);
#endif
#if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
   adc_cali_line_fitting_config_t cali_config = {
      .unit_id = adc_unit,
      .atten = ADC_ATTEN,
      .bitwidth = ADC_BITWIDTH_DEFAULT,
   };
   adc_cali_create_scheme_line_fitting (&cali_config, &adc_cali_handle);
#endif
   while (1)
   {
      int raw = 0,
         volt = 0;
      adc_oneshot_read (adc_handle, adc_channel, &raw);
      adc_cali_raw_to_voltage (adc_cali_handle, raw, &volt);
      voltage = volt * ADC_SCALE;
      sleep (1);
   }
   adc_oneshot_del_unit (adc_handle);
   vTaskDelete (NULL);
}

float micmag = 0;
float micband[MICBANDS] = { 0 };

SemaphoreHandle_t mic_mutex = NULL;
void
mic_task (void *arg)
{
   jo_t e (esp_err_t err, const char *msg)
   {                            // Error
      jo_t j = jo_object_alloc ();
      if (msg)
         jo_string (j, "message", msg);
      if (err)
         jo_string (j, "error", esp_err_to_name (err));
      if (micdata.set)
         jo_int (j, "data", micdata.num);
      if (micclock.set)
         jo_int (j, "clock", micclock.num);
      return j;
   }
   esp_err_t err;
   i2s_chan_handle_t i = { 0 };
   i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG (I2S_NUM_AUTO, I2S_ROLE_MASTER);
   err = i2s_new_channel (&chan_cfg, NULL, &i);
   uint8_t bytes = (micws.set ? 4 : 2);
   uint8_t *micraw = mallocspi (bytes * MICSAMPLES * MICOVERSAMPLE);
   float *fftre = mallocspi (sizeof (float) * MICSAMPLES);
   float *fftim = mallocspi (sizeof (float) * MICSAMPLES);
   float micgain = 10;
   if (micrange <= 0)
      micrange = 1;
   if (micws.set)
   {                            // 24 bit Philips format
      ESP_LOGE (TAG, "I2S init CLK %d DAT %d WS %d", micclock.num, micdata.num, micws.num);
      i2s_std_config_t cfg = {
         .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG (MICRATE * MICOVERSAMPLE),
         .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG (I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_STEREO),
         .gpio_cfg = {
                      .mclk = I2S_GPIO_UNUSED,
                      .bclk = micclock.num,
                      .ws = micws.num,
                      .dout = I2S_GPIO_UNUSED,
                      .din = micdata.num,
                      .invert_flags = {
                                       .mclk_inv = false,
                                       .bclk_inv = micclock.invert,
                                       .ws_inv = micws.invert,
                                       },
                      },
      };
      cfg.slot_cfg.slot_mask = (micright ? I2S_STD_SLOT_RIGHT : I2S_STD_SLOT_LEFT);
      if (bytes == 3)
         cfg.clk_cfg.mclk_multiple = 384;
      if (!err)
         err = i2s_channel_init_std_mode (i, &cfg);
   } else
   {                            // PDM 16 bit
      ESP_LOGE (TAG, "I2S init PDM CLK %d DAT %d", micclock.num, micdata.num);
      i2s_pdm_rx_config_t cfg = {
         .clk_cfg = I2S_PDM_RX_CLK_DEFAULT_CONFIG (MICRATE * MICOVERSAMPLE),
         .slot_cfg = I2S_PDM_RX_SLOT_DEFAULT_CONFIG (I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
         .gpio_cfg = {
                      .clk = micclock.num,
                      .din = micdata.num,
                      .invert_flags = {
                                       .clk_inv = micclock.invert}
                      }
      };
      cfg.slot_cfg.slot_mask = (micright ? I2S_PDM_SLOT_RIGHT : I2S_PDM_SLOT_LEFT);
      if (!err)
         err = i2s_channel_init_pdm_rx_mode (i, &cfg);
   }
   gpio_pulldown_en (micdata.num);
   if (!err)
      err = i2s_channel_enable (i);
   if (err)
   {
      revk_ate_fail ("MIC/I2S failed");
      ESP_LOGE (TAG, "I2S failed");
      jo_t j = e (err, "Failed init I2S");
      revk_error ("i2s", &j);
      vTaskDelete (NULL);
      return;
   }
   ESP_LOGE (TAG, "Audio started, %d*%d bits at %dHz", MICSAMPLES * MICOVERSAMPLE, bytes * 8, MICRATE * MICOVERSAMPLE);
   while (1)
   {
      size_t n = 0;
      i2s_channel_read (i, micraw, bytes * MICSAMPLES * MICOVERSAMPLE, &n, 100);
      if (n < bytes * MICSAMPLES * MICOVERSAMPLE)
         continue;
      if (!b.micok && *(int32_t *) micraw)
      {
         b.micok = 1;
         ESP_LOGE (TAG, "Audio running");
      }
      {                         // Magnitude
         float mag = 0;
         uint8_t *p = micraw;
         for (int i = 0; i < MICSAMPLES * MICOVERSAMPLE; i++)
         {
            int32_t raw;
            if (bytes == 4)
               raw = *(int32_t *) p;    // PCM 32 bit (TDK populates top 24 bits and rest 0)
            else
               raw = *(int16_t *) p << 16;      // PDM 16 bit mode
            p += bytes;
            float v = (float) raw / 2147483648;
            mag += v * v;
         }
         micmag = sqrt (mag / MICSAMPLES / MICOVERSAMPLE);
         if (micmag > MICCLAP && onclap && onclap <= CONFIG_REVK_WEB_EXTRA_PAGES && *effect[onclap - 1])
         {                      // Loud noise - tap or loud clap
            if (!(haon & (1ULL << (onclap - 1))))
            {
               ESP_LOGD (TAG, "Clap start effect %d (%f)", onclap, micmag);
               haon |= (1ULL << (onclap - 1));
               b.hacheck = 1;
            } else
            {
               ESP_LOGD (TAG, "Clap restart effect %d (%f)", onclap, micmag);
               for (unsigned int i = 0; i < MAXAPPS; i++)
                  if (active[i].preset == onclap)
                  {
                     active[i].stop = 0;
                     if (active[i].cycle > active[i].fadein)
                        active[i].cycle = (active[i].fadein ? : 1);
                  }
            }
         }
      }
      if (!b.micon)
         continue;
      {
         uint8_t *p = micraw;
         for (int i = 0; i < MICSAMPLES; i++)
         {
            int32_t raw;
            if (bytes == 4)
               raw = *(int32_t *) p;    // PCM 32 bit (TDK populates top 24 bits and rest 0)
            else
               raw = *(int16_t *) p << 16;      // PDM 16 bit mode
            p += bytes;
            float v = (float) raw / 2147483648;
            fftre[i] = v * micgain / MICOVERSAMPLE;
            for (int q = 0; q < MICOVERSAMPLE - 1; q++)
            {
               if (bytes == 4)
                  raw = *(int32_t *) p << 1;    // Philips mode
               else
                  raw = *(int16_t *) p << 16;   // PDM 16 bit mode
               p += bytes;
               float v = (float) raw / 2147483648;
               fftre[i] += v * micgain / MICOVERSAMPLE;
            }
            fftim[i] = 0;
         }
      }
      fft (fftre, fftim, MICSAMPLES);
      float band[MICBANDS];     // Should get main audio in first 16 or so slots
      for (int b = 0; b < MICBANDS; b++)
         band[b] = NAN;
      {                         // log frequency
         float low = log (MICMIN),
            high = log (MICMAX),
            step = (high - low) / MICBANDS;
         for (int i = MICMIN * MICSAMPLES / MICRATE; i < MICMAX * MICSAMPLES / MICRATE && i < MICSAMPLES / 2; i++)
         {
            float l = log (i * MICRATE / MICSAMPLES);
            int b = (l - low) / step;
            if (b >= 0 && b < MICBANDS) // In case of rounding going too far!
            {
               fftre[i] /= (MICSAMPLES / 2);
               fftim[i] /= (MICSAMPLES / 2);
               float v = sqrt (fftre[i] * fftre[i] + fftim[i] * fftim[i]);
               if (isnan (band[b]))
                  band[b] = v;
               else
                  band[b] += v;
            }
         }
      }
      for (int b = 0; b < MICBANDS - 1; b++)
         if (!isnan (band[b]) && isnan (band[b + 1]))
         {
            int q = 2;
            while (b + q < MICBANDS && isnan (band[b + q]))
               q++;
            float v = band[b];
            for (int z = 0; z < q; z++)
               band[b + z] = v / q;
         }
      //ESP_LOGE (TAG, "FFT %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f gain %6.2f", band[0], band[3], band[6], band[9], band[12], band[15], band[18], band[21], micgain);
      float max = 0;
      // Log scale
      for (int b = 0; b < MICBANDS; b++)
      {
         if (band[b] > max)
            max = band[b];
         band[b] = 10 * log10 (band[b]);        // OK no clue why but if we average we end up with way lower top frequencies
      }
      for (int b = 0; b < MICBANDS; b++)
         band[b] = (band[b] + micrange) / micrange;     // makes more 0-1 level output, max should be 1 so log will be 0
      //ESP_LOGE (TAG, "max %lf gain %lf", max, micgain);
      // Auto gain aims for max peak of 1
      if (max > 1)
         micgain = (micgain * 9 + micgain / max) / 10;  // Drop gain faster if overloading
      else if (max > 0)
         micgain = (micgain * 99 + micgain / max) / 100;        // Bring back gain slowly
      float limit = pow (10, (float) micmaxgain / 10);
      if (micgain > limit)
         micgain = limit;
      //ESP_LOGE (TAG, "FFT %6.2f %6.2f %6.2f %6.2f %6.2f %6.2f %6.2f %6.2f", band[0], band[3], band[6], band[9], band[12], band[15], band[18], band[21]);
      xSemaphoreTake (mic_mutex, portMAX_DELAY);
      for (int i = 0; i < MICBANDS; i++)
      {
         if (band[i] > micband[i] || !micdamp)
            micband[i] = band[i];
         else
            micband[i] = (micband[i] * micdamp + band[i]) / (micdamp + 1);
      }
      xSemaphoreGive (mic_mutex);
   }

   vTaskDelete (NULL);
}

uint8_t
michz2band (uint32_t hz)
{
   if (hz)
      return 0;
   float low = log (MICMIN),
      high = log (MICMAX),
      val = log (hz);
   int b = MICBANDS * (val - low) / (high - low);
   if (b < 0)
      b = 0;
   if (b >= MICBANDS)
      b = MICBANDS;
   return b;
}

uint32_t
micband2hz (uint8_t b)
{
   float low = log (MICMIN),
      high = log (MICMAX),
      val = b * (high - low) / MICBANDS + low;
   return exp (val);
}

#undef	N

void
bargraph (app_t *a, pixel_t *pixel, int v, int total, uint8_t fade)
{
   if (!total)
      total = 1;
   int t = a->top;
   if (t < 0)
      t = -t;                   // TODO
   if (t > a->start)
   {
      int N = t - a->start + 1;
      uint32_t n = (uint32_t) 256 * N * v / total;
      uint8_t f = n & 255;
      n /= 256;
      int p = t;
      unsigned int i = 0;
      while (i < n)
         pixel (a, p--, i++, N, fade);
      if (f)
         pixel (a, p--, i++, N, ((int) f * fade / 255));
      while (i < N)
         pixel (a, p--, i++, N, 0);
   }
   if (t < a->start + a->len - 1)
   {
      int N = a->start + a->len - t;
      uint32_t n = (uint32_t) 256 * N * v / total;
      uint8_t f = n & 255;
      n /= 256;
      int p = t;
      unsigned int i = 0;
      while (i < n)
         pixel (a, p++, i++, N, fade);
      if (f)
         pixel (a, p++, i++, N, ((int) f * fade / 255));
      while (i < N)
         pixel (a, p++, i++, N, 0);
   }
}

void
dokey (uint32_t key)
{
   const char *k = NULL;
   if (ir4x11 && !(key & 0xFFFFFF00))
   {
      int q = 0;
      for (q = 0; q < sizeof (ir4x11id) && ir4x11id[q] != key; q++);
      if (q < sizeof (ir4x11id))
         k = ir4x11name[q];
   }
   if (ir4x6 && (key & 0xFFFFFF00) == 0x00100000 && (key & 0xFF) < sizeof (ir4x6name) / sizeof (*ir4x6name))
      k = ir4x6name[key & 0xFF];
   if (!k)
      return;
   if (!strncmp (k, "DIY", 3))
   {                            // Preset control
      app_callback (0, topiccommand, NULL, k + 3, NULL);
      return;
   }
   xSemaphoreTake (app_mutex, portMAX_DELAY);
   if (!active[0].app)
      addapp (0, 0, "idle", NULL);
   uint8_t adjust (uint8_t v, char d)
   {
      if (d == '-')
      {
         if (v < 15)
            v = 0;
         else
            v -= 15;
      } else if (d == '+')
      {
         if (v > 240)
            v = 255;
         else
            v += 15;
      }
      return v;
   }
   if (*k == 'P' || !strcmp (k, "OFF"))
      active[0].stop = active[0].fadeout;
   else if (*k == '#')
      setcolour (&active[0], k);
   else if (*k == '+' || *k == '-')
      active[0].bright = adjust (active[0].bright, *k);
   else if (*k == 'R')
      active[0].r = adjust (active[0].r, k[1]);
   else if (*k == 'G')
      active[0].g = adjust (active[0].g, k[1]);
   else if (*k == 'B')
      active[0].b = adjust (active[0].b, k[1]);
   xSemaphoreGive (app_mutex);
   jo_t j = jo_create_alloc ();
   jo_string (j, NULL, k);
   revk_info ("ir", &j);
}

static void
ir_callback (uint8_t coding, uint16_t lead0, uint16_t lead1, uint8_t len, uint8_t *data)
{                               // Handle generic IR https://www.amazon.co.uk/dp/B07DJ58XGC
   //ESP_LOGE (TAG, "IR CB %d %d %d %d", coding, lead0, lead1, len);
   static uint32_t key = 0;
   static uint8_t count = 0;
   if (coding == IR_PDC && len == 32 && lead0 > 8500 && lead0 < 9500 && lead1 > 4000 && lead1 < 5000 && (data[2] ^ data[3]) == 0xFF)
   {                            // Key (NEC) - normally address and inverted address, but allow for special cases, as long as code and inverted code.
      key = (((data[0] ^ ~data[1]) & 0xFF) << 16 | (data[0] << 8) | data[2]);
      count = 1;
      //ESP_LOGE (TAG, "Key %04lX", key);
   }
   if (count && coding == IR_ZERO && len == 1 && lead0 > 8500 && lead0 < 9500 && lead1 > 1500 && lead1 < 2500 && key)
   {                            // Continue - ignore for now
      if (count < 255)
         count++;
      if (count == 10 || count == 20)
      {
         dokey (key);
         count = 15;
      }
   }
   if (count && coding == IR_IDLE)
   {
      if (count < 10)
         dokey (key);
      key = 0;
      count = 0;
   }
}

void
app_main ()
{
   //ESP_LOGE (TAG, "Started");
   app_mutex = xSemaphoreCreateBinary ();
   xSemaphoreGive (app_mutex);
   mic_mutex = xSemaphoreCreateBinary ();
   xSemaphoreGive (mic_mutex);
   revk_boot (&app_callback);
#ifdef	CONFIG_REVK_MATTER
   extern void matter_main (void);
   matter_main ();
#endif
   revk_start ();
   if (dark)
      revk_blink (0, 0, "K");
   if (!cps)
      cps = 10;                 // Safety for division
   if (micdata.set && micclock.set)
      revk_task ("i2s", mic_task, NULL, 8);
   if (lssda.set && lsscl.set)
      revk_task ("i2c", i2c_task, NULL, 4);
   if (adc.set)
      revk_task ("adc", adc_task, NULL, 4);
   memset (habright, 255, sizeof (habright));
   if (b.rgbw)
      memset (haw, 255, sizeof (haw));
   else
   {
      memset (har, 255, sizeof (har));
      memset (hag, 255, sizeof (hag));
      memset (hab, 255, sizeof (hab));
   }
   revk_task ("LED", led_task, NULL, 4);
   if (irgpio.set)
      ir_start (irgpio, ir_callback);
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
         register_ws_uri ("/status", web_status);
      }
   }
   if (micdata.set && micclock.set)
   {
      sleep (1);
      if (!b.micok)
         revk_blink (10, 0, "R");
   }
   revk_ate_pass ();
   while (1)
   {
      time_t now = time (0);
      if (now < 1000000000)
      {                         // Clock not set
         sleep (1);
         continue;
      }
      struct tm tm;
      localtime_r (&now, &tm);
      int hhmm = tm.tm_hour * 100 + tm.tm_min;
      uint64_t t = 0;
      for (int p = 0; p < CONFIG_REVK_WEB_EXTRA_PAGES; p++)
         if (timed[p] && timed[p] == hhmm)
            t |= (1ULL << p);
      if (t)
      {
         haon |= t;
         hastatus |= t;
         b.hacheck = 1;
      }
      sleep (60 - (now % 60));
   }
   //hargb = -1;
}
