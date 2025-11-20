// Text block and time

// TODO use config JSON for settings including height, direction, etc

#include "app.h"
#include "chars.h"

static const char *
showtext (app_t *a, const char *data, uint8_t dokern)
{
   // stage is character position - number of characters to skip
   // pos is pixel position - number of pixels off left to skip
   int32_t h = textheight;
   if (!h)
      return "No height";
   int32_t w = (a->len + h - 1) / h;    // Width
   if (!w)
      return "No space";
   int s = (a->speed / 6 ? : 1);        // this is number of steps for each speed seconds. We want to go faster by the character width basis
   // h is pixels high
   // w is pixels wide
   {
      int c = a->stage;         // Whole characters to skip for where we are (stage)
      while (c && *data)
      {
         c--;
         data++;
         while ((*data & 0xC0) == 0x80)
            data++;             // Unicode
      }
   }
   uint8_t l = a->fader;
   unsigned char k[8];
   memset (k, 0xFE, 8);         // Previous character - stretched
   int32_t c = -(int) a->step / s;      // Column, starts off left
   uint32_t pos = 0;            // character pos relative to this (stage) character
   while (c < w && *data)
   {
      char t[5],
       *o = t;
      // Next (UTF-8) char
      *o++ = *data++;
      while (o < t + sizeof (t) - 1 && (*data & 0xC0) == 0x80)
         *o++ = *data++;
      *o = 0;
      int i = 0;
      if (*t)
         for (i = 0; i < sizeof (chars) / sizeof (*chars); i++)
            if (!strcmp (chars[i].c, t))
               break;
      if (i == sizeof (chars) / sizeof (*chars))
      {                         // Unknown character
         if (c < 0)
            a->stage++;         // Skip
         continue;
      }
      if (dokern)
      {                         // Kerning calc
         unsigned char k2[8];   // This character, stretched
         if (!i)
            memset (k2, 0xFC, 8);       // Space 4 pixels
         else if (dokern == 2)
            memset (k2, strchr (".:|", *t) ? 0x78 : 0xFE, 8);   // Thin or full
         else
         {
            unsigned char k3[8];
            for (int y = 0; y < 8; y++)
               k3[y] = ((chars[i].b[y]) | (chars[i].b[y] >> 1) | (chars[i].b[y] >> 2));
            k2[0] = (k3[0] | k3[1]);
            for (int y = 1; y < 7; y++)
               k2[y] = (k3[y - 1] | k3[y] | k3[y + 1]);
            k2[7] = (k3[6] | k3[7]);
         }
         if (i)
            for (int x = 6; x > 0; x--)
            {
               int y;
               for (y = 0; y < 8; y++)
                  if (((uint32_t) k[y] << x) & chars[i].b[y])
                     break;
               if (y < 8)
                  break;
               c--;
            }
         memcpy (k, k2, 8);
      }
      if (!c && pos == 1)
      {                         // First whole character is off left - this is where to start next character
         a->stage++;
         a->step = 0;
      }
      for (int x = 0; x < 6; x++)
      {
         if (c >= 0 && c < w)
         {
            if (textsnake ? ((c ^ textflip) & 1) : !textflip)
               for (int y = 0; y < h; y++)
               {                // Up
                  if (y < 8 && chars[i].b[y] & (0x80 >> x))
                     setl (a->start + c * h + y, a, c * h + y, a->len, l);
            } else
            {                   // Down
               for (int y = 0; y < h; y++)
                  if (y < 8 && chars[i].b[y] & (0x80 >> x))
                     setl (a->start + c * h + h - 1 - y, a, c * h + y, a->len, l);
            }
         }
         c++;
      }
      pos++;
   }
   if (c <= w && !*data)
   {                            // Back to start
      a->stage = 0;
      a->step = 0;
   } else
      a->step++;                // Scroll
   return NULL;
}

const char *
apptime (app_t *a)
{
   if (!textheight)
      return "No height";
   if (!a->cycle)
   {
      if (!a->colourset)
         setcolour (a, "cycling");
   }
   char temp[10];
   time_t now = time (0);
   struct tm tm;
   localtime_r (&now, &tm);
   if (a->len / textheight > 40)
      snprintf (temp, sizeof (temp), "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
   else
      snprintf (temp, sizeof (temp), "%02d:%02d", tm.tm_hour, tm.tm_min);
   for (char *p = temp; *p; p++)
      if (*p == '0')
         *p = 'O';              // nicer for a clock - later we must add choice of zeros as an option
   return showtext (a, temp, 2);
}

const char *
apptext (app_t *a)
{
   if (!a->cycle)
   {
      if (!a->data)
         return "No data";
      if (!a->colourset)
         setcolour (a, "cycling");
   }
   return showtext (a, (const char *) a->data, 0);
}

const char *
appkern (app_t *a)
{
   if (!a->cycle)
   {
      if (!a->data)
         return "No data";
      if (!a->colourset)
         setcolour (a, "cycling");
   }
   return showtext (a, (const char *) a->data, 1);
}
