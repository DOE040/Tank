#include <PS2X_lib.h>

#define PS2_DAT 13   
#define PS2_CMD 11
#define PS2_SEL 10
#define PS2_CLK 12

#define BRPin 3
#define FRPin 5
#define BLPin 6
#define FLPin 9

PS2X ps2x;
int leftVal;
int rightVal;
int x;
int y;

void setup() {
  Serial.begin(57600);
  delay(300);
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
  delay(1000);
}

void loop() {
  ps2x.read_gamepad();
  
  y = map(ps2x.Analog(PSS_LY), 0, 255, -255, 255);
  x = map(ps2x.Analog(PSS_LX), 0, 255, 255, -255);

  leftVal = y+x;
  rightVal = y-x;

  if (leftVal > 255){leftVal = 255;}
  if (leftVal < -255){leftVal = -255;}
  if (rightVal > 255){rightVal = 255;}
  if (rightVal < -255){rightVal = -255;}

  if (leftVal >= 0){
    analogWrite(FLPin, leftVal);
    analogWrite(BLPin, 0);}
  else {
    analogWrite(FLPin, 0);
    analogWrite(BLPin, -leftVal);
  }
  if (rightVal >= 0){
    analogWrite(FRPin, rightVal);
    analogWrite(BRPin, 0);}
  else {
    analogWrite(FRPin, 0);
    analogWrite(BRPin, -rightVal);
  }
  
  Serial.print("Stick Values: ");
  Serial.print(leftVal);
  Serial.println(rightVal);
}
