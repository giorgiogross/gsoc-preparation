/**
Use this code to spam the NUM_MSGS messages via the TX1 pin of the Arduino,
each of them having 1 byte and thus representing one package sent via UART.
After waiting PAUSE_TIME milliseconds the procedure is repeated.

This sketch helps in testing the serial communication on the BeagleBone Black.
*/

// set this to 0 for non-canonical input mode
#define FINISH_WITH_NL 1

// number of messages sent at once
#define NUM_MSGS 4096
// pause before sending starts
#define PAUSE_TIME 3000

// control led on the board
#define CONROL_LED 13

// 0 if you want to send the messages only once or -1 to send continuously
int ONE_SHOT = 0;

void setup() {
  Serial.begin(230400);
  Serial1.begin(230400);
  
  pinMode(CONROL_LED, OUTPUT);
}

void loop() {
  digitalWrite(CONROL_LED, HIGH);
  delay(PAUSE_TIME);
  
  // don't do anything if we already sent all messages and 
  // ONE_SHOT was initially set to 0
  if(ONE_SHOT > 0) return;
  
  // signal start of transmission
  digitalWrite(CONROL_LED, LOW);
  for(int i = 0; i < NUM_MSGS; i++){
    Serial1.write('1');
  }
  if(FINISH_WITH_NL) Serial1.println("");
  
  if(ONE_SHOT == 0) ONE_SHOT++;
}
