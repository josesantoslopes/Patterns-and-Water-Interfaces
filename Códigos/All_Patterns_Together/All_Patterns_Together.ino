int SENSOR_PIN_1 = A0; // the pin the first sensor is connected to
int SENSOR_PIN_2 = A1; // the pin the second sensor is connected to
int SENSOR_PIN_3 = A2; // the pin the third sensor is connected to
int SENSOR_PIN_4 = A3; // the pin the fourth sensor is connected to
int RESISTOR_VALUE = 560; // resistor value, in Ohms

float ZERO_VALUE = 1585.62; // the zero value given by the sensor
float MAX_VALUE = 313.29; // the maximum value given by the sensor

float previousValue1 = 0;
float previousValue2 = 0;

void setup(void) {
  Serial.begin(9600);
  analogReference(EXTERNAL);
}

void loop(void) {
 
  float waterLevel1 = readResistance(SENSOR_PIN_1, RESISTOR_VALUE);
  float waterLevel2 = readResistance(SENSOR_PIN_2, RESISTOR_VALUE);
  float waterLevel3 = readResistance(SENSOR_PIN_3, RESISTOR_VALUE);
  float waterLevel4 = readResistance(SENSOR_PIN_4, RESISTOR_VALUE);
  
  
  /*
  Serial.print("Water level: ");
  Serial.print(formatWaterLevel(waterLevel1), 4);
  Serial.print(", ");
  Serial.print(formatWaterLevel(waterLevel2), 4);
  Serial.print(", ");
  Serial.print(formatWaterLevel(waterLevel3), 4);
  Serial.print(", ");
  Serial.print(formatWaterLevel(waterLevel4), 4);
  Serial.println();
  */
  
  if ( previousValue1 != 0 && formatWaterLevel(waterLevel1) != 0){
    if ( putIntoWater(previousValue1,previousValue2,formatWaterLevel(waterLevel1),formatWaterLevel(waterLevel2)) == 1 ){
      Serial.print("Put something into water");
      Serial.println();
    }
    else if ( swirlWater(previousValue1,previousValue2,formatWaterLevel(waterLevel1),formatWaterLevel(waterLevel2)) == 1 ){
      Serial.print("Swirling the water");
      Serial.println();
    }
    else if ( removeWater(previousValue1,previousValue2,formatWaterLevel(waterLevel1),formatWaterLevel(waterLevel2)) == 1 ){
      Serial.print("Taking out some water");
      Serial.println();
    }
    else if ( flapWater(previousValue1,previousValue2,formatWaterLevel(waterLevel1),formatWaterLevel(waterLevel2)) == 1 ){
      Serial.print("Flaping the water");
      Serial.println();
    }
    else if ( moveWater(previousValue1,previousValue2,formatWaterLevel(waterLevel1),formatWaterLevel(waterLevel2)) == 1 ){
      Serial.print("Moving the water");
      Serial.println();
    }
  }
  previousValue1 = formatWaterLevel(waterLevel1);
  previousValue2 = formatWaterLevel(waterLevel2);
  
  delay(1000);
}
//Returns 1 if something is put into water
int putIntoWater ( float pValue1, float pValue2, float value1, float value2 ){
  if ( value1 > pValue1 && value2 > pValue2 ){
    return 1;
  }
  else{
    return 0;
  }
}
//Returns 1 if something is put into water
int removeWater ( float pValue1, float pValue2, float value1, float value2 ){
  if ( value1 < pValue1 && value2 < pValue2 ){
    return 1;
  }
  else{
    return 0;
  }
}
//Returns 1 is you are swirling the water
int swirlWater ( float pValue1, float pValue2, float value1, float value2 ){
  if  ( variation((pValue1 + 0.4),value1,0.5) == 1 && variation((pValue2 + 0.4),value2,0.5) == 1 ){
    return 1;
  }
  else{
    return 0;
  }
}
//Returns 1 if you are flaping the water
int flapWater ( float pValue1, float pValue2, float value1, float value2 ){
  if  ( variation((pValue1 + 0.2),value1,0.1) == 1 && variation((pValue2 + 0.2),value2,0.1) == 1 ){
    return 1;
  }
  else{
    return 0;
  }
}
//Returns 1 if you are moving the water
int moveWater ( float pValue1, float pValue2, float value1, float value2 ){
  if  ( variation((pValue1 + 0.45),value1,0.2) == 1 && variation((pValue2 + 0.2),value2,0.2) == 1 ){
    return 1;
  }
  else{
    return 0;
  }
}

int variation ( float stableValue, float newValue, float variation ){
  if ( newValue > 0 && stableValue > 0){
    if ( newValue > (stableValue - variation) && newValue < (stableValue + variation) ){
      return 1;
    }
    else{
      return 0;
    }
  }
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
