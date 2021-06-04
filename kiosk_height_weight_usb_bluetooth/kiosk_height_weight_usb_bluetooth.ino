#include <HX711.h>
const int out = 2;
const int clck = 3;
const int trigPin = 10; const int echoPin = 11; float refDistance; long duration;
int resetPin = 8;
float sensing[15];
const int trigPin1 = 12; const int echoPin1 = 13;
HX711 scale(out, clck); byte i = '0';
float CalibrationFactor = -22070;  // Replace -12000 the calibration factor.
float cmdi1, cmdi2, cmdi0;

void setup()
{
  digitalWrite(resetPin, HIGH);
  delay(200);
  pinMode(resetPin, OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  Serial.println("reset");
  //Serial.println("Press 'T' or 't' to tare");
  scale.set_scale(CalibrationFactor);
  scale.tare();
}

void loop()
{
  if (Serial.available()) {
    i = Serial.read();
  }
  if (i == 't')
  {
    Serial.print("Weight: ");
    Serial.print(scale.get_units(), 3);
    Serial.println(" Kilogram");
    scale.tare();
    i = '0';
    delay(10);
    yield();
  }
  if (i == 'z')
  {
    delay(10);
    digitalWrite(resetPin, LOW);
    delay(10);
    Serial.println("mission_impossible");
  }
  if (i == '0') {
    float d1 = cmdistance1();
    float d2 = cmdistance2();
    float w = weight_measurement();
    //delay(10);

    //    for (int counter = 0; counter < 2;  counter++) {
    //      sensing[counter] = cmdi[counter];
    //    }
    Serial.println((String)d1 + ',' + (String)d2 + ',' + (String)w);

    //Serial.write('/n');
    yield();
  }
}

float cmdistance1() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(50);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(50);
  digitalWrite(trigPin, LOW);
  float d = pulseIn(echoPin, HIGH);
  float ref = ((d / 2) / 29.1);
  ref = 213 - ref;
  //Serial.print("height: ");
  //Serial.print(refDistance);
  //Serial.print(',');
  //Serial.print('/');
  return ref;
}

float cmdistance2() {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(50);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(50);
  digitalWrite(trigPin1, LOW);
  float d1 = pulseIn(echoPin1, HIGH);
  float ref1 = ((d1 / 2) / 29.1);
  ref1 = 213 - ref1;
  //Serial.print("height: ");
  //Serial.print(refDistance);
  //Serial.print(',');
  //Serial.print('/');
  return ref1;
}
float weight_measurement() {
  //Serial.print("Weight: ");
  float weight = scale.get_units();
  //Serial.print(weight);
  //Serial.print('/');
  //  Serial.println('/n');
  //Serial.println(scale.get_units(), 3);
  //Serial.println(" Kilogram");
  if (Serial.available())
  {
    char var = Serial.read();
    if (var == 't')
    {
      scale.tare();
    }
    if (var == 'T')
    {
      scale.tare();
    }
  }
  return weight;
}
