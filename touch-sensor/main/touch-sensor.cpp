#include "Arduino.h"
#include "ESPMax.h"
#include "Buzzer.h"
#include "SuctionNozzle.h"
#include "ESP32PWMServo.h"
#include "LobotSerialServoControl.h"
#include "esp32-hal-gpio.h"

#define sensor_pin 23

extern "C" void app_main(void)
{
  // initialize libraries
  Buzzer_init();
  ESPMax_init();
  Nozzle_init();
  PWMServo_init();
  pinMode(sensor_pin, INPUT_PULLUP);
  setBuzzer(100);
  go_home(2000);
  SetPWMServo(1, 1500, 2000);
  Serial.begin(115200);
  
  int num = 0;
  int angle_pul[3] = {1800, 2000, 2200};
  while(true) {
    float pos[3];

    float sensor_state = 0.0;
    for(int i=0;i<3;i++) {
      sensor_state += digitalRead(sensor_pin);
      delay(20);
    }
    if(sensor_state == 0.0){ // pin set to low when touch sensor detects a target
      Serial.print("num: ");
      Serial.println(num+1);
      setBuzzer(100);
      pos[0] = 0; pos[1] = -160; pos[2] = 100;
      set_position(pos, 1500);
      delay(1500);
      pos[0] = 0; pos[1] = -160; pos[2] = 85;
      set_position(pos, 800);
      Pump_on();
      delay(1000);
      pos[0] = 120;pos[1] = (-20-60*num);pos[2] = 180;
      set_position(pos, 1500);
      Serial.println(angle_pul[num]);
      delay(100);
      SetPWMServo(1, angle_pul[num], 1000);
      delay(500);
      pos[0] = 120; pos[1] = (-20-60*num);pos[2] = (83+num);
      set_position(pos, 1000);
      delay(1200);
      Valve_on();
      pos[0] = 120;pos[1] = (-20-60*num);pos[2] = 200;
      delay(1000);
      Valve_off();
      go_home(1500);
      delay(100);
      SetPWMServo(1, 1500, 1500);
      num += 1;
      if(num >= 3) {
        num = 0;
        setBuzzer(100);
        delay(100);
        setBuzzer(100);
      }
    }
    else {
      delay(100);
    } 
  }
}
