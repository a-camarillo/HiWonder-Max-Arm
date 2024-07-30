#include "Buzzer.h"

int Buzzer_freq = 2500;   // frequency
int Buzzer_channel = 5;   // channel
int Buzzer_resolution = 10;   // resolution
const int Buzzer_Pin = 27; // pin

void Buzzer_init(){
    ledcAttach(Buzzer_Pin, Buzzer_channel, Buzzer_resolution);
}

void Buzzer_on(){
    ledcWrite(Buzzer_channel, 300);  // Output PWM
}

void Buzzer_off(){
    ledcWrite(Buzzer_channel, 0);
}

void setBuzzer(int s){
    Buzzer_on();
    delay(s);
    Buzzer_off();
}
