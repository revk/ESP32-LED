// Application structure

#include "revk.h"

#define	params		\
	u16r(s,start,)	\
	u16r(l,len,)	\
	s16r(t,top,)	\
	u8(S,speed,)	\
	u8(f,fade,)	\
	u8(b,bright,)	\
	s8(h,height,)	\
	u32(d,delay,)	\
	u32(T,limit,)	\

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

#define	MAXAPPS	50

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
#define u8(s,n,d)		uint8_t n;
#define u8r(s,n,d)	uint8_t n;
#define u16(s,n,d)	uint16_t n;
#define u16r(s,n,d)	uint16_t n;
#define s8(s,n,d)		int8_t n;
#define s8r(s,n,d)	int8_t n;
#define s16r(s,n,d)	int16_t n;
#define u32(s,n,d)	uint32_t n;
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
