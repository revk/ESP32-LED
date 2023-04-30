/* Make a ring of LEDs */
/* (c) 2023 Adrian Kennard Andrews & Arnold Ltd */

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <popt.h>
#include <err.h>
#include <float.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

int
main(int argc, const char *argv[])
{
   const char     *filename = "PCB/Coaster/Coaster.kicad_pcb";
   int             leds = 12;
   int             radius = 35;
   int             width = 100;
   int             debug = 0;
   int             edge = 8;
   int             cx = 150;
   int             cy = 100;
   int             notchw = 10;
   int             notchh = 8;
   const char     *led = "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm";
   const char     *cap = "RevK:C_0603";
   const char     *hole = "RevK:LEDHOLE";
   const char     *join = "RevK:PCB-Join";
   {
      poptContext     optCon;   /* context for parsing  command - line options */
      const struct poptOption optionsTable[] = {
         {"file", 'f', POPT_ARG_STRING | POPT_ARGFLAG_SHOW_DEFAULT, &filename, 0, "File", "filename"},
         {"leds", 'l', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &leds, 0, "LEDs", "N"},
         {"radius", 'r', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &radius, 0, "Radius", "mm"},
         {"width", 'w', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &width, 0, "Width", "mm"},
         {"cx", 'x', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &cx, 0, "Centre X", "mm"},
         {"cy", 'y', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &cy, 0, "Centre Y", "mm"},
         {"edge", 'e', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &edge, 0, "Border Edges", "N"},
         {"notchw", 'n', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &notchw, 0, "Border notch width", "mm"},
         {"notchh", 'N', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &notchh, 0, "Border notch height", "mm"},
         {"debug", 'v', POPT_ARG_NONE, &debug, 0, "Debug"},
         POPT_AUTOHELP {}
      };

      optCon = poptGetContext(NULL, argc, argv, optionsTable, 0);
      /* poptSetOtherOptionHelp(optCon, ""); */

      int             c;
      if ((c = poptGetNextOpt(optCon)) < -1)
         errx(1, "%s: %s\n", poptBadOption(optCon, POPT_BADOPTION_NOALIAS), poptStrerror(c));

      poptFreeContext(optCon);
   }

   FILE           *i = fopen(filename, "r");
   if (!i)
      err(1, "This works on an existing file, create first: %s", filename);
   char           *temp;
   if (asprintf(&temp, "%s-new", filename) < 0)
      errx(1, "malloc");
   FILE           *o = fopen(temp, "w");
   if (!o)
      err(1, "Cannot make temp file: %s", temp);

   {
      //Copy to end
         char           *line = NULL;
      size_t          linecap = 0;
      ssize_t         linelen;
      char            skipping = 0;
      while ((linelen = getline(&line, &linecap, i)) > 0)
      {
         if (!strcmp(line, ")\n"))
            break;              /* end */
         if (!strncmp(line, "  (gr_line ", 11) && strstr(line, "(layer \"Edge.Cuts\")") && strstr(lined, "(width 0.05)"))
            continue;           /* edge cuts (size is how we know it is ours) */
         if (skipping)
         {
            if (!strncmp(line, "  )", 3))
               skipping = 0;
            continue;
         }
         int             found(const char *f)
         {
            if (!f)
               return 0;
            if (strncmp(line, "  (footprint \"", 14))
               return 0;
            int             l = strlen(f);
            if              (strncmp(line + 14, f, l))
                               return 0;
            if              (line[14 + l] != '"')
                               return 0;
                            skipping = 1;
                            return 1;
         }
         if              (found(led))
                            continue;
         if (found(hole))
            continue;
         if (found(cap))
            continue;
         if (found(join))
            continue;
         fwrite(line, linelen, 1, o);
      }
   }

   void            addborder(float x, float y, int nx, int ny)
   {
      float           w = width / cos(M_PI * 2 * 0.5 / edge);
      for             (int i = 0; i < edge; i++)
      {
         float           x1 = x + w * sin(M_PI * 2 * (i + 0.5) / edge) / 2;
         float           y1 = y + w * cos(M_PI * 2 * (i + 0.5) / edge) / 2;
         float           x2 = x + w * sin(M_PI * 2 * (i + 1.5) / edge) / 2;
         float           y2 = y + w * cos(M_PI * 2 * (i + 1.5) / edge) / 2;
         if              (nx && ny && y1 == y2 && y1 > y)
         {
            fprintf(o, "  (gr_line (start %.2f %.2f) (end %.2f %.2f) (layer \"Edge.Cuts\") (width 0.05))\n", x1, y1, x - nx / 2, y2);
            fprintf(o, "  (gr_line (start %.2f %.2f) (end %.2f %.2f) (layer \"Edge.Cuts\") (width 0.05))\n", x - nx / 2, y1, x - nx / 2, y2 - ny);
            fprintf(o, "  (gr_line (start %.2f %.2f) (end %.2f %.2f) (layer \"Edge.Cuts\") (width 0.05))\n", x - nx / 2, y1 - ny, x + nx / 2, y2 - ny);
            fprintf(o, "  (gr_line (start %.2f %.2f) (end %.2f %.2f) (layer \"Edge.Cuts\") (width 0.05))\n", x + nx / 2, y1 - ny, x + nx / 2, y2);
            fprintf(o, "  (gr_line (start %.2f %.2f) (end %.2f %.2f) (layer \"Edge.Cuts\") (width 0.05))\n", x + nx / 2, y1, x2, y2);
         } else if       (join && x1 == x2 && (x < cx ? x1 > x : x1 < x))
         {
            fprintf(o, "  (gr_line (start %.2f %.2f) (end %.2f %.2f) (layer \"Edge.Cuts\") (width 0.05))\n", x1, y1, x2, y2 > y1 ? y - 2 : y + 2);
            fprintf(o, "  (gr_line (start %.2f %.2f) (end %.2f %.2f) (layer \"Edge.Cuts\") (width 0.05))\n", x1, y2 > y1 ? y + 2 : y - 2, x2, y2);
         } else
            fprintf(o, "  (gr_line (start %.2f %.2f) (end %.2f %.2f) (layer \"Edge.Cuts\") (width 0.05))\n", x1, y1, x2, y2);
      }
   }

   void            footprint(float x, float y, int r, const char *prefix, int id, const char *part)
   {
      fprintf(o, "  (footprint \"%s\" (layer \"F.Cu\")\n", part);
      fprintf(o, "    (at %.2f %.2f %d)\n", x, y, r % 360);
      fprintf(o, "    (fp_text reference \"%s%d\" (at 0 0) (layer \"F.SilkS\") hide\n", prefix, id);
      fprintf(o, "      (effects (font (size 1 1) (thickness 0.15)))\n");
      fprintf(o, "    )\n");
      fprintf(o, "    (fp_text value \"-\" (at 0 0) (layer \"F.SilkS\") hide\n");
      fprintf(o, "      (effects (font (size 1 1) (thickness 0.15)))\n");
      fprintf(o, "    )\n");
      fprintf(o, "  )\n");
   }

   void            addleds(int x, int y, int p, int r, const char *id, const char *part)
   {
      for (int i = 0; i < leds; i++)
      {
         float           xc = (float)x + (float)(radius + p) * sin(M_PI * 2 * i / leds);
         float           yc = (float)y + (float)(radius + p) * cos(M_PI * 2 * i / leds);
                         footprint(xc, yc, (360 * i / leds + r), id, i + 1, part);
      }
   }

                   addborder(cx - width / 2 - 1, cy, notchw, notchh);
   if (hole)
      addleds(cx - width / 2 - 1, cy, 0, 180, "H", hole);
   addborder(cx + width / 2 + 1, cy, 0, 0);
   if (led)
      addleds(cx + width / 2 + 1, cy, 0, 270, "D", led);
   if (cap)
      addleds(cx + width / 2 + 1, cy, 4, 180, "C", cap);
   if (join)
      footprint(cx, cy, 0, "J", 1, join);

   fprintf(o, ")\n");
   fclose(i);
   fclose(o);
   if (rename(temp, filename))
   {
      unlink(temp);
      err(1, "Cannot overwrite: %s", filename);
   }
}
