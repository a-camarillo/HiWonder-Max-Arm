#include "ESP32PWMServo.h"

Servo servo1;
Servo servo2;
static const int servo1Pin = 15;
static const int servo2Pin = 4;

int status = 0;
int init_pulse[2] = {500,500};

void PWMServo_init(){
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);
}

void SetPWMServo(int id, int pul, int duration){
    if((0 < id) & (id < 3)){
        if(pul < 500) pul = 500;
        if(pul > 2500) pul = 2500;
        if(status == 0){
            int pulse = init_pulse[id-1];
            int value = pul - pulse;
            int degree = duration / 20;
            int d = value / degree;
            for(int count=0; count<int(degree); count++){            
                pulse = int(pulse + d);
                Serial.println(pulse);
                if(id == 1)servo1.writeMicroseconds(pulse);    // Output PWM
                else if(id == 2)servo2.writeMicroseconds(pulse); // Output PWM
                delay(20);
            }
            init_pulse[id-1] = pul;
        }  
        else{
            if(id == 1)servo1.writeMicroseconds(pul); // Output PWM
            else if(id == 2)servo2.writeMicroseconds(pul); // Output PWM
            init_pulse[id-1] = pul;
            status = 1;
        }
    }
}
