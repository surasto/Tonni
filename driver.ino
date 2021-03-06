// Tonni Drivers
#include "driver.h"
#include <Servo.h>

#define DRIVE_A 13
#define DRIVE_B 12
#define STEER_A 9
#define STEER_B 8
#define POTI A0

  int driveDirection;        // Holds drive direction 
  int steerDirection;

  Servo eyeServo;   // Create ServoObjects
  Servo lidServo;

void tonniInit() {
  //Control Outputs
  pinMode(DRIVE_A, OUTPUT);
  pinMode(DRIVE_B, OUTPUT);
  digitalWrite(DRIVE_A, LOW);
  digitalWrite(DRIVE_B, LOW);

  //Steering Outputs
  pinMode(STEER_A, OUTPUT);
  pinMode(STEER_B, OUTPUT);
  digitalWrite(STEER_A, LOW);
  digitalWrite(STEER_B, LOW);

  //Steering Feedback
  pinMode(POTI, INPUT);

  eyeServo.attach(A3);
  lidServo.attach(A4);
  eyeServo.writeMicroseconds(1600);  // set servo to mid-point
  lidServo.writeMicroseconds(2100);  // set servo to mid-point
}

//======================================
//Controls Drive Direction
//driveDir = FORWARD | BACKWARD | STOP
//======================================
void tonniDrive(int driveDir) {
  if(driveDir == BACKWARD){
    digitalWrite(DRIVE_A, HIGH);
    digitalWrite(DRIVE_B, LOW);
  } else if(driveDir == FORWARD){
    digitalWrite(DRIVE_A, LOW);
    digitalWrite(DRIVE_B, HIGH);
  } else{
    digitalWrite(DRIVE_A, LOW);
    digitalWrite(DRIVE_B, LOW);
  }
  driveDirection = driveDir;
}

//======================================
//Controls Steering Motor
//steerDir = STEER_RIGHT | STEER_LEFT | STEER_STRAIGHT
//======================================
void tonniSteer(int steerDir) {
  int potVal;  // Read from Poti
  int targetVal;
  int delta;

  if(steerDir == STEER_LEFT) targetVal = 750;
  if(steerDir == STEER_RIGHT) targetVal = 250;
  if(steerDir == STEER_STRAIGHT) targetVal = 500;
  
  potVal = analogRead(POTI);
  delta = potVal - targetVal;
  
  if(delta <= 0){
      digitalWrite(STEER_A, HIGH);
      digitalWrite(STEER_B, LOW);
//      Serial.println("---  >0   ----");
  } 
  if(delta > 0){
      digitalWrite(STEER_A, LOW);
      digitalWrite(STEER_B, HIGH);
//      Serial.println("---- <0 -------");
  }

  do{
    potVal = analogRead(POTI);

    delta = potVal - targetVal;
  //  Serial.println(delta);
  } while(abs(delta)>10);
  
  digitalWrite(STEER_A, LOW);
  digitalWrite(STEER_B, LOW);

  steerDirection = steerDir;
}

int getSteerDir() {
  return steerDirection;
}

int getDriveDir() {
  return driveDirection;
}

//========================================================
//  getDist(dir)
//  measures Distance via ultra sonic sensor
//  dir = DIST_FRONT | DIST_RIGHT | DIST_LEFT | DIST_BACK
//========================================================
int getDist(int dir) {
  int cm, cm1, cm2;
  
  if (dir == DIST_FRONT) {
    cm1 = distMeasure(3,2);
    Serial.print("cm1 = "); Serial.println(cm1);
    cm2 = distMeasure(5,4);
    Serial.print("cm2 = "); Serial.println(cm2);
    if (cm1<cm2) cm = cm1; else cm=cm2;
       
  } else if (dir == DIST_RIGHT) {
    cm = distMeasure(7,6);
    Serial.print("cm = "); Serial.println(cm);
    
  } else if (dir == DIST_LEFT) {
    cm = distMeasure(11,10);
    Serial.print("cm = "); Serial.println(cm);

  } else if (dir == DIST_BACK) {
    cm = distMeasure(A2,A1);
    Serial.print("cm = "); Serial.println(cm);
    
  } else return (-1);

  return(cm);
}
  
int distMeasure(int pingPin, int start_signal) {

  long duration;
  long cm;
  
  pinMode(pingPin,OUTPUT);     // Pins vorbereiten
  pinMode(start_signal,OUTPUT);
  digitalWrite(start_signal,HIGH);
  delayMicroseconds(20);

  digitalWrite(start_signal,LOW);  // Starte Messung mit fallender Flanke
  digitalWrite(pingPin,LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin,HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin,LOW);
  pinMode(pingPin,INPUT);

  duration = pulseIn(pingPin,HIGH);  // Messung der Verzögerung bis Echo
  cm = duration / 29 / 2 ;
  
  //Serial.print(cm);        // Nur für Debug
  //Serial.println("cm");
  delay(50);
  return cm;
}

void eyes(int dir) {
  if (dir == LOOK_RIGHT) eyeServo.writeMicroseconds(1900);
  else if (dir == LOOK_LEFT) eyeServo.writeMicroseconds(1300);
  else eyeServo.writeMicroseconds(1600);
}

void lid(int dir) {
  if (dir == OPEN) lidServo.writeMicroseconds(800);
  if (dir == CLOSE) lidServo.writeMicroseconds(1900);
}


