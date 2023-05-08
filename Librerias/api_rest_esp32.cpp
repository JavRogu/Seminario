#include "api_rest_esp32.h"
#include <HTTPClient.h>

APIRestESP32::APIRestESP32(const char* serverUrl) {
  this->serverUrl = serverUrl;
}

void APIRestESP32::sendData(float accX, float accY, float accZ, const String& dateTime) {
  // Crear el JSON con los datos
  String jsonPayload = "{";
  jsonPayload += "\"aceleracion_x\": " + String(accX) + ",";
  jsonPayload += "\"aceleracion_y\": " + String(accY) + ",";
  jsonPayload += "\"aceleracion_z\": " + String(accZ) + ",";
  jsonPayload += "\"fecha_hora\": \"" + dateTime + "\"";
  jsonPayload += "}";

  // Realizar la solicitud HTTP POST
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonPayload);

  // Verificar la respuesta del servidor
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respuesta del servidor: " + response);
  } else {
    Serial.println("Error en la solicitud HTTP: " + String(httpResponseCode));
  }

  http.end();

  // Esperar un tiempo antes de enviar la siguiente solicitud
  delay(5000);
}
