/*
  Fade

  This example shows how to control the speed of a motor on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fade
*/

int motor = 9;           // the PWM pin the motor is attached to
int speed = 0;           // how fast the motor is
int speedAmount = 5;      // how many points to slow the motor by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(motor, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the speed of pin 9:
  analogWrite(motor, speed);

  // change the speed for next time through the loop:
  speed = speed + speedAmount;

  // reverse the direction of the fading at the ends of the speed:
  if (speed <= 0 || speed >= 255) {
    speedAmount = -speedAmount;
  }
  // wait for 300 milliseconds to see the speed effect
  delay(300);
}
