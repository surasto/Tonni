// Tonni 1.0
// Testsoftware for the driving trashbin
// CC-BY SA NC surasto.de  2017

#include "driver.h"

void setup() {
  Serial.begin(9600);
  tonniInit();
}

void loop() {
  delay(500);
  tonniSteer(STEER_STRAIGHT);
  delay(2000);
  tonniSteer(STEER_RIGHT);
  delay(2000);
  tonniDrive(FORWARD);
  delay(2000);
  tonniSteer(STEER_LEFT);
  delay(2000);
  tonniDrive(BACKWARD);
}
