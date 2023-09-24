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
   int rows = 8;
   int cols = 0;
   double spacing = 2;
   double widthend = 0;
   double widthjoin = 0;
   double widthpower = 0;
   double padoffset = 0.6010407;
   double capoffset = 1.15;
   double viaoffset = 1.9;
   double left = NAN;
   double top = NAN;
   int sides = 0;
   int vias = 0;
   const char *layer = NULL;
   poptContext optCon;
   {
      const struct poptOption optionsTable[] = {
         {"pcb-file", 0, POPT_ARG_STRING, &pcbfile, 0, "PCB file", "filename"},
         {"diode", 0, POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &diode, 0, "Start diode number", "N"},
         {"cap", 0, POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &cap, 0, "Start cap number", "N"},
         {"rows", 0, POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &rows, 0, "Number of rows", "N"},
         {"cols", 0, POPT_ARG_INT, &cols, 0, "Number of cols", "N"},
         {"spacing", 0, POPT_ARG_DOUBLE | POPT_ARGFLAG_SHOW_DEFAULT, &spacing, 0, "LED spacing", "mm"},
         {"width-end", 0, POPT_ARG_DOUBLE, &widthend, 0, "Track at ends (data)", "mm"},
         {"width-join", 0, POPT_ARG_DOUBLE, &widthjoin, 0, "Track joining LEDs (data)", "mm"},
         {"width-power", 0, POPT_ARG_DOUBLE, &widthpower, 0, "Track joining LEDs (power)", "mm"},
         {"sides", 0, POPT_ARG_NONE, &sides, 0, "Sides on sides (end of rows) rather than top/bottom"},
         {"pad-offset", 0, POPT_ARG_DOUBLE | POPT_ARGFLAG_SHOW_DEFAULT, &padoffset, 0, "Pad offset (square)", "mm"},
         {"cap-offset", 0, POPT_ARG_DOUBLE | POPT_ARGFLAG_SHOW_DEFAULT, &capoffset, 0, "Cap offset", "mm"},
         {"via-offset", 0, POPT_ARG_DOUBLE | POPT_ARGFLAG_SHOW_DEFAULT, &viaoffset, 0, "Via offset", "mm"},
         {"vias", 0, POPT_ARG_NONE, &vias, 0, "Add vias"},
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
   if (!(sides ? rows : cols))
      errx (1, "Need to know size");
   pcb_t *pcb = pcb_load (pcbfile);
   double diodex (int d)
   {
      if (sides)
         return left + spacing * (d % cols);
      return left + spacing * (d / rows);
   }
   double diodey (int d)
   {
      if (sides)
         return top + spacing * (d / cols);
      return top + spacing * (d % rows);
   }
   int dioder (int d)
   {
      return sides ? -135 : 135;
   }
   double capx (int c)
   {
      if (sides)
         return (c & 1) ? left + spacing * (cols - 1) + capoffset : left - capoffset;
      return left + spacing * (c / 2);
   }
   double capy (int c)
   {
      if (sides)
         return top + spacing * (c / 2);
      return (c & 1) ? top + spacing * (rows - 1) + capoffset : top - capoffset;
   }
   int capr (int c)
   {
      return sides ? 90 : 0;
   }

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
         if (*ref != 'D')
            continue;
         int d = atoi (ref + 1);
         if (d != diode)
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
      }
   }
   if (isnan (left) || isnan (top) || !layer)
      warnx ("Cannot find start point (i.e. D%d)", diode);
   int leds = 0;
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
         if (rows && cols && d >= diode + rows * cols)
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
         if ((sides ? rows : cols) && c >= cap + (sides ? rows : cols) * 2)
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
   int diff(double a,double b)
   {
	   if(round(a*10000)!=round(b*10000))return 1;
	   return 0;
   }
   void track (double x1, double y1, double x2, double y2, double w)
   {                            // Add a track
      pcb_t *s =NULL,*o;
      while((s=pcb_find(pcb,"segment",s)))
		      {
			      o=pcb_find(s,"start",NULL);
			      if(!o||o->valuen!=2||!o->values[0].isnum||!o->values[1].isnum||diff(o->values[0].num,x1)||diff(o->values[1].num,y1))continue;
			      o=pcb_find(s,"end",NULL);
			      if(!o||o->valuen!=2||!o->values[0].isnum||!o->values[1].isnum||diff(o->values[0].num,x2)||diff(o->values[1].num,y2))continue;
			      s->tag=NULL; // Suppress as we are replacing
		      }
	      s=pcb_append_obj (pcb, "segment"),
         *o;
      o = pcb_append_obj (s, "start");
      pcb_append_num (o, x1);
      pcb_append_num (o, y1);
      o = pcb_append_obj (s, "end");
      pcb_append_num (o, x2);
      pcb_append_num (o, y2);
      o = pcb_append_obj (s, "width");
      pcb_append_num (o, w);
      o = pcb_append_obj (s, "layer");
      pcb_append_txt (o, layer);
   }
   void via (double x, double y)
   {
      pcb_t *s =NULL,*o;
      while((s=pcb_find(pcb,"via",s)))
		      {
			      o=pcb_find(s,"at",NULL);
			      if(!o||o->valuen!=2||!o->values[0].isnum||!o->values[1].isnum||diff(o->values[0].num,x)||diff(o->values[1].num,y))continue;
			        s->tag=NULL; // Suppress as we are replacing
                      }
	     s= pcb_append_obj (pcb, "via"),
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
   if (widthend)
   {                            // Data at ends
      if (sides)
         for (int r = 0; r < rows; r++)
         {
            track (diodex (r * cols) - viaoffset, diodey (r * cols), diodex (r * cols) - padoffset, diodey (r * cols), widthend);
            track (diodex (r * cols + cols - 1) + padoffset, diodey (r * cols + cols - 1), diodex (r * cols + cols - 1) + viaoffset,
                   diodey (r * cols + cols - 1), widthend);
      } else
         for (int c = 0; c < cols; c++)
         {
            track (diodex (c * rows), diodey (c * rows) - viaoffset, diodex (c * rows), diodey (c * rows) - padoffset, widthend);
            track (diodex (c * rows + rows - 1), diodey (c * rows + rows - 1) + padoffset, diodex (c * rows + rows - 1),
                   diodey (c * rows + rows - 1) + viaoffset, widthend);
         }
   }
   if (widthjoin)
   {                            // Data joining adjacent LEDs
      if (sides)
      {
         for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols - 1; c++)
               track (diodex (c + r * cols) + padoffset, diodey (c + r * cols), diodex (c + r * cols + 1) - padoffset,
                      diodey (c + r * cols + 1), widthjoin);
      } else
      {
         for (int c = 0; c < cols; c++)
            for (int r = 0; r < rows - 1; r++)
               track (diodex (r + c * rows), diodey (r + c * rows) + padoffset, diodex (r + c * rows + 1),
                      diodey (r + c * rows + 1) - padoffset, widthjoin);
      }
   }
   if (widthpower)
   {                            // Joining power
      if (sides)
      {
         for (int r = 0; r < rows; r++)
         {
            track (diodex (r * cols) - capoffset, diodey (r * cols) - padoffset, diodex (r * cols), diodey (r * cols) - padoffset,
                   widthpower);
            track (diodex (r * cols) - capoffset, diodey (r * cols) + padoffset, diodex (r * cols), diodey (r * cols) + padoffset,
                   widthpower);
            for (int c = 0; c < cols - 1; c++)
            {
               track (diodex (c + r * cols), diodey (c + r * cols) - padoffset, diodex (c + r * cols + 1),
                      diodey (c + r * cols + 1) - padoffset, widthpower);
               track (diodex (c + r * cols), diodey (c + r * cols) + padoffset, diodex (c + r * cols + 1),
                      diodey (c + r * cols + 1) + padoffset, widthpower);
            }
            track (diodex (r * cols + cols - 1), diodey (r * cols + cols - 1) - padoffset, diodex (r * cols + cols - 1) + capoffset,
                   diodey (r * cols + cols - 1) - padoffset, widthpower);
            track (diodex (r * cols + cols - 1), diodey (r * cols + cols - 1) + padoffset, diodex (r * cols + cols - 1) + capoffset,
                   diodey (r * cols + cols - 1) + padoffset, widthpower);
         }
      } else
      {
         for (int c = 0; c < cols; c++)
         {
            track (diodex (c * rows) - padoffset, diodey (c * rows) - capoffset, diodex (c * rows) - padoffset, diodey (c * rows),
                   widthpower);
            track (diodex (c * rows) + padoffset, diodey (c * rows) - capoffset, diodex (c * rows) + padoffset, diodey (c * rows),
                   widthpower);
            for (int r = 0; r < rows - 1; r++)
            {
               track (diodex (r + c * rows) - padoffset, diodey (r + c * rows), diodex (r + c * rows + 1) - padoffset,
                      diodey (r + c * rows + 1), widthpower);
               track (diodex (r + c * rows) + padoffset, diodey (r + c * rows), diodex (r + c * rows + 1) + padoffset,
                      diodey (r + c * rows + 1), widthpower);
            }
            track (diodex (c * rows + rows - 1) - padoffset, diodey (c * rows + rows - 1), diodex (c * rows + rows - 1) - padoffset,
                   diodey (c * rows + rows - 1) + capoffset, widthpower);
            track (diodex (c * rows + rows - 1) + padoffset, diodey (c * rows + rows - 1), diodex (c * rows + rows - 1) + padoffset,
                   diodey (c * rows + rows - 1) + capoffset, widthpower);
         }
      }
   }
   if (vias)
   {                            // Add vias
      if (sides)
         for (int r = 0; r < rows; r++)
         {
            via (diodex (r * cols) - viaoffset, diodey (r * cols));
            via (diodex (r * cols + cols - 1) + viaoffset, diodey (r * cols + cols - 1));
#if 0
            if (r)
            {
               via (diodex (r * cols) - viaoffset, diodey (r * cols) - spacing / 2);
               via (diodex (r * cols + cols - 1) + viaoffset, diodey (r * cols + cols - 1) - spacing / 2);
            }
#endif
      } else
         for (int c = 0; c < cols; c++)
         {
            via (diodex (c * rows), diodey (c * rows) - viaoffset);
            via (diodex (c * rows + rows - 1), diodey (c * rows + rows - 1) + viaoffset);
#if 0
            if (c)
            {
               via (diodex (c * rows) - spacing / 2, diodey (c * rows) - viaoffset);
               via (diodex (c * rows + rows - 1) - spacing / 2, diodey (c * rows + rows - 1) + viaoffset);
            }
#endif
         }
   }

   pcb_write (pcbfile, pcb);
   pcb = pcb_free (pcb);

   poptFreeContext (optCon);
   return 0;
}
