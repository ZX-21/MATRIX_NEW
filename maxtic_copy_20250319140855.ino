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

static bool lastButtonState = false;
static bool isToggled = false;
// PID variables


void setup() {
  MiniR4.begin();
  Serial.begin(115200);
  angle = 100;
  angle3 = 180;

  angle2 = 10;
  angle4 = 170;

  MiniR4.RC1.setAngle(angle);
  MiniR4.RC2.setAngle(angle2);

  MiniR4.RC3.setAngle(angle3);
  MiniR4.RC4.setAngle(angle4);
  //MiniR4.RC4.setAngle(180);

  MiniR4.Motion.resetIMUValues();
  //  delay(500);
  MiniR4.I2C4.MXLaser.begin();

  ////////////////////////////////////JOY
  MiniR4.PWR.setBattCell(3);
  MiniR4.M1.setReverse(true);   // กำหนดทิศทางของมอเตอร์ M1
  MiniR4.M2.setReverse(false);  // กำหนดทิศทางของมอเตอร์ M2
  MiniR4.M1.setSpeed(0);        // ตั้งความเร็วของมอเตอร์ M1 เป็น 0
  MiniR4.M2.setSpeed(0);        // ตั้งความเร็วของมอเตอร์ M2 เป็น 0
  MiniR4.PS2.read_gamepad(false, 0);
  delay(500);


  start();
  middle();
  pwback(380);
  delay(500);
  left();
  middleright();
  //back();
  // TaskEncoder();
 // at();
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
    if (angle > 0) {
      angle = angle + -5;
      delay(2);
    }
  }
  if (MiniR4.PS2.Button(PSB_L1)) {
   if (angle < 175) {
       angle = angle + 5;
      delay(2);
   }
  }
  //   if (MiniR4.PS2.Button(PSB_R1)) {
  //     angle3 = 0;
  // } else{
  //   angle3 = 180;
  //   }

if (MiniR4.PS2.Button(PSB_R1)) {
    if (!lastButtonState) {
        isToggled = !isToggled;  
        angle3 = isToggled ? 180 : 0; 
    }
    lastButtonState = true; 
} else {
    lastButtonState = false; 
}


if (MiniR4.PS2.Button(PSB_R2)) {

      MiniR4.RC2.setAngle(130);
      MiniR4.RC4.setAngle(50);
      delay(2);
  }
 else {
  MiniR4.RC2.setAngle(10); 
  MiniR4.RC4.setAngle(170);
 delay(2);
 } 
  if (MiniR4.PS2.Button(PSB_TRIANGLE)) {

      angle2 = 0;
      delay(2);
  }

  if (MiniR4.PS2.Button(PSB_CIRCLE)) {
    angle = 0;
  }
  
    if (MiniR4.PS2.Button(PSB_SQUARE)) {
    angle = 25;
  }

   if (MiniR4.PS2.Button(PSB_PAD_UP)) {
     MiniR4.M1.setPower(-170);  // มอเตอร์ M1
     MiniR4.M2.setPower(-170);  // มอเตอร์ M2
   }
    if (MiniR4.PS2.Button(PSB_PAD_LEFT)) {
     MiniR4.M1.setPower(170);  // มอเตอร์ M1
     MiniR4.M2.setPower(-170);  // มอเตอร์ M2
   }
    if (MiniR4.PS2.Button(PSB_PAD_RIGHT)) {
     MiniR4.M1.setPower(-170);  // มอเตอร์ M1
     MiniR4.M2.setPower(170);  // มอเตอร์ M2
   }
    if (MiniR4.PS2.Button(PSB_PAD_DOWN)) {
     MiniR4.M1.setPower(170);  // มอเตอร์ M1
     MiniR4.M2.setPower(170);  // มอเตอร์ M2
   }




  // if (MiniR4.PS2.Button(PSB_CROSS)) {
    
  //   int dis = MiniR4.I2C1.MXLaser.getDistance();
  //   if (dis == 8191) {
  //     MiniR4.M1.setSpeed(-100);
  //     MiniR4.M2.setSpeed(-100);
  //   } else if (dis > 144) {
  //     MiniR4.M1.setSpeed(-100);
  //     MiniR4.M2.setSpeed(-100);
  //   } else if (dis < 140) {
  //     MiniR4.M1.setSpeed(100);
  //     MiniR4.M2.setSpeed(100);
  //   } else {
  //     MiniR4.M1.setSpeed(0);
  //     MiniR4.M2.setSpeed(0);
  //     delay(100);
  //   }
  // }
  
  // if (MiniR4.PS2.Button(PSB_SQUARE)) {
  //   int dis = MiniR4.I2C1.MXLaser.getDistance();
  //   if (dis == 8191) {
  //     MiniR4.M1.setSpeed(-100);
  //     MiniR4.M2.setSpeed(-100);
  //   } else if (dis > 144) {
  //     MiniR4.M1.setSpeed(-90);
  //     MiniR4.M2.setSpeed(-90);
  //   } else if (dis < 131) {
  //     MiniR4.M1.setSpeed(85);
  //     MiniR4.M2.setSpeed(85);
  //   } else {
  //     MiniR4.M1.setSpeed(0);
  //     MiniR4.M2.setSpeed(0);
  //     MiniR4.M1.setBrake(true);
  //     MiniR4.M2.setBrake(true);
  //     delay(100);
  //     MiniR4.RC1.setAngle(22);
  //     delay(700);
  //     MiniR4.RC3.setAngle(180);
  //     delay(300);
  //     angle2 = 180;
  //     angle = 90;

  //   }
  // }
    
  // if (MiniR4.PS2.Button(PSB_PAD_UP)) {
  //   angle = 23;

  // }
  //   if (MiniR4.PS2.Button(PSB_PAD_DOWN)) {
  //    angle = 180;

  // }



  // อ่านค่า Analog จาก Joystick ซ้าย
  PWR_LY = map(MiniR4.PS2.Analog(PSS_LY), 0, 255, -100, 100);  // แกน Y ของ Joystick ซ้าย (พลังงาน)

  // // อ่านค่า Analog จาก Joystick ขวา
  PWR_RY = map(MiniR4.PS2.Analog(PSS_RY), 0, 255, -100, 100);  // แกน Y ของ Joystick ขวา (พลังงาน)

  // การใช้ปุ่ม L1 และ R1


  // ควบคุมมอเตอร์ตามค่า PWR และ STR
  MiniR4.RC1.setAngle(angle);
 
  MiniR4.RC3.setAngle(angle3);


  
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
     MiniR4.PS2.read_gamepad(false, 0);
    if (MiniR4.PS2.Button(PSB_CROSS)) {
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

void TaskEncoder() {
  MiniR4.M1.resetCounter();
  MiniR4.M2.resetCounter();


  while (true) {
    Serial.print("M1: ");
    Serial.print(MiniR4.M1.getDegrees());
    Serial.print(", M2: ");
    Serial.println(MiniR4.M2.getDegrees());

    delay(100);
  }
}

void middle() {
  MiniR4.M1.resetCounter();
  MiniR4.M2.resetCounter();

  while (true) {
    // แก้ไขวงเล็บในเงื่อนไข if
    Serial.print("M1: ");
    Serial.print(MiniR4.M1.getDegrees());
    Serial.print(", M2: ");
    Serial.println(MiniR4.M2.getDegrees());

    if (MiniR4.M1.getDegrees() > -100 && MiniR4.M2.getDegrees() < 115) {
      MiniR4.M1.setPower(36);  // มอเตอร์ M1
      MiniR4.M2.setPower(30);  // มอเตอร์ M2
      delay(5);
    } else {
      MiniR4.M1.setPower(0);  // มอเตอร์ M1
      MiniR4.M2.setPower(0);  // มอเตอร์ M2
      delay(5);
      
      // ทำการปรับมุมของเซอร์โวมอเตอร์ RC1, RC3
      MiniR4.RC1.setAngle(25); 
      delay(100);
      delay(1000);  // หน่วงเวลาหนึ่งวินาที

      MiniR4.RC3.setAngle(0); 
      delay(100);
      delay(1000);  // หน่วงเวลาหนึ่งวินาที

      MiniR4.RC2.setAngle(130); 
      MiniR4.RC4.setAngle(50); 

      delay(500);  // หน่วงเวลาหนึ่งวินาที

      MiniR4.RC1.setAngle(80); 
      delay(100);
      delay(1000);  // หน่วงเวลาหนึ่งวินาที

      pwback(240);
      back();
      encfront();

      MiniR4.RC1.setAngle(35); 
      delay(100);
      delay(1000);  // หน่วงเวลาหนึ่งวินาที

      MiniR4.RC3.setAngle(180); 
      delay(100);
      delay(1000);  // หน่วงเวลาหนึ่งวินาที

      MiniR4.RC1.setAngle(85); 
      delay(100);
      delay(1000);  // หน่วงเวลาหนึ่งวินาที

      break;  // ออกจากลูป while
    }
  }
}


void back() {
  MiniR4.M1.resetCounter();
  MiniR4.M2.resetCounter();

    while (true) {
    Serial.print("M1: ");
    Serial.print(MiniR4.M1.getDegrees());
    Serial.print(", M2: ");
    Serial.println(MiniR4.M2.getDegrees());

    // แก้ไขวงเล็บในเงื่อนไข if
    if (MiniR4.M1.getDegrees() < 605 && MiniR4.M2.getDegrees() < 510) {
      MiniR4.M1.setPower(-63);  // มอเตอร์ M1
      MiniR4.M2.setPower(60);  // มอเตอร์ M2
      delay(5);
    } else {
      MiniR4.M1.setPower(0);  // มอเตอร์ M1
      MiniR4.M2.setPower(0);  // มอเตอร์ M2
      delay(5);

      delay(500);
      break;  // ออกจากลูป while
    }
  }

  }

void encback() {
  MiniR4.M1.resetCounter();
  MiniR4.M2.resetCounter();

   while (true) {
    // แก้ไขวงเล็บในเงื่อนไข if
    Serial.print("M1: ");
    Serial.print(MiniR4.M1.getDegrees());
    Serial.print(", M2: ");
    Serial.println(MiniR4.M2.getDegrees());

    if (MiniR4.M1.getDegrees() > 160 && MiniR4.M2.getDegrees() < -175) {
      MiniR4.M1.setPower(-65);  // มอเตอร์ M1
      MiniR4.M2.setPower(-60);  // มอเตอร์ M2
      delay(5);
    } else {
      MiniR4.M1.setPower(0);  // มอเตอร์ M1
      MiniR4.M2.setPower(0);  // มอเตอร์ M2
      delay(5);
      break;
    }
}
}

void encfront() {
  MiniR4.M1.resetCounter();
  MiniR4.M2.resetCounter();

   while (true) {
    // แก้ไขวงเล็บในเงื่อนไข if
    Serial.print("M1: ");
    Serial.print(MiniR4.M1.getDegrees());
    Serial.print(", M2: ");
    Serial.println(MiniR4.M2.getDegrees());

    if (MiniR4.M1.getDegrees() > -250 && MiniR4.M2.getDegrees() < 265) {
      MiniR4.M1.setPower(35);  // มอเตอร์ M1
      MiniR4.M2.setPower(30);  // มอเตอร์ M2
      delay(5);
    } else {
      MiniR4.M1.setPower(0);  // มอเตอร์ M1
      MiniR4.M2.setPower(0);  // มอเตอร์ M2
      delay(5);
      break;
    }
}
}

void pwback(int a) {
  while(true) {
  // MiniR4.RC2.setAngle(130); 
  // MiniR4.RC4.setAngle(50); 
  // delay(500);  // หน่วงเวลาหนึ่งวินาที
  MiniR4.M1.setPower(-60);  // มอเตอร์ M1
  MiniR4.M2.setPower(-60);  // มอเตอร์ M2
  delay(a);
  MiniR4.M1.setPower(0);  // มอเตอร์ M1
  MiniR4.M2.setPower(0);  // มอเตอร์ M2
  break;
  }
}

void left() {
  MiniR4.M1.resetCounter();
  MiniR4.M2.resetCounter();

    while (true) {
    Serial.print("M1: ");
    Serial.print(MiniR4.M1.getDegrees());
    Serial.print(", M2: ");
    Serial.println(MiniR4.M2.getDegrees());

    // แก้ไขวงเล็บในเงื่อนไข if
    if (MiniR4.M1.getDegrees() > -270 && MiniR4.M2.getDegrees() > -270) {
      MiniR4.M1.setPower(63);  // มอเตอร์ M1
      MiniR4.M2.setPower(-60);  // มอเตอร์ M2
      delay(5);
    } else {
      MiniR4.M1.setPower(0);  // มอเตอร์ M1
      MiniR4.M2.setPower(0);  // มอเตอร์ M2
      delay(5);

      delay(500);
      break;  // ออกจากลูป while
    }
  }
  }

  void middleright() {
  MiniR4.M1.resetCounter();
  MiniR4.M2.resetCounter();

  while (true) {
    // แก้ไขวงเล็บในเงื่อนไข if
    Serial.print("M1: ");
    Serial.print(MiniR4.M1.getDegrees());
    Serial.print(", M2: ");
    Serial.println(MiniR4.M2.getDegrees());

    if (MiniR4.M1.getDegrees() > -850 && MiniR4.M2.getDegrees() < 900) {
      MiniR4.M1.setPower(43);  // มอเตอร์ M1
      MiniR4.M2.setPower(43);  // มอเตอร์ M2
      delay(5);
    } else {
      MiniR4.M1.setPower(0);  // มอเตอร์ M1
      MiniR4.M2.setPower(0);  // มอเตอร์ M2
      delay(5);
      
      // ทำการปรับมุมของเซอร์โวมอเตอร์ RC1, RC3
      MiniR4.RC1.setAngle(25); 
      delay(100);
      delay(1000);  // หน่วงเวลาหนึ่งวินาที

      MiniR4.RC3.setAngle(0); 
      delay(100);
      delay(1000);  // หน่วงเวลาหนึ่งวินาที

      MiniR4.RC2.setAngle(110); 
      MiniR4.RC4.setAngle(70); 

      delay(500);  // หน่วงเวลาหนึ่งวินาที

      MiniR4.RC1.setAngle(80); 
      delay(100);
      delay(1000);  // หน่วงเวลาหนึ่งวินาที

      break;  // ออกจากลูป while
    }
  }
}