//=================================================================================================
// AVI_Auxiliar.cpp
//
// Aguado, Pablo.
// Areche, Ariadna.
// Barragan, Edwin.
// Icard, Nicolas.
// Mas, German Emilio.
// 
// Año 2016
//
//=================================================================================================

#include "Arduino.h"
#include "AVI_Auxiliar.h"

// Constructor
FiltroMA::FiltroMA(int cant)
{
  Serial.println("Constructor!");
  _datos = new float[cant];
  _cant = cant;
  Serial.println("Inicializacion");
  for(int i=0; i<_cant; i++)
  {
    _datos[i] = 0;
    Serial.println(_datos[i]);
  }
  _prom = 0;
}

// Carga un nuevo valor (FIFO)
void FiltroMA::cargar(float dato)
{
  Serial.println("Valores Antes y Despues");
  for(int i=_cant-1; i>0; i--)
  {
    Serial.print("Antes:\t");
    Serial.print(_datos[i]);
    _datos[i] = _datos[i-1];
    Serial.print("\tDespues:\t");
    Serial.println(_datos[i]);
  }
  _datos[0] = dato;  
}

// Devuelve el Promedio
float FiltroMA::promedio()
{
  float suma = 0;
  for(int i=0; i<_cant; i++)
  {
    suma += _datos[i];
  }
  return (suma /= _cant);
}
