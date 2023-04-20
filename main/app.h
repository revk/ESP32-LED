// Application structure

#include "revk.h"

#define settings                \
        io(ledgpio,22)  \
        u8(bright,63)   \
        u8(leds,1)      \
	u8(ringstart,)	\
	u8(ringlen,)	\
	u8(ringtop,)	\

#define u32(n,d)	extern uint32_t n;
#define u32l(n,d)	extern uint32_t n;
#define s8(n,d)		extern int8_t n;
#define s8n(n,d)	extern int8_t n[d];
#define u8(n,d)		extern uint8_t n;
#define u8l(n,d)	extern uint8_t n;
#define b(n)		extern uint8_t n;
#define s(n)		extern char * n;
#define io(n,d)           extern uint8_t n;
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
typedef struct app_s app_t;
typedef const char *app_f (app_t *);    // Return NULL normally, "" for normal end, other string for error

extern uint8_t *ledr;           // The current LED, set by the apps
extern uint8_t *ledg;           // The current LED, set by the apps
extern uint8_t *ledb;           // The current LED, set by the apps

extern const uint8_t sin256[256];

struct app_s
{                               // Note LED number start from 1 with 0 meaning not set, stage 0 means app should sanity check parameters
   app_f *app;
   // Common settings
   uint8_t start;               // LED number Start LEDs
   uint8_t len;                 // Number of LEDs
   uint8_t top;                 // LED number Top (of ring)
   uint8_t tail;                // Use for fading / moving like spin or cylon - how many LEDs trail
   uint8_t speed;               // This depends on app, e.g. spin uses this to mean how many calls (10th second) per full ring (default is number of LEDs in ring)
   struct
   {
      uint8_t r,
        g,
        b;
      uint8_t set:1;            // Colour is set
      uint8_t cycle:1;          // Colour should be cycled
   } colour;
   uint32_t time;               // Total time in cycles (10th second) after which the app is automatically stopped - app can pre-empt fade out, etc if it wants by checking cycle against this
   // Scratchpad for apps
   uint32_t cycle;              // This is set by caller - counts the cycle since started
   uint8_t stage;               // The stage of a sequential display
   uint8_t step;                // Steps in the stage
};
