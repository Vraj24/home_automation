#include <dht.h>

dht DHT;

#define fan 3
#define bulb 2

#define temper 7

#define trigPin 9
#define echoPin 10

void setup() {

  Serial.begin(9600);
  pinMode(fan, OUTPUT);
  pinMode(bulb, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
}

void loop() {

  int distance;
  long duration;
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; //measure in centimeter
  // Prints the distance on the Serial Monitor

  if(distance<6)
  {
    Serial.print("Some is coming inside...");
  }

  int readData = DHT.read11(temper);
  float t = DHT.temperature;

  if(Serial.available() == 1)
  {
    String val = Serial.readString();
    if(val == "read temperature")
    {
      Serial.print(t);
    }
    if(val == "fan on")
    {
      if(t>=28)
      {
        analogWrite(fan, 255);
      }
      if(t<28 && t>=18)
      {
        analogWrite(fan, 130);
      }
      if(t<18)
      {
        analogWrite(fan, 50);
      }
    }
    if(val == "fan of")
    {
      digitalWrite(fan, LOW);
    }
    if(val == "bulb on")
    {
      digitalWrite(bulb, HIGH);
    }
    if(val == "bulb of")
    {
      digitalWrite(bulb, LOW);
    }
    if(val == "all on")
    {
      digitalWrite(fan, HIGH);
      digitalWrite(bulb, HIGH);
    }
    if(val == "all of")
    {
      digitalWrite(bulb, LOW);
      digitalWrite(fan, LOW);
    }
  }
}