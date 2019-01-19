int SENSOR_PIN_1 = A0; // the pin the first sensor is connected to
int SENSOR_PIN_2 = A1; // the pin the second sensor is connected to
int SENSOR_PIN_3 = A2; // the pin the third sensor is connected to
int SENSOR_PIN_4 = A3; // the pin the fourth sensor is connected to
int RESISTOR_VALUE = 560; // resistor value, in Ohms

float ZERO_VALUE = 1585.62; // the zero value given by the sensor
float MAX_VALUE = 313.29; // the maximum value given by the sensor

int counter = 0;

void setup(void) {
  Serial.begin(9600);
  analogReference(EXTERNAL);
}

void loop(void) {
 
  float waterLevel1 = readResistance(SENSOR_PIN_1, RESISTOR_VALUE);
  float waterLevel2 = readResistance(SENSOR_PIN_2, RESISTOR_VALUE);
  float waterLevel3 = readResistance(SENSOR_PIN_3, RESISTOR_VALUE);
  float waterLevel4 = readResistance(SENSOR_PIN_4, RESISTOR_VALUE);
  
  Serial.print(counter);
  Serial.print(" - ");
  Serial.print("Water level: ");
  Serial.print(formatWaterLevel(waterLevel1), 4);
  Serial.print(", ");
  Serial.print(formatWaterLevel(waterLevel2), 4);
  Serial.print(", ");
  Serial.print(formatWaterLevel(waterLevel3), 4);
  Serial.print(", ");
  Serial.print(formatWaterLevel(waterLevel4), 4);
  Serial.println();
  
  counter++;
  
  delay(1000);
}

// http://www.ryanbyrd.net/techramble/2013/02/22/8
// https://learn.adafruit.com/smart-measuring-cup/calibration
float readResistance(int pin, int seriesResistance) {
  // convert the sensor reading to resistance
  float resistance = analogRead(pin);
  resistance = (1023.0 / resistance) - 1.0;
  resistance = seriesResistance / resistance;
  return resistance;
}

float formatWaterLevel(float waterLevel) {
  if (waterLevel <= ZERO_VALUE && waterLevel >= MAX_VALUE) {
    return (ZERO_VALUE - waterLevel) / (ZERO_VALUE - MAX_VALUE);
  }
  return 0;
}
