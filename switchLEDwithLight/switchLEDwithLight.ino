/* Change lights with light sensor
   Changes which light is on, depending whether light is shine on the light sensor
*/

// These constants won't change
const int sensorPin = A0; // pin that the sensor is attached to // from https://www.arduino.cc/en/tutorial/calibration
const int ledOnePin = 1;     // pin that LED1 is attached to
const int ledTwoPin = 2;     // pin that LED2 is attached to

// Variables:
int sensorValue = 0;      // the sensor value
int sensorMin = 1023;     // minimum sensor value
int sensorMax = 0;        // maximum sensor value

void setup() {
  // turns on LEDs to signal the start of a calibration period and check LEDs
  pinMode(ledOnePin, OUTPUT);
  digitalWrite(ledOnePin, HIGH);
  pinMode(ledTwoPin, OUTPUT);
  digitalWrite(ledTwoPin, HIGH);

  // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  // signal the end of the calibration period
  digitalWrite(ledOnePin, LOW);
  digitalWrite(ledTwoPin, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the sensor
  sensorValue = analogRead(sensorPin);

  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255); // map(value, fromLow, fromHigh, toLow, toHigh)

  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, 0, 255); // constrain(x, a, b) --> a = lower end of the range; b = upper end of the range

  // set either one of the LEDs on depending on incoming light
  if (sensorValue < 128) {
    analogWrite(ledOnePin, HIGH); //turn the first LED on (HIGH is the voltage level)
    analogWrite(ledTwoPin, LOW); //turn the first LED on (HIGH is the voltage level)
  } else {
    analogWrite(ledOnePin, LOW); //turn the first LED on (HIGH is the voltage level)
    analogWrite(ledTwoPin, HIGH); //turn the first LED on (HIGH is the voltage level)
  }
} 

