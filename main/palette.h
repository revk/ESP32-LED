// Palette logic

// Takes time/position/value and sets R/G/B/W, time and value are 0-255, position is p/n
typedef void palette_t (uint8_t t, int p, int n, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w);

typedef struct
{
   const char *name;
   palette_t *run;
} palettes_t;
extern palettes_t palettes[];

#define p(x) extern palette_t palette_##x;
#include "palette.m"
