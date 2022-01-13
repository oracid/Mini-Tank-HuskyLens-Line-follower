// 12/01/2022 - MiniTank line tracking with HuskyLens
#include "HUSKYLENS.h"
#include <Servo.h>
Servo sR,sL;                        // right servo and left servo
int R, L;                           // right servo value, left servo value
HUSKYLENS huskylens; int ID1=1;     // HuskyLens objet

void setup() {
  Serial.begin(9600);
  pinMode(0,INPUT_PULLUP);          // start/stop button attachment
  sR.attach(3); sR.write(90);       // right servo initialization
  sL.attach(4); sL.write(90);       // left servo initialization

  Wire.begin();                     // I2C
  while (!huskylens.begin(Wire)) {Serial.print("\n Check I2C"); delay(100);}
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING); //Switch the algorithm to line tracking.

  Serial.print("\n\t To start, click on the Start button"); while( digitalRead(0) ); delay(400);
}

void loop() {
  huskylens.request(ID1);
  HUSKYLENSResult result = huskylens.read();
  int err = map(result.xTarget,0,320,-90,90);                 // getting and maping error
  if ( err < 0) { L=0-err; R=180; } else { L=0; R=180-err; }  // error makes turning left or right
  sR.write(R);  sL.write(L);                                  // right and left servos orders
}
