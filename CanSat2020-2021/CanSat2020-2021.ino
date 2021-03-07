#include <Wire.h>
#include <SPI.h> //Needed for the BMP280 sensor 
#include <Adafruit_Sensor.h> //Needed for the BMP220
#include "Adafruit_BMP280.h" //It's in the name

Adafruit_BMP280 bmp;


//Those are all pins Analog Pins in the arduino (A0 = 0,A1 = 1...)
int pressurePin = 1; // the MPX 4115A goes to pin A1
int ThermistorPin = 0; // the thermistor goes to pin A0
int altimeterforBMP;    //for BMP
//for thermistor
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
//end of thermistor 
float pressurefromBMP;    //To store the barometric pressure (Pa)
float temperaturefromBMP;  //To store the temperature (Celcius)
float readPressurefromMPX(int pin){
    int pressureValue = analogRead(pin);
    float pressure=((pressureValue/1024.0)+0.095)/0.000009;
    return pressure;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(6900);
  bmp.begin();    //Begin the sensor
  Serial.println("Adafruit BMP280 test:");

}



void loop() {
  // put your main code here, to run repeatedly:

  float pressurefromMPX = readPressurefromMPX(A1);
  float millibars = pressurefromMPX/100;

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
  Serial.print("Temperature Sensor :");
  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" F"); 
  Serial.print("Pressure Sensor :");
  Serial.print("Pressure = ");
  Serial.println(pressurefromMPX);
  Serial.print("pascals");
  delay(500);
}






void loop() {
  //Read values from the sensor:
  pressure = bmp.readPressure();
  temperature = bmp.readTemperature();
  altimeter = bmp.readAltitude (1050.35); //Change the "1050.35" to your city current barrometric pressure (https://www.wunderground.com)
  
  //Print values to serial monitor:
  Serial.print(F("Pressure: "));
    Serial.print(pressure);
    Serial.print(" Pa");
    Serial.print("\t");
    Serial.print(("Temp: "));
    Serial.print(temperature);
    Serial.print(" oC");
  Serial.print("\t");
    Serial.print("Altimeter: ");
    Serial.print(altimeter); // this should be adjusted to your local forcase
    Serial.println(" m");
    
