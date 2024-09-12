/*
    This example reads the distance from a HC-SR04 sensor and
    prints it to the serial port.

    by Segilmez06, 22 April 2023.
*/

#include <SRF05.h>

// Define pins
const int echoPin = 11;
const int trigPin = 10;

// Start the sensor -- single pin mode.
SRF05 sensor(trigPin,echoPin);

void setup () {
    // Start serial port
    Serial.begin(115200);
}

void loop () {
    // Get distance in cm
    int distance = sensor.getCentimeter();

    // Write values to serial port
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println("cm");

    // Wait a bit
    delay(500);
}
