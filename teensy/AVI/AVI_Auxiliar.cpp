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
  _datos = new float[cant];
  _cant = cant;
  for(int i=0; i<_cant; i++)
  {
    _datos[i] = 0;
  }
  _prom = 0;
}

// Coloca en 0 todos los elementos
void FiltroMA::reiniciar()
{
  for(int i=0; i<_cant; i++)
  {
    _datos[i] = 0;
  }
}

// Carga un nuevo valor (FIFO)
void FiltroMA::cargar(float dato)
{
  for(int i=_cant-1; i>0; i--)
  {
    _datos[i] = _datos[i-1];
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
