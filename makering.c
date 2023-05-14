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
   int             leds = 24;
   int             radius = 35;
   int             width = 98;
   int             debug = 0;
   int             edge = 0;
   int             cx = 150;
   int             cy = 100;
   int             notch = 10;
   const char     *led = "RevK:SMD2020";
   const char     *cap = "RevK:C_0603";
   const char     *hole = "RevK:LEDHOLE";
   const char     *zonegnd = "GND";
   const char     *zonegnd2 = "GND2";
   const char     *zonevcc = "VCC";
   int             netgnd = 0,
                   netgnd2 = 0,
                   netvcc = 0;
   float           ledw = 2.1,
                   ledx = 0.5,
                   ledy = 0.85;
   float           clearance = 0.3;
   {
      poptContext     optCon;   /* context for parsing  command - line options */
      const struct poptOption optionsTable[] = {
         {"file", 'f', POPT_ARG_STRING | POPT_ARGFLAG_SHOW_DEFAULT, &filename, 0, "File", "filename"},
         {"leds", 'l', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &leds, 0, "LEDs", "N"},
         {"radius", 'r', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &radius, 0, "Radius", "mm"},
         {"width", 'w', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &width, 0, "Width", "mm"},
         {"cx", 'x', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &cx, 0, "Centre X", "mm"},
         {"cy", 'y', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &cy, 0, "Centre Y", "mm"},
         {"ledw", 'L', POPT_ARG_FLOAT | POPT_ARGFLAG_SHOW_DEFAULT, &ledw, 0, "LED width", "mm"},
         {"ledx", 'L', POPT_ARG_FLOAT | POPT_ARGFLAG_SHOW_DEFAULT, &ledx, 0, "LED pad x", "mm"},
         {"ledy", 'L', POPT_ARG_FLOAT | POPT_ARGFLAG_SHOW_DEFAULT, &ledy, 0, "LED pad y", "mm"},
         {"edge", 'e', POPT_ARG_INT, &edge, 0, "Border Edges", "N"},
         {"notch", 'n', POPT_ARG_INT | POPT_ARGFLAG_SHOW_DEFAULT, &notch, 0, "Border notch", "mm"},
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
   if (!edge)
      edge = leds;

   FILE           *i = fopen(filename, "r");
   if (!i)
      err(1, "This works on an existing file, create first: %s", filename);
   char           *temp;
   if (asprintf(&temp, "%s-new", filename) < 0)
      errx(1, "malloc");
   FILE           *o = fopen(temp, "w");
   if (!o)
      err(1, "Cannot make temp file: %s", temp);

   int            *netled = calloc(leds, sizeof(int));

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
         if (!strncmp(line, "  (net ", 7))
         {
            int             n = atoi(line + 7);
            const char     *q = strchr(line, '"');
            if (q++)
            {
               if (zonegnd && !strncmp(q, zonegnd, strlen(zonegnd)) && q[strlen(zonegnd)] == '"')
                  netgnd = n;
               if (zonegnd2 && !strncmp(q, zonegnd2, strlen(zonegnd2)) && q[strlen(zonegnd2)] == '"')
                  netgnd2 = n;
               if (zonevcc && !strncmp(q, zonevcc, strlen(zonevcc)) && q[strlen(zonevcc)] == '"')
                  netvcc = n;
               if (!strncmp(q, "Net-(D", 6))
               {
                  q += 6;
                  int             d = atoi(q);
                  if (d && d <= leds)
                  {
                     while (isdigit(*q))
                        q++;
                     if (!strncmp(q, "-Pad2)\"", 7))
                        netled[d - 1] = n;
                  }
               }
            }
         }
         if (!strncmp(line, "  (segment ", 11) || !strncmp(line, "  (arc ", 7))
         {
            const char     *n = strstr(line, "(net ");
            if (n)
            {
               int             net = atoi(n + 5);
               if (net)
               {
                  int             led;
                  for (led = 0; led < leds && net != netled[led]; led++);
                  if (led < leds)
                     continue;  /* Skip just this line */
               }
            }
         }
         if (!strncmp(line, "  (gr_line ", 11) && strstr(line, "(layer \"Edge.Cuts\")") && strstr(line, "(width 0.05)"))
            continue;           /* edge cuts (size is how we know it is ours) */ /* DOES NOT WORK ON VERSION 7 */
         if (skipping)
         {
            if (!strncmp(line, "  )", 3))
               skipping = 0;
            continue;
         }
         int             foundzone(const char *f)
         {
            if (!f)
               return 0;
            if (strncmp(line, "  (zone ", 8))
               return 0;
            const char     *n = strstr(line, "(net_name \"");
            if              (!n)
                               return 0;
                            n += 11;
            int             l = strlen(f);
            if              (strncmp(n, f, l))
                               return 0;
            if              (n[l] != '"')
                               return 0;
                            skipping = 1;
                            return 1;
         }
         int             foundfootprint(const char *f)
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
         if              (foundfootprint(led))
                            continue;
         if (foundfootprint(hole))
            continue;
         if (foundfootprint(cap))
            continue;
         if (foundzone(zonegnd))
            continue;
         if (foundzone(zonegnd2))
            continue;
         if (foundzone(zonevcc))
            continue;
         fwrite(line, linelen, 1, o);
      }
   }

   void            addborder(float x, float y, int n)
   {
      float           w = width / cos(M_PI * 2 * 0.5 / edge);
      for             (int i = 0; i < edge; i++)
      {
         float           x1 = x - w * sin(M_PI * 2 * (i + 0.5) / edge) / 2;
         float           y1 = y + w * cos(M_PI * 2 * (i + 0.5) / edge) / 2;
         float           x2 = x - w * sin(M_PI * 2 * (i + 1.5) / edge) / 2;
         float           y2 = y + w * cos(M_PI * 2 * (i + 1.5) / edge) / 2;
         if              (n && y1 == y2 && y1 > y)
         {
            fprintf(o, "  (gr_line (start %.2f %.2f) (end %.2f %.2f) (layer \"Edge.Cuts\") (width 0.05))\n", x1, y1, x1 < x2 ? x - n / 2 : x + n / 2, y2);
            fprintf(o, "  (gr_line (start %.2f %.2f) (end %.2f %.2f) (layer \"Edge.Cuts\") (width 0.05))\n", x1 < x2 ? x + n / 2 : x - n / 2, y1, x2, y2);
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
      fprintf(o, "    (attr smd)\n");
      fprintf(o, "  )\n");
   }

   void            addleds(int x, int y, float ox, float oy, int r, const char *id, const char *part, int idbase)
   {
      for (int i = 0; i < leds; i++)
      {
         float           xc = (float)x - (float)(radius + oy) * sin(M_PI * 2 * i / leds + ox / radius);
         float           yc = (float)y + (float)(radius + oy) * cos(M_PI * 2 * i / leds + ox / radius);
                         footprint(xc, yc, (360 * (leds - i) / leds + r - (360 * ox / radius / 2 / M_PI)), id, i + idbase, part);
      }
   }

   void            addzones(int x, int y, int netgnd, const char *gnd, int netvcc, const char *vcc)
   {
      if (!netgnd && !netvcc)
         return;
      void            start(int netid, const char *net, const char *layer)
      {
         fprintf(o, "  (zone (net %d) (net_name \"%s\") (layers \"%s\") (hatch edge 0.508)\n", netid, net, layer);
         fprintf(o, "    (connect_pads (clearance 0.2))\n");
         fprintf(o, "    (min_thickness 0.254) (filled_areas_thickness no)\n");
         fprintf(o, "    (fill yes (thermal_gap 0.5) (thermal_bridge_width 0.75))\n");
         fprintf(o, "    (polygon\n");
         fprintf(o, "      (pts\n");
      }
      void            stop(void)
      {
         fprintf(o, "      )\n");
         fprintf(o, "    )\n");
         fprintf(o, "  )\n");
      }
      void            edges(int sides, float radius, int dir)
      {
         radius /= cos(M_PI * 2 * 0.5 / sides);
         for (int i = 0; i <= sides; i++)
            fprintf(o, "        (xy %.2f %.2f)\n", (float)x - (float)radius * sin(M_PI * 2 * (0.5 + i * dir) / sides), (float)y + (float)radius * cos(M_PI * 2 * (0.5 + i * dir) / sides));
      }
      if              (netgnd)
      {
         if (netvcc)
         {
            start(netgnd, gnd, "B.Cu");
            edges(edge, width / 2, 1);
            stop();
         }
                         start(netgnd, gnd, "F.Cu");
         edges(edge, width / 2, 1);
         if (netvcc)
            edges(leds * 8, radius + clearance / 2, -1);
         stop();
         if (netvcc)
         {
            start(netvcc, vcc, "F.Cu");
            edges(leds * 8, radius - clearance / 2, 1);
            edges(leds * 8, radius - 4 + clearance / 2, -1);
            stop();
            start(netgnd, gnd, "F.Cu");
            edges(leds * 8, radius - 4 - clearance / 2, -1);
            stop();
         }
      }
   }
   void            addtracks(int x, int y)
   {
      float           s = radius * 2 * M_PI / leds - ledx * 2;
      for             (int i = 1; i < leds; i++)
      {
         float           lx = 0,
                         ly = 0;
         void            segment(int i, float nx, float ny, float mx, float my)
         {
            float           Nx = (float)x - (float)(radius + ny) * sin(M_PI * 2 * i / leds + nx / radius);
            float           Ny = (float)y + (float)(radius + ny) * cos(M_PI * 2 * i / leds + nx / radius);
            if              (lx || ly)
            {
               fprintf(o, "  (%s ", isnan(mx) ? "segment" : "arc");
               fprintf(o, "(start %.2f %.2f) ", lx, ly);
               if (!isnan(mx))
               {
                  float           Mx = (float)x - (float)(radius + my) * sin(M_PI * 2 * i / leds + mx / radius);
                  float           My = (float)y + (float)(radius + my) * cos(M_PI * 2 * i / leds + mx / radius);
                                  fprintf(o, "(mid %.2f %.2f) ", Mx, My);
               }
                               fprintf(o, "(end %.2f %.2f) ", Nx, Ny);
                               fprintf(o, "(width 0.25) (layer \"F.Cu\") (net %d))\n", netled[i]);
            }
                            lx = Nx;
            ly = Ny;
         }
         segment(i, -ledx, -ledy, NAN, NAN);
         segment(i, -1 - ledx, 0, -ledx - 0.3, -ledy * 0.3);
         segment(i, 1 - s - ledx, 0, -s / 2 - ledx, 0);
         segment(i - 1, ledx, ledy, ledx + 0.3, ledy * 0.3);
      }
   }

   addzones(cx - width / 2 - 1, cy, netgnd, zonegnd, 0, NULL);
   addborder(cx - width / 2 - 1, cy, 0);
   if (hole)
      addleds(cx - width / 2 - 1, cy, 0, 0, 180, "H", hole, 1);
   addborder(cx + width / 2 + 1, cy, notch);
   if (led)
      addleds(cx + width / 2 + 1, cy, 0, 0, 270, "D", led, 1);
   if (cap)
   {
      addleds(cx + width / 2 + 1, cy, -ledw / 2 - 1, 0, 270, "C", cap, 1);
      addleds(cx + width / 2 + 1, cy, +ledw / 2 + 1, 0, 270, "C", cap, 1 + leds);
   }
   addzones(cx + width / 2 + 1, cy, netgnd2, zonegnd2, netvcc, zonevcc);
   addtracks(cx + width / 2 + 1, cy);

   fprintf(o, ")\n");
   fclose(i);
   fclose(o);
   if (rename(temp, filename))
   {
      unlink(temp);
      err(1, "Cannot overwrite: %s", filename);
   }
}
