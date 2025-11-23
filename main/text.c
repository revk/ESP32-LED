// Text block and time

// TODO use config JSON for settings including direction, etc

#include "app.h"
#include "chars.h"

static const char *
showtext (app_t *a, const char *data, uint8_t dokern)
{
   // stage is character position - number of characters to skip
   // pos is pixel position - number of pixels off left to skip
   int32_t h = textheight ? : gridheight;
   if (!h || !gridheight)
      return "No height";
   int32_t w = (a->len + h - 1) / gridheight;   // Width
   if (!w)
      return "No space";
   int s = (a->speed / 6 ? : 1);        // this is number of steps for each speed seconds. We want to go faster by the character width basis
   // h is pixels high
   // w is pixels wide
   uint8_t l = a->fader;
   unsigned char k[CHARH];
   memset (k, 0xFE, CHARH);     // Previous character - stretched
   int32_t c = -(a->step / s);  // Column, starts off left
   const char *d = data + a->stage;
   while (c < w && *d)
   {
      char t[5],
       *o = t;
      // Next (UTF-8) char
      *o++ = *d++;
      while (o < t + sizeof (t) - 1 && (*d & 0xC0) == 0x80)
         *o++ = *d++;
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
      uint8_t b[CHARH];
      memcpy (b, chars[i].b, CHARH);
      if (h < CHARH)
      {                         // pack to smaller
         int y = CHARH - 1;
         int p = CHARH - h;
         while (y && p && !b[y])
         {                      // Blank at end
            p--;
            y--;
         }
         while (y && p)
         {                      // Pack duplicates until in space if possible
            y--;
            if (b[y] != b[y + 1])
               continue;
            p--;
            memmove (b + y, b + y + 1, CHARH - y - 1);
            b[CHARH - 1] = 0;
         }
         while (p && !b[0])
         {                      // Blank at top
            p--;
            memmove (b, b + 1, CHARH - 1);
            b[CHARH - 1] = 0;
         }
      }
      uint8_t offset = 0;       // left offset
      if (dokern)
      {                         // Kerning calc
         unsigned char k2[CHARH];       // This character, stretched
         if (!i)
            memset (k2, 0xFC, CHARH);   // Space 4 pixels
         else if (dokern == 2)
         {
            if (strchr (".:|", *t))
               memset (k2, 0x38, CHARH);
            else
               memset (k2, 0xFE, CHARH);
         } else
         {
            unsigned char k3[CHARH];
            for (int y = 0; y < CHARH; y++)
               k3[y] = ((b[y]) | (b[y] >> 1) | (b[y] >> 2));
            k2[0] = (k3[0] | k3[1]);
            for (int y = 1; y < CHARH - 1; y++)
               k2[y] = (k3[y - 1] | k3[y] | k3[y + 1]);
            k2[CHARH - 1] = (k3[CHARH - 2] | k3[CHARH - 1]);
         }
         // Shift left slotting to previous character for kerning
         for (int x = 6; x > 0; x--)
         {
            int y;
            for (y = 0; y < CHARH; y++)
               if (((uint32_t) k[y] << x) & k2[y])
                  break;
            if (y < CHARH)
               break;
            offset++;
         }
         memcpy (k, k2, CHARH);
      }
      c -= offset;
      if (!offset && c < -6 && !(a->step % s))
      {                         // Move on starting point, allowing for hidden character to get kerning in place, and pick a character with no offset
         a->step = (-c) * s;
         a->stage = d - data - strlen (t);
      }
      for (int x = 0; x < 6; x++)
      {
         if (c >= 0 && c < w)
         {
            if (gridsnake ? ((c ^ gridflip) & 1) : !gridflip)
               for (int y = 0; y < h; y++)
               {                // Up
                  if (y < CHARH && b[y] & (0x80 >> x))
                     setl (a->start + c * gridheight + y, a, c * gridheight + y, a->len, l);
            } else
            {                   // Down
               for (int y = 0; y < h; y++)
                  if (y < CHARH && b[y] & (0x80 >> x))
                     setl (a->start + c * gridheight + gridheight - 1 - y, a, c * gridheight + y, a->len, l);
            }
         }
         c++;
      }
   }
   if (c <= w + h && !*d)
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
   if (a->len / gridheight > 40)
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
