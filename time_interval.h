#if !defined _TIME_INTERVAL_H_
  #include <time.h>
  #define _TIME_INTERVAL_H_
  #define TIME_INTERVAL unsigned int
  typedef class time_interval
  {
    protected:
       TIME_INTERVAL clk;
       TIME_INTERVAL h;
       TIME_INTERVAL m;
       TIME_INTERVAL s;
       void (*hook)(void);
    public:
       char isPassed(void){ return (s==0 && m==0 && h==0); };
      class time_interval& Set(class time_interval &o){ s = o.s; m = o.m; h = o.h; return *this; };
      class time_interval& Set(class time_interval *o){ if(o != NULL){ s = o->s; m = o->m; h = o->h; } return *this; };
      class time_interval& Set(TIME_INTERVAL as, TIME_INTERVAL am, TIME_INTERVAL ah){ s = as; m = am; h = ah; return *this; };
            time_interval(TIME_INTERVAL as, TIME_INTERVAL am, TIME_INTERVAL ah){ Set(as,am,ah); clk = CLOCKS_PER_SEC; };
            time_interval(TIME_INTERVAL as, TIME_INTERVAL am){ Set(as,am,0); clk = CLOCKS_PER_SEC; };
            time_interval(TIME_INTERVAL as){ Set(as,0,0); clk = CLOCKS_PER_SEC; };
            time_interval(void){ Set(0,0,0); clk = CLOCKS_PER_SEC; };
           ~time_interval(){};
      class time_interval& Wait(clock_t next){ while(clock() < next); return *this; };
      class time_interval& Reset(){ Set(0,0,0); return *this; }
      class time_interval& setS(TIME_INTERVAL as){ s = as; return *this; }
      class time_interval& setM(TIME_INTERVAL am){ m = am; return *this; }
      class time_interval& setH(TIME_INTERVAL ah){ h = ah; return *this; }
            TIME_INTERVAL  getS(void){ return s; }
            TIME_INTERVAL  getM(void){ return m; }
            TIME_INTERVAL  getH(void){ return h; }
      class time_interval& setHook(void (*foo)(void)){ hook = foo;   return *this; }
      class time_interval& callHook(void){ if((*hook)){ (*hook)(); } return *this; };
      class time_interval& setTickRate(TIME_INTERVAL cy){ clk = cy;  return *this; };
      class time_interval& deltaTickRate(int dcy);
            TIME_INTERVAL  getTickRate(void){ return clk; };
      class time_interval& Normalize(void);
      class time_interval& Decrement(void){ if(s > 0){ s--; } return *this; }
      class time_interval& Print(void){ printf("\nTime(%u): %5u, %5u, %5u",clk,s,m,h); return *this; };
      class time_interval& Print(char c){ printf("\nTime(%u)[%c]: %5u, %5u, %5u",clk,c,s,m,h); return *this; };
      class time_interval& Print(char *str){ printf("\nTime(%u)[%s]: %5u, %5u, %5u",clk,str,s,m,h); return *this; };
      class time_interval& TickSecond(void){ return Wait(clock() + CLOCKS_PER_SEC); }
      class time_interval& TickSecond(TIME_INTERVAL s){ return Wait(clock() + (s * CLOCKS_PER_SEC)); }
      class time_interval& Tick(void){ return Wait(clock() + clk); }
  } tmi;

  tmi& time_interval::Normalize(void)
  {
    if(!m && h){ m = 60; h--; }
    if(!s && m){ s = 60; m--; }
    return *this;
  }

  tmi& time_interval::deltaTickRate(int dcy)
  {
    if((dcy > 0) && (clk + dcy) < clk){ return *this; }
    if((dcy < 0) && (clk + dcy) > clk){ return *this; }
    return setTickRate(clk + dcy);
  }

#endif
