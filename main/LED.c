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

#define a(app)	extern const char* app(app_t*);
#include "apps.h"

struct applist_s
{
   const char *appname;
   app_f *app;
} applist[] = {
#define a(app)	{#app,&app},
#include "apps.h"
};

uint8_t *ledr = NULL;
uint8_t *ledg = NULL;
uint8_t *ledb = NULL;

#define u32(n,d)        uint32_t n;
#define u32l(n,d)        uint32_t n;
#define s8(n,d) int8_t n;
#define s8n(n,d) int8_t n[d];
#define u8(n,d) uint8_t n;
#define u8l(n,d) uint8_t n;
#define b(n) uint8_t n;
#define s(n) char * n;
#define io(n,d)           uint8_t n;
settings
#undef io
#undef u32
#undef u32l
#undef s8
#undef s8n
#undef u8
#undef u8l
#undef b
#undef s
   uint8_t gatedial = 0;

const char *
app_callback (int client, const char *prefix, const char *target, const char *suffix, jo_t j)
{
   if (client || !prefix || target || strcmp (prefix, prefixcommand) || !suffix)
      return NULL;              // Not for us or not a command from main MQTT
   // TODO command to set active apps

   return NULL;
}

void
led_task (void *x)
{
   ESP_LOGI (TAG, "Started using GPIO %d%s", ledgpio & 63, ledgpio & 64 ? " (inverted)" : "");

   led_strip_handle_t strip = NULL;

   led_strip_config_t strip_config = {
      .strip_gpio_num = (ledgpio & 63),
      .max_leds = leds,         // The number of LEDs in the strip,
      .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
      .led_model = LED_MODEL_WS2812,    // LED strip model
      .flags.invert_out = ((ledgpio & 64) ? 1 : 0),     // whether to invert the output signal (useful when your hardware has a level inverter)
   };

   led_strip_rmt_config_t rmt_config = {
      .clk_src = RMT_CLK_SRC_DEFAULT,   // different clock source can lead to different power consumption
      .resolution_hz = 10 * 1000 * 1000,        // 10MHz
      .flags.with_dma = false,  // whether to enable the DMA feature
   };
   REVK_ERR_CHECK (led_strip_new_rmt_device (&strip_config, &rmt_config, &strip));

   REVK_ERR_CHECK (led_strip_clear (strip));

   ledr = calloc (leds, sizeof (*ledr));
   ledg = calloc (leds, sizeof (*ledg));
   ledb = calloc (leds, sizeof (*ledb));

#define	MAXAPPS 10
   app_t active[MAXAPPS] = { 0 };
   active[0].app = spin;        // Dummy start
   active[0].colour.cycle=1;

   while (1)
   {                            // Main loop
      usleep (100000LL - (esp_timer_get_time () % 100000LL));
      for (unsigned int i = 0; i < MAXAPPS; i++)
         if (active[i].app)
         {
		 if(active[i].colour.cycle)
		 { // Cycle the colour
			 active[i].colour.r=active[i].cycle;
			 active[i].colour.g=active[i].cycle+85;
			 active[i].colour.b=active[i].cycle+170;
			 // TODO proper cycle
		 }
            const char *e = active[i].app (&active[i]);
            if (e)
            {
               active[i].app = NULL;    // Done
               if (*e)
               {
                  ESP_LOGI (TAG, "App failed %s", e);   // TODO report via MQTT
               }
            }
            active[i].cycle++;
	    if(active[i].time&&active[i].cycle>=active[i].time)active[i].app = NULL;    // Complete
         }

      for (unsigned int i = 0; i < leds; i++)
      {
         led_strip_set_pixel (strip, i, (unsigned int) bright * ledr[i] / 255, (unsigned int) bright * ledg[i] / 255,
                              (unsigned int) bright * ledb[i] / 255);
      }
      REVK_ERR_CHECK (led_strip_refresh (strip));
   }
}

void
app_main ()
{
   revk_boot (&app_callback);
#define io(n,d)           revk_register(#n,0,sizeof(n),&n,"- "#d,SETTING_SET|SETTING_BITFIELD);
#define b(n) revk_register(#n,0,sizeof(n),&n,NULL,SETTING_BOOLEAN);
#define u32(n,d) revk_register(#n,0,sizeof(n),&n,#d,0);
#define u32l(n,d) revk_register(#n,0,sizeof(n),&n,#d,SETTING_LIVE);
#define s8(n,d) revk_register(#n,0,sizeof(n),&n,#d,SETTING_SIGNED);
#define s8n(n,d) revk_register(#n,d,sizeof(*n),&n,NULL,SETTING_SIGNED);
#define u8(n,d) revk_register(#n,0,sizeof(n),&n,#d,0);
#define u8l(n,d) revk_register(#n,0,sizeof(n),&n,#d,SETTING_LIVE);
#define s(n) revk_register(#n,0,0,&n,NULL,0);
   settings
#undef io
#undef u32
#undef u32l
#undef s8
#undef s8n
#undef u8
#undef u8l
#undef b
#undef s
      revk_start ();

   revk_task ("LED", led_task, NULL);
}
