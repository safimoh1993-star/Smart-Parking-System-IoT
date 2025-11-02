#include <LiquidCrystal.h>

// Initialize the LCD. (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define pins for ultrasonic sensors and LEDs
const int trigPin1 = 6;
const int echoPin1 = 7;
const int trigPin2 = 8;
const int echoPin2 = 9;

const int greenLed1 = A0;
const int redLed1 = A1;
const int greenLed2 = A2;
const int redLed2 = A3;

// Variables to store distances
long duration1, distance1;
long duration2, distance2;

void setup() {
  lcd.begin(16, 2); // Set up the LCD 16x2
  lcd.print("Smart Parking");

  // Initialize pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(greenLed1, OUTPUT);
  pinMode(redLed1, OUTPUT);
  pinMode(greenLed2, OUTPUT);
  pinMode(redLed2, OUTPUT);

  delay(2000);
  lcd.clear();
}

void loop() {
  // Read parking spot 1
  distance1 = getDistance(trigPin1, echoPin1);
  if(distance1 < 15) { // Spot occupied
    digitalWrite(redLed1, HIGH);
    digitalWrite(greenLed1, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Spot 1: Occupied ");
  } else { // Spot free
    digitalWrite(redLed1, LOW);
    digitalWrite(greenLed1, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Spot 1: Free     ");
  }

  // Read parking spot 2
  distance2 = getDistance(trigPin2, echoPin2);
  if(distance2 < 15) { // Spot occupied
    digitalWrite(redLed2, HIGH);
    digitalWrite(greenLed2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Spot 2: Occupied ");
  } else { // Spot free
    digitalWrite(redLed2, LOW);
    digitalWrite(greenLed2, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Spot 2: Free     ");
  }

  delay(500); // Update every 0.5 sec
}

// Function to measure distance using ultrasonic sensor
long getDistance(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}
