#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "time_interval.h"

tmi D, T;
int pitch     =  0 ;
char key      =  0 ;
char buf[256] = {0};

char getKeyboard(void)
{
  if(kbhit()){ return getch(); } return 0x20;
}

void isrTimer(void)
{
  if(!pitch){
    printf(" Using: <%s>",buf);
  }else{
    printf(" Using pitch of: <%d>",pitch);
  }
}

int main(int argc, char** argv)
{
  TIME_INTERVAL argi[3] = {0};
  if(argc > 1){
    printf("\nargc = %d",argc);
    for(int i = 1; ((i < 4) && (i < argc)); i++)
    {
      argi[i-1] = (TIME_INTERVAL)atoi(argv[i]);
      printf("\nargv[%d] = <%s> #%u",i,argv[i],argi[i-1]);
    }
  }

  printf("\nAlarm type: "); gets(buf);

  pitch = atoi(buf);
  if(pitch){
    sscanf(buf,"%d %u %u %u",&pitch,&argi[0],&argi[1],&argi[2]);
  }

  D.Set(argi[0],argi[1],argi[2]);

  T.Set(D);
  T.setHook(isrTimer);

  while(27 != (key = getKeyboard()))
  {
    T.Normalize().Tick().Decrement();
    if(T.isPassed()){ T.callHook().Set(D); }
    T.Print(key);
  }
  return EXIT_SUCCESS;
}
