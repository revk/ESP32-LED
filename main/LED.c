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
	u8(leds,80)	\
	u8(ledmax,50)	\
	u8(ledtop,36)	\
	s8n(gatechevron,3)	\
	u32(gateopen,10)	\
	u32(gatespin,2000)	\
	u32(clockfade,1000)	\
	b(reverse)		\

#define u32(n,d)        uint32_t n;
#define s8(n,d) int8_t n;
#define s8n(n,d) int8_t n[d];
#define u8(n,d) uint8_t n;
#define b(n) uint8_t n;
#define s(n) char * n;
#define io(n,d)           uint8_t n;
settings
#undef io
#undef u32
#undef s8
#undef s8n
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
   if (!strcmp(suffix, "close"))
   {                            // Close the gate
      gatedial = 0;
      return "";
   }

   return NULL;
}

void led_task(void *x)
{
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

   {                            // Startup
      int dir = reverse ? -1 : 1;
      strip->set_pixel(strip, ledtop % leds, ledmax, ledmax, ledmax);
      strip->set_pixel(strip, (ledtop + leds + dir * leds / 4) % leds, ledmax, 0, 0);
      strip->set_pixel(strip, (ledtop + leds + dir * 2 * leds / 4) % leds, 0, ledmax, 0);
      strip->set_pixel(strip, (ledtop + leds + dir * 3 * leds / 4) % leds, 0, 0, ledmax);
      ESP_ERROR_CHECK(strip->refresh(strip, 100));
      sleep(5);
   }

   while (1)
   {                            // Main loop
      if (gatedial)
      {                         // Do gate dialling sequence (note leds should be for full ring even if there are actually fewer, and ledtop set accordingly)
         uint8_t led1[leds];
         uint8_t led2[leds];
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
            if (reverse)
            {
               dir = -dir;
               chevron = -chevron;
            }
            int p = ledtop;
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
               usleep(gatespin * 1000 / leds);
            } while (p != ledtop);
            for (fade = 0; fade < 255; fade += 10)
            {
               strip->set_pixel(strip, chevron, fade * ledmax / 255, fade * ledmax / 255, 0);
               ESP_ERROR_CHECK(strip->refresh(strip, 100));
               usleep(2000);
            }
            chevron = (ledtop + chevron + leds) % leds;
            if (chevron >= 0)
               led1[chevron] = 1;
         }

         // 7 x Run a blue light around and clock each chevron yellow
         memset(led1, 0, leds); // Use led1 as flags
         for (int c = 2; c >= 0; c--)
            if (gatechevron[c])
            {
               spin(1, gatechevron[c]);
               spin(-1, -gatechevron[c]);
            }
         spin(1, 0);
         usleep(500000);

         // Fade up white quickly
         memset(led1, 0, leds);
         memset(led2, ledmax * 2, leds);
         fader(5);
         memset(led2, ledmax, leds);
         fader(1);

         // Fade from solid white to 50% white with random white
         time_t done = time(0) + gateopen;
         while (gatedial && (!gateopen || done > time(0)))
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
         gatedial = 0;
      }

      if (clockfade)
      {                         // Clock
         while (!gatedial)
         {                      // Clock runs when not dialling request
            struct tm t;
            struct timeval tv;
            gettimeofday(&tv, NULL);
            localtime_r(&tv.tv_sec, &t);
            uint32_t usecs = (((t.tm_hour % 12) * 60 + t.tm_min) * 60 + t.tm_sec) * 1000 + tv.tv_usec / 1000;
            for (int pos = 0; pos < leds; pos++)
            {
               int clock = (ledtop + leds + (reverse ? -pos : pos)) % leds;
               int col(int scale) {
                  scale *= 1000;        // ms
                  uint32_t u = usecs % scale;   // What ms in the clock face we are on
                  int hand = leds * u / scale;  // What hand position we are on
                  int perhand = scale / leds;   // How many ms per hand to hand step
                  int fade = (!clockfade || clockfade > perhand ? perhand : clockfade);
                  int sub = u - hand * perhand; // Where we are in the hand to hand steps
                  if (sub > perhand - fade)
                  {             // Last fade period (ms)
                     if (hand == clock)
                        return (perhand - sub) * ledmax / fade; // Fade out in last period
                     if ((hand + 1) % leds == clock)
                        return ledmax - (perhand - sub) * ledmax / fade;        // Fade in next in last period
                  }
                  if (hand == clock)
                     return ledmax;
                  return 0;
               }
               strip->set_pixel(strip, pos, col(12 * 60 * 60), col(60 * 60), col(60));
            }
            ESP_ERROR_CHECK(strip->refresh(strip, 100));
            usleep(10000);
         }
      }
      usleep(10000);
   }
}

void app_main()
{
   revk_boot(&app_callback);
#define io(n,d)           revk_register(#n,0,sizeof(n),&n,"- "#d,SETTING_SET|SETTING_BITFIELD);
#define b(n) revk_register(#n,0,sizeof(n),&n,NULL,SETTING_BOOLEAN);
#define u32(n,d) revk_register(#n,0,sizeof(n),&n,#d,0);
#define s8(n,d) revk_register(#n,0,sizeof(n),&n,#d,SETTING_SIGNED);
#define s8n(n,d) revk_register(#n,d,sizeof(*n),&n,NULL,SETTING_SIGNED);
#define u8(n,d) revk_register(#n,0,sizeof(n),&n,#d,0);
#define s(n) revk_register(#n,0,0,&n,NULL,0);
   settings
#undef io
#undef u32
#undef s8
#undef s8n
#undef u8
#undef b
#undef s
       revk_start();

   revk_task("LED", led_task, NULL);
}
