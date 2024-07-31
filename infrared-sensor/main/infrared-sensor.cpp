#include "Arduino.h"
#include "ESPMax.h"
#include "Buzzer.h"
#include "SuctionNozzle.h"
#include "ESP32PWMServo.h"
#include "LobotSerialServoControl.h"
#include "esp32-hal-gpio.h"
#include "esp32-hal.h"

// Single infrared sensor(control)
// #define sensor_pin 23

// Double infrared sensor(sorting)
#define infrared_left 23
#define infrared_right 32

extern "C" void app_main(void)
{
  // initialize libraries
  Buzzer_init();
  ESPMax_init();
  Nozzle_init();
  PWMServo_init();
  // single sensor setup
  // pinMode(sensor_pin, INPUT_PULLUP);
  
  // setup of dual sensors
  pinMode(infrared_left, INPUT_PULLUP);
  pinMode(infrared_right, INPUT_PULLUP);

  Serial.begin(115200);
  setBuzzer(100);
  go_home(2000);
  SetPWMServo(1, 1500, 2000);
  
  while(true) {
    float pos[3];
    
//  dual sensor
    float sensor_left = 0.0;
    float sensor_right = 0.0;

    for (int i = 0; i < 5; i++) {
      sensor_left += digitalRead(infrared_left);
      sensor_right += digitalRead(infrared_right);
      delay(50);
    }

    if (sensor_right == 0.0) {
      setBuzzer(100);
      pos[0] = 70;pos[1] = -165;pos[2] = 120;
      set_position(pos, 1500);
      delay(1500);
      pos[0] = 70;pos[1] = -165;pos[2] = 86;
      set_position(pos, 800);
      Pump_on();
      delay(1000);
      pos[0] = 70;pos[1] = -165;pos[2] = 200;
      set_position(pos, 1000);
      delay(1000);
      pos[0] = 150;pos[1] = -35;pos[2] = 200;
      set_position(pos, 800);
      delay(800);
      SetPWMServo(1, 1800, 500);
      delay(200);
      pos[0] = 150;pos[1] = -35;pos[2] = 90;
      set_position(pos, 800);
      delay(800);
      pos[0] = 150;pos[1] = 10;pos[2] = 88;
      set_position(pos, 500);
      delay(500);
      Valve_on();
      pos[0] = 150;pos[1] = 10;pos[2] = 200;
      set_position(pos, 1000);
      delay(1000);
      Valve_off();
      go_home(1500);
      delay(200);
      SetPWMServo(1, 1500, 500);
      delay(1500);
    }
    else if (sensor_left == 0.0) {
      setBuzzer(100);
      pos[0] = -70;pos[1] = -165;pos[2] = 120;
      set_position(pos, 1500);
      delay(1500);
      pos[0] = -70;pos[1] = -165;pos[2] = 86;
      set_position(pos, 800);
      Pump_on();
      delay(1000);
      pos[0] = -70;pos[1] = -165;pos[2] = 200;
      set_position(pos, 1000);
      delay(1000);
      pos[0] = -150;pos[1] = -35;pos[2] = 200;
      set_position(pos, 800);
      delay(800);
      SetPWMServo(1, 1200, 500);
      delay(200);
      pos[0] = -150;pos[1] = -35;pos[2] = 90;
      set_position(pos, 800);
      delay(800);
      pos[0] = -150;pos[1] = 10;pos[2] = 88;
      set_position(pos, 500);
      delay(500);
      Valve_on();
      pos[0] = -150;pos[1] = 10;pos[2] = 200;
      set_position(pos, 1000);
      delay(1000);
      Valve_off();
      go_home(1500);
      delay(200);
      SetPWMServo(1, 1500, 500);
      delay(1500);
    }
//  single sensor
//  float sensor_state = 0.0;
//  for(int i=0;i<5;i++) {
//  sensor_state += digitalRead(sensor_pin);
//  delay(50);
//  }
//  if(sensor_state == 0.0){ // pin set to low when infrared sensor detects a target
//  setBuzzer(100);
//  pos[0] = 0; pos[1] = -160; pos[2] = 100;
//  set_position(pos, 1500);
//  delay(1500);
//  pos[0] = 0; pos[1] = -160; pos[2] = 85;
//  set_position(pos, 800);
//  Pump_on();
//  delay(1000);
//  pos[0] = 70;pos[1] = -160;pos[2] = 200;
//  set_position(pos, 1000);
//  delay(1000);
//  pos[0] = 70;pos[1] = -150;pos[2] = 200;
//  set_position(pos, 800);
//  delay(800);
//  SetPWMServo(1, 2200, 500);
//  delay(200);
//  pos[0] = 70; pos[1] = -150;pos[2] = 90;
//  set_position(pos, 800);
//  delay(800);
//  pos[0] = 130; pos[1] = -150;pos[2] = 88;
//  set_position(pos, 500);
//  delay(500);
//  Valve_on();
//  pos[0] = 130;pos[1] = -150;pos[2] = 200;
//  set_position(pos, 1000);
//  delay(1000);
//  Valve_off();
//  go_home(1500);
//  delay(200);
//  SetPWMServo(1, 1500, 1500);
//  delay(1500);
//  } 
    else {
      delay(100);
    } 
  }
}
