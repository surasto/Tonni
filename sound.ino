// ========================================================================================
// Send commands to DayPower soundmodule 
// Keys 1...9 play the respective soundfile regardless if the module is in pause or play mode
// RPT (Repeat) gets reset after power cycle
// Pause is a toggle switch (retains state even after power cycle)
// CC3.0 SA-BY-NC surasto.de
// ========================================================================================
#define sendPin 7
#define KEY_PAUSE "00100010110111011"
#define KEY_RPT   "10011000011001111"
#define KEY_1     "00110000110011111"
#define KEY_2     "00011000111001111"
#define KEY_3     "01111010100001011"

void setup() {
  pinMode(sendPin,OUTPUT);
  digitalWrite(sendPin, HIGH);
  Serial.begin(9600);
}

void loop() {
  int c;
  
  if (Serial.available()>0) {
    c = Serial.read();
    switch (c) {
      case 'p': sendCommand(KEY_PAUSE); break;
      case '1': sendCommand(KEY_1); break; 
      case '2': sendCommand(KEY_2); break; 
      case '3': sendCommand(KEY_3); break; 
    } 
  delay(10);
  }
}

//-------------- Library --------------------

void sendCommand(char *cmd) {
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

