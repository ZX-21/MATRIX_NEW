#include <MatrixMiniR4.h>
int i;
int PWR_LY;  // Power for left joystick (LY axis)
int STR_LX;  // Steering for left joystick (LX axis)
int PWR_RY;  // Power for right joystick (RY axis)
int STR_RX;  // Steering for right joystick (RX axis)
#define head_Kp 1.8f
#define head_Kd 1.0f
#define head_Ki 0.0f
float head_error, head_pError, head_w, head_d, head_i;
float angle;
float angle2;
float angle3;
float angle4;

float previous_error = 0.0;
float integral = 0.0;
unsigned long previous_time = 0;
const float MIN_SPEED =22.0;

void setup() {
  MiniR4.begin();
  Serial.begin(115200);
  angle = 100;
  angle2 = 0;
  angle3 = 171;
  angle4 = 9;
  MiniR4.RC1.setAngle(angle);
  MiniR4.RC3.setAngle(angle2);
  MiniR4.Motion.resetIMUValues();
  //  delay(500);
  MiniR4.I2C1.MXLaser.begin();

  ////////////////////////////////////JOY
  MiniR4.PWR.setBattCell(2);
  MiniR4.M1.setReverse(true);   // กำหนดทิศทางของมอเตอร์ M1
  MiniR4.M2.setReverse(false);  // กำหนดทิศทางของมอเตอร์ M2
  MiniR4.M1.setSpeed(0);        // ตั้งความเร็วของมอเตอร์ M1 เป็น 0
  MiniR4.M2.setSpeed(0);        // ตั้งความเร็วของมอเตอร์ M2 เป็น 0
  MiniR4.PS2.read_gamepad(false, 0);
  delay(500);

  
  // angle = 80;
  // delay(700);


  //////////////////////////////////JOY
  // fwimu(); delay(1000);
  // rimu(); delay(1000);
  // fwimu(); delay(1000);
  // rimu(); delay(1000);
  // fwimu(); delay(1000);
  // rimu(); delay(1000);
  // fwimu(); delay(1000);
  // rimu(); delay(1000);
  // fwimu(); delay(1000);
  // rimu(); delay(1000);
  // fw();
  // delay(1000);
  // rr();




  // encordd(); delay(500);
  // backencordd(); delay(500);
  // encordd(); delay(500);
  // backencordd(); delay(500);
  // encordd(); delay(500);
  // backencordd(); delay(500);
  // encordd(); delay(500);
  // backencordd(); delay(500);
  // encordd(); delay(500);
  // backencordd(); delay(500);

  // square();
  //Tasksquare();
  //fw();delay(200);
  //rr();delay(200);
}
void loop() {


  //TaskI2CColor();
  // TaskGrayscale();
  //TaskPowerView();
  //fwimupid(5, 0.5, 1, 1);
  //TaskIMU();
  //heading(5, 0);
  //TaskIMU();
  //TaskI2CLaser();
  /////////////////////////////////////////////////JOYY
  ///*
 // อ่านข้อมูลจาก PS2 controller
  
  MiniR4.PS2.read_gamepad(false, 0);  // อ่านข้อมูลจาก PS2 controller

  if (MiniR4.PS2.Button(PSB_L2)) {
    if (angle > 6) {
      angle = angle + -3;
      delay(2);
    }
  }
  if (MiniR4.PS2.Button(PSB_L1)) {
   if (angle < 110) {
       angle = angle + 3;
      delay(2);
   }
   else {angle = 110;}
  }
  

if (MiniR4.PS2.Button(PSB_R2)) {

       MiniR4.RC3.setAngle(180);
      delay(2);
    
  }
  if (MiniR4.PS2.Button(PSB_TRIANGLE)) {

      angle2 = 0;
      delay(2);
  }

  if (MiniR4.PS2.Button(PSB_CIRCLE)) {
      MiniR4.RC1.setAngle(15);
      delay(500);
      MiniR4.RC3.setAngle(0);
      delay(500);
      MiniR4.RC1.setAngle(100);
      delay(500);
      angle2 = 180;
      delay(2);
      angle2 = 0;
      delay(2);
  }

  if (MiniR4.PS2.Button(PSB_R1)) {
      angle3 = 0;
      angle4 = 180;
  } else{
    angle3 = 171;
    angle4 = 9;
    }
  if (MiniR4.PS2.Button(PSB_CROSS)) {
    
    int dis = MiniR4.I2C1.MXLaser.getDistance();
    if (dis == 8191) {
      MiniR4.M1.setSpeed(-100);
      MiniR4.M2.setSpeed(-100);
    } else if (dis > 144) {
      MiniR4.M1.setSpeed(-100);
      MiniR4.M2.setSpeed(-100);
    } else if (dis < 140) {
      MiniR4.M1.setSpeed(100);
      MiniR4.M2.setSpeed(100);
    } else {
      MiniR4.M1.setSpeed(0);
      MiniR4.M2.setSpeed(0);
      delay(100);
    }
  }
  
  if (MiniR4.PS2.Button(PSB_SQUARE)) {
    int dis = MiniR4.I2C1.MXLaser.getDistance();
    if (dis == 8191) {
      MiniR4.M1.setSpeed(-100);
      MiniR4.M2.setSpeed(-100);
    } else if (dis > 144) {
      MiniR4.M1.setSpeed(-90);
      MiniR4.M2.setSpeed(-90);
    } else if (dis < 131) {
      MiniR4.M1.setSpeed(85);
      MiniR4.M2.setSpeed(85);
    } else {
      MiniR4.M1.setSpeed(0);
      MiniR4.M2.setSpeed(0);
      MiniR4.M1.setBrake(true);
      MiniR4.M2.setBrake(true);
      delay(100);
      MiniR4.RC1.setAngle(22);
      delay(700);
      MiniR4.RC3.setAngle(180);
      delay(300);
      angle2 = 180;
      angle = 90;

    }
  }
    if (MiniR4.PS2.Button(PSB_PAD_RIGHT)) {
    MiniR4.M1.setSpeed(-70);  // มอเตอร์ M1
    MiniR4.M2.setSpeed(70);

  }
    if (MiniR4.PS2.Button(PSB_PAD_LEFT)) {
    MiniR4.M1.setSpeed(70);  // มอเตอร์ M1
    MiniR4.M2.setSpeed(-70);

  }
  if (MiniR4.PS2.Button(PSB_PAD_UP)) {
    angle = 23;

  }
    if (MiniR4.PS2.Button(PSB_PAD_DOWN)) {
     angle = 180;

  }



  // อ่านค่า Analog จาก Joystick ซ้าย
  PWR_LY = map(MiniR4.PS2.Analog(PSS_LY), 0, 255, -100, 100);  // แกน Y ของ Joystick ซ้าย (พลังงาน)

  // // อ่านค่า Analog จาก Joystick ขวา
  PWR_RY = map(MiniR4.PS2.Analog(PSS_RY), 0, 255, -100, 100);  // แกน Y ของ Joystick ขวา (พลังงาน)

  // การใช้ปุ่ม L1 และ R1


  // ควบคุมมอเตอร์ตามค่า PWR และ STR
  MiniR4.RC1.setAngle(angle);
  MiniR4.RC3.setAngle(angle2);
  MiniR4.RC2.setAngle(angle3);
  MiniR4.RC4.setAngle(angle4);
  
  MiniR4.M1.setPower((PWR_LY)*2);  // มอเตอร์ M1
  MiniR4.M2.setPower((PWR_RY)*2);  // มอเตอร์ M2

  //*/

  ///////////////////////////////////////////////////JOYYYYY
  // TaskIMU();
  // delay(1);
  // MiniR4.M1.setSpeed(50); delay(1000);
  // MiniR4.M1.setSpeed(0); delay(500);
  // MiniR4.M1.setSpeed(-50); delay(1000);
  // MiniR4.M1.setSpeed(0); delay(500);
  // if (MiniR4.BTN_UP.getState()) {
  //   MiniR4.LED.setColor(1, 255, 0, 0);  // Red
  //   MiniR4.LED.setColor(2, 0, 0, 255);  // Blue
  // }
  // if (MiniR4.BTN_DOWN.getState()) {
  //   MiniR4.LED.setColor(1, 0, 0, 255);  // Blue
  //   MiniR4.LED.setColor(2, 255, 0, 0);  // Red
  // }
}

void start() {
  while (true) {
    if (MiniR4.BTN_UP.getState()) {
      MiniR4.Buzzer.Tone(NOTE_C4, 1000);
      delay(200);
      MiniR4.Buzzer.NoTone();
      delay(50);
      MiniR4.Buzzer.Tone(NOTE_C4, 1000);
      delay(200);
      MiniR4.Buzzer.NoTone();
      delay(50);
      MiniR4.Buzzer.Tone(NOTE_C4, 1000);
      delay(200);
      MiniR4.Buzzer.NoTone();
      delay(500);
      break;
    } else {
      delay(50);
    }
  }
}

