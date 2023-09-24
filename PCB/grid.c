// LED grid

#include <stdio.h>
#include <string.h>
#include <popt.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <ctype.h>
#include <err.h>
#include "pcb.h"

int             debug = 0;

int
main(int argc, const char *argv[])
{
   const char     *pcbfile = NULL;
   int             diode = 1;
   int             cap = 1;
   int             rows = 8;
   int             cols = 0;
   double          spacing = 2;
   double          widthend = 0;
   double          widthjoin = 0;
   double          widthpower = 0;
   double          padpos = 0.425;
   int             sides = 0;
   poptContext     optCon;
   /* context for parsing command - line options */
   {
      //POPT
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
         {"pad-pos", 0, POPT_ARG_DOUBLE | POPT_ARGFLAG_SHOW_DEFAULT, &padpos, 0, "Pad offset (square)", "mm"},
         {"sides", 0, POPT_ARG_NONE, &sides, 0, "Sides on sides (end of rows) rather than top/bottom"},
         {"debug", 'v', POPT_ARG_NONE, &debug, 0, "Debug"},
         POPT_AUTOHELP {}
      };

      optCon = poptGetContext(NULL, argc, argv, optionsTable, 0);
      //poptSetOtherOptionHelp(optCon, "");

      int             c;
      if ((c = poptGetNextOpt(optCon)) < -1)
         errx(1, "%s: %s\n", poptBadOption(optCon, POPT_BADOPTION_NOALIAS), poptStrerror(c));

      if (!pcbfile && poptPeekArg(optCon))
         pcbfile = poptGetArg(optCon);
      if (poptPeekArg(optCon) || !pcbfile)
      {
         poptPrintUsage(optCon, stderr, 0);
         return -1;
      }
   }
   pcb_t          *pcb = pcb_load(pcbfile);
   pcb_write(pcbfile, pcb);
   pcb = pcb_delete(pcb);

   poptFreeContext(optCon);
   return 0;
}
