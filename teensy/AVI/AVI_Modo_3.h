//=================================================================================================
// AVI_Modo_3.h
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

#ifndef AVI_MODO_3_H
#define AVI_MODO_3_H

#include "Arduino.h"
#include "AVI_Config.h"
#include "AVI_Pines.h"
#include "AVI_LEDs.h"

// Variables Globales
extern LEDs leds;

// Realiza el algoritmo del Modo 3
void Modo3(int umbral, int segundos);

#endif // AVI_MODO_3_H
