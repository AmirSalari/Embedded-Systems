#include "mbed.h"
PwmOut PwmLed (PTD2);
DigitalIn switchOn(PTD3);
int step = 0;
bool switch_check = false;
int main()
{
    PwmLed.period(0.01);PwmLed=0.0;
    while(true)
    {
      if(switchOn==false){
		  switch_check = true;
		  wait(0.4);
	  }
      if(switch_check == true){
        if(step==5){
            step=0;
            PwmLed=0;
        }
        else{
            step++;
            PwmLed = 0.2 * step;        
        }
		switch_check = false;
     }
   }
}
