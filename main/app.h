// Application structure

#include "revk.h"

#define settings	\
	u8(cps,10)	\
        io(ledgpio,22)  \
        u8(bright,63)   \
        u8(leds,12)     \
	s(app,spin)	\

#define	params		\
	u8r(start,)	\
	u8r(len,)	\
	u8r(top,)	\
	u8(speed,)	\
	u32(delay,)	\
	u32(limit,)	\

#define	MAXAPPS	10

#define u32(n,d)	extern uint32_t n;
#define u32l(n,d)	extern uint32_t n;
#define s8(n,d)		extern int8_t n;
#define s8n(n,d)	extern int8_t n[d];
#define u8(n,d)		extern uint8_t n;
#define u8r(n,d)	extern uint8_t n,ring##n;
#define u8l(n,d)	extern uint8_t n;
#define b(n)		extern uint8_t n;
#define s(n,d)		extern char * n;
#define io(n,d)         extern uint8_t n;
settings                        //
   params                       //
#undef io
#undef u32
#undef u32l
#undef s8
#undef s8n
#undef u8
#undef u8r
#undef u8l
#undef b
#undef s
typedef struct app_s app_t;
typedef const char *app_f (app_t *);    // Return NULL normally, "" for normal end, other string for error

extern uint8_t *ledr;           // The current LED, set by the apps
extern uint8_t *ledg;           // The current LED, set by the apps
extern uint8_t *ledb;           // The current LED, set by the apps

extern const uint8_t cos256[256];

static inline void
clear (uint8_t start, uint8_t len)
{
   if (!start || start > leds || start + len - 1 > leds)
      return;
   memset (ledr + start - 1, 0, len);
   memset (ledg + start - 1, 0, len);
   memset (ledb + start - 1, 0, len);
}

static inline void
setrgb (uint8_t index, uint8_t r, uint8_t g, uint8_t b)
{
   if (!index || index > leds)
      return;
   ledr[index - 1] = r;
   ledg[index - 1] = g;
   ledb[index - 1] = b;
}

#define	setrgbl(i,r,g,b,l)	setrgb(i,(int)(l)*(r)/255,(int)(l)*(g)/255,(int)(l)*(b)/255)
#define	setl(i,a,l)		setrgbl(i,a->r,a->g,a->b,l)

struct app_s
{                               // Note LED number start from 1 with 0 meaning not set, stage 0 means app should sanity check parameters
   const char *name;
   app_f *app;
#define u8(n,d)		uint8_t n;
#define u8r(n,d)	uint8_t n;
#define u32(n,d)	uint32_t n;
     params
#undef	u8
#undef	u8r
#undef	u32
      // Common settings
     uint8_t r, g, b;		// Colour
   uint8_t colourset:1;         // Colour is set
   uint8_t rainbow:1;           // Colour should be cycled
   uint8_t rainbow2:1;          // Colour should be cycled
   // Scratchpad for apps
   uint32_t cycle;              // This is set by caller - counts the cycle since started
   uint8_t stage;               // The stage of a sequential display
   uint8_t step;                // Steps in the stage
};
