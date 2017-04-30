// Tonni 1.0
// Testsoftware for the driving trashbin
// CC-BY SA NC surasto.de  2017

#include "driver.h"
#include "sound.h"

void setup() {
  Serial.begin(9600);
  tonniInit();
  soundInit();
  delay(5000);

  tonniDrive(STOP);

  // All Functions get Tested here
  soundCommand(KEY_1);  // Sound #1 = Startup
  Serial.println("Sound Started");
  delay(1000);
  tonniSteer(STEER_RIGHT);
  Serial.println("Steer Right");
  delay(500);
  tonniSteer(STEER_STRAIGHT);
  Serial.println("Steer Straight");
  delay(500);
  tonniSteer(STEER_LEFT);
  Serial.println("Steer Left");
  eyes(LOOK_LEFT);
  Serial.println("Look Left");
  delay(1000);
  eyes(LOOK_STRAIGHT);
  Serial.println("Look Straight");
  delay(1000);
  eyes(LOOK_RIGHT);
  Serial.println("Look Right");
  delay(1000);
  eyes(LOOK_STRAIGHT);
  Serial.println("Look Straight");
  delay(1000);
  lid(OPEN);
  Serial.println("Open Mouth");
  delay(1000);
  lid(CLOSE);
  Serial.println("Close Mouth");
  delay(500); 
  soundCommand(KEY_RPT);
  delay(100);
  soundCommand(KEY_2);   // Sound #2 = Drive
  Serial.println("Sound Stopped");
  delay(200);
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

  if (getDist(DIST_FRONT)>50) { 
    tonniDrive(FORWARD);
    if (getDriveDir() != FORWARD) { 
       soundCommand(KEY_2);   // Sound #2 = Drive
    }
  } else {
    if (getDriveDir() != BACKWARD) {
      soundCommand(KEY_5);   // Sound #5 = Backwards (spare)
      tonniDrive(STOP);
      lid(OPEN);
      delay(2000);
      lid(CLOSE);
      eyes(LOOK_LEFT);
      delay(500);
      eyes(LOOK_STRAIGHT);
      delay(500);
      eyes(LOOK_RIGHT);
      delay(500);
      eyes(LOOK_STRAIGHT);
      if (getDist(DIST_LEFT) > getDist(DIST_RIGHT)) {
        eyes(LOOK_RIGHT);
        tonniSteer(STEER_RIGHT); 
      }
      else {
        eyes(LOOK_LEFT);
        tonniSteer(STEER_LEFT);
      }
      tonniDrive(BACKWARD);
      while ((getDist(DIST_BACK)  >50) && 
             (getDist(DIST_LEFT)  >20) && 
             (getDist(DIST_RIGHT) >20) && 
             (getDist(DIST_FRONT) <200)) { 
                delay(50); 
                Serial.println(getDist(DIST_BACK)); 
              }
      tonniDrive(STOP);
      eyes(LOOK_STRAIGHT);
      tonniSteer(STEER_STRAIGHT);
    }
  }

  if (getDist(DIST_RIGHT)<30) {
    if (getSteerDir() != STEER_LEFT) {
        tonniDrive(STOP);
        eyes(LOOK_LEFT);
        tonniSteer(STEER_LEFT);
    }
  }
  
  if (getDist(DIST_LEFT)<30) {
    if (getSteerDir() != STEER_RIGHT) {
      tonniDrive(STOP);
      eyes(LOOK_RIGHT);
      tonniSteer(STEER_RIGHT);
    }
  }

  if ((getDist(DIST_LEFT)>40) && (getDist(DIST_RIGHT)>40)) {
    eyes(LOOK_STRAIGHT);
    tonniSteer(STEER_STRAIGHT);
  }

  delay (100);
}

 
