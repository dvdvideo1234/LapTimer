#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "time_interval.h"

tmi D, T;

void isrTimer(void)
{
  printf("[%5d]This ia a test\n",T.getTickRate());
}

int main()
{
  char key;
  unsigned int cy = 50;
  D.Set(5,0,0);

  T.Set(D);
  T.setHook(isrTimer);
  T.setTickRate(cy);

  while(42)
  {
    if ( kbhit() ){ key = getch(); }
    switch(key)
    {
      case 'l':
      {
        cy++;
        T.setTickRate(cy); break;
      }
      case 'k':
      {
        cy--;
        T.setTickRate(cy); break;
      }
    }
    T.Normalize().Decrement().Tick();
    if(T.isPassed())
    {
      T.callHook().Set(D);
    }
    key = 'x';
  }
  return 0;
}
