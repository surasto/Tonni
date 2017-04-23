// Tonni Drivers
#include "driver.h"
#include <Servo.h>

#define DRIVE_A A0
#define DRIVE_B A1
#define STEER_A A2
#define STEER_B A3
#define POTI A5


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

  eyeServo.attach(2);
  lidServo.attach(3);
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
      Serial.println("---  >0   ----");
  } 
  if(delta > 0){
      digitalWrite(STEER_A, LOW);
      digitalWrite(STEER_B, HIGH);
      Serial.println("---- <0 -------");
  }

  do{
    potVal = analogRead(POTI);

    delta = potVal - targetVal;
    Serial.println(delta);
  } while(abs(delta)>10);
  
  digitalWrite(STEER_A, LOW);
  digitalWrite(STEER_B, LOW);
    
}

//========================================================
//  getDist(dir)
//  measures Distance via ultra sonic sensor
//  dir = DIST_FRONT | DIST_RIGHT | DIST_LEFT | DIST_BACK
//========================================================
int getDist(int dir) {
  int cm, cm1, cm2;
  
  if (dir == DIST_FRONT) {
    cm1 = distMeasure(10,11);
    //Serial.print("cm1 = "); Serial.println(cm1);
    cm2 = distMeasure(4,5);
    //Serial.print("cm2 = "); Serial.println(cm2);
    if (cm1<cm2) cm = cm1; else cm=cm2;
       
  } else if (dir == DIST_RIGHT) {
    cm = distMeasure(8,9);
    
  } else if (dir == DIST_LEFT) {
    cm = distMeasure(12,13);

  } else if (dir == DIST_BACK) {
    cm = distMeasure(6,7);
    
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
  if (dir == CLOSE) lidServo.writeMicroseconds(2100);
}


