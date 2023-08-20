// The list of apps

#ifndef	a
#define	a(n,d)
#endif
#ifndef	r
#define	r(n,d) a(n,d)
#endif
#ifndef	t
#define	t(n,d) a(n,d)
#endif

a (idle, Idle)                  //
   a (pulse, Pulse)             //
   a (cylon, Cylon)             //
   a (countdown, Countdown)     //
   a (random, Random)           //
   a (twinkle, Twinkle)         //
   r (clock, Clock face)        //
   r (stargate, Stargate dialling)
   //
   r (spin, Spin)               //
   r (lava, Lava Lamp)          //
   t (text, Text)               //
   t (kern, Text (kerned))      //
   t (time, Text time)          //
#undef a
#undef r
#undef t
