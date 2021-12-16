/* LED app */
/* Copyright ©2019 - 21 Adrian Kennard, Andrews & Arnold Ltd.See LICENCE file for details .GPL 3.0 */

static const char TAG[] = "LED";

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
	u8(ledmax,50)	\
	s8(gatetop,36)	\
	s8(gatechevron1,8)	\
	s8(gatechevron2,16)	\
	s8(gatechevron3,23)	\
	u32(gateopen,100)	\
	s8(clocktop,-1)		\
	u8(clockfade,10)	\

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
    uint8_t gatedial = 0;

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
   if (!strcmp(suffix, "dial"))
   {                            // Dial the gate
      gatedial = 1;
      return "";
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
   ESP_ERROR_CHECK(strip->refresh(strip, 100));

   if (gatetop >= 0)
   {                            // Start gate
      uint8_t led1[leds];
      uint8_t led2[leds];
      while (1)
      {
         int fade,
          pos;
         void fader(int step) { // Fade led1 to led2
            for (fade = 0; fade < 255; fade += step)
            {
               for (pos = 0; pos < leds; pos++)
               {
                  uint8_t white = (fade * led2[pos] + (255 - fade) * led1[pos]) / 255;
                  strip->set_pixel(strip, pos, white, white, white);
               }
               ESP_ERROR_CHECK(strip->refresh(strip, 100));
               usleep(5000);
            }
            memcpy(led1, led2, leds);
         }
         void spin(int dir, int chevron) {
            int p = gatetop;
            do
            {
               p += dir;
               if (p == -1)
                  p = leds - 1;
               else if (p == leds)
                  p = 0;
               for (pos = 0; pos < leds; pos++)
                  strip->set_pixel(strip, pos, led1[pos] ? ledmax : 0, led1[pos] ? ledmax : 0, pos == p ? ledmax : 0);
               ESP_ERROR_CHECK(strip->refresh(strip, 100));
               usleep(10000);
            } while (p != gatetop);
            for (fade = 0; fade < 255; fade += 10)
            {
               strip->set_pixel(strip, chevron, fade * ledmax / 255, fade * ledmax / 255, 0);
               ESP_ERROR_CHECK(strip->refresh(strip, 100));
               usleep(2000);
            }
            if (chevron >= 0 && chevron < leds)
               led1[chevron] = 1;
         }

         // Wait for trigger
         while (!gatedial)
            usleep(100000);
         gatedial = 0;

         // 7 x Run a blue light around and clock each chevron yellow (gatetop/ledspace)
         memset(led1, 0, leds); // Use led1 as flags
         if (gatechevron3)
         {
            spin(1, gatetop + gatechevron3);
            spin(-1, gatetop - gatechevron3);
         }
         if (gatechevron2)
         {
            spin(1, gatetop + gatechevron2);
            spin(-1, gatetop - gatechevron2);
         }
         if (gatechevron1)
         {
            spin(1, gatetop + gatechevron1);
            spin(-1, gatetop - gatechevron1);
         }
         spin(1, gatetop);
         usleep(500000);

         // Fade up white quickly
         memset(led1, 0, leds);
         memset(led2, ledmax * 2, leds);
         fader(5);
         memset(led2, ledmax, leds);
         fader(1);

         // Fade from solid white to 50% white with random white
         int sparkle = gateopen;
         while (sparkle-- && !gatedial)
         {
            esp_fill_random(led2, leds);
            for (pos = 0; pos < leds; pos++)
               led2[pos] = ((int) led2[pos] * ledmax / 255);
            fader(5);
         }
         // Fade out
         memset(led2, 0, leds);
         fader(5);

         sleep(1);
      }
   }

   if (clocktop >= 0)
   {                            // Simple clock
      strip->set_pixel(strip, clocktop, ledmax, ledmax, ledmax);
      ESP_ERROR_CHECK(strip->refresh(strip, 100));
      sleep(5);
      while (1)
      {
         struct tm t;
         struct timeval tv;
         gettimeofday(&tv, NULL);
         localtime_r(&tv.tv_sec, &t);
         for (int pos = 0; pos < leds; pos++)
         {
            int clock = (pos + clocktop) % leds;
            int col(int v, int u) {
               int hand = leds * v / u;
               int sub = ledmax * clockfade * (leds * v % u) / u - ledmax * (clockfade - 1);
               if (sub < 0)
                  sub = 0;
               if (hand == clock)
                  return ledmax - sub;
               hand = (hand + 1) % leds;
               if (hand == clock)
                  return sub;
               return 0;
            }
            strip->set_pixel(strip, pos, col((t.tm_hour % 12) * 60 + t.tm_min, 12 * 60), col(t.tm_min * 60 + t.tm_sec, 60 * 60), col(t.tm_sec * 1000 + tv.tv_usec / 1000, 60000));
         }
         ESP_ERROR_CHECK(strip->refresh(strip, 100));
         usleep(10000);
      }
   }
}
