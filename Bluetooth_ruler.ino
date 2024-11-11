#include <SoftwareSerial.h> // Include the SoftwareSerial library for Bluetooth communication

// Define pins for the ultrasonic sensor
const int trigPin = 9;  // Pin to send the trigger signal
const int echoPin = 10;  // Pin to receive the echo signal

// Define pins for the HC-05 Bluetooth module
const int bluetoothTX = 11; // Arduino TX pin connected to HC-05 RX pin
const int bluetoothRX = 12; // Arduino RX pin connected to HC-05 TX pin

// Create a SoftwareSerial object for the HC-05 Bluetooth module
SoftwareSerial BTSerial(bluetoothRX, bluetoothTX); // RX, TX

void setup() {
  // Initialize serial communication for debugging and monitoring
  Serial.begin(9600);       // Set up Serial Monitor communication at 9600 baud
  BTSerial.begin(9600);     // Set up communication with HC-05 Bluetooth module at 9600 baud
  
  // Set the trigPin as an OUTPUT to send the trigger signal
  pinMode(trigPin, OUTPUT);
  
  // Set the echoPin as an INPUT to receive the echo signal
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clear the trigPin to ensure a clean trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // Wait for 2 microseconds

  // Set the trigPin HIGH for 10 microseconds to send a trigger pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Wait for 10 microseconds
  digitalWrite(trigPin, LOW); // Set the trigPin back to LOW

  // Read the echoPin; this returns the duration of the echo signal in microseconds
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  // The speed of sound is approximately 34300 cm/s (or 0.0343 cm/us)
  float distance = (duration * 0.0343) / 2; // Divide by 2 to account for the sound traveling to the object and back

  // Print the distance to the Serial Monitor for debugging
  Serial.print("Distance: "); // Print the text "Distance: "
  Serial.print(distance); // Print the calculated distance
  Serial.println(" cm"); // Print " cm" to indicate the unit of measurement

  // Send the distance to the HC-05 Bluetooth module for wireless transmission
  BTSerial.print("Distance: "); // Send the text "Distance: " via Bluetooth
  BTSerial.print(distance); // Send the calculated distance via Bluetooth
  BTSerial.println(" cm"); // Send " cm" to indicate the unit of measurement

  // Wait a bit before measuring again to prevent flooding with data
  delay(1000); // Delay for 1 second before the next measurement
}
