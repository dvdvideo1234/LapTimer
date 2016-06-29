#if !defined _TIME_INTERVAL_H_

  #define _TIME_INTERVAL_H_

  typedef class time_interval
  {
    protected:
       int clk;
       int h;
       int m;
       int s;
      void (*hook)(void);
    public:
       char isPassed(void){ return (s==0 && m==0 && h==0); }
      class time_interval& Set(class time_interval &o){ s = o.s; m = o.m; h = o.h; return *this; }
      class time_interval& Set(class time_interval *o){ if(o != NULL){ s = o->s; m = o->m; h = o->h; } return *this; }
      class time_interval& Set(int as, int am, int ah){ s = as; m = am; h = ah; return *this; }
            time_interval(int as, int am, int ah){ Set(as,am,ah); clk = CLOCKS_PER_SEC; }
            time_interval(int as, int am){ Set(as,am,0); clk = CLOCKS_PER_SEC; }
            time_interval(int as){ Set(as,0,0); clk = CLOCKS_PER_SEC; }
            time_interval(void){ Set(0,0,0); clk = CLOCKS_PER_SEC; }
           ~time_interval(){}
      class time_interval& Reset(){ Set(0,0,0); return *this; }
      class time_interval& setS(int as){ s = as; return *this; }
      class time_interval& setM(int am){ m = am; return *this; }
      class time_interval& setH(int ah){ h = ah; return *this; }
              unsigned int getS(void){ return s; }
              unsigned int getM(void){ return m; }
              unsigned int getH(void){ return h; }
      class time_interval& setHook(void (*foo)(void)){ hook = foo; return *this; }
      class time_interval& callHook(void){ (*hook)(); return *this; };
      class time_interval& setTickRate(int cy){ if(cy > 0){ clk = cy; } return *this; };
              unsigned int getTickRate(void){ return clk; };
      class time_interval& Normalize(void);
      class time_interval& Decrement(void){ if(s > 0){ s--; } return *this; }
      class time_interval& Print(void){ printf("Diff(%d): %15d, %15d, %15d\n",clk,s,m,h); return *this; };
      class time_interval& TickSecond(void);
      class time_interval& Tick(void);
  } tmi;

  tmi& time_interval::Normalize(void)
  {
    if(!m && h > 0){ m = 60; h--; }
    if(!s && m > 0){ s = 60; m--; }
    return *this;
  }

  tmi& time_interval::Tick()
  {
    clock_t next = clock() + clk;
    while(clock() < next);
    return *this;
  }

  tmi& time_interval::TickSecond(void)
  {
    clock_t next = clock() + CLOCKS_PER_SEC;
    while(clock() < next);
    return *this;
  }

#endif
