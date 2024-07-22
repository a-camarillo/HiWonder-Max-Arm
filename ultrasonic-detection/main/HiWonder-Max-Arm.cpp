#include "Arduino.h"
#include "ESPMax.h"
#include "Buzzer.h"
#include "TM1640.h"
#include "Ultrasound.h"
#include "SuctionNozzle.h"
#include "ESP32PWMServo.h"
#include "_espmax.h"

float distance;
int i;
uint16_t r;
uint16_t g;
uint16_t b;

TM1640 display(32, 33);
Ultrasound ultrasound;

extern "C" void app_main(void)
{
  initArduino();
  ESPMax_init();
  Buzzer_init();
  Nozzle_init();
  PWMServo_init();
  Valve_on();
  go_home(2000);
  delay(2000);
  SetPWMServo(1, 1500, 1000);
  Valve_off();
  Serial.begin(115200);
  ultrasound.Breathing(30, 50, 60, 20, 30, 50); // 发光超声波模块幻彩模式
  while(!Serial) {
    ;
  }
  Serial.println("start...");

  while(true) {
      // define position variables
      float pos[3];
      char text[6];
      int distance = 0;
      for(int i=0; i<5; i++){
        distance += ultrasound.GetDistance();
        delay(200);
      }
      int dis = int(distance/5);
      Serial.println(dis);
      display.setDisplayToDecNumber(dis, 4);
      if((60 < dis) & (dis < 80)) {
        setBuzzer(100);
        pos[0] = 0; pos[1] = -160;pos[2] = 100;
        set_position(pos, 1600);
        delay(1500);
        pos[0] = 0; pos[1] = -160;pos[2] = 85;
        set_position(pos, 800);
        Pump_on();
        delay(1000);
        pos[0] = 0;pos[1] = -160;pos[2] = 200;
        set_position(pos,1000);  //机械臂抬起来
        delay(1000);
        pos[0] = 70;pos[1] = -150;pos[2] = 200;
        set_position(pos,800);   //到放置区上方
        delay(800);
        SetPWMServo(1, 2200, 500);
        delay(200);
        pos[0] = 70;pos[1] = -150;pos[2] = 90;
        set_position(pos,800);   //到放置区
        delay(800);
        pos[0] = 130;pos[1] = -150;pos[2] = 88;
        set_position(pos,500);   //向左推一下
        delay(500);
        Valve_on();   //关闭气泵，打开电磁阀
        pos[0] = 130;pos[1] = -150;pos[2] = 200;
        set_position(pos,1000);  //机械臂抬起来
        delay(1000);
        Valve_off();   //关闭电磁阀
        go_home(1500); //机械臂复位
        delay(200);
        SetPWMServo(1, 1500, 500);
        delay(1500);
      }
    }
}
