//=================================================================================================
// AVI_Interfaz.h
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
// - Contiene las funciones relacionadas al interfaz de usuario.
// 
//=================================================================================================

#ifndef AVI_INTERFAZ_H
#define AVI_INTERFAZ_H

#include "AVI_Config.h"
#include "AVI_Pines.h"
#include "AVI_LEDs.h"
#include "Arduino.h"

// Enum 
enum class Modos
{
  modo1 = 1,
  modo2 = 2,
  modo3 = 3,
  modo4 = 4,
  modo5 = 5
};

//-------------------------------------------------------------------------------------------------
// Elige el modo.
// Botón 1 (Izquierda) - Avanza.
// Botón 2 (Derecha) - Retrocede.
// Ambos botones presionados - Elige Modo.
// Nota: No se implementan configuraciones de parámetros.
Modos elegir_modo(void);

//-------------------------------------------------------------------------------------------------
// Muestra el modo seleccionado con los LEDs o Puerto Serie.
void mostrar_modo_seleccionado( Modos modo_seleccionado );

#endif // AVI_INTERFAZ_H
 
