/*
KYGM Services LLC All Rights Reserved
Kevin Gutierrez
11/18/2022
Chicken Heater:
  This project starts a 1500 watt heater if the temperature
  falls below 40*f. This is rechecked every 5 minutes.
  Graph of temperature as a function of time is about
  f(t)=sin(t) as the temperature will rise to 40+a and 
  drop to 40-b with inflection points every 5 minutes.

*/

//defining macros for readability
#define out_low(port,pin) port &= ~(1<<pin)  //example: port = DDRD and pin = 4 for 
#define out_high(port,pin) port |= (1<<pin)
#define set_input(portDirection, pin) portDirection &= ~(1<<pin)
#define set_output(portDirection, pin) portDirection |= (1<<pin)


#include "DHT.h"
#define DHTPIN 4 
const int relay = 3;   // Use 1500W rated relay.
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  Serial.println("Initializing...");
  set_output(DDRD, relay); //repalces pinMode method
 
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float tempc = dht.readTemperature();
  float tempf = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(tempc) || isnan(tempf)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Must send in temp in Fahrenheit!
  float heatIndex = dht.computeHeatIndex(tempf, humidity);

  debugPrintTemp(humidity,tempc,tempf,heatIndex);  

  if(tempf < 38)//69 for testing, 38 for poduction
  {
    out_high(PORTD, relay); //digital pin 4 = PD4
  }
  else
  {
    out_low(PORTD, relay);
  }
          //min * seconds * milliseconds
  int wait = 5 * 60 * 1000; //production wait time -> 5min, develop wait time -> 1000ms
  delay(wait); //switch to wait variable in production
}

void debugPrintTemp(float hum,float tc,float tf,float hi)
{
  Serial.print("Humidity: "); 
  Serial.print(hum);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(tc);
  Serial.print(" *C ");
  Serial.print(tf);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");  
}
