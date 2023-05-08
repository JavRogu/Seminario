#ifndef API_REST_ESP32_H
#define API_REST_ESP32_H

#include <WiFi.h>

class APIRestESP32 {
public:
  APIRestESP32(const char* serverUrl);
  void sendData(float accX, float accY, float accZ, const String& dateTime);
  
private:
  const char* serverUrl;
};

#endif
