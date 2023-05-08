#include "gps.h"

#define RXD2 16
#define TXD2 17

TinyGPSPlus gps;
HardwareSerial neogps(1);


double latitude = 0.0;
double longitude = 0.0;
int year = 0;
int month = 0;
int day = 0;
int hour = 0;
int minute = 0;
int second = 0;

void setupGPS() {
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
  delay(1000);
}

void obtenerDatosGPS() {
  // Obtener datos de ubicación, fecha y hora del módulo GPS
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid() && gps.date.isValid() && gps.time.isValid()) {
        // Obtener latitud, longitud, fecha y hora
        latitude = gps.location.lat();
        longitude = gps.location.lng();
        year = gps.date.year();
        month = gps.date.month();
        day = gps.date.day();
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();

      }
    }
  }
}
