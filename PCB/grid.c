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
   double padoffset = 0.425;
   double capoffset = 1.15;
   double viaoffset = 1.9;
   double left = NAN;
   double top = NAN;
   int sides = 0;
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
      d -= diode;
      if (sides)
         return left + spacing * (d % cols);
      return left + spacing * (d / rows);
   }
   double diodey (int d)
   {
      d -= diode;
      if (sides)
         return top + spacing * (d / cols);
      return top + spacing * (d % rows);
   }
   int dioder (int d)
   {
      d -= diode;
      return sides ? -135 : 135;
   }
   double capx (int c)
   {
      c -= cap;
      if (sides)
         return (c & 1) ? left + spacing * (cols - 1) + capoffset : left - capoffset;
      return left + spacing * (c / 2);
   }
   double capy (int c)
   {
      c -= cap;
      if (sides)
         return top + spacing * (c / 2);
      return (c & 1) ? top + spacing * (rows - 1) + capoffset : top - capoffset;
   }
   int capr (int c)
   {
      c -= cap;
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
         {
            warnx ("Cannot place %s", ref);
            continue;
         }
         left = t->values[0].num;
         top = t->values[1].num;
      }
   }
   if (isnan (left) || isnan (top))
      warnx ("Cannot find start point (i.e. D%d)", diode);
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
         pcb_append_num (t, diodex (d));
         pcb_append_num (t, diodey (d));
         pcb_append_num (t, dioder (d));
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
         pcb_append_num (t, capx (c));
         pcb_append_num (t, capy (c));
         pcb_append_num (t, capr (c));
         continue;
      }
   }
   if (widthend)
   {                            // Data at ends
   }
   if (widthjoin)
   {                            // Data joining adjacent LEDs

   }
   if (widthpower)
   {                            // Joining power
   }

   pcb_write (pcbfile, pcb);
   pcb = pcb_free (pcb);

   poptFreeContext (optCon);
   return 0;
}
