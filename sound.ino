// ========================================================================================
// Send commands to DayPower soundmodule 
// Keys 1...9 play the respective soundfile regardless if the module is in pause or play mode
// RPT (Repeat) gets reset after power cycle
// Pause is a toggle switch (retains state even after power cycle)
// CC3.0 SA-BY-NC surasto.de
// ========================================================================================
#include "sound.h"

void soundInit() {
  pinMode(sendPin,OUTPUT);
  digitalWrite(sendPin, HIGH);
}

//-------------- Library --------------------

void soundCommand(char *cmd) {
  sendHeader();
  for (int i=0; i<17; i++) 
    if (cmd[i]=='0') sendZero(); else sendOne();
}

// Every Command Starts with this header
void sendHeader() {
   digitalWrite(sendPin,LOW);
   delayMicroseconds(8800);
   digitalWrite(sendPin,HIGH);
   delayMicroseconds(4400);

   for (int i=0; i<8; i++) sendZero();
   for (int i=0; i<8; i++) sendOne();
}

//      _
//   |_|   2 x 600us
void sendZero() {
   digitalWrite(sendPin,LOW);
   delayMicroseconds(600);
   digitalWrite(sendPin,HIGH);
   delayMicroseconds(600);
}

//     ___   
//  |_|     4 x 600us
void sendOne() {   
   digitalWrite(sendPin,LOW);
   delayMicroseconds(600);
   digitalWrite(sendPin,HIGH);
   delayMicroseconds(1800);
}

