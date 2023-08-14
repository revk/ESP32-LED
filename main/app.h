// Application structure

#include "revk.h"

#ifdef	CONFIG_IDF_TARGET_ESP32
#define	gpio	\
	io(ledgpio,22)	\
	led(blink,3,-20 -8 -21)\

#endif

#ifdef	CONFIG_IDF_TARGET_ESP32S3
#define	gpio	\
	io(ledgpio,8)	\
	led(blink,3,-10 -9 -11)\

#endif

#define settings	\
	u8(cps,10)	\
        u8(maxr,255)	\
        u8(maxg,255)	\
        u8(maxb,255)	\
        u16(leds,12)	\
	s(app,pulse)	\
	gpio		\

#define	params		\
	u16r(start,)	\
	u16r(len,)	\
	s16r(top,)	\
	u8(speed,)	\
	u8(fade,)	\
	s8(height,)	\
	u32(delay,)	\
	u32(limit,)	\

#define	colours		\
	c(000,black)	\
	c(F00,red)	\
	c(FF0,yellow)	\
	c(0F0,green)	\
	c(0FF,cyan)	\
	c(00F,blue)	\
	c(F0F,magenta)	\
	c(FFF,white)	\
	c(F80,orange)	\
	c(F88,pink)	\

#define	MAXAPPS	10

#define u32(n,d)	extern uint32_t n;
#define u32l(n,d)	extern uint32_t n;
#define s8(n,d)		extern int8_t n;
#define s8n(n,d)	extern int8_t n[d];
#define u8(n,d)		extern uint8_t n;
#define u8r(n,d)	extern uint8_t n,ring##n;
#define u16(n,d)	extern uint16_t n;
#define u16r(n,d)	extern uint16_t n,ring##n;
#define s16r(n,d)	extern int16_t n,ring##n;
#define s8r(n,d)	extern int8_t n,ring##n;
#define u8l(n,d)	extern uint8_t n;
#define b(n)		extern uint8_t n;
#define s(n,d)		extern char * n;
#define io(n,d)         extern uint8_t n;
#define led(n,a,d)      extern uint8_t n[a];
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
typedef struct app_s app_t;
typedef const char *app_f (app_t *);    // Return NULL normally, "" for normal end, other string for error

extern uint8_t *ledr;           // The current LED, set by the apps
extern uint8_t *ledg;           // The current LED, set by the apps
extern uint8_t *ledb;           // The current LED, set by the apps

extern const uint8_t cos8[256];
extern const uint8_t wheel[256];
extern const uint8_t zig[256];

static inline void
clear (uint16_t start, uint16_t len)
{
   if (!start || start > leds || start + len - 1 > leds)
      return;
   memset (ledr + start - 1, 0, len);
   memset (ledg + start - 1, 0, len);
   memset (ledb + start - 1, 0, len);
}

static inline uint8_t
getr (uint16_t index)
{
   if (!index || index > leds)
      return 0;
   return ledr[index - 1];
}

static inline uint8_t
getg (uint16_t index)
{
   if (!index || index > leds)
      return 0;
   return ledg[index - 1];
}

static inline uint8_t
getb (uint16_t index)
{
   if (!index || index > leds)
      return 0;
   return ledb[index - 1];
}

static inline void
setr (uint16_t index, uint8_t v)
{
   if (!index || index > leds)
      return;
   ledr[index - 1] = v;
}

static inline void
setg (uint16_t index, uint8_t v)
{
   if (!index || index > leds)
      return;
   ledg[index - 1] = v;
}

static inline void
setb (uint16_t index, uint8_t v)
{
   if (!index || index > leds)
      return;
   ledb[index - 1] = v;
}

static inline void
setrgb (uint16_t index, uint8_t r, uint8_t g, uint8_t b)
{
   if (!index || index > leds)
      return;
   ledr[index - 1] = r;
   ledg[index - 1] = g;
   ledb[index - 1] = b;
}

static inline void
setrgbl (uint16_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t l)
{
   if (!index || index > leds)
      return;
   ledr[index - 1] = ((int) l * r + (int) (255 - l) * ledr[index - 1]) / 255;
   ledg[index - 1] = ((int) l * g + (int) (255 - l) * ledg[index - 1]) / 255;
   ledb[index - 1] = ((int) l * b + (int) (255 - l) * ledb[index - 1]) / 255;
}

#define	setl(i,a,l)		setrgbl(i,a->r,a->g,a->b,l)

struct app_s
{                               // Note LED number start from 1 with 0 meaning not set, stage 0 means app should sanity check parameters
   const char *name;
   app_f *app;
#define u8(n,d)		uint8_t n;
#define u8r(n,d)	uint8_t n;
#define u16(n,d)	uint16_t n;
#define u16r(n,d)	uint16_t n;
#define s8(n,d)		int8_t n;
#define s8r(n,d)	int8_t n;
#define s16r(n,d)	int16_t n;
#define u32(n,d)	uint32_t n;
     params
#undef	u8
#undef	u8r
#undef	u16
#undef	u16r
#undef	s8
#undef	s8r
#undef	s16r
#undef	u32
      // Common settings
     uint8_t r, g, b;           // Colour
   uint8_t stop;                // If set this is a count down to stopping, typically to fade out
   uint8_t colourset:1;         // Colour is set
   uint8_t rainbow:1;           // Colour should be cycled
   uint8_t cycling:1;           // Colour should be cycled - more overlap than rainbow
   // Scratchpad for apps
   uint32_t cycle;              // This is set by caller - counts the cycle since started
   uint32_t stage;              // The stage of a sequential display
   uint32_t step;               // Steps in the stage
   void *data;                  // Malloc'd data area
};
