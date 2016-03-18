//=================================================================================================
// AVI_Modo_1.h
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

#ifndef AVI_MODO_1_H
#define AVI_MODO_1_H

#include "Arduino.h"
#include "AVI_Auxiliar.h"
#include "AVI_Config.h"
#include "AVI_Pines.h"
#include "AVI_LEDs.h"

// Variables Globales
extern LEDs leds;

// Realiza el algoritmo del Modo 1
void Modo1(int umbral);

#endif // AVI_MODO_1_H
