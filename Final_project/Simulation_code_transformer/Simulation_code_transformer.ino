#include <SimpleDHT.h>


// pin Configuration, 
int pinDHT11 = 2;
int levelPin = A0;
int voltagePin = A1;
int currentPin = A2;
int ledPin = 6;
int motorPin = 7;

// Global Variables Initialisation
int levelValue = 0;
int voltageValue = 0;
int currentValue = 0;
float currentSclValue = 0;

bool tempHi = 0;

SimpleDHT11 dht11;

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
    digitalWrite(motorPin, LOW);
    digitalWrite(ledPin, LOW);
}

void loop() 
{
// start working...
  Serial.println("=================================");
  Serial.println("Sample from Transformer");
  
// read without samples.
  byte temperature = 0;
  byte humidity = 0;

// Error Message.  
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
// read the values from the sensor:
  levelValue = analogRead(levelPin);
  voltageValue = analogRead(voltagePin);
  currentValue = analogRead(currentPin);

// Scale the values:
  float level= levelValue * (100.0 / 1023.0);  
  float voltage= voltageValue * (5.0 / 1023.0);
  float currentSclValue = map(currentValue, 512.0, 647, 0.0, 1023.0);
  float current= currentSclValue * (10.0 / 1023.0);
  

// Output the Data
  Serial.print(" Ampere: ");     Serial.print(current);           Serial.println(" A");
  Serial.print(" Volt: ");       Serial.print(voltage);           Serial.println(" V");
  Serial.print(" level: ");      Serial.print((int)level);        Serial.println(" cm");
  Serial.print(" Temp: ");       Serial.print((int)temperature);  Serial.println(" *C");
  Serial.print(" Humidity: ");   Serial.print((int)humidity);     Serial.println(" *H");

// Flag setting for the Cooling system
    if(temperature>45)
    {
      tempHi = 1;
    }
    else
    {
      tempHi = 0;
    }

// Cooling system Control
    if(tempHi == 1)
    {
      digitalWrite(motorPin, HIGH);
      digitalWrite(ledPin, HIGH);
    }
    else
    {
      digitalWrite(motorPin, LOW);
      digitalWrite(ledPin, LOW);      
    }
 
 // sampling rate is 1HZ.
  delay(1000);
}
