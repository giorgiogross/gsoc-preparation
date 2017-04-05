/*
    gsoc-preparation  Serial port communication and web servers on BeagleBone Black
    Copyright (C) 2017  Giorgio Gross   <contact@giorgio-gross.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
Use this code to spam the NUM_MSGS messages via the TX1 pin of the Arduino,
each of them having 1 byte and thus representing one package sent via UART.
After waiting PAUSE_TIME milliseconds the procedure is repeated.

This sketch helps in testing the serial communication on the BeagleBone Black.
*/

#define NUM_MSGS 20000
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
    Serial1.write('1');
  }
  if(ONE_SHOT == 0) ONE_SHOT++;
}
