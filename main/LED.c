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

#define a(app)	extern void app(app_t*);
#include "apps.h"

struct applist_s
{
	const char *appname;
	app_f*app;
} applist[]={
#define a(app)	{#app,&app},
#include "apps.h"
};

#define	settings		\
	io(ledgpio,22)	\
	u8(bright,63)	\
	u8(leds,1)	\

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



   return NULL;
}

void
led_task (void *x)
{
   ESP_LOGI (TAG, "Started using GPIO %d%s", ledgpio & 63, ledgpio & 64 ? " (inverted)" : "");

   led_strip_handle_t led=NULL;

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
   REVK_ERR_CHECK (led_strip_new_rmt_device (&strip_config, &rmt_config, &led));

   REVK_ERR_CHECK (led_strip_clear (led));

   led_strip_set_pixel(led,0,bright,0,0);
   led_strip_set_pixel(led,1,0,bright,0);
   led_strip_set_pixel(led,2,0,0,bright);

   while (1)
   {                            // Main loop
      sleep (1);
      REVK_ERR_CHECK (led_strip_refresh (led));
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
