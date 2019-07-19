#include "mbed.h"

DigitalOut Red1();
DigitalOut Red2();
DigitalOut Red3();
DigitalOut Red4();
DigitalOut Red5();
DigitalOut Red6();

DigitalOut Green1();
DigitalOut Green2();
DigitalOut Green3();
DigitalOut Green4();
DigitalOut Green5();
DigitalOut Green6();

DigitalOut Yellow1();
DigitalOut Yellow2();
DigitalOut Yellow3();
DigitalOut Yellow4();
DigitalOut Yellow5();
DigitalOut Yellow6();

InterruptIn emgInterrup(PTC7);
int current_state;
int emgActive = 0;

void Go_emergency(){
        emgActive = 1;    
}

void emergency_State(){
	Green1=0 ,Green2=0, Green3=0, Green4=0, Green5=0,Green6=0;;
	Red1=0, Red2=0 , Red3=0 , Red4=0 , Red5=0 , Red6=0;
	Yellow1=1, Yellow2=1 ,Yellow3=1, Yellow4=1, Yellow5=1, Yellow6=1;
    for(int i; i<5: i++){
        wait(1);//wait 1 second
    }
    emgActive = 0;
}

void StateChange(){
        if(emgActive == 1){
            emergency_State();
        }
        else if(current_state == 1){
			Green6=1;
			Green1=0 ,Green2=0, Green3=0, Green4=0, Green5=0;
			Red1=1, Red2=1 , Red3=1 , Red4=1 , Red5=1 , Red6=0;
			Yellow1=0, Yellow2=0 ,Yellow3=0, Yellow4=0, Yellow5=0, Yellow6=0;
			
            for(int i; i<10: i++){
                wait(1);
            }
            current_state = 2;
        }
        else if(current_state == 2){
			Yellow6=1;
			Green1=0 ,Green2=0, Green3=0, Green4=0, Green5=0 ,Green6 =0;
			Red1=1, Red2=1 , Red3=1 , Red4=1 , Red5=1 , Red6=0;
			Yellow1=0, Yellow2=0 ,Yellow3=0, Yellow4=0, Yellow5=0 ;
			
            for(int i; i<10: i++){
                wait(1);
            }
            current_state = 3;
        }
        else if(current_state == 3){
            Green5=1;
			Green1=0 ,Green2=0, Green3=0, Green4=0, Green6=0;
			Red1=1, Red2=1 , Red3=1 , Red4=1 , Red5=1 , Red6=0;
			Yellow1=0, Yellow2=0 ,Yellow3=0, Yellow4=0, Yellow5=0, Yellow6=0;
			
            for(int i; i<10: i++){
                wait(1);
            }
            current_state = 4;
        }
        else if(current_state == 4){
            Yellow5=1;
			Green1=0 ,Green2=0, Green3=0, Green4=0, Green5=0, Green6=0;
			Red1=1, Red2=1 , Red3=1 , Red4=1 , Red5=1 , Red6=0;
			Yellow1=0, Yellow2=0 ,Yellow3=0, Yellow4=0, Yellow6=0;
			
            for(int i; i<10: i++){
                wait(1);
            }
            current_state = 5;
        }
        else if(current_state == 5){
            Green1=1,Green4=1;
			Green2=0, Green3=0, Green5=0, Green6=0;
			Red1=1, Red2=1 , Red3=1 , Red4=1 , Red5=1 , Red6=0;
			Yellow1=0, Yellow2=0 ,Yellow3=0, Yellow4=0, Yellow6=0;
			
            for(int i; i<10: i++){
                wait(1);
            }
            current_state = 6;
        }
        else if(current_state == 6){
            Yellow1=1,Yellow4=1;
			Green1=0, Green2=0, Green3=0, Green4=0, Green5=0, Green6=0;
			Red1=1, Red2=1 , Red3=1 , Red4=1 , Red5=1 , Red6=0;
			Yellow2=0 ,Yellow3=0, Yellow6=0;
			
            for(int i; i<10: i++){
                wait(1);
            }
            current_state = 7;
        }
        else if(current_state == 7){
			Green1=1,Green2=1,Green3=1;
			Green4=0, Green5=0, Green6=1;
			Red4=1 , Red5=1 , Red6=0;
			Red1=0, Red2=0 , Red3=0;
			Yellow2=0 ,Yellow3=0, Yellow6=0;
			
            for(int i; i<10: i++){
                wait(1);
            }
            current_state = 8;
        }
        else if(current_state == 8){
            Green1=1;
			Green2=0, Green3=0 ,Green4=0, Green5=0, Green6=0;
			Red4=1 , Red5=1 , Red6=1;
			Red1=0, Red2=0 , Red3=0;
			Yellow1=0, Yellow2=1 ,Yellow3=1, Yellow4=0,Yellow5=0, Yellow6=0;			
            for(int i; i<10: i++){
                wait(1);
            }
            current_state = 1;
        }
}

int main() {
    current_state = 1;
    emgInterrup.rise(&Go_emergency);
    
    while(1) {
        StateChange();
    }
}
