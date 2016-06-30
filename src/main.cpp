#include "Arduino.h"
#include "Servo.h"

// Main Engine vibration Servo
Servo mainEngineServo;

// Piezo vibration sensor at Board - Analog Input A0
const int vibrationSensor = A0;

// Store current Pin resp. for switching
const int switchPin = 2;

// LED mappings on Board
const int yellowLED = 3;
const int greenLED = 4;
const int redLED = 5;

// Current values of vibration sensored and
int vibrationIntensity = 0;
int seriousEventOccurence = 0;

// Current Switch value
int switchVal;

// Vibration Thresholds
const int lowVibration = 10;
const int highVibration = 100;

// Conditional Variables
boolean normalOperation = false;


// user-define Functions go on-top
void checkForVibration() {

  vibrationIntensity = analogRead(vibrationSensor);

  if(vibrationIntensity > lowVibration && vibrationIntensity < highVibration) {

    digitalWrite(yellowLED, HIGH);

    delay(50);

    digitalWrite(yellowLED, LOW);
    Serial.print("Vibration detected with intensity of: ");
    Serial.println(vibrationIntensity);

    delay(20);

    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);

  }
  else if (vibrationIntensity >= highVibration){

    seriousEventOccurence++;

    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);

    Serial.println("");
    Serial.print("Minor vibration detected with intensity of: ");
    Serial.println(vibrationIntensity);

    Serial.print("Major vibration detected. The Component's vibration intensity has exceeded the max threshold by: ");
    Serial.println(vibrationIntensity - highVibration);

    Serial.print("This condition has been raised ");
    Serial.print(seriousEventOccurence);
    Serial.println(" times since the last maintenance job of this component.");
    Serial.println("In order to avoid downtime, please consider either overhauling or replacing the component.");
    Serial.println("Pausing monitoring for 5 seconds...");

    delay(5000);

    Serial.println("Monitoring activated again!");

  }
  else {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
  }
}

void setup()
{
      mainEngineServo.attach(9);

      pinMode(yellowLED, OUTPUT);
      pinMode(redLED, OUTPUT);
      pinMode(greenLED, OUTPUT);
      pinMode(switchPin, INPUT);

      Serial.begin(9600);

      digitalWrite(greenLED, HIGH);
      mainEngineServo.write(0);

      Serial.begin(9600);
}


void loop() {
  while(true){
      checkForVibration();
  }
}
