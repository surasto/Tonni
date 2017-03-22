// Tonni 1.0
// Testsoftware for the driving trashbin
// CC-BY SA NC surasto.de  2017

#include "driver.h"

void setup() {
  Serial.begin(9600);
  tonniInit();
  tonniSteer (STEER_STRAIGHT);

}

void loop() {
  int dist;
  int go;

//  if ((getDist(DIST_LEFT)>20)&&(getDist(DIST_RIGHT)>20)&&(getDist(DIST_FRONT)>20)) go = FORWARD;
//  else go = STOP;
   tonniDrive (FORWARD);

//  Serial.println(go);
//  tonniDrive(go);
  delay (5000);
}

 
