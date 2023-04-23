// Text block and time

#include "app.h"
#include "chars.h"

static void
showtext (app_t * a, const char *data)
{

}

const char *
apptime (app_t * a)
{
   char temp[6];
   time_t now = time (0);
   struct tm tm;
   localtime_r (&now, &tm);
   snprintf (temp, sizeof (temp), "%02d:%02d", tm.tm_hour, tm.tm_min);
   showtext (a, temp);
   return NULL;
}

const char *
apptext (app_t * a)
{
   if (!a->cycle)
   {
      if (!a->data)
         return "No data";
   }
   showtext (a, (const char *) a->data);
   return NULL;
}
