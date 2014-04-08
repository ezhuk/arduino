// Copyright (c) 2014 Eugene Zhuk.
// Use of this source code is governed by the MIT license that can be found
// in the LICENSE file.
//
// Control the LED brightness using a photoresistor and change the blinking
// rate through a potentiometer.
//
//
//                  o +5V
//                  |
//      o PIN 9     |
//      |          |¯| //
//      |          | |``
//     _|_         |_|
//     \ / LED      |
//     ¯|¯          |
//      |           o-------o PIN A0
//      |           |
//      |           |
//     |¯|         |¯|
//     | | 330     | | 10K
//     |_|         |_|
//      |           |
//      |           |
//      o-----------o
//      |           |
//      |           |
//     ¯¯¯         |¯|
//                 | |<-----o PIN A1
//                 |_|
//                  |
//                  |
//                  o +5V

int const photoresistor = 0;
int const potentiometer = 1;
int const led = 10;

int value = 0;
int state = LOW;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  adjust_brightness();
  adjust_rate();
}

void adjust_brightness() {
  static int min = 1023;
  static int max = 0;

  value = analogRead(photoresistor);
  if (value < min)
    min = value;
  if (value > max)
    max = value;

  value = map(value, min + 25, max - 25, 0, 255);
  value = constrain(value, 0, 255);

  if (HIGH == state)
    analogWrite(led, value);
}

void adjust_rate() {
  static unsigned long prev = 0;

  unsigned long time = millis();
  if (time - prev > analogRead(potentiometer)) {
    prev = time;
    state = !state;
    analogWrite(led, (HIGH == state) ? value : 0);
  }
}

