// Tonni 1.0
// Testsoftware for the driving trashbin
// CC-BY SA NC surasto.de  2017

#include "driver.h"

void setup() {
  Serial.begin(9600);
  tonniInit();
  tonniSteer (STEER_STRAIGHT);
   //tonniDrive (BACKWARD);
}

void loop() {
  int dist;
  int go;

  if (getDist(DIST_FRONT)<50) tonniDrive(STOP);
  else tonniDrive(FORWARD);

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

 
