// Application structure

#include "revk.h"
#include "palette.h"

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

#define	MICOVERSAMPLE	4       // From raw to FFT
#define	MICHZ		((int)cps)      // Hz step
#define	MICSAMPLES	512     // Power of 2 (this is multiplied by oversample)
#define	MICRATE	(MICSAMPLES*MICHZ)  // Hz which is multiplied by oversample (TDK 25-300ks/s in theory but 25k seemed not to work)
#define	MICMIN	((int)cps*2)    // Hz
#define	MICMAX	((int)cps*(MICSAMPLES/2))     // Hz
#define	MICBANDS	42      // How many bands we make log based
#define	MICSTEP	((MICMAX-MICMIN)/MICBANDS)        // Hz steps
#define	MICGAINMIN	0.01
#define	MICGAINMAX	(micmaxgain)
extern SemaphoreHandle_t mic_mutex;
extern float micband[MICBANDS];
extern float micmag;
uint8_t michz2band (uint32_t hz);
uint32_t micband2hz (uint8_t b);

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
   uint8_t palette;             // Which palette (+1)
   uint8_t r,
     g,
     b,
     w;                         // Colour
   uint8_t stop;                // If set this is a count down to stopping
   uint8_t fader;               // Effective brightness (set to bright unless fading in or out)
   uint8_t colourset:1;         // Colour is set
   uint8_t sound:1;             // Audio app
   uint8_t ring:1;              // Ring app
   uint8_t text:1;              // Text app
   // Scratchpad for apps
   uint32_t cycle;              // This is set by caller - counts the cycle since started
   uint32_t stage;              // The stage of a sequential display
   uint32_t step;               // Steps in the stage
   char *config;                // Malloc'd JSON config
   void *data;                  // Malloc'd data area
};

extern int ledmax;              // Total LEDs

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
setl (uint16_t i, app_t * a, int p, int n, uint8_t l)
{                               // i is the LED, a is app, p/n is position, l is level
   if (a->palette)
      l = palettes[a->palette - 1].run (a->cycle, p, n, l, &a->r, &a->g, &a->b, &a->w);
   setRGBWl (i, a->r, a->g, a->b, a->w, l);
}

uint8_t setcolour (app_t * a, const char *colour);

typedef void pixel_t (app_t * a, int pos, int p, int n, uint8_t l);
void bargraph (app_t * a, pixel_t *, int v, int total, uint8_t fade);
