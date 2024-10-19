// Palette logic

#include "revk.h"
#include "app.h"

palettes_t palettes[] = {
#define	p(x)	{#x,&palette_##x},
#include "palette.m"
   {0}
};


// Common functions (typically palette based on value, called from the palette functions)
static void
dorainbow (uint8_t n, uint8_t l, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{
   n = 110 - n;
   *r = (int) wheel[n] * l / 255;
   *g = (int) wheel[(n + 85) & 255] * l / 255;
   *b = (int) wheel[(n + 170) & 255] * l / 255;
   *w = 0;
}

static void
dowheel (uint8_t n, uint8_t l, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{
   n = 255 - n;
   *r = (int) cos8[n] * l / 255;
   *g = (int) cos8[(n + 85) & 255] * l / 255;
   *b = (int) cos8[(n + 170) & 255] * l / 255;
   *w = 0;
}

static void
dofire (uint8_t n, uint8_t l, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{
   *r = (int) n *l / 255;
   if (n > 128)
      *g = (int) ((n - 128) * 2) * l / 255;
   else
      *g = 0;
   if (n > 192)
      *b = (int) ((n - 192) * 4) * l / 255;
   else
      *b = 0;
   if (n > 224)
      *w = (int) ((n - 224) * 8) * l / 255;
   else
      *w = 0;
}

void
palette_rainbow (uint8_t t, uint8_t p, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // Position based rainbow (starts in the red)
   dorainbow (p, v, r, g, b, w);
}

void
palette_revbow (uint8_t t, uint8_t p, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // Position based rainbow (reversed, starts in the blue)
   dorainbow (230 - p, v, r, g, b, w);
}

void
palette_wheel (uint8_t t, uint8_t p, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // Time based wheel
   dowheel (t, v, r, g, b, w);
}

void
palette_cycling (uint8_t t, uint8_t p, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // Time based rainbow
   dorainbow (t, v, r, g, b, w);
}

void
palette_fire (uint8_t t, uint8_t p, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // test position based
   dofire (v, 255, r, g, b, w);
}
