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
// DESCRIPCION
// - Contiene clases y métodos auxiliares.
// 
//=================================================================================================
// CLASES:
// - FiltroMA: Filtro Promediador de Media Movil.
//
//=================================================================================================
// METODOS AUXILIARES:
// - pinInit() Inicializacion de Pines.
//
//=================================================================================================

#include "Arduino.h"
#include "AVI_Auxiliar.h"
#include "AVI_Pines.h"

//=================================================================================================
// CLASES
//=================================================================================================

// Constructor
FiltroMA::FiltroMA(int cant)
{
  _datos = new float[cant];
  _cant = cant;
  for(int i=0; i<_cant; i++)
  {
    _datos[i] = 0;
  }
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

//=================================================================================================
// METODOS AUXILIARES
//=================================================================================================

void pinInit()
{
  // Los Motores inicializan sus pines en su clase.
  // Los LEDs inicializan sus pines en su clase.

  // Botones
  pinMode(PIN_BOTON_1, INPUT_PULLUP);
  pinMode(PIN_BOTON_2, INPUT_PULLUP);

  // Audio
  pinMode(PIN_MIC_GATE, INPUT);
}