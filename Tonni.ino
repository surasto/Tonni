// Tonni 1.0
// Testsoftware for the driving trashbin
// CC-BY SA NC surasto.de  2017

#include "driver.h"
#include "sound.h"

void setup() {
  Serial.begin(9600);
  tonniInit();
  soundInit();
  delay(500);

  // All Functions get Tested here
  soundCommand(SOUND_STARTUP);
  delay(3000);
  tonniSteer(STEER_RIGHT);
  delay(500);
  tonniSteer(STEER_STRAIGHT);
  delay(500);
  tonniSteer(STEER_LEFT);
  eyes(LOOK_LEFT);
  delay(1000);
  eyes(LOOK_STRAIGHT);
  delay(1000);
  eyes(LOOK_RIGHT);
  delay(1000);
  eyes(LOOK_STRAIGHT);
  delay(1000);
  lid(OPEN);
  delay(1000);
  lid(CLOSE);
  delay(500); 
  soundCommand(SOUND_SILENCE); 
}

void loop() {
  int dist;
  int c;
  
  if (Serial.available()>0) {
    c = Serial.read();
    switch (c) {
      case 'p': soundCommand(KEY_PAUSE); break;
      case '1': soundCommand(KEY_1); break; 
      case '2': soundCommand(KEY_2); break; 
      case '3': soundCommand(KEY_3); break; 
      case '4': soundCommand(KEY_4); break; 
      case '5': soundCommand(KEY_5); break; 
      case '6': soundCommand(KEY_6); break; 
      case '7': soundCommand(KEY_7); break; 
      case '8': soundCommand(KEY_8); break; 
      case '9': soundCommand(KEY_9); break; 
    } 
  }

  if (getDist(DIST_FRONT)<50) tonniDrive(STOP);
  else {
//    soundCommand(SOUND_DRIVE);
    tonniDrive(FORWARD);
  }

  if (getDist(DIST_RIGHT)<20) {
    tonniDrive(STOP);
    tonniSteer(STEER_LEFT);
    tonniDrive(FORWARD);
    while (getDist (DIST_RIGHT)<30) delay(10);
    tonniDrive(STOP);
    tonniSteer(STEER_STRAIGHT);
  }
  
  else if (getDist(DIST_LEFT)<20) {
    tonniDrive(STOP);
    tonniSteer(STEER_RIGHT);
    tonniDrive(FORWARD);
    while (getDist (DIST_LEFT)<30) delay(10);
    tonniDrive(STOP);
    tonniSteer(STEER_STRAIGHT);
  }

  delay (100);
}

 
