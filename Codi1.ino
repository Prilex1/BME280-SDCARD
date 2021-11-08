#include <SD.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_BME280.h>
 
#define SEALEVELPRESSURE_HPA (1022)  
Adafruit_BME280 bme;
#define SSpin 10
File archivo;

void setup()
{
  Serial.begin(9600);
  if (!bme.begin(0x76)) 
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);

      Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(SSpin)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

}

 
void loop()
{
float tiempoold = millis();
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  float humidity = bme.readHumidity();

archivo = SD.open("DATALOG.txt", FILE_WRITE);

if (archivo){
  archivo.println("-------------------------");
  
  archivo.println(F("Temperatura = "));
  archivo.println(temperature);
  
  archivo.println(F("Pressio = "));
  archivo.println(pressure);
 
  archivo.println(F("Altitud Aproximada = "));
  archivo.println(altitude);
 
  archivo.println(F("Humitat = "));
  archivo.println(humidity);
}
  Serial.print(F("Temperatura = "));
  Serial.print(temperature);
  Serial.println(F("*C"));
 
  Serial.print(F("Pressio = "));
  Serial.print(pressure);
  Serial.println(F("hPa"));
 
  Serial.print(F("Altitud Aproximada = "));
  Serial.print(altitude);
  Serial.println(F("m"));
 
  Serial.print(F("Humitat = "));
  Serial.print(humidity);
  Serial.println(F("%"));

  archivo.close();

  while (millis()<tiempoold + 30000)

  Serial.print("");
}


//THX MONICA SERRA, SERGI ALBERT,...
