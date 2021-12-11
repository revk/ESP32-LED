/* Gate app */
/* Copyright ©2019 - 21 Adrian Kennard, Andrews & Arnold Ltd.See LICENCE file for details .GPL 3.0 */

static const char TAG[] = "Gate";

#include "revk.h"
#include "esp_sleep.h"
#include "esp_task_wdt.h"
#include "vl53l0x.h"
#include "vl53l1x.h"
#include <driver/gpio.h>
#include <driver/uart.h>
#include "driver/adc.h"
#include "driver/rmt.h"
#include "esp_adc_cal.h"
#include "led_strip.h"

#define	settings		\
	u8(ledgpio,16)	\
	u8(ledchan,0)	\
	u8(leds,72)	\
	u8(ledtop,36)	\
	u8(ledspace,8)	\

#define u32(n,d)        uint32_t n;
#define s8(n,d) int8_t n;
#define u8(n,d) uint8_t n;
#define b(n) uint8_t n;
#define s(n) char * n;
#define io(n,d)           uint8_t n;
settings
#undef io
#undef u32
#undef s8
#undef u8
#undef b
#undef s
const char *app_callback(int client, const char *prefix, const char *target, const char *suffix, jo_t j)
{
   if (client || !prefix || target || strcmp(prefix, prefixcommand) || !suffix)
      return NULL;
   /* Not for us or not a command from main MQTT */
   char value[100];
   int len = 0;
   if (j)
   {
      len = jo_strncpy(j, value, sizeof(value));
      if (len < 0)
         return "Expecting JSON string";
      if (len > sizeof(value))
         return "Too long";
   }
   return NULL;
}

void app_main()
{
   revk_boot(&app_callback);
#define io(n,d)           revk_register(#n,0,sizeof(n),&n,"- "#d,SETTING_SET|SETTING_BITFIELD);
#define b(n) revk_register(#n,0,sizeof(n),&n,NULL,SETTING_BOOLEAN);
#define u32(n,d) revk_register(#n,0,sizeof(n),&n,#d,0);
#define s8(n,d) revk_register(#n,0,sizeof(n),&n,#d,SETTING_SIGNED);
#define u8(n,d) revk_register(#n,0,sizeof(n),&n,#d,0);
#define s(n) revk_register(#n,0,0,&n,NULL,0);
   settings
#undef io
#undef u32
#undef s8
#undef u8
#undef b
#undef s
       revk_start();

   led_strip_t *strip = NULL;
   if (leds)
   {
      /* RMT control */
      rmt_config_t config = RMT_DEFAULT_CONFIG_TX(ledgpio, ledchan);
      config.clk_div = 2;
      REVK_ERR_CHECK(rmt_config(&config));
      REVK_ERR_CHECK(rmt_driver_install(config.channel, 0, 0));
      led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(leds, (led_strip_dev_t) config.channel);
      strip = led_strip_new_rmt_ws2812(&strip_config);
      if (!strip)
         ESP_LOGE(TAG, "install WS2812 driver failed");
   }
   if (!strip)
      return;                   // Uh?
   REVK_ERR_CHECK(strip->clear(strip, 100));
   while (1)
   {
	   // Wait for trigger
	   // 7 x Run a blue light around and clock each chevron yellow (ledtop/ledspace)
	   // Fad up white quickly
	   // Fade from solid white to 50% white with random white
	   // Hold
	   // Fade out quickly

      static uint8_t t = 0;
      for (int p = 0; p < leds; p++)
      {
         t+=10;
         ESP_ERROR_CHECK(strip->set_pixel(strip, p, t, t + 85, t + 85*2));
      }
      ESP_ERROR_CHECK(strip->refresh(strip, 100));
      usleep(100000);
   }
}
