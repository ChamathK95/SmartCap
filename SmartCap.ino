// Ultrasonic Sensor Pins
const int trigPin = 9;    // Trigger pin for the Ultrasonic Sensor
const int echoPin = 8;    // Echo pin for the Ultrasonic Sensor

// PIR Motion Sensor Pin
const int pirPin = 7;     // Output pin for the PIR Motion Sensor

// Vibration Motors Control Pins
const int motor1Pin = 5;  // Control pin for Vibration Motor 1
const int motor2Pin = 6;  // Control pin for Vibration Motor 2

// Variables for distance measurement
long duration;            // Variable to store the duration of the ultrasonic pulse
int distance;             // Variable to store the calculated distance

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);

  // Ultrasonic sensor pins setup
  pinMode(trigPin, OUTPUT);  // Set the trigPin as OUTPUT
  pinMode(echoPin, INPUT);   // Set the echoPin as INPUT

  // PIR motion sensor pin setup
  pinMode(pirPin, INPUT);    // Set the pirPin as INPUT

  // Vibration motor control pins setup
  pinMode(motor1Pin, OUTPUT); // Set motor1Pin as OUTPUT
  pinMode(motor2Pin, OUTPUT); // Set motor2Pin as OUTPUT

  // Initial state of vibration motors OFF
  digitalWrite(motor1Pin, LOW);
  digitalWrite(motor2Pin, LOW);
}

void loop() {
  // Measure distance using Ultrasonic Sensor
  measureDistance();

  // Read PIR Motion Sensor value
  int motionDetected = digitalRead(pirPin);

  // Control vibration motors based on sensor readings
  if (distance <= 50 || motionDetected == HIGH) {  // If an obstacle is within 50 cm or motion is detected
    activateMotors();    // Activate both vibration motors
    Serial.println("Obstacle or Motion Detected!");
  } else {
    deactivateMotors();  // Turn off both vibration motors
  }

  delay(200);  // Short delay to avoid rapid switching
}

void measureDistance() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)
  
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void activateMotors() {
  digitalWrite(motor1Pin, HIGH);  // Turn on Motor 1
  digitalWrite(motor2Pin, HIGH);  // Turn on Motor 2
}

void deactivateMotors() {
  digitalWrite(motor1Pin, LOW);   // Turn off Motor 1
  digitalWrite(motor2Pin, LOW);   // Turn off Motor 2
}
