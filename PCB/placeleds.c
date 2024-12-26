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

#define	delta 0.1               // Matched position

int
main (int argc, const char *argv[])
{
   const char *pcbfile = NULL;
   int diode = 1;
   int cap = 0;
   int rows = 0;
   int cols = 0;
   int count = 0;
   double spacing = 0;
   double trackwidth = 0.2;
   double padoffset = 0.6010407;
   double padsize = 0.3181981;  // extra to diagonal on power
   double clearance = 0.127;
   double capoffset = 1.15;
   double zonei = NAN;
   double zoneo = NAN;
   double startx = NAN;
   double starty = NAN;
   double diameter = 0;
   double radius = 0;
   double angle = 0;
   int group = 0;
   int sides = 0;
   int tracks = 0;
   double viaoffset = 0;
   double vias = 0;
   double powervias = 0;
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
         {"sides", 0, POPT_ARG_NONE, &sides, 0, "LED on sides rather than starty/bottom (grid)"},
         {"count", 0, POPT_ARG_INT, &count, 0, "Number of leds", "N"},
         {"diameter", 'd', POPT_ARG_DOUBLE, &diameter, 0, "LED ring diameter", "mm"},
         {"radius", 'r', POPT_ARG_DOUBLE, &radius, 0, "LED ring radius", "mm"},
         {"zone-in", 0, POPT_ARG_DOUBLE, &zonei, 0, "Zone inside ", "mm"},
         {"zone-out", 0, POPT_ARG_DOUBLE, &zoneo, 0, "Zone outside ", "mm"},
         {"angle", 'd', POPT_ARG_DOUBLE, &angle, 0, "Angle offset", "degrees"},
         {"group", 0, POPT_ARG_INT, &group, 0, "Group LEDs (ring)", "N"},
         {"pad-offset", 0, POPT_ARG_DOUBLE | POPT_ARGFLAG_SHOW_DEFAULT, &padoffset, 0, "Pad offset (square)", "mm"},
         {"cap-offset", 0, POPT_ARG_DOUBLE | POPT_ARGFLAG_SHOW_DEFAULT, &capoffset, 0, "Cap offset", "mm"},
         {"via-offset", 0, POPT_ARG_DOUBLE, &viaoffset, 0, "Via offset", "mm"},
         {"tracks", 0, POPT_ARG_NONE, &tracks, 0, "Add tracks"},
         {"vias", 0, POPT_ARG_DOUBLE, &vias, 0, "Add vias", "mm"},
         {"power-vias", 0, POPT_ARG_DOUBLE, &powervias, 0, "Add power vias", "mm"},
         {"fill", 0, POPT_ARG_STRING, &fill, 0, "Fill GND/POWER", "Power net name"},
         {"startx", 'x', POPT_ARG_DOUBLE, &startx, 0, "Left (grid) / Centre (ring)", "X"},
         {"starty", 'y', POPT_ARG_DOUBLE, &starty, 0, "Top (grid) / Centre (ring)", "Y"},
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
   if (radius && !diameter)
      diameter = radius * 2;
   if (radius && diameter && diameter != radius * 2)
      errx (1, "Pick --radius or --diameter");
   if ((rows || cols || sides) && diameter)
      errx (1, "Ring or grid, not both");
   if (diameter)
   {                            // Sanity check ring
      if (spacing && !group && !count)
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
      if (!spacing)
         spacing = 2;
   }
   if (diode && !cap)
      cap = diameter ? diode : (diode - 1) / (sides ? rows : cols) + 1;
   if (!viaoffset)
      viaoffset = !diameter ? 1.9 : 1.1;
   if (isnan (zonei))
      zonei = padoffset + padsize + clearance;
   else
      zonei -= clearance / 2;
   if (isnan (zoneo))
      zoneo = padoffset + padsize + clearance;
   else
      zoneo -= clearance / 2;
   double pada = 2 * padoffset / diameter;      // Angle for pad offset
   double spacinga = 2 * spacing / diameter;    // Angle for spacing of groups
   pcb_t *pcb = pcb_load (pcbfile);
   double ad (double d)
   {                            // Angle for diode
      double a (int d)
      {
         if (!group)
            return 2.0 * M_PI * d / count;
         return 2.0 * M_PI * (d / group) / (count / group) + spacinga * (-0.5 * (group - 1) + (d % group));
      }
      double f = floor (d);
      return a (f) * (f + 1 - d) + a (f + 1) * (d - f) + angle * M_PI / 180;
   }
   double ax (double a, double o)
   {                            // X for angle and offset
      return startx + (diameter / 2 + o) * sin (a);
   }
   double ay (double a, double o)
   {                            // Y for angle and offset
      return starty - (diameter / 2 + o) * cos (a);
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
      if (diameter)
         return cx (d, 0, 0);
      if (sides)
         return startx + spacing * (d % cols);
      return startx + spacing * (d / rows);
   }
   double diodey (int d)
   {
      if (diameter)
         return cy (d, 0, 0);
      if (sides)
         return starty + spacing * (d / cols);
      return starty + spacing * (d % rows);
   }
   double dioder (int d)
   {
      if (diameter)
         return -135 - ad (d) * 180 / M_PI;
      return sides ? -135 : 135;
   }
   double capx (int c)
   {
      if (diameter)
         return cx (0.5 + c, 0, 0);
      if (sides)
         return (c & 1) ? startx + spacing * (cols - 1) + capoffset : startx - capoffset;
      return startx + spacing * (c / 2);
   }
   double capy (int c)
   {
      if (diameter)
         return cy (0.5 + c, 0, 0);
      if (sides)
         return starty + spacing * (c / 2);
      return (c & 1) ? starty + spacing * (rows - 1) + capoffset : starty - capoffset;
   }
   double capr (int c)
   {
      if (diameter)
         return 90 - ad (0.5 + c) * 180 / M_PI;
      return sides ? 90 : 0;
   }
   int tooclose = ((!group && (M_PI * 2 - (ad (count - 0.5) - angle * M_PI / 180)) < pada * 4) || (group && spacing < padoffset * 6));  // Too close together for data pins together at end

   pcb_t *footprint = NULL;
   if (isnan (startx) || isnan (starty))
   {
      while ((footprint = pcb_find (pcb, "footprint", footprint)))
      {
         pcb_t *t = pcb_find (footprint, "property", NULL);
         if (!t)
            continue;
         if (!t || t->valuen < 2 || !t->values[0].istxt || strcmp (t->values[0].txt, "Reference") || !t->values[1].istxt)
            continue;
         const char *ref = t->values[1].txt;
         if (*ref != (!group || (group & 1) ? 'D' : 'C'))
            continue;
         int d = atoi (ref + 1);
         if (d != (!group || (group & 1) ? diode : cap))
            continue;
         t = pcb_find (footprint, "at", NULL);
         if (!t || t->valuen < 2 || !t->values[0].isnum || !t->values[1].isnum)
            continue;
         startx = t->values[0].num;
         starty = t->values[1].num;
         t = pcb_find (footprint, "layer", NULL);
         if (!t || t->valuen < 1 || !t->values[0].istxt)
            continue;
         layer = t->values[0].txt;
         break;
      }
      if (diameter)
      {                         // Assuming start D/C is top
         startx += diameter / 2;
         starty += diameter / 2;
      }
   }
   if (!layer)
      layer = "F.Cu";
   if (isnan (startx) || isnan (starty))
      warnx ("Cannot find start point (i.e. %c%d)", !group || (group & 1) ? 'D' : 'C', !group || (group & 1) ? diode : cap);
   int leds = 0;
   int countcap = !diameter ? (sides ? rows : cols) * 2 : count;
   footprint = NULL;
   while ((footprint = pcb_find (pcb, "footprint", footprint)))
   {
      pcb_t *t = pcb_find (footprint, "property", NULL);
      if (!t)
         continue;
      if (!t || t->valuen < 2 || !t->values[0].istxt || strcmp (t->values[0].txt, "Reference") || !t->values[1].istxt)
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
   void zaptrack (double x1, double y1, double x2, double y2)
   {
      pcb_t *s = NULL,
         *o;
      while ((s = pcb_find (pcb, isnan (x2) ? "segment" : "arc", s)))
      {
         o = pcb_find (s, "layer", NULL);
         if (!o || o->valuen != 1 || !o->values[0].istxt || strcmp (o->values[0].txt, layer))
            continue;
         o = pcb_find (s, "start", NULL);
         if (!o || o->valuen != 2 || !o->values[0].isnum || !o->values[1].isnum)
            continue;
         double d = (o->values[0].num - x1) * (o->values[0].num - x1) + (o->values[1].num - y1) * (o->values[1].num - y1);
         if (d >= delta * delta)
            continue;
         // No need to check mid
         o = pcb_find (s, "end", NULL);
         if (!o || o->valuen != 2 || !o->values[0].isnum || !o->values[1].isnum)
            continue;
         d = (o->values[0].num - x2) * (o->values[0].num - x2) + (o->values[1].num - y2) * (o->values[1].num - y2);
         if (d >= delta * delta)
            continue;
         s->tag = NULL;         // Suppress as we are replacing
      }
   }
   void track (double x1, double y1, double x2, double y2, double x3, double y3, double w)
   {                            // Add a track
      pcb_t *s = NULL,
         *o;
      zaptrack (x1, y1, x3, y3);
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
   double checkpad (double x, double y, const char *net)
   {
      double best = NAN;
      pcb_t *f = NULL,
         *o;
      while ((f = pcb_find (pcb, "footprint", f)))
      {
         o = pcb_find (f, "at", NULL);
         if (!o || o->valuen < 2 || !o->values[0].isnum || !o->values[1].isnum)
            continue;
         double fx = o->values[0].num,
            fy = o->values[1].num;
         double fa = 0;
         if (o->valuen > 2 && o->values[2].isnum)
            fa = -o->values[2].num * M_PI * 2 / 360;
         pcb_t *p = NULL;
         while ((p = pcb_find (f, "pad", p)))
         {
            o = pcb_find (p, "net", NULL);
            if (o && o->valuen >= 2 && o->values[1].istxt && !strcmp (o->values[1].txt, net))
               continue;
            o = pcb_find (p, "at", NULL);
            if (!o || o->valuen < 2 || !o->values[0].isnum || !o->values[1].isnum)
               continue;
            double ax = o->values[0].num,
               ay = o->values[1].num;
            double px = fx + ax * cos (fa) - ay * sin (fa),
               py = fy + ax * sin (fa) + ay * cos (fa);
            double d = (px - x) * (px - x) + (py - y) * (py - y);
            if (isnan (best) || d < best)
               best = d;
         }
      }
      return sqrt (best);
   }
   double zapvia (double x, double y)
   {                            // Zap a matching via, return closest non match
      double best = NAN;
      pcb_t *s = NULL,
         *o;
      while ((s = pcb_find (pcb, "via", s)))
      {
         o = pcb_find (s, "at", NULL);
         if (!o || o->valuen != 2 || !o->values[0].isnum || !o->values[1].isnum)
            continue;
         double d = (o->values[0].num - x) * (o->values[0].num - x) + (o->values[1].num - y) * (o->values[1].num - y);
         if (d < delta * delta)
            s->tag = NULL;      // Suppress as we are replacing
         else if (isnan (best) || d < best)
            best = d;
      }
      return sqrt (best);
   }
   void addvia (double x, double y, double size)
   {                            // add a via
      pcb_t *s = NULL,
         *o;
      s = pcb_append_obj (pcb, "via");
      o = pcb_append_obj (s, "at");
      pcb_append_num (o, x);
      pcb_append_num (o, y);
      o = pcb_append_obj (s, "size");
      pcb_append_num (o, size);
      o = pcb_append_obj (s, "drill");
      pcb_append_num (o, size / 2);
      o = pcb_append_obj (s, "layers");
      pcb_append_txt (o, "F.Cu");
      pcb_append_txt (o, "B.Cu");
   }
   void via (double x, double y, double size)
   {                            // Add a via replacing existing
      if (!size)
         return;                // Not doing via
      zapvia (x, y);
      addvia (x, y, size);
   }
   void trackvia (double x1, double y1, double x2, double y2, double w, double v)
   {
      if (!v)
         return;
      track (x1, y1, NAN, NAN, x2, y2, w);
      via (x2, y2, v);
   }
   void trackviamaybe (double x1, double y1, double x2, double y2, double w, double v, const char *net)
   {
      if (!v)
         return;
      double d = zapvia (x2, y2);
      if (!isnan (d) && d < (powervias ? : vias) + clearance)
      {
         zaptrack (x1, y1, x2, y2);
         return;                // Too close to another via
      }
      d = checkpad (x2, y2, net);
      if (!isnan (d) && d < (powervias ? : vias) / 2 + clearance + padsize)
      {
         zaptrack (x1, y1, x2, y2);
         return;                // Too close to another pad (different net)
      }
      track (x1, y1, NAN, NAN, x2, y2, w);
      addvia (x2, y2, v);
   }
   pcb_t *zone (const char *net, const char *layer)
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
   void zapzone (double x, double y, const char *net, const char *layer)
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
         if (!o || o->valuen != 2 || !o->values[0].isnum || !o->values[1].isnum)
            continue;
         double d = (o->values[0].num - x) * (o->values[0].num - x) + (o->values[1].num - y) * (o->values[1].num - y);
         if (d < delta * delta)
            s->tag = NULL;
      }
   }
   void ringzone (double a, double b, const char *net, const char *layer)
   {
      if (a == b)
         return;
      zapzone (ax (0, a), ay (0, a), net, layer);
      pcb_t *z = zone (net, layer);
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
      if (x1 == x2 || y1 == y2)
         return;
      zapzone (x1, y1, net, layer);
      pcb_t *z = zone (net, layer);
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

   if (tracks && trackwidth)
   {
      if (diameter)
      {                         // Ring
         double m = trackwidth / 2 + clearance + powervias / 2;
         double zi = zonei - powervias / 2;
         if (zi < m)
            zi = m;
         else
            zi = (m + zi) / 2;
         double zo = zoneo - powervias / 2;
         if (zo < m)
            zo = m;
         else
            zo = (m + zo) / 2;
         // Data
         for (int d = 0; d < count - 1; d++)
            track (cx (d, pada, 0), cy (d, pada, 0), cx (0.5 + d, 0, 0), cy (0.5 + d, 0, 0), cx (1 + d, -pada, 0),
                   cy (1 + d, -pada, 0), trackwidth);
         // Data end
         if (tooclose)
         {
            trackvia (cx (0, -pada, 0), cy (0, -pada, 0), cx (0, -pada, -viaoffset), cy (0, -pada, -viaoffset), trackwidth, vias);
            trackvia (cx (count - 1, pada, 0), cy (count - 1, pada, 0), cx (count - 1, pada, viaoffset),
                      cy (count - 1, pada, viaoffset), trackwidth, vias);
         } else
         {
            trackvia (cx (0, -pada, 0), cy (0, -pada, 0), cx (0, -pada * 2, -zi), cy (0, -pada * 2, -zi), trackwidth, vias);
            track (cx (count - 1, pada, 0), cy (count - 1, pada, 0), cx (count - 0.5, 0, 0), cy (count - 0.5, 0, 0),
                   cx (0, -pada * 2, 0), cy (0, -pada * 2, 0), trackwidth);
            trackvia (cx (0, -pada * 2, 0), cy (0, -pada * 2, 0), cx (0, -pada * 2, zo), cy (0, -pada * 2, zo), trackwidth, vias);
         }
         // Power
         for (int d = 0; d < count - 1; d++)
         {
            track (cx (d, 0, padoffset), cy (d, 0, padoffset), cx (0.5 + d, 0, padoffset), cy (0.5 + d, 0, padoffset),
                   cx (1 + d, 0, padoffset), cy (1 + d, 0, padoffset), trackwidth);
            track (cx (d, 0, -padoffset), cy (d, 0, -padoffset), cx (0.5 + d, 0, -padoffset), cy (0.5 + d, 0, -padoffset),
                   cx (1 + d, 0, -padoffset), cy (1 + d, 0, -padoffset), trackwidth);
         }
         // Power end
         if (tooclose)
         {
            track (cx (count - 0.5, 0, padoffset), cy (count - 0.5, 0, padoffset), cx (count - 0.25, 0, padoffset),
                   cy (count - 0.25, 0, padoffset), cx (0, 0, padoffset), cy (0, 0, padoffset), trackwidth);
            track (cx (count - 1, 0, -padoffset), cy (count - 1, 0, -padoffset), cx (count - 0.75, 0, -padoffset),
                   cy (count - 0.75, 0, -padoffset), cx (count - 0.5, 0, -padoffset), cy (count - 0.5, 0, -padoffset), trackwidth);
         } else
         {
            track (cx (count - 1, 0, padoffset), cy (count - 1, 0, padoffset), cx (count - 0.75, 0, padoffset),
                   cy (count - 0.75, 0, padoffset), cx (count - 0.5, 0, padoffset), cy (count - 0.5, 0, padoffset), trackwidth);
            track (cx (count - 1, 0, -padoffset), cy (count - 1, 0, -padoffset), cx (count - 0.75, 0, -padoffset),
                   cy (count - 0.75, 0, -padoffset), cx (count - 0.5, 0, -padoffset), cy (count - 0.5, 0, -padoffset), trackwidth);
         }

         if (powervias)
         {
            if (tooclose)
            {
               for (int d = 1; d < count; d++)
                  trackviamaybe (cx (d, -pada, padoffset), cy (d, -pada, padoffset), cx (d, -pada, viaoffset),
                                 cy (d, -pada, viaoffset), trackwidth, powervias, "GND");
               for (int d = 0; d < count - 1; d++)
                  trackviamaybe (cx (d, pada, -padoffset), cy (d, pada, -padoffset), cx (d, pada, -viaoffset),
                                 cy (d, pada, -viaoffset), trackwidth, powervias, fill ? : "VCC");
            } else
            {
               for (int d = 0; d < count; d++)
               {
                  trackviamaybe (cx (d + 0.25, 0, padoffset), cy (d + 0.25, 0, padoffset),
                                 cx (d + 0.25, 0, zo), cy (d + 0.25, 0, zo), trackwidth, powervias, "GND");
                  trackviamaybe (cx (d + 0.25, 0, -padoffset), cy (d + 0.25, 0, -padoffset),
                                 cx (d + 0.25, 0, -zi), cy (d + 0.25, 0, -zi), trackwidth, powervias, fill ? : "VCC");
               }
               for (int d = 1; d <= count; d++)
               {
                  trackviamaybe (cx (d - 0.25, 0, padoffset), cy (d - 0.25, 0, padoffset),
                                 cx (d - 0.25, 0, zo), cy (d - 0.25, 0, zo), trackwidth, powervias, "GND");
                  trackviamaybe (cx (d - 0.25, 0, -padoffset), cy (d - 0.25, 0, -padoffset),
                                 cx (d - 0.25, 0, -zi), cy (d - 0.25, 0, -zi), trackwidth, powervias, fill ? : "VCC");
               }
               track (cx (count - 0.5, 0, padoffset), cy (count - 0.5, 0, padoffset), cx (count - 0.375, 0, padoffset),
                      cy (count - 0.375, 0, padoffset), cx (count - 0.25, 0, padoffset), cy (count - 0.25, 0, padoffset),
                      trackwidth);
               track (cx (count - 0.5, 0, -padoffset), cy (count - 0.5, 0, -padoffset), cx (count - 0.375, 0, -padoffset),
                      cy (count - 0.375, 0, -padoffset), cx (count - 0.25, 0, -padoffset), cy (count - 0.25, 0, -padoffset),
                      trackwidth);
            }
         }
      } else if (sides)
      {                         // Grid with caps on sides
         for (int r = 0; r < rows; r++)
         {
            track (diodex (r * cols) - viaoffset, diodey (r * cols), NAN, NAN, diodex (r * cols) - padoffset, diodey (r * cols),
                   trackwidth);
            trackvia (diodex (r * cols + cols - 1) + padoffset, diodey (r * cols + cols - 1),
                      diodex (r * cols + cols - 1) + viaoffset, diodey (r * cols + cols - 1), trackwidth, vias);
         }
         for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols - 1; c++)
               track (diodex (c + r * cols) + padoffset, diodey (c + r * cols), NAN, NAN, diodex (c + r * cols + 1) - padoffset,
                      diodey (c + r * cols + 1), trackwidth);
         for (int r = 0; r < rows; r++)
         {
            track (diodex (r * cols) - capoffset, diodey (r * cols) - padoffset, NAN, NAN, diodex (r * cols),
                   diodey (r * cols) - padoffset, trackwidth);
            track (diodex (r * cols) - capoffset, diodey (r * cols) + padoffset, NAN, NAN, diodex (r * cols),
                   diodey (r * cols) + padoffset, trackwidth);
            for (int c = 0; c < cols - 1; c++)
            {
               track (diodex (c + r * cols), diodey (c + r * cols) - padoffset, NAN, NAN, diodex (c + r * cols + 1),
                      diodey (c + r * cols + 1) - padoffset, trackwidth);
               track (diodex (c + r * cols), diodey (c + r * cols) + padoffset, NAN, NAN, diodex (c + r * cols + 1),
                      diodey (c + r * cols + 1) + padoffset, trackwidth);
            }
            track (diodex (r * cols + cols - 1), diodey (r * cols + cols - 1) - padoffset, NAN, NAN,
                   diodex (r * cols + cols - 1) + capoffset, diodey (r * cols + cols - 1) - padoffset, trackwidth);
            track (diodex (r * cols + cols - 1), diodey (r * cols + cols - 1) + padoffset, NAN, NAN,
                   diodex (r * cols + cols - 1) + capoffset, diodey (r * cols + cols - 1) + padoffset, trackwidth);
         }
      } else
      {                         // Grid with caps at top/bottom
         for (int c = 0; c < cols; c++)
         {
            trackvia (diodex (c * rows), diodey (c * rows) - padoffset, diodex (c * rows), diodey (c * rows) - viaoffset,
                      trackwidth, vias);
            trackvia (diodex (c * rows + rows - 1), diodey (c * rows + rows - 1) + padoffset, diodex (c * rows + rows - 1),
                      diodey (c * rows + rows - 1) + viaoffset, trackwidth, vias);
         }
         for (int c = 0; c < cols; c++)
            for (int r = 0; r < rows - 1; r++)
               track (diodex (r + c * rows), diodey (r + c * rows) + padoffset, NAN, NAN, diodex (r + c * rows + 1),
                      diodey (r + c * rows + 1) - padoffset, trackwidth);
         for (int c = 0; c < cols; c++)
         {
            track (diodex (c * rows) - padoffset, diodey (c * rows) - capoffset, NAN, NAN, diodex (c * rows) - padoffset,
                   diodey (c * rows), trackwidth);
            track (diodex (c * rows) + padoffset, diodey (c * rows) - capoffset, NAN, NAN, diodex (c * rows) + padoffset,
                   diodey (c * rows), trackwidth);
            for (int r = 0; r < rows - 1; r++)
            {
               track (diodex (r + c * rows) - padoffset, diodey (r + c * rows), NAN, NAN, diodex (r + c * rows + 1) - padoffset,
                      diodey (r + c * rows + 1), trackwidth);
               track (diodex (r + c * rows) + padoffset, diodey (r + c * rows), NAN, NAN, diodex (r + c * rows + 1) + padoffset,
                      diodey (r + c * rows + 1), trackwidth);
            }
            track (diodex (c * rows + rows - 1) - padoffset, diodey (c * rows + rows - 1), NAN, NAN,
                   diodex (c * rows + rows - 1) - padoffset, diodey (c * rows + rows - 1) + capoffset, trackwidth);
            track (diodex (c * rows + rows - 1) + padoffset, diodey (c * rows + rows - 1), NAN, NAN,
                   diodex (c * rows + rows - 1) + padoffset, diodey (c * rows + rows - 1) + capoffset, trackwidth);
         }
         if (powervias)
         {
            for (int c = 0; c < cols - 1; c++)
               trackviamaybe (diodex (c * rows + rows - 1) + padoffset, diodey (c * rows + rows - 1) + capoffset,
                              diodex (c * rows + rows - 1) + spacing / 2, diodey (c * rows + rows - 1) + viaoffset, trackwidth,
                              powervias, "GND");
            for (int c = 1; c < cols; c++)
               trackviamaybe (diodex (c * rows) - padoffset, diodey (c * rows) - capoffset, diodex (c * rows) - spacing / 2,
                              diodey (c * rows) - viaoffset, trackwidth, powervias, fill ? : "VCC");
         }
      }
   }
   if (fill)
   {
      if (diameter)
      {
         ringzone (clearance / 2, zoneo, "GND", layer);
         ringzone (-clearance / 2, -zonei, fill, layer);
         if (powervias)
         {
            ringzone (clearance / 2, zoneo, "GND", *layer == 'F' ? "B.Cu" : "F.Cu");
            ringzone (-clearance / 2, -zonei, fill, *layer == 'F' ? "B.Cu" : "F.Cu");
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
            boxzone (diodex (c * rows) + clearance / 2, diodey (c * rows) - spacing / 2,
                     diodex (c * rows + rows - 1) + spacing / 2 - clearance / 2, diodey (c * rows + rows - 1) + spacing / 2, "GND");
            boxzone (diodex (c * rows) - clearance / 2, diodey (c * rows) - spacing / 2,
                     diodex (c * rows + rows - 1) - spacing / 2 + clearance / 2, diodey (c * rows + rows - 1) + spacing / 2, fill);
         }
   }

   pcb_write (pcbfile, pcb);
   pcb = pcb_free (pcb);

   poptFreeContext (optCon);
   return 0;
}
