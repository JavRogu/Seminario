#include "aceleracion.h"
#include <WiFi.h>
#include "wifi_helper.h"
#include "api_rest_esp32.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "SPIFFS.h"

const char* serverUrl = "http://tu_servidor.com/api/datos-aceleracion";
APIRestESP32 apiRest(serverUrl);

#define RXD2 16
#define TXD2 17
#define NMEA 0

char Trama_NMEA = 0;

TinyGPSPlus gps;
HardwareSerial neogps(1);

const char* ssid = "Redmi Note 8";
const char* password = "jav199806";

// Pin analógico al que está conectado el acelerómetro
const int PIN_X = 34;
const int PIN_Y = 35;
const int PIN_Z = 13;

// Sensibilidad del acelerómetro según el rango
const float sensibilidad = 1000.0; // 1000mV/g para el rango de +-2g
//const float sensibilidad = 333.0; // 333mV/g para el rango de +-6g

// Rango máximo de la conversión analógica a digital (12 bits)
const int escala = 4095;

String readAccelerations() {
  // Obtener los valores de aceleración en los ejes X, Y y Z
  float accelerationX = calcularAceleracion(PIN_X, sensibilidad, escala);
  float accelerationY = calcularAceleracion(PIN_Y, sensibilidad, escala);
  float accelerationZ = calcularAceleracion(PIN_Z, sensibilidad, escala);

  // Crear un objeto JSON con los datos de aceleración
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["acceleracionX"] = accelerationX;
  jsonDoc["acceleracionY"] = accelerationY;
  jsonDoc["acceleracionZ"] = accelerationZ;

  // Convertir el objeto JSON a una cadena
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  return jsonString;
}


void setup() {
  Serial.begin(9600);
  conectarWiFi(ssid, password);

  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/accelerations", HTTP_GET, [](AsyncWebServerRequest *request) {
  request->send(200, "application/json", readAccelerations());
});

}

void loop() {
  // Leer el valor de aceleración
  float aceleracionX = calcularAceleracion(PIN_X, sensibilidad, escala);
  float aceleracionY = calcularAceleracion(PIN_Y, sensibilidad, escala);
  float aceleracionZ = calcularAceleracion(PIN_Z, sensibilidad, escala);
  
  if (NMEA)
 {
    while (neogps.available())
    {
     Trama_NMEA  = (char)neogps.read(); 
     Serial.print (Trama_NMEA);
    }
 } 
  if(neogps.available() > 0) {
    if (gps.encode(neogps.read())) {
      if (gps.location.isValid() && gps.date.isValid() && gps.time.isValid()) {
        // Obtener latitud, longitud, fecha y hora
        double latitude = gps.location.lat();
        double longitude = gps.location.lng();
        int year = gps.date.year();
        int month = gps.date.month();
        int day = gps.date.day();
        int hour = gps.time.hour();
        int minute = gps.time.minute();
        int second = gps.time.second();
      }
    }
  }
  
  sprintf(fechaHora, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
  apiRest.sendData(aceleracionX, aceleracionX, aceleracionX, fechaHora);




  delay(1000);
}
