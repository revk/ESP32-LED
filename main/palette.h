// Palette logic

// Takes time/position/value (alld 0-255) and sets R/G/B/W
typedef void palette_t (uint8_t t, uint8_t p, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w);

typedef struct
{
   const char *name;
   palette_t *run;
} palettes_t;
extern palettes_t palettes[];

#define p(x) extern palette_t palette_##x;
#include "palette.m"