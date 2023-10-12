/* LED app */
/* Copyright ©2019 - 23 Adrian Kennard, Andrews & Arnold Ltd.See LICENCE file for details .GPL 3.0 */

static const char TAG[] = "LED";

#include "revk.h"
#include "esp_sleep.h"
#include "esp_task_wdt.h"
#include <driver/gpio.h>
#include <driver/uart.h>
#include "led_strip.h"
#include "app.h"
#include <esp_http_server.h>

#define a(a,d)	extern const char* app##a(app_t*);
#include "apps.h"

struct applist_s
{
   const char *name;
   app_f *app;
   uint8_t ring:1;              // Is a ring based app
} applist[] = {
#define a(a,d)	{#a,&app##a,0},
#define r(a,d)	{#a,&app##a,1},
#include "apps.h"
};

static httpd_handle_t webserver = NULL;

uint8_t *ledr = NULL;
uint8_t *ledg = NULL;
uint8_t *ledb = NULL;

#define	IO_MASK	0x3F
#define	IO_INV	0x40

#define u32(n,d)        uint32_t n;
#define u32l(n,d)        uint32_t n;
#define s8(n,d) int8_t n;
#define s8n(n,d) int8_t n[d];
#define u8(n,d) uint8_t n;
#define u8r(n,d) uint8_t n,ring##n;
#define u16(n,d) uint16_t n;
#define u16r(n,d) uint16_t n,ring##n;
#define s8r(n,d) int8_t n,ring##n;
#define s16r(n,d) int16_t n,ring##n;
#define u8l(n,d) uint8_t n;
#define b(n) uint8_t n;
#define s(n,d) char * n;
#define io(n,d)           uint8_t n;
#ifdef  CONFIG_REVK_BLINK
#define led(n,a,d)      extern uint8_t n[a];
#else
#define led(n,a,d)      uint8_t n[a];
#endif
settings                        //
   params                       //
#undef led
#undef io
#undef u32
#undef u32l
#undef s8
#undef s8n
#undef u8
#undef u8r
#undef u16
#undef u16r
#undef s8r
#undef s16r
#undef u8l
#undef b
#undef s
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

const uint8_t gamma8[256] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
   2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5,
   5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
   115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
   144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
   177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
   215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

app_t active[MAXAPPS] = { 0 };

static SemaphoreHandle_t app_mutex = NULL;

void
appzap (app_t * a)
{                               // Assumes mutex, Delete an app
   free (a->data);
   memset (a, 0, sizeof (*a));
}

app_t *
addapp (int index, const char *name, jo_t j)
{                               // Assumes mutex, store an app
   if (index >= MAXAPPS)
      return NULL;
   app_t *a = &active[index];
   if (!name || !*name)
      appzap (a);
   for (int i = 0; i < sizeof (applist) / sizeof (*applist); i++)
      if (!strcasecmp (name, applist[i].name))
      {
         uint8_t setcolour (jo_t j)
         {
            char temp[20];
            jo_strncpy (j, temp, sizeof (temp));
            if (!strcasecmp (temp, "rainbow"))
               a->colourset = a->rainbow = 1;
            else if (!strcasecmp (temp, "cycling"))
               a->colourset = a->cycling = 1;
#define	c(h,c)	else if(!strcasecmp(temp,#c))strcpy(temp,#h);
            colours
#undef c
            char *c = temp;
            if (*c == '#')
               c++;
#define x(n)((c[n] & 0xF) + (isalpha ((uint8_t)c[n]) ? 9 : 0))
            if (strlen (c) == 3 && isxdigit ((int) c[0]) && isxdigit ((int) c[1]) && isxdigit ((int) c[2]))
            {
               a->colourset = 1;
               a->r = x (0) * 17;
               a->g = x (1) * 17;
               a->b = x (2) * 17;
            } else
               if (strlen (c) == 6 && isxdigit ((int) c[0]) && isxdigit ((int) c[1]) && isxdigit ((int) c[2])
                   && isxdigit ((int) c[3]) && isxdigit ((int) c[4]) && isxdigit ((int) c[5]))
            {
               a->colourset = 1;
               a->r = x (0) * 16 + x (1);
               a->g = x (2) * 16 + x (3);
               a->b = x (4) * 16 + x (5);
            } else
               return 0;
            return 1;
#undef x
         }
         if (!a->app || a->name != applist[i].name || a->stop)
            appzap (a);
         a->name = applist[i].name;
         // Defaults
#define u8(n,d)         a->n=n;
#define u8r(n,d)        if(applist[i].ring)a->n=(ring##n?:n); else u8(n,d)
#define u16(n,d)         u8(n,d)
#define u16r(n,d)        u8r(n,d)
#define s8(n,d)        u8(n,d)
#define s8r(n,d)        u8r(n,d)
#define s16r(n,d)        u16r(n,d)
#define u32(n,d)        u8(n,d)
         params
#undef  u8
#undef  u8r
#undef  u16
#undef  u16r
#undef  s8
#undef  s8r
#undef  s16r
#undef  u32
            if (j && jo_here (j) == JO_OBJECT)
         {                      // Expects to be at start of object
            while (jo_next (j) == JO_TAG)
            {
#define u8(n,d)         if(!jo_strcmp(j,#n)){if(jo_next(j)==JO_NUMBER)a->n=jo_read_int(j);continue;}
#define u8r(n,d)        u8(n,d)
#define u16(n,d)        u8(n,d)
#define u16r(n,d)        u8(n,d)
#define s8(n,d)        u8(n,d)
#define s8r(n,d)        u8(n,d)
#define s16r(n,d)        u8(n,d)
#define u32(n,d)        u8(n,d)
               params
#undef  u8
#undef  u8r
#undef  u16
#undef  u16r
#undef  s8
#undef  s8r
#undef  s16r
#undef  u32
                  if (!jo_strcmp (j, "colour"))
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
            a->limit = jo_read_int (j);
         if (!a->start)
            a->start = 1;
         if (!a->top)
            a->top = a->start;
         if (!a->len)
            a->len = leds + 1 - a->start;
         if (!a->speed)
            a->speed = cps;
         if (!a->fade)
            a->fade = cps;
         if (!a->height)
            a->height = 8;
         a->app = applist[i].app;
         ESP_LOGI (TAG, "Adding app %d: %s (%lu)", index, name, a->cycle);
         return a;
      }
   appzap (a);
   ESP_LOGI (TAG, "App not found %s", name);
   jo_t e = jo_object_alloc ();
   jo_int (j, "level", index);
   jo_string (e, "app", name);
   revk_error ("not-found", &e);
   return NULL;
}

void
appzapall (int index)
{                               // Assumes mutex, clears all apps at index to end
   while (index < MAXAPPS)
      appzap (&active[index++]);
}

int
apptidy (uint8_t stop)
{                               // Assumes mutex, packs all apps to start, if stop set then stops active apps, returns first unused app (must be checked against MAXAPPS)
   int i = 0,
      o = 0;
   while (i < MAXAPPS)
   {
      app_t *a = &active[i];
      if (stop && a->delay)
         appzap (a);            // Not started, so simply zap
      if (stop && a->app && !a->stop)
         a->stop = a->fade;     // Running, so controlled stop
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
led_add (const char *tag, jo_t j)
{
   for (int i = 0; i < sizeof (applist) / sizeof (*applist); i++)
      if (!strcasecmp (tag, applist[i].name))
      {                         // Direct command
         xSemaphoreTake (app_mutex, portMAX_DELAY);
         int index = apptidy (1);
         addapp (index++, tag, j);
         xSemaphoreGive (app_mutex);
         return "";
      }
   return "Unknown";
}

const char *
app_callback (int client, const char *prefix, const char *target, const char *suffix, jo_t j)
{
   if (client || !prefix || target || strcmp (prefix, prefixcommand))
      return NULL;              // Not for us or not a command from main MQTT
   if (suffix && !strcasecmp (suffix, "stop"))
      return led_stop ();
   if (suffix && strcmp (suffix, "add"))
      return led_add (suffix, j);
   // Process command to set apps
   xSemaphoreTake (app_mutex, portMAX_DELAY);
   int index = apptidy (suffix ? 0 : 1);
   if (!suffix)
      index = 0;                // Overwrite existing
   jo_type_t t = jo_here (j);
   if (t == JO_STRING)
   {                            // Simple add app
      char temp[20];
      jo_strncpy (j, temp, sizeof (temp));
      addapp (index++, temp, NULL);
   } else if (t == JO_ARRAY)
   {
      while ((t = jo_next (j)) == JO_STRING)
      {
         char temp[20];
         jo_strncpy (j, temp, sizeof (temp));
         addapp (index++, temp, NULL);
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
         addapp (index++, temp, j);
      }
   }
   appzapall (index);
   xSemaphoreGive (app_mutex);
   return "";
}

void
led_task (void *x)
{
   ESP_LOGI (TAG, "Started using GPIO %d%s", ledgpio & IO_MASK, ledgpio & IO_INV ? " (inverted)" : "");
   led_strip_handle_t strip = NULL;
   led_strip_config_t strip_config = {
      .strip_gpio_num = (ledgpio & IO_MASK),
      .max_leds = leds,         // The number of LEDs in the strip,
      .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
      .led_model = LED_MODEL_WS2812,    // LED strip model
      .flags.invert_out = ((ledgpio & IO_INV) ? 1 : 0), // whether to invert the output signal (useful when your hardware has a level inverter)
   };
   led_strip_rmt_config_t rmt_config = {
      .clk_src = RMT_CLK_SRC_DEFAULT,   // different clock source can lead to different power consumption
      .resolution_hz = 10 * 1000 * 1000,        // 10MHz
#ifdef	CONFIG_IDF_TARGET_ESP32S3
      .flags.with_dma = true,
#endif
   };
   REVK_ERR_CHECK (led_strip_new_rmt_device (&strip_config, &rmt_config, &strip));
   REVK_ERR_CHECK (led_strip_clear (strip));
   ledr = calloc (leds, sizeof (*ledr));
   ledg = calloc (leds, sizeof (*ledg));
   ledb = calloc (leds, sizeof (*ledb));
   if (*app)
      addapp (0, app, NULL);
   if (!cps)
      cps = 10;
   uint32_t tick = 1000000LL / cps;
   if (!leds)
      leds = 1;
   uint8_t idle = 0;
   while (1)
   {                            // Main loop
      usleep (tick - (esp_timer_get_time () % tick));
      clear (1, leds);
      xSemaphoreTake (app_mutex, portMAX_DELAY);
      for (unsigned int i = 0; i < MAXAPPS; i++)
      {
         app_t *a = &active[i];
         if (a->app)
         {
            const char *name = a->name;
            if (a->delay)
            {                   // Delayed start
               a->delay--;
               continue;
            }
            idle = 0;
            if (a->rainbow)
            {                   // Cycle the colour
               a->r = wheel[(a->cycle) & 255];
               a->g = wheel[(a->cycle + 85) & 255];
               a->b = wheel[(a->cycle + 170) & 255];
            } else if (a->cycling)
            {                   // Cycle the colour
               a->r = cos8[(a->cycle) & 255];
               a->g = cos8[(a->cycle + 85) & 255];
               a->b = cos8[(a->cycle + 170) & 255];
            }
            if (!a->cycle)
            {                   // Starting
               jo_t j = jo_object_alloc ();
               jo_int (j, "level", i);
               jo_string (j, "app", a->name);
#define u8(n,d)         if(a->n)jo_int(j,#n,a->n);
#define u8r(n,d)        u8(n,d)
#define u16(n,d)         u8(n,d)
#define u16r(n,d)        u8(n,d)
#define s8(n,d)        u8(n,d)
#define s8r(n,d)        u8(n,d)
#define s16r(n,d)        u8(n,d)
#define u32(n,d)        u8(n,d)
               params
#undef  u8
#undef  u8r
#undef  u16
#undef  u16r
#undef  s8
#undef  s8r
#undef  s16r
#undef  u32
                  if (a->rainbow)
                  jo_string (j, "colour", "rainbow");
               else if (a->cycling)
                  jo_string (j, "colour", "cycling");
               else if (a->colourset)
               {
                  if (!(a->r % 17) && !(a->g % 17) && !(a->b % 17))
                     jo_stringf (j, "colour", "%X%X%X", a->r / 17, a->g / 17, a->b / 17);
                  else
                     jo_stringf (j, "colour", "%02X%02X%02X", a->r, a->g, a->b);
               }
               if (a->data)
                  jo_string (j, "data", (char *) a->data);
               revk_info ("start", &j);
            }
            const char *e = a->app (a);
            if (e)
               appzap (a);
            a->cycle++;
            if (a->stop && !--a->stop)
               appzap (a);
            else if (!a->stop && a->limit && a->cycle >= a->limit)
               a->stop = a->fade;       // Tell app to stop
            if (!a->app)
            {                   // Done
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
      for (unsigned int i = 0; i < leds; i++)
      {
         led_strip_set_pixel (strip, i,
                              gamma8[(unsigned int) maxr * ledr[i] / 255],
                              gamma8[(unsigned int) maxg * ledg[i] / 255], gamma8[(unsigned int) maxb * ledb[i] / 255]);
      }
      if (idle < 2)
      {
         idle++;
         REVK_ERR_CHECK (led_strip_refresh (strip));
      }
   }
}

void
revk_web_extra (httpd_req_t * req)
{
   httpd_resp_sendstr_chunk (req, "<tr><td>LEDs</td><td><input size=3 name=leds value='");
   char temp[20];
   sprintf (temp, "%d", leds);
   httpd_resp_sendstr_chunk (req, temp);
   httpd_resp_sendstr_chunk (req, "'></td></tr>");
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
            app_callback (0, prefixcommand, NULL, app, j);
         }
      }
   }

   httpd_resp_sendstr_chunk (req, "<h1>LED controller: ");
   httpd_resp_sendstr_chunk (req, hostname);
   httpd_resp_sendstr_chunk (req, "</h1><ul>");
   xSemaphoreTake (app_mutex, portMAX_DELAY);
   for (unsigned int i = 0; i < MAXAPPS; i++)
   {
      app_t *a = &active[i];
      if (a->app && *a->name && !a->stop)
      {
         httpd_resp_sendstr_chunk (req, "<li>");
         httpd_resp_sendstr_chunk (req, a->name);
         httpd_resp_sendstr_chunk (req, "</li>");
      }
   }
   xSemaphoreGive (app_mutex);
   httpd_resp_sendstr_chunk (req,
                             "</ul><fieldset><legend>Effect</legend><form method=get><p><input name='colour' placeholder='RGB' size=6></p><p><input name='data' placeholder='Data'></p><p>");
   void button (const char *tag)
   {
      httpd_resp_sendstr_chunk (req, "<input type=submit name='app' value='");
      httpd_resp_sendstr_chunk (req, tag);
      httpd_resp_sendstr_chunk (req, "'/>");
   }
#define a(x,d) if(strcmp(#x,"idle"))button(#x);
#define t(x,d)
#include "apps.h"
   httpd_resp_sendstr_chunk (req, "</p></form></fieldset>");
   return revk_web_foot (req, 0, webcontrol >= 2 ? 1 : 0);
}

void
app_main ()
{
#ifdef  CONFIG_IDF_TARGET_ESP32S3
   {                            // All unused input pins pull down
      gpio_config_t c = {.pull_down_en = 1,.mode = GPIO_MODE_DISABLE };
      for (uint8_t p = 0; p <= 48; p++)
         if (gpio_ok (p) & 2)
            c.pin_bit_mask |= (1LL << p);
      gpio_config (&c);
   }
#endif
   app_mutex = xSemaphoreCreateBinary ();
   xSemaphoreGive (app_mutex);
   revk_boot (&app_callback);
#ifndef CONFIG_REVK_BLINK
#define led(n,a,d)      revk_register(#n,a,sizeof(*n),&n,"- "#d,SETTING_SET|SETTING_BITFIELD|SETTING_FIX);
#else
#define led(n,a,d)
#endif
#define io(n,d)           revk_register(#n,0,sizeof(n),&n,"- "#d,SETTING_SET|SETTING_BITFIELD|SETTING_FIX);
#define b(n) revk_register(#n,0,sizeof(n),&n,NULL,SETTING_BOOLEAN);
#define u32(n,d) revk_register(#n,0,sizeof(n),&n,#d,0);
#define u32l(n,d) revk_register(#n,0,sizeof(n),&n,#d,SETTING_LIVE);
#define s8(n,d) revk_register(#n,0,sizeof(n),&n,#d,SETTING_SIGNED);
#define s8n(n,d) revk_register(#n,d,sizeof(*n),&n,NULL,SETTING_SIGNED);
#define u8(n,d) revk_register(#n,0,sizeof(n),&n,#d,0);
#define u8r(n,d) revk_register(#n,0,sizeof(n),&n,#d,0); revk_register("ring"#n,0,sizeof(ring##n),&ring##n,#d,0);
#define u16(n,d) revk_register(#n,0,sizeof(n),&n,#d,0);
#define u16r(n,d) revk_register(#n,0,sizeof(n),&n,#d,0); revk_register("ring"#n,0,sizeof(ring##n),&ring##n,#d,0);
#define s8r(n,d) revk_register(#n,0,sizeof(n),&n,#d,0); revk_register("ring"#n,0,sizeof(ring##n),&ring##n,#d,SETTING_SIGNED);
#define s16r(n,d) revk_register(#n,0,sizeof(n),&n,#d,0); revk_register("ring"#n,0,sizeof(ring##n),&ring##n,#d,SETTING_SIGNED);
#define u8l(n,d) revk_register(#n,0,sizeof(n),&n,#d,SETTING_LIVE);
#define s(n,d) revk_register(#n,0,0,&n,#d,0);
   settings                     //
      params                    //
#undef io
#undef u32
#undef u32l
#undef s8
#undef s8n
#undef u8
#undef u8r
#undef u16
#undef u16r
#undef s8r
#undef s16r
#undef u8l
#undef b
#undef s
#ifdef	CONFIG_REVK_MATTER
   extern void matter_main (void);
   matter_main ();
#endif
   revk_start ();
   if (dark)
      revk_blink (0, 0, "K");
   if (webcontrol)
   {
      // Web interface
      httpd_config_t config = HTTPD_DEFAULT_CONFIG ();
      // When updating the code below, make sure this is enough
      // Note that we're also 4 adding revk's web config handlers
      config.max_uri_handlers = 8;
      if (!httpd_start (&webserver, &config))
      {
         if (webcontrol >= 2)
            revk_web_settings_add (webserver);
         register_get_uri ("/", web_root);
      }
   }
   revk_task ("LED", led_task, NULL, 4);
}
