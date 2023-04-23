// Text block and time

#include "app.h"
#include "chars.h"

static const char *
showtext (app_t * a, const char *data)
{
   uint8_t flip = 0;
   uint8_t h = a->height;
   if (a->height < 0)
   {
      h = -a->height;
      flip = 1;
   }
   uint8_t w = a->len / h;      // Width
   if (!w)
      return "No space";
   // TODO control characters - special colours
   // TODO stage and step for chars and pixels maybe so we can do proportional spaced?
   // Where to start in text...
   {
      int c = a->stage / 6;     // Whole to skip
      while (c && *data)
      {
         c--;
         data++;
         while ((*data & 0xC0) == 0x80)
            data++;             // Unicode
      }
   }
   uint8_t l = 255;
   if (a->limit && a->limit - a->cycle < a->fade)
      l = 255 * (a->limit - a->cycle + 1) / a->fade;
   else if (a->fade && a->cycle < a->fade)
      l = 255 * (a->cycle + 1) / a->fade;
   int c = -(a->stage % 6);     // Column
   while (c < w)
   {
      char t[5],
       *o = t;
      if (*data)
      {
         *o++ = *data++;
         while (o < t + sizeof (t) - 1 && (*data & 0xC0) == 0x80)
            *o++ = *data++;
      }
      *o = 0;
      int i = 0;
      if (*t)
         for (i = 0; i < sizeof (chars) / sizeof (*chars); i++)
            if (!strcmp (chars[i].c, t))
               break;
      if (i == sizeof (chars) / sizeof (*chars))
         i = 0;                 // Space
      for (int x = 0; x < 6; x++)
      {
         if (c >= 0 && c < w)
         {
            if ((c ^ flip) & 1)
               for (int y = 0; y < h; y++)
                  setl (a->start + c * h + y, a, y < 8 ? chars[i].b[y] & (0x80 >> x) ? l : 0 : 0);
            else
               for (int y = 0; y < h; y++)
                  setl (a->start + c * h + h - 1 - y, a, y < 8 ? chars[i].b[y] & (0x80 >> x) ? l : 0 : 0);
         }
         c++;
      }
   }
   if (*data)
      a->stage++;
   else
      a->stage = 0;
   return NULL;
}

const char *
apptime (app_t * a)
{
   if (!a->cycle)
   {
      if (!a->colourset)
         a->cycling = 1;
   }
   char temp[6];
   time_t now = time (0);
   struct tm tm;
   localtime_r (&now, &tm);
   snprintf (temp, sizeof (temp), "%02d:%02d", tm.tm_hour, tm.tm_min);
   return showtext (a, temp);
}

const char *
apptext (app_t * a)
{
   if (!a->cycle)
   {
      if (!a->data)
         return "No data";
      if (!a->colourset)
         a->cycling = 1;
   }
   return showtext (a, (const char *) a->data);
}
