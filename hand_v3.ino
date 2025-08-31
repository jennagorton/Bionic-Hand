#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN  125 // This is the 'minimum' pulse length count (out of 4096) 150
#define SERVOMAX  525 // This is the 'maximum' pulse length count (out of 4096) 550
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

//servo driver pin
#define MIDDLE 0
#define THUMB 1
#define RING 2
#define INDEX 3
#define PINKY 4



//global variable to track position 0:open 1:close
int indexPos = 0;
int middlePos = 0;
int thumbPos = 0;
int ringPos = 0;
int pinkyPos = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(6, INPUT);
  pinMode(5, INPUT);


  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);

  //initalize all servos open
  pwm.setPWM(PINKY, 0, SERVOMAX);
  pwm.setPWM(RING, 0, SERVOMAX);
  pwm.setPWM(INDEX, 0, SERVOMAX);
  pwm.setPWM(MIDDLE, 0, SERVOMAX);
  pwm.setPWM(THUMB, 0, SERVOMAX);


  Serial.println("Type hand gesture");


}

void loop() {
  // Wait for user input
  while (!Serial.available()) {
    // do nothing until user types something

    //testing touch sensor
    int c1r1 = digitalRead(2);
    int c2r1 = digitalRead(3);
    //int c3r1 = digitalRead(4);
    int c4r1 = digitalRead(5);
    //int c5r1 = digitalRead(6);
    int c3r2 = digitalRead(7);
    int c2r2 = digitalRead(8);
    int c3r1 = digitalRead(9);
    int c4r2 = digitalRead(10);
    int c5r1 = digitalRead(11);
    delay(50);

    // Check each touch input
    //top row
    if (c1r1 == 1) Serial.println("c1r1 touched");
    if (c2r1 == 1) Serial.println("c2r1 touched");
    if (c3r1 == 1) Serial.println("c3r1 touched");
    if (c4r1 == 1) Serial.println("c4r1 touched");
    if (c4r2 == 1) Serial.println("c4r2 touched");
    
    //bottom row
    if (c2r2 == 1) Serial.println("c2r2 touched");
    if (c3r2 == 1) Serial.println("c3r2 touched");
    if (c5r1 == 1) Serial.println("c5r1 touched");
    
    String input = Serial.readStringUntil('\n');
    input.trim(); // remove any whitespace or newline characters

    /***************FIRST ROW SENSORS********************/
    //each sensor controls one finger to open and close
    if(c1r1 == 1 && pinkyPos != 1){
      pwm.setPWM(PINKY, 0, SERVOMIN);
      pinkyPos = 1;
    }
    else if(c1r1 == 1 && pinkyPos == 1){
      pwm.setPWM(PINKY, 0, SERVOMAX);
      pinkyPos = 0;
    }

    if(c2r1 == 1 && ringPos != 1){
      pwm.setPWM(RING, 0, SERVOMIN);
      ringPos = 1;
    }
    else if(c2r1 == 1 && ringPos == 1){
      pwm.setPWM(RING, 0, SERVOMAX);
      ringPos = 0;
    }

    if(c3r1 == 1 && middlePos != 1){
      pwm.setPWM(MIDDLE, 0, SERVOMIN);
      middlePos = 1;
    }
    else if(c3r1 == 1 && middlePos == 1){
      pwm.setPWM(MIDDLE, 0, SERVOMAX);
      middlePos = 0;
    }

    if(c4r1 == 1 && indexPos != 1){
      pwm.setPWM(INDEX, 0, SERVOMIN);
      indexPos = 1;
    }
    else if(c4r1 == 1 && indexPos == 1){
      pwm.setPWM(INDEX, 0, SERVOMAX);
      indexPos = 0;
    }

    if(c5r1 == 1 && thumbPos != 1){
      pwm.setPWM(THUMB, 0, SERVOMIN);
      thumbPos = 1;
    }
    else if(c5r1 == 1 && thumbPos == 1){
      pwm.setPWM(THUMB, 0, SERVOMAX);
      thumbPos = 0;
    }

    /***************SECOND ROW SENSORS********************/
    if (c2r2 == 1){ // close fist 
      for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) { //closing
        if (indexPos == 0){
          pwm.setPWM(INDEX, 0, pulselen);
        }
        if (middlePos == 0){
            pwm.setPWM(MIDDLE, 0, pulselen);
        }

        if (ringPos == 0){
            pwm.setPWM(RING, 0, pulselen);
        }

        if (pinkyPos == 0){
            pwm.setPWM(PINKY, 0, pulselen);
        }

        if (thumbPos == 0){
            pwm.setPWM(THUMB, 0, pulselen);
        }
        delay(3);
      }
      indexPos = middlePos = ringPos = pinkyPos = thumbPos = 1;
    }

    if (c3r2 == 1){ // open all
      for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) { //opening
        if (indexPos == 1){
            pwm.setPWM(INDEX, 0, pulselen);
        }
        
        if (middlePos == 1){
            pwm.setPWM(MIDDLE, 0, pulselen);
        }

        if (ringPos == 1){
            pwm.setPWM(RING, 0, pulselen);
        }

        if (pinkyPos == 1){
            pwm.setPWM(PINKY, 0, pulselen);
        }

        if (thumbPos == 1){
            pwm.setPWM(THUMB, 0, pulselen);
        }
        delay(3);
      }
      indexPos = middlePos = ringPos = pinkyPos = thumbPos = 0;
    }

    if (c5r1 == 1){ //peace sign
      for (uint16_t pulselen = SERVOMAX, pulseopp = SERVOMIN; 
        pulselen > SERVOMIN && pulseopp < SERVOMAX; 
        pulselen--, pulseopp++) {
        //closing
        if (thumbPos == 0) {
          pwm.setPWM(THUMB, 0, pulselen);
        }

        if (ringPos == 0) {
          pwm.setPWM(RING, 0, pulselen);
        }

        if (pinkyPos == 0) {
          pwm.setPWM(PINKY, 0, pulselen);
        }

        //opening
        if (middlePos == 1){
          pwm.setPWM(MIDDLE, 0, pulseopp);
        }
        
        if (indexPos == 1){
          pwm.setPWM(INDEX, 0, pulseopp);
        }
        delay(3);
      }
      indexPos = middlePos = 0;
      ringPos = pinkyPos = thumbPos = 1;
    }
  }
}
