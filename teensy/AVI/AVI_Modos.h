//=================================================================================================
// AVI_Modos.h
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

#ifndef AVI_MODOS_H
#define AVI_MODOS_H

#include "Arduino.h"
#include "AVI_Auxiliar.h"
#include "AVI_Config.h"
#include "AVI_Pines.h"
#include "AVI_LEDs.h"

// Variables Globales
extern LEDs leds;

// Funciones
void Modo1(int umbral);
void Modo2(int umbral);
void Modo3(int umbral, int segundos);
void Modo4(void);
void Modo5(void);

#endif // AVI_MODOS_H
