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
// METODOS
// - pinInit(): Inicializa los pines
//
//=================================================================================================

#include "Arduino.h"
#include "AVI_Auxiliar.h"

//-------------------------------------------------------------------------------------------------
// CLASES

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

//-------------------------------------------------------------------------------------------------
// METODOS
void pinInit()
{
  // Motores (Redundante. Se inicializan en los constructores)
  pinMode(PIN_PWM_A, OUTPUT);
  pinMode(PIN_MOTOR_A_1, OUTPUT);
  pinMode(PIN_MOTOR_A_2, OUTPUT);
  pinMode(PIN_PWM_B, OUTPUT);
  pinMode(PIN_MOTOR_B_1, OUTPUT);
  pinMode(PIN_MOTOR_B_2, OUTPUT);
  pinMode(PIN_PWM_C, OUTPUT);
  pinMode(PIN_MOTOR_C_1, OUTPUT);
  pinMode(PIN_MOTOR_C_2, OUTPUT);
  pinMode(PIN_PWM_D, OUTPUT);
  pinMode(PIN_MOTOR_D_1, OUTPUT);
  pinMode(PIN_MOTOR_D_2, OUTPUT);

  // Botones
  pinMode(PIN_BOTON_1, INPUT_PULLUP);
  pinMode(PIN_BOTON_2, INPUT_PULLUP);

  // LED
  pinMode(PIN_LED_DATA, OUTPUT);

  // Microfono - Los analogicos no se declaran
  pinMode(PIN_MIC_GATE, INPUT);
}
