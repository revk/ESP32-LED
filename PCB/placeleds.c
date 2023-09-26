// LED grid

#include <stdio.h>
#include <string.h>
#include <popt.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <ctype.h>
#include <err.h>
#include <math.h>
#include "pcb.h"

int debug = 0;

int
main (int argc, const char *argv[])
{
   const char *pcbfile = NULL;
   int diode = 1;
   int cap = 1;
   int rows = 0;
   int cols = 0;
   int count = 0;
   double clearance = 0.15;
   double spacing = NAN;
   double pair = NAN;
   double widthend = 0;
   double widthjoin = 0;
   double widthpower = 0;
   double padoffset = 0.6010407;
   double capoffset = 1.15;
   double viaoffset = NAN;
   double left = NAN;
   double top = NAN;
   double diameter = NAN;
   int sides = 0;
   int vias = 0;
   int powervias = 0;
   const char *fill = NULL;
   const char *layer = NULL;
   poptContext optCon;
   // TODO reverse option and B.Cu logic
   {
      const struct poptOption optionsTable[] = {
         {"pcb-file", 0, POPT_ARG_STRING, &pcbfile, 0, "PCB file", "filename"},
         {"diode", 0, POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &diode, 0, "Start diode number", "N"},
         {"cap", 0, POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &cap, 0, "Start cap number", "N"},
         {"rows", 0, POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &rows, 0, "Number of rows (grid)", "N"},
         {"cols", 0, POPT_ARG_INT, &cols, 0, "Number of cols (grid)", "N"},
         {"spacing", 0, POPT_ARG_DOUBLE | POPT_ARGFLAG_SHOW_DEFAULT, &spacing, 0, "LED spacing (grid)", "mm"},
         {"sides", 0, POPT_ARG_NONE, &sides, 0, "LED on sides rather than top/bottom (grid)"},
         {"count", 0, POPT_ARG_INT, &count, 0, "Number of leds", "N"},
         {"diameter", 0, POPT_ARG_DOUBLE, &diameter, 0, "LED ring diameter", "mm"},
         {"pair", 0, POPT_ARG_DOUBLE, &pair, 0, "Paired LEDs (ring)", "mm"},
         {"width-end", 0, POPT_ARG_DOUBLE, &widthend, 0, "Track at ends (data)", "mm"},
         {"width-join", 0, POPT_ARG_DOUBLE, &widthjoin, 0, "Track joining LEDs (data)", "mm"},
         {"width-power", 0, POPT_ARG_DOUBLE, &widthpower, 0, "Track joining LEDs (power)", "mm"},
         {"pad-offset", 0, POPT_ARG_DOUBLE | POPT_ARGFLAG_SHOW_DEFAULT, &padoffset, 0, "Pad offset (square)", "mm"},
         {"cap-offset", 0, POPT_ARG_DOUBLE | POPT_ARGFLAG_SHOW_DEFAULT, &capoffset, 0, "Cap offset", "mm"},
         {"via-offset", 0, POPT_ARG_DOUBLE, &viaoffset, 0, "Via offset", "mm"},
         {"vias", 0, POPT_ARG_NONE, &vias, 0, "Add vias"},
         {"power-vias", 0, POPT_ARG_NONE, &powervias, 0, "Add power vias"},
         {"fill", 0, POPT_ARG_STRING, &fill, 0, "Fill GND/POWER", "Power net name"},
         {"left", 0, POPT_ARG_DOUBLE, &left, 0, "Left", "mm"},
         {"top", 0, POPT_ARG_DOUBLE, &top, 0, "Top", "mm"},
         {"debug", 'v', POPT_ARG_NONE, &debug, 0, "Debug"},
         POPT_AUTOHELP {}
      };

      optCon = poptGetContext (NULL, argc, argv, optionsTable, 0);
      //poptSetOtherOptionHelp(optCon, "");

      int c;
      if ((c = poptGetNextOpt (optCon)) < -1)
         errx (1, "%s: %s\n", poptBadOption (optCon, POPT_BADOPTION_NOALIAS), poptStrerror (c));

      if (!pcbfile && poptPeekArg (optCon))
         pcbfile = poptGetArg (optCon);
      if (poptPeekArg (optCon) || !pcbfile)
      {
         poptPrintUsage (optCon, stderr, 0);
         return -1;
      }
   }
   if ((rows || cols || sides) && !isnan (diameter))
      errx (1, "Ring or grid, not both");
   if (!isnan (diameter))
   {                            // Sanity check ring
      if (!isnan (pair))
         count *= 2;
      if (!isnan (spacing) && !count)
         count = diameter * M_PI / spacing;
      if (count < 3)
         errx (1, "Specify LED count (more than 2)");
   } else
   {                            // Sanity check grid
      if (count && !rows)
         rows = count / cols;
      else if (count && !cols)
         cols = count / rows;
      if (!(sides ? rows : cols))
         errx (1, "Need to know size");
      count = rows * cols;
      if (isnan (spacing))
         spacing = 2;
   }
   if (isnan (viaoffset))
      viaoffset = isnan (diameter) ? 1.9 : 1.1;
   double pada = 2 * padoffset / diameter;      // Angle for pad offset
   double paira = pair / diameter;      // Angle for (half) pair offset
   pcb_t *pcb = pcb_load (pcbfile);
   double ad (double d)
   {                            // Angle for diode
      double a (int d)
      {
         if (isnan (pair))
            return 2.0 * M_PI * d / count;
         double a = 2.0 * M_PI * (d / 2) / (count / 2);
         if (d & 1)
            a += paira;
         else
            a -= paira;
         return a;
      }
      double f = floor (d);
      return a (f) * (f + 1 - d) + a (f + 1) * (d - f);
   }
   double ax (double a, double o)
   {                            // X for angle and offset
      return left + (diameter / 2 + o) * sin (a);
   }
   double ay (double a, double o)
   {                            // Y for angle and offset
      return top - (diameter / 2 + o) * cos (a);
   }
   double cx (double d, double a, double o)
   {                            // X for diode and offset
      return ax (ad (d) + a, o);
   }
   double cy (double d, double a, double o)
   {                            // Y for diode and offset
      return ay (ad (d) + a, o);
   }
   double diodex (int d)
   {
      if (!isnan (diameter))
         return cx (d, 0, 0);
      if (sides)
         return left + spacing * (d % cols);
      return left + spacing * (d / rows);
   }
   double diodey (int d)
   {
      if (!isnan (diameter))
         return cy (d, 0, 0);
      if (sides)
         return top + spacing * (d / cols);
      return top + spacing * (d % rows);
   }
   double dioder (int d)
   {
      if (!isnan (diameter))
         return -135 - ad (d) * 180 / M_PI;
      return sides ? -135 : 135;
   }
   double capx (int c)
   {
      if (!isnan (diameter))
         return cx (0.5 + c, 0, 0);
      if (sides)
         return (c & 1) ? left + spacing * (cols - 1) + capoffset : left - capoffset;
      return left + spacing * (c / 2);
   }
   double capy (int c)
   {
      if (!isnan (diameter))
         return cy (0.5 + c, 0, 0);
      if (sides)
         return top + spacing * (c / 2);
      return (c & 1) ? top + spacing * (rows - 1) + capoffset : top - capoffset;
   }
   double capr (int c)
   {
      if (!isnan (diameter))
         return 90 - ad (0.5 + c) * 180 / M_PI;
      return sides ? 90 : 0;
   }
int tooclose=((M_PI*2-ad(count-0.5))<pada*4); // Too close together for data pins together at end

   pcb_t *footprint = NULL;
   if (isnan (left) || isnan (top))
   {
      while ((footprint = pcb_find (pcb, "footprint", footprint)))
      {
         pcb_t *t = pcb_find (footprint, "fp_text", NULL);
         if (!t)
            continue;
         if (!t || t->valuen < 2 || !t->values[0].islit || strcmp (t->values[0].txt, "reference") || !t->values[1].istxt)
            continue;
         const char *ref = t->values[1].txt;
         if (*ref != (isnan (pair) ? 'D' : 'C'))
            continue;
         int d = atoi (ref + 1);
         if (d != (isnan (pair) ? diode : cap))
            continue;
         t = pcb_find (footprint, "at", NULL);
         if (!t || t->valuen < 2 || !t->values[0].isnum || !t->values[1].isnum)
            continue;
         left = t->values[0].num;
         top = t->values[1].num;
         t = pcb_find (footprint, "layer", NULL);
         if (!t || t->valuen < 1 || !t->values[0].istxt)
            continue;
         layer = t->values[0].txt;
         break;
      }
   } else if (!isnan (diameter))
      left += diameter / 2;     // Start LED position
   if (isnan (left) || isnan (top) || !layer)
      warnx ("Cannot find start point (i.e. %c%d)", isnan (pair) ? 'D' : 'C', isnan (pair) ? diode : cap);
   if (!isnan (diameter))
      top += diameter / 2;      // Center of ring
   int leds = 0;
   int countcap = isnan (diameter) ? (sides ? rows : cols) * 2 : count;
   footprint = NULL;
   while ((footprint = pcb_find (pcb, "footprint", footprint)))
   {
      pcb_t *t = pcb_find (footprint, "fp_text", NULL);
      if (!t)
         continue;
      if (!t || t->valuen < 2 || !t->values[0].islit || strcmp (t->values[0].txt, "reference") || !t->values[1].istxt)
         continue;
      const char *ref = t->values[1].txt;
      if (*ref == 'D')
      {                         // Diode placement
         int d = atoi (ref + 1);
         if (d < diode)
            continue;           // Before start
         if (count && d >= diode + count)
            continue;           // Off end
         t = pcb_find (footprint, "at", NULL);
         if (!t)
            t = pcb_append_obj (footprint, "at");
         else
            pcb_clear (t);
         d -= diode;
         pcb_append_num (t, diodex (d));
         pcb_append_num (t, diodey (d));
         pcb_append_num (t, dioder (d));
         leds++;
         continue;
      }
      if (*ref == 'C')
      {                         // Cap placement
         int c = atoi (ref + 1);
         if (c < cap)
            continue;           // Before start
         if (countcap && c >= cap + countcap)
            continue;           // Off end
         t = pcb_find (footprint, "at", NULL);
         if (!t)
            t = pcb_append_obj (footprint, "at");
         else
            pcb_clear (t);
         c -= cap;
         pcb_append_num (t, capx (c));
         pcb_append_num (t, capy (c));
         pcb_append_num (t, capr (c));
         continue;
      }
   }
   if (sides)
      rows = leds / cols;
   else
      cols = leds / rows;
   int diff (double a, double b)
   {
      if (round (a * 100000) != round (b * 100000))
         return 1;
      return 0;
   }
   void track (double x1, double y1, double x2, double y2, double x3, double y3, double w)
   {                            // Add a track
      pcb_t *s = NULL,
         *o;
      while ((s = pcb_find (pcb, isnan (x2) ? "segment" : "arc", s)))
      {
         o = pcb_find (s, "layer", NULL);
         if (!o || o->valuen != 1 || !o->values[0].istxt || strcmp (o->values[0].txt, layer))
            continue;
         o = pcb_find (s, "start", NULL);
         if (!o || o->valuen != 2 || !o->values[0].isnum || !o->values[1].isnum || diff (o->values[0].num, x1)
             || diff (o->values[1].num, y1))
            continue;
         if (!isnan (x2))
         {
            o = pcb_find (s, "mid", NULL);
            if (!o || o->valuen != 2 || !o->values[0].isnum || !o->values[1].isnum || diff (o->values[0].num, x2)
                || diff (o->values[1].num, y2))
               continue;
         }
         o = pcb_find (s, "end", NULL);
         if (!o || o->valuen != 2 || !o->values[0].isnum || !o->values[1].isnum || diff (o->values[0].num, x3)
             || diff (o->values[1].num, y3))
            continue;
         s->tag = NULL;         // Suppress as we are replacing
      }
      s = pcb_append_obj (pcb, isnan (x2) ? "segment" : "arc"), *o;
      o = pcb_append_obj (s, "start");
      pcb_append_num (o, x1);
      pcb_append_num (o, y1);
      if (!isnan (x2))
      {
         o = pcb_append_obj (s, "mid");
         pcb_append_num (o, x2);
         pcb_append_num (o, y2);
      }
      o = pcb_append_obj (s, "end");
      pcb_append_num (o, x3);
      pcb_append_num (o, y3);
      o = pcb_append_obj (s, "width");
      pcb_append_num (o, w);
      o = pcb_append_obj (s, "layer");
      pcb_append_txt (o, layer);
   }
   void via (double x, double y)
   {
      pcb_t *s = NULL,
         *o;
      while ((s = pcb_find (pcb, "via", s)))
      {
         o = pcb_find (s, "at", NULL);
         if (!o || o->valuen != 2 || !o->values[0].isnum || !o->values[1].isnum || diff (o->values[0].num, x)
             || diff (o->values[1].num, y))
            continue;
         s->tag = NULL;         // Suppress as we are replacing
      }
      s = pcb_append_obj (pcb, "via");
      o = pcb_append_obj (s, "at");
      pcb_append_num (o, x);
      pcb_append_num (o, y);
      o = pcb_append_obj (s, "size");
      pcb_append_num (o, 0.8);
      o = pcb_append_obj (s, "drill");
      pcb_append_num (o, 0.4);
      o = pcb_append_obj (s, "layers");
      pcb_append_txt (o, "F.Cu");
      pcb_append_txt (o, "B.Cu");
   }
   pcb_t *zone (const char *net,const char *layer)
   {
      pcb_t *s,
       *o,
       *p;
      s = pcb_append_obj (pcb, "zone");
      o = pcb_append_obj (s, "priority");
      pcb_append_num (o, 2);
      o = pcb_append_obj (s, "net_name");
      pcb_append_txt (o, net);
      o = pcb_append_obj (s, "layer");
      pcb_append_txt (o, layer);
      o = pcb_append_obj (s, "hatch");
      pcb_append_lit (o, "edge");
      pcb_append_num (o, .5);
      o = pcb_append_obj (s, "connect_pads");
      pcb_append_lit (o, "yes");
      p = pcb_append_obj (o, "clearance");
      pcb_append_num (p, clearance);
      o = pcb_append_obj (s, "min_thickness");
      pcb_append_num (o, .25);
      o = pcb_append_obj (s, "filled_areas_thickness");
      pcb_append_lit (o, "no");
      o = pcb_append_obj (s, "fill");
      pcb_append_lit (o, "yes");
      p = pcb_append_obj (o, "thermal_gap");
      pcb_append_num (p, .5);
      p = pcb_append_obj (o, "thermal_bridge_width");
      pcb_append_num (p, .75);
      o = pcb_append_obj (s, "polygon");
      o = pcb_append_obj (o, "pts");
      return o;
   }
   void zapzone (double x, double y, const char *net,const char *layer)
   {
      pcb_t *s = NULL,
         *o;
      while ((s = pcb_find (pcb, "zone", s)))
      {
         o = pcb_find (s, "net_name", NULL);
         if (!o || o->valuen != 1 || !o->values[0].istxt || strcmp (o->values[0].txt, net))
            continue;
         o = pcb_find (s, "layer", NULL);
         if (!o || o->valuen != 1 || !o->values[0].istxt || strcmp (o->values[0].txt, layer))
            continue;
         o = pcb_find (s, "polygon", NULL);
         o = pcb_find (o, "pts", NULL);
         o = pcb_find (o, "xy", NULL);
         if (!o || o->valuen != 2 || !o->values[0].isnum || !o->values[1].isnum || diff (o->values[0].num, x)
             || diff (o->values[1].num, y))
            continue;
         s->tag = NULL;
      }
   }

   void ringzone (double a, double b, const char *net,const char *layer)
   {
      zapzone (cx (0, 0, a), cy (0, 0, a), net,layer);
      pcb_t *z = zone (net,layer);
      void xy (double d, double o)
      {
         pcb_t *xy = pcb_append_obj (z, "xy");
         pcb_append_num (xy, ax (d, o));
         pcb_append_num (xy, ay (d, o));
      }
      int steps = M_PI * diameter / 2;
      xy (0, a);
      for (int d = 0; d <= steps; d++)
         xy (M_PI * 2 * d / steps, b);
      for (int d = steps; d > 0; d--)
         xy (M_PI * 2 * d / steps, a);
   }

   void boxzone (double x1, double y1, double x2, double y2, const char *net)
   {
      zapzone (x1, y1, net,layer);
      pcb_t *z = zone (net,layer);
      void xy (double x, double y)
      {
         pcb_t *xy = pcb_append_obj (z, "xy");
         pcb_append_num (xy, x);
         pcb_append_num (xy, y);
      }
      xy (x1, y1);
      xy (x1, y2);
      xy (x2, y2);
      xy (x2, y1);
   }

   if (widthend)
   {                            // Data at ends
      if (!isnan (diameter))
      {
         track (cx (0, -pada, 0), cy (0, -pada, 0), NAN, NAN, cx (0, -pada, viaoffset), cy (0, -pada, viaoffset), widthend);
	 if(tooclose)
		  track(cx(count-1,pada,0),cy(count-1,pada,0),NAN,NAN,cx(count-1,pada,-viaoffset),cy(count-1,pada,-viaoffset),widthend);
	 else
	 {
	 track(cx(count-1,pada,0),cy(count-1,pada,0),cx(count-0.5,0,0),cy(count-0.5,0,0),cx(0,-pada*2,0),cy(0,-pada*2,0),widthend);
         track (cx(0,-pada*2,0),cy(0,-pada*2,0),NAN,NAN,cx(0,-pada*2,-viaoffset),cy(0,-pada*2,-viaoffset),widthend);
	 }
      } else if (sides)
         for (int r = 0; r < rows; r++)
         {
            track (diodex (r * cols) - viaoffset, diodey (r * cols), NAN, NAN, diodex (r * cols) - padoffset, diodey (r * cols),
                   widthend);
            track (diodex (r * cols + cols - 1) + padoffset, diodey (r * cols + cols - 1), NAN, NAN,
                   diodex (r * cols + cols - 1) + viaoffset, diodey (r * cols + cols - 1), widthend);
      } else
         for (int c = 0; c < cols; c++)
         {
            track (diodex (c * rows), diodey (c * rows) - viaoffset, NAN, NAN, diodex (c * rows), diodey (c * rows) - padoffset,
                   widthend);
            track (diodex (c * rows + rows - 1), diodey (c * rows + rows - 1) + padoffset, NAN, NAN, diodex (c * rows + rows - 1),
                   diodey (c * rows + rows - 1) + viaoffset, widthend);
         }
   }
   if (widthjoin)
   {                            // Data joining adjacent LEDs
      if (!isnan (diameter))
      {
         for (int d = 0; d < count - 1; d++)
            track (cx (d, pada, 0), cy (d, pada, 0), cx (0.5 + d, 0, 0), cy (0.5 + d, 0, 0), cx (1 + d, -pada, 0),
                   cy (1 + d, -pada, 0), widthjoin);
      } else if (sides)
      {
         for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols - 1; c++)
               track (diodex (c + r * cols) + padoffset, diodey (c + r * cols), NAN, NAN, diodex (c + r * cols + 1) - padoffset,
                      diodey (c + r * cols + 1), widthjoin);
      } else
      {
         for (int c = 0; c < cols; c++)
            for (int r = 0; r < rows - 1; r++)
               track (diodex (r + c * rows), diodey (r + c * rows) + padoffset, NAN, NAN, diodex (r + c * rows + 1),
                      diodey (r + c * rows + 1) - padoffset, widthjoin);
      }
   }
   if (widthpower)
   {                            // Joining power
      if (!isnan (diameter))
      {
         for (int d = 0; d < count - 1; d++)
         {
            track (cx (d, 0, padoffset), cy (d, 0, padoffset), cx (0.5 + d, 0, padoffset), cy (0.5 + d, 0, padoffset),
                   cx (1 + d, 0, padoffset), cy (1 + d, 0, padoffset), widthpower);
            track (cx (d, 0, -padoffset), cy (d, 0, -padoffset), cx (0.5 + d, 0, -padoffset), cy (0.5 + d, 0, -padoffset),
                   cx (1 + d, 0, -padoffset), cy (1 + d, 0, -padoffset), widthpower);
         }
	 // Connect to caps at end
	 if(tooclose)
         track (cx (count-0.5, 0, -padoffset), cy (count-0.5, 0, -padoffset), cx (count-0.25, 0, -padoffset), cy (count-0.25, 0, -padoffset),
                cx (0, 0, -padoffset), cy (0, 0, -padoffset), widthpower);
	 else
         track (cx (count-1, 0, -padoffset), cy (count-1, 0, -padoffset), cx (count-0.75, 0, -padoffset), cy (count-0.75, 0, -padoffset),
                cx (count-0.5, 0, -padoffset), cy (count-0.5, 0, -padoffset), widthpower);
         track (cx (count - 1, 0, padoffset), cy (count - 1, 0, padoffset), cx (count - 0.75, 0, padoffset),
                cy (count - 0.75, 0, padoffset), cx (count - 0.5, 0, padoffset), cy (count - 0.5, 0, padoffset), widthpower);

	 if(powervias)
	 {
		 if(tooclose)
		 {
		 for(int d=1;d<count;d++)
         track (cx (d, -pada, padoffset), cy (d, -pada, padoffset), NAN, NAN, cx (d, -pada, viaoffset), cy (d, -pada, viaoffset), widthpower);
		 for(int d=0;d<count-1;d++)
         track (cx (d, pada, -padoffset), cy (d, pada, -padoffset), NAN, NAN, cx (d, pada, -viaoffset), cy (d, pada, -viaoffset), widthpower);
		 }
		 else
		 {
	      for(int d=1;d<count;d++)
         track (cx (d-0.25, 0, padoffset), cy (d-0.25, 0, padoffset),NAN,NAN,cx (d-0.25, 0, padoffset+clearance/2), cy (d-0.25, 0, padoffset+clearance/2),widthpower);
	      for(int d=0;d<count-1;d++)
         track (cx (d+0.25, 0, -padoffset), cy (d+0.25, 0, -padoffset),NAN,NAN,cx (d+0.25, 0, -padoffset-clearance/2), cy (d+0.25, 0, -padoffset-clearance/2),widthpower);
		 }
	 }
      } else if (sides)
      {
         for (int r = 0; r < rows; r++)
         {
            track (diodex (r * cols) - capoffset, diodey (r * cols) - padoffset, NAN, NAN, diodex (r * cols),
                   diodey (r * cols) - padoffset, widthpower);
            track (diodex (r * cols) - capoffset, diodey (r * cols) + padoffset, NAN, NAN, diodex (r * cols),
                   diodey (r * cols) + padoffset, widthpower);
            for (int c = 0; c < cols - 1; c++)
            {
               track (diodex (c + r * cols), diodey (c + r * cols) - padoffset, NAN, NAN, diodex (c + r * cols + 1),
                      diodey (c + r * cols + 1) - padoffset, widthpower);
               track (diodex (c + r * cols), diodey (c + r * cols) + padoffset, NAN, NAN, diodex (c + r * cols + 1),
                      diodey (c + r * cols + 1) + padoffset, widthpower);
            }
            track (diodex (r * cols + cols - 1), diodey (r * cols + cols - 1) - padoffset, NAN, NAN,
                   diodex (r * cols + cols - 1) + capoffset, diodey (r * cols + cols - 1) - padoffset, widthpower);
            track (diodex (r * cols + cols - 1), diodey (r * cols + cols - 1) + padoffset, NAN, NAN,
                   diodex (r * cols + cols - 1) + capoffset, diodey (r * cols + cols - 1) + padoffset, widthpower);
         }
      } else
      {
         for (int c = 0; c < cols; c++)
         {
            track (diodex (c * rows) - padoffset, diodey (c * rows) - capoffset, NAN, NAN, diodex (c * rows) - padoffset,
                   diodey (c * rows), widthpower);
            track (diodex (c * rows) + padoffset, diodey (c * rows) - capoffset, NAN, NAN, diodex (c * rows) + padoffset,
                   diodey (c * rows), widthpower);
            for (int r = 0; r < rows - 1; r++)
            {
               track (diodex (r + c * rows) - padoffset, diodey (r + c * rows), NAN, NAN, diodex (r + c * rows + 1) - padoffset,
                      diodey (r + c * rows + 1), widthpower);
               track (diodex (r + c * rows) + padoffset, diodey (r + c * rows), NAN, NAN, diodex (r + c * rows + 1) + padoffset,
                      diodey (r + c * rows + 1), widthpower);
            }
            track (diodex (c * rows + rows - 1) - padoffset, diodey (c * rows + rows - 1), NAN, NAN,
                   diodex (c * rows + rows - 1) - padoffset, diodey (c * rows + rows - 1) + capoffset, widthpower);
            track (diodex (c * rows + rows - 1) + padoffset, diodey (c * rows + rows - 1), NAN, NAN,
                   diodex (c * rows + rows - 1) + padoffset, diodey (c * rows + rows - 1) + capoffset, widthpower);
         }
      }
   }
   if (vias)
   {                            // Add vias
      if (!isnan (diameter))
      {
         via (cx (0, -pada, viaoffset), cy (0, -pada, viaoffset));
	 if(tooclose)
         via (cx (count - 1, pada, -viaoffset), cy (count - 1, pada, -viaoffset));
	 else
		 via(cx(0,-pada*2,-viaoffset),cy(0,-pada*2,-viaoffset));
      } else if (sides)
         for (int r = 0; r < rows; r++)
         {
            via (diodex (r * cols) - viaoffset, diodey (r * cols));
            via (diodex (r * cols + cols - 1) + viaoffset, diodey (r * cols + cols - 1));
      } else
         for (int c = 0; c < cols; c++)
         {
            via (diodex (c * rows), diodey (c * rows) - viaoffset);
            via (diodex (c * rows + rows - 1), diodey (c * rows + rows - 1) + viaoffset);
         }
   }
   if(powervias)
   {
	         if (!isnan (diameter))
      {
	      if(tooclose)
	      {
	      for(int d=1;d<count;d++)
         via (cx (d, -pada, viaoffset), cy (d, -pada, viaoffset));
	      for(int d=0;d<count-1;d++)
         via (cx (d, pada, -viaoffset), cy (d, pada, -viaoffset));
	      }else
	      {
	      for(int d=1;d<count;d++)
         via (cx (d-0.25, 0, padoffset+clearance/2), cy (d-0.25, 0, padoffset+clearance/2));
	      for(int d=0;d<count-1;d++)
         via (cx (d+0.25, 0, -padoffset-clearance/2), cy (d+0.25, 0, -padoffset-clearance/2));
	      }
      } else if (sides)
		 {
		 }
		 else
		 {
		 }
   }
   if (fill)
   {
      if (!isnan (diameter))
      {
         ringzone (0, padoffset * 2, "GND",layer);
         ringzone (-padoffset * 2, 0, fill,layer);
	 if(powervias)
	 {
         ringzone (0, padoffset * 2, "GND",*layer=='F'?"B.Cu":"F.Cu");
         ringzone (-padoffset * 2, 0, fill,*layer=='F'?"B.Cu":"F.Cu");
	 }
      } else if (sides)
         for (int r = 0; r < rows; r++)
         {
            boxzone (diodex (r * cols) - spacing / 2, diodey (r * cols) - spacing / 2 + clearance / 2,
                     diodex (r * cols + cols - 1) + spacing / 2, diodey (r * cols + cols - 1), "GND");
            boxzone (diodex (r * cols) - spacing / 2, diodey (r * cols), diodex (r * cols + cols - 1) + spacing / 2,
                     diodey (r * cols + cols - 1) + spacing / 2 - clearance / 2, fill);
      } else
         for (int c = 0; c < cols; c++)
         {
            boxzone (diodex (c * rows), diodey (c * rows) - spacing / 2, diodex (c * rows + rows - 1) + spacing / 2 - clearance / 2,
                     diodey (c * rows + rows - 1) + spacing / 2, "GND");
            boxzone (diodex (c * rows) - spacing / 2 + clearance / 2, diodey (c * rows) - spacing / 2, diodex (c * rows + rows - 1),
                     diodey (c * rows + rows - 1) + spacing / 2, fill);
         }
   }

   pcb_write (pcbfile, pcb);
   pcb = pcb_free (pcb);

   poptFreeContext (optCon);
   return 0;
}
