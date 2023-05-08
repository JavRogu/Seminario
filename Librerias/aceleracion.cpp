#include "aceleracion.h"

float calcularAceleracion(int pinAnalogico, float sensibilidad, int escala) {
  int valorAnalogico = analogRead(pinAnalogico);
  float aceleracion = (valorAnalogico / escala) * sensibilidad;
  return aceleracion;
}
