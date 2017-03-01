// Tonni Drivers
#include "driver.h"

#define DRIVE_A A0
#define DRIVE_B A1
#define STEER_A A2
#define STEER_B A3
#define POTI A5

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
  
  do{
    potVal = analogRead(POTI);

    delta = potVal - targetVal;
    Serial.println(delta);
    
    if(delta < -10){
      digitalWrite(STEER_A, HIGH);
      digitalWrite(STEER_B, LOW);
    } else if(delta > 10){
      digitalWrite(STEER_A, LOW);
      digitalWrite(STEER_B, HIGH);
    } else{
      digitalWrite(STEER_A, LOW);
      digitalWrite(STEER_B, LOW);
    }
  } while(abs(delta)>10);
}

