// The list of apps

#ifndef	a
#define	a(n,d)                  // App
#endif
#ifndef	r
#define	r(n,d) a(n,d)           // Ring
#endif
#ifndef	t
#define	t(n,d) a(n,d)           // Text
#endif
#ifndef	s
#define	s(n,d) a(n,d)           // Sound
#endif

//
a (idle, Idle)                  //
   a (pulse, Pulse)             //
   a (bargraph, Bargraph)       //
   a (cylon, Cylon)             //
   a (countdown, Countdown)     //
   a (random, Random)           //
   a (twinkle, Twinkle)         //
   a (neenaw, Nee Naw)          //
   // Sound
   s (audio, Audio experimental)//
   // Ring/loop
   r (clock, Clock face)        //
   r (stargate, Stargate dialling)
                                //
   r (endtest, End Test)        //
   r (spin, Spin)               //
   r (lava, Lava Lamp)          //
   // Text
   t (text, Text)               //
   t (kern, Text (kerned))      //
   t (time, Text time)          //
#undef a
#undef r
#undef t
#undef s
