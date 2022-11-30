/*
Copyright: KYGM Services LLC All Rights Reserved
11-14-2022
Kevin Gutierrez
*/

int relay = 1;
int therm = 0;
float voltage;
float R1;
float logR2, R2,T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {

  Serial.begin(9600);

}

void loop() {

  voltage = analogRead(therm);
  R2 = R1 * (1023.0 / (float)voltage - 1.0);
  logR2 = log(R2);

  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 

  //temperature = T
  if(T <= 40)
  {
    digitalWrite(relay, HIGH);
  }
  else
  {
    digitalWrite(relay, LOW);
  }
  delay(500);
  Serial.println(T);
  //int minutes = 5;
  //delay(minutes*60*1000); //wait five minutes before turning heater on again
  

}