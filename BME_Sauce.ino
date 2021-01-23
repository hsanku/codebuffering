/***
  Read Our Complete Guide: https://RandomNerdTutorials.com/bme680-sensor-arduino-gas-temperature-humidity-pressure/
  
  Designed specifically to work with the Adafruit BME680 Breakout ----> http://www.adafruit.com/products/3660 These sensors use I2C or SPI to communicate, 2 or 4 pins are required to interface. Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit! Written by Limor Fried & Kevin Townsend for Adafruit Industries. BSD license, all text above must be included in any redistribution
 ***/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

/*#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10*/

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C
//Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
char flag;
String flagunion;
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("BME680 async test"));

  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  Serial.println("Temprature/Pressure/Humidity/Gas_Resistance/altitude")
}

void loop() {
  // Tell BME680 to begin measurement.
  unsigned long endTime = bme.beginReading();
  if (endTime == 0) {
    Serial.println(F("Failed to begin reading :("));
    return;
  }
  
  



  
   // This represents parallel work.
  // There's no need to delay() until millis() >= endTime: bme.endReading()
  // takes care of that. It's okay for parallel work to take longer than
  // BME680's measurement time.

  // Obtain measurement results from BME680. Note that this operation isn't
  // instantaneous even if milli() >= endTime due to I2C/SPI latency.
  if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
  }
  // bme.temprature
  //bme.pressure/100.0
  //bme.humidity
  //bme.gas_resistance / 1000.0
  //bme.readAltitude(SEALEVELPRESSURE_HPA)
  //millis = measurement duration
  
  Serial.print(bme.temperature);
  Serial.print("/");
  Serial.print(bme.pressure / 100.0);
  Serial.print("/");
  Serial.print(bme.humidity);
  Serial.print("/");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.print("/");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  
  Serial.println();
  delay(100);
  
   delay(2000);

}
