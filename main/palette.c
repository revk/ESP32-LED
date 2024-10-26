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
dorainbow (uint8_t n, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{
   n = 110 - n;
   *r = (int) wheel[n];
   *g = (int) wheel[(n + 85) & 255];
   *b = (int) wheel[(n + 170) & 255];
   *w = 0;
}

static void
dowheel (uint8_t n, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{
   n = 255 - n;
   *r = (int) cos8[n];
   *g = (int) cos8[(n + 85) & 255];
   *b = (int) cos8[(n + 170) & 255];
   *w = 0;
}

static void
dofire (uint8_t n, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{
   *r = (int) n;
   if (n > 128)
      *g = ((n - 128) * 2);
   else
      *g = 0;
   if (n > 192)
      *b = ((n - 192) * 4);
   else
      *b = 0;
   if (n > 224)
      *w = ((n - 224) * 8);
   else
      *w = 0;
}

uint8_t
palette_rainbow (uint8_t t, int p, int n, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // Position based rainbow (starts in the red)
   dorainbow (255 * p / n, r, g, b, w);
   return v;
}

uint8_t
palette_revbow (uint8_t t, int p, int n, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // Position based rainbow (reversed, starts in the blue)
   dorainbow (230 - (255 * p / n), r, g, b, w);
   return v;
}

uint8_t
palette_wheel (uint8_t t, int p, int n, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // Time based wheel
   dowheel (t, r, g, b, w);
   return v;
}

uint8_t
palette_cycling (uint8_t t, int p, int n, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // Time based rainbow
   dorainbow (t, r, g, b, w);
   return v;
}

uint8_t
palette_fire (uint8_t t, int p, int n, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // Value based fire black/red/yellow/white
   dofire (v, r, g, b, w);
   return 255; // Does not blend, which is a shame
}

uint8_t
palette_xmas (uint8_t t, int p, int n, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // Position based red/green
   *r = ((p & 1) ? 255 : 0);
   *g = ((p & 1) ? 0 : 255);
   *b = 0;
   *w = 0;
   return v;
}

uint8_t
palette_neenaw (uint8_t t, int p, int n, uint8_t v, uint8_t * r, uint8_t * g, uint8_t * b, uint8_t * w)
{                               // Time based red/blue
   if (cps > 10)
      t /= 2;
   if (cps > 20)
      t /= 2;
   int q = t % 16;
   if (q == 1 || q == 3 || q == 5)
   {
      *r = 255;
      *b = 0;
   } else if (q == 9 || q == 11 || q == 13)
   {
      *r = 0;
      *b = 255;
   } else
   {
      *r = 0;
      *b = 0;
   }
   *g = 0;
   *w = 0;
   return v;
}
