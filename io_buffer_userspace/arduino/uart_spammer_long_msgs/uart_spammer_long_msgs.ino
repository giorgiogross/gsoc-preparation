/**
Use this code to spam the NUM_MSGS messages via the TX1 pin of the Arduino,
each of them having 3 bytes.
After waiting PAUSE_TIME milliseconds the procedure is repeated.

This sketch helps in testing the serial communication on the BeagleBone Black.
*/

#define NUM_MSGS 1
#define PAUSE_TIME 3000
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
    Serial1.println("This is a test message followed by a separate message with 255 characters.");
    // write 255 chars 
    Serial1.println("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
  }
  
  if(ONE_SHOT == 0) ONE_SHOT++;
}
