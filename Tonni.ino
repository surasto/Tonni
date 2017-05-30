// Tonni 1.0
// Testsoftware for the driving trashbin
// CC-BY SA NC surasto.de  2017

#include "driver.h"
#include "sound.h"

boolean activeDrive;   // This variable hold the drive state. If false none of teh motors are activated
unsigned long lastAction;
unsigned long lastSpeach;
unsigned long timeStamp;

void setup() {
  int i, dist;

  Serial.begin(9600);
  tonniInit();
  soundInit();

  delay(200);
  dist = getDist(DIST_FRONT);  // Dummy Call - first call is sometimes wrong;
  dist = 0;
  for (i = 0; i<10; i++) dist += getDist(DIST_FRONT);
  if (dist < 200) activeDrive = false; else activeDrive = true;   // Distance in average < 20cm

  delay(2000);

  tonniDrive(STOP);

  // Check if Tonni shall drive around or switch to displayMode. In that mode all Motors are off
  // Display Mode is activeted by covering one of the front sensors with the hand while 
  // switching on Tonni.

  Serial.print("===== Drive Mode: ");
  Serial.print(activeDrive);
  Serial.println(" ==========");

  // All Functions get Tested here
  if (activeDrive) soundCommand(KEY_3); else soundCommand(KEY_4); 
  Serial.println("Sound Started");
  delay(1500);
  lid(OPEN);
  Serial.println("Open Mouth");
  delay(4000);
  lid(CLOSE);
  Serial.println("Close Mouth");
  delay(100); 
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

  if (activeDrive == true) {
     tonniSteer(STEER_RIGHT);
     Serial.println("Steer Right");
     delay(500);
     tonniSteer(STEER_STRAIGHT);
     Serial.println("Steer Straight");
     delay(500);
     tonniSteer(STEER_LEFT);
     Serial.println("Steer Left");
     soundCommand(KEY_2);   // Sound #2 = Drive
     Serial.println("Drive Sound");
     delay(200);
  } else {
     soundCommand(KEY_1);   // Sound #1 = Silense
     Serial.println("Sound stopped");
     delay(200);
  }
  lastAction = millis();
  lastSpeach = millis();
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

  if (activeDrive == true) {          // This part will be executed when motors are enabled
    if (getDist(DIST_FRONT)>50) { 
      tonniDrive(FORWARD);
      if (millis() > lastAction + 6000 + random(5000)) {
        eyes(LOOK_LEFT);
        delay(500);
        eyes(LOOK_STRAIGHT);
        delay(500);
        eyes(LOOK_RIGHT);
        delay(500);
        eyes(LOOK_STRAIGHT);
        lastAction = millis();
      }
      if (getDriveDir() != FORWARD) { 
         soundCommand(KEY_2);   // Sound #2 = Drive
      }
    } else {
      if (getDriveDir() != BACKWARD) {
        tonniDrive(STOP);
        playRandomSpeach();    // Key 3 .. 9
        lid(OPEN);
        delay(6000);
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
        soundCommand(KEY_2);   // Sound #2 = Drive
        timeStamp =millis();
        while ((getDist(DIST_BACK)  >50) && 
               (getDist(DIST_LEFT)  >20) && 
               (getDist(DIST_RIGHT) >20) && 
               (getDist(DIST_FRONT) <80) &&
               (millis() < timeStamp + 8000)) { 
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
  } else { // this part will be executed when motors are disabled
    
    if (((getDist(DIST_FRONT) < 80) && (millis() > lastSpeach + 15000)) || (millis() > lastSpeach + 30000)) {
      eyes(LOOK_LEFT);
      delay(500);
      eyes(LOOK_STRAIGHT);
      delay(500);
      eyes(LOOK_RIGHT);
      delay(500);
      eyes(LOOK_STRAIGHT);

      playRandomSpeach();
      lid(OPEN);
      delay(6000);
      lid(CLOSE);
      delay(5000);
      soundCommand(KEY_1);   // Sound #1 = Silense

      lastSpeach = millis();
    }

    if (millis() > lastAction + 6000 + random(5000)) {
      eyes(LOOK_LEFT);
      delay(500);
      eyes(LOOK_STRAIGHT);
      delay(500);
      eyes(LOOK_RIGHT);
      delay(500);
      eyes(LOOK_STRAIGHT);
      lastAction = millis();
    }
  }

  delay (100);
}


void playRandomSpeach() {
  int i;

  i=random(3,9);
  switch (i) {
    case 3: soundCommand(KEY_3); break; 
    case 4: soundCommand(KEY_4); break; 
    case 5: soundCommand(KEY_5); break; 
    case 6: soundCommand(KEY_6); break; 
    case 7: soundCommand(KEY_7); break; 
    case 8: soundCommand(KEY_8); break; 
    case 9: soundCommand(KEY_9); break; 
  }
  delay(1000);
}
