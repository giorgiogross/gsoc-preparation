/**
Use this code to spam the NUM_MSGS messages via the TX1 pin of the Arduino,
each of them having 1 byte and thus representing one package sent via UART.
After waiting PAUSE_TIME milliseconds the procedure is repeated.

This sketch helps in testing the serial communication on the BeagleBone Black.
*/
#define NUM_MSGS 500
#define PAUSE_TIME 3000
#define CONROL_LED 13

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  
  pinMode(CONROL_LED, OUTPUT);
}

void loop() {
  // signal start of transmission
  digitalWrite(CONROL_LED, HIGH);
  delay(PAUSE_TIME);
  digitalWrite(CONROL_LED, LOW);
  for(int i = 0; i < NUM_MSGS; i++){
    Serial1.write('1');
  }
}
