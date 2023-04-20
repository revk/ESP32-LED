// Application structure

#include "revk.h"

typedef struct app_s app_t;
typedef struct colour_s colour_t;
typedef void app_f(app_t *);

struct colour_s
{
	uint8_t r,g,b,w;	// Full scale colours
};

struct app_s
{
	app_f *app;
	// Common settings
	uint8_t start;	// Start LEDs
	uint8_t len;	// Number of LEDs
	colour_t colour;	// Base colour
	// Scratchpad for apps
	uint8_t stage;	// The stage of a sequential display
	uint8_t step;	// Steps in the stage
};
