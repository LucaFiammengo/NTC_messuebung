#include <Arduino.h>

#define NTC_PIN A0
#define R1 2200.0 
#define VCC 5.0 

void setup()
{
  Serial.begin(9600);
  Serial.println("Temperaturmessung :)");
}

float voltageNTC = 0;
unsigned long previousMillis = 0;
const long interval = 500;

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int adcValue = analogRead(NTC_PIN);
    float voltageNTC = (adcValue / 1023.0) * VCC;

    float voltageR1 = VCC - voltageNTC; 
    float current = voltageR1 / R1; 
    float resistanceNTC = voltageNTC / current; 

    float temperature = 1.0 / (1.0 / 298.15 + (1.0 / 3977.0) * log10(resistanceNTC / 2200.0));

    float tempC = temperature - 273.15;

    float tempCorrected = 0.4028 * exp(0.1425 * tempC);
    Serial.println(tempCorrected);
  }
}