#ifndef GPS_H
#define GPS_H


#include <TinyGPS++.h>

extern SoftwareSerial gpsSerial;
extern TinyGPSPlus gps;
extern double latitude;
extern double longitude;
extern int year;
extern int month;
extern int day;
extern int hour;
extern int minute;
extern int second;

void setupGPS();
void obtenerDatosGPS();

#endif
