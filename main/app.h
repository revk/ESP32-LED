// Application structure

#include "revk.h"

#define	params		\
	u16r(s,start,)	\
	u16r(l,len,)	\
	s16r(t,top,)	\
	u8(b,bright,)	\
	s8(h,height,)	\
	u8d(f,fadein,)	\
	u8d(f,fadeout,)	\
	u32d(S,speed,)	\
	u32d(d,delay,)	\
	u32d(T,limit,)	\

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

//#define	AUDIOSAMPLES	2048
//#define	AUDIORATE	48000L	// Hz (full rate
#define	AUDIOSAMPLES	1024
#define	AUDIORATE	36000L	// Hz (TDK is OK with this)
#define	AUDIOMIN	300L	// Hz
#define	AUDIOMAX	4000L	// Hz
#define	AUDIOBANDS	24
#define	AUDIOSTEP	((AUDIOMAX-AUDIOMIN)/AUDIOBANDS)	// Hz steps
#define	AUDIOGAINMIN	1
#define	AUDIOGAINMAX	5
extern float audioband[AUDIOBANDS];
extern float audiomag;

typedef struct app_s app_t;
typedef const char *app_f (app_t *);    // Return NULL normally, "" for normal end, other string for error

struct app_s
{                               // Note LED number start from 1 with 0 meaning not set, stage 0 means app should sanity check parameters
   const char *name;
   app_f *app;
#define u8(s,n,d)		uint8_t n;
#define u8d(s,n,d)		uint8_t n;
#define u8r(s,n,d)	uint8_t n;
#define u16(s,n,d)	uint16_t n;
#define u16r(s,n,d)	uint16_t n;
#define s8(s,n,d)		int8_t n;
#define s8r(s,n,d)	int8_t n;
#define s16r(s,n,d)	int16_t n;
#define u32(s,n,d)	uint32_t n;
#define u32d(s,n,d)	uint32_t n;
     params
#undef	u8
#undef	u8d
#undef	u8r
#undef	u16
#undef	u16r
#undef	s8
#undef	s8r
#undef	s16r
#undef	u32
#undef	u32d
      // Common settings
     uint8_t preset;            // If this is a preset
   uint8_t r,
     g,
     b,
     w;                         // Colour
   uint8_t stop;                // If set this is a count down to stopping
   uint8_t fader;               // Effective brightness (set to bright unless fading in or out)
   uint8_t colourset:1;         // Colour is set
   uint8_t rainbow:1;           // Colour should be rainbow along strip
   uint8_t wheel:1;             // Colour should be cycled over time
   uint8_t cycling:1;           // Colour should be cycled over time (more overlap)
   // Scratchpad for apps
   uint32_t cycle;              // This is set by caller - counts the cycle since started
   uint32_t stage;              // The stage of a sequential display
   uint32_t step;               // Steps in the stage
   void *data;                  // Malloc'd data area
};

extern int ledmax;		// Total LEDs

extern uint8_t *ledr;           // The current LED, set by the apps
extern uint8_t *ledg;           // The current LED, set by the apps
extern uint8_t *ledb;           // The current LED, set by the apps
extern uint8_t *ledw;           // The current LED, set by the apps

extern const uint8_t cos8[256];
extern const uint8_t wheel[256];
extern const uint8_t zig[256];

static inline void
clear (uint16_t start, uint16_t len)
{
   if (!start || start > ledmax || start + len - 1 > ledmax)
      return;
   memset (ledr + start - 1, 0, len);
   memset (ledg + start - 1, 0, len);
   memset (ledb + start - 1, 0, len);
   if (ledw)
      memset (ledw + start - 1, 0, len);
}

static inline uint8_t
getR (uint16_t index)
{
   if (!index || index > ledmax)
      return 0;
   return ledr[index - 1];
}

static inline uint8_t
getG (uint16_t index)
{
   if (!index || index > ledmax)
      return 0;
   return ledg[index - 1];
}

static inline uint8_t
getB (uint16_t index)
{
   if (!index || index > ledmax)
      return 0;
   return ledb[index - 1];
}

static inline uint8_t
getW (uint16_t index)
{
   if (!ledw || !index || index > ledmax)
      return 0;
   return ledw[index - 1];
}

static inline void
setR (uint16_t index, uint8_t v)
{
   if (!index || index > ledmax)
      return;
   ledr[index - 1] = v;
}

static inline void
setG (uint16_t index, uint8_t v)
{
   if (!index || index > ledmax)
      return;
   ledg[index - 1] = v;
}

static inline void
setB (uint16_t index, uint8_t v)
{
   if (!index || index > ledmax)
      return;
   ledb[index - 1] = v;
}

static inline void
setW (uint16_t index, uint8_t v)
{
   if (!ledw || !index || index > ledmax)
      return;
   ledw[index - 1] = v;
}

static inline void
setRGB (uint16_t index, uint8_t r, uint8_t g, uint8_t b)
{
   if (!index || index > ledmax)
      return;
   ledr[index - 1] = r;
   ledg[index - 1] = g;
   ledb[index - 1] = b;
}

static inline void
setRGBW (uint16_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
   if (!index || index > ledmax)
      return;
   ledr[index - 1] = r;
   ledg[index - 1] = g;
   ledb[index - 1] = b;
   if (ledw)
      ledw[index - 1] = w;
}

static inline void
setRGBl (uint16_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t l)
{
   if (!index || index > ledmax)
      return;
   ledr[index - 1] = ((int) l * r + (int) (255 - l) * ledr[index - 1]) / 255;
   ledg[index - 1] = ((int) l * g + (int) (255 - l) * ledg[index - 1]) / 255;
   ledb[index - 1] = ((int) l * b + (int) (255 - l) * ledb[index - 1]) / 255;
}

static inline void
setRGBWl (uint16_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint8_t l)
{
   if (!index || index > ledmax)
      return;
   ledr[index - 1] = ((int) l * r + (int) (255 - l) * ledr[index - 1]) / 255;
   ledg[index - 1] = ((int) l * g + (int) (255 - l) * ledg[index - 1]) / 255;
   ledb[index - 1] = ((int) l * b + (int) (255 - l) * ledb[index - 1]) / 255;
   if (ledw)
      ledw[index - 1] = ((int) l * w + (int) (255 - l) * ledw[index - 1]) / 255;
}

static inline void
setl (uint16_t i, app_t * a, uint8_t l)
{
   if (a->rainbow)
   {
      uint8_t p = 110 - 255 * ((a->len + i - a->start) % a->len) / a->len;
      setRGBl (i, wheel[p], wheel[(p + 85) & 255], wheel[(p + 170) & 255], l);
   } else
      setRGBWl (i, a->r, a->g, a->b, a->w, l);
}
