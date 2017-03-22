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
  long duration, cm;
  int pingPin; 
  int start_signal;

  if (dir == DIST_FRONT) {
    pingPin = 10;
    start_signal = 11;
  } else if (dir == DIST_RIGHT) {
    pingPin = 8;
    start_signal = 9;
  } else if (dir == DIST_LEFT) {
    pingPin = 12;
    start_signal = 13; 
  } else return (-1);
 

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
  
  Serial.print(cm);        // Nur für Debug
  Serial.println("cm");
  delay(50);
  return cm;
}
  


