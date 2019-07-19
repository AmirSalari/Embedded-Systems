#include "mbed.h"
DigitalIn switchOn(PTD3);
DigitalOut LedDig(PTD2);
int step=-1;
bool s = false;
int main()
{
    LedDig=0;
    step = 3;
    while(true)
    {
      if(switchOn == false){
          s=true;
          if(step==0){
            step=1;
          }
          else if(step==1){
              step=2;
          }else if(step==2){
              step=3;
          }else if(step==3){
              step=4;
          }else if(step==4){
              step=5;
          }else if(step==5){
              step=-1;
          }else if(step==-1){
              step=0;
          }
          wait(0.2);
      }
      if(s == true){
        if(step == 0){
            LedDig = 1;
            wait(0.002);
            LedDig = 0;
            wait(0.008);   
        }
        if(step == 1){
            LedDig = 1;
            wait(0.004);
            LedDig = 0;
            wait(0.006);   
        }
        if(step == 2){
            LedDig = 1;
            wait(0.006);
            LedDig = 0;
            wait(0.004);   
        }
        if(step == 3){
            LedDig = 1;
            wait(0.008);
            LedDig = 0;
            wait(0.002);   
        }
        if(step == 4){
            LedDig = 1;
            wait(0.01);   
        }
        if(step == 5){
            LedDig = 0;
            wait(0.01);   
        }
      }
   }
}