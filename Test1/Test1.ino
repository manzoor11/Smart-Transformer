#include <DHT.h>

dht DHT;

#define DHT11_PIN 4

void setup(){
  Serial.begin(9600);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
 
  Serial.print("Temp = ");
  Serial.print(DHT.temperature);
  Serial.print(" Humidity = ");
  Serial.print(DHT.humidity);
  Serial.println(" ");
 
}
