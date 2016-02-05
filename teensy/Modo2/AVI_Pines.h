//=================================================================================================
// AVI_Pines.h
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
// FUENTES
// - Diagrama de Pines
//
//=================================================================================================
// DESCRIPCION
// - Definicion de pines de la Teensy 3.1
//
//=================================================================================================
// COMENTARIOS GENERALES
// - Los nombres comienzan con "PIN" y se separan con "_".
// - Los motores se nombran con letras de A a D.
// - "PWM_n" indica el PWM del motor n.
// - La polaridad de los motores se indica con "MOTOR_n_1" y "MOTOR_n_2"
//
//=================================================================================================

#ifndef AVI_PINES_H
#define AVI_PINES_H

//-------------------------------------------------------------------------------------------------
// Motor A
#define PIN_PWM_A 3
#define PIN_MOTOR_A_1 7
#define PIN_MOTOR_A_2 8

//-------------------------------------------------------------------------------------------------
// Motor B
#define PIN_PWM_B 4
#define PIN_MOTOR_B_1 11
#define PIN_MOTOR_B_2 12

//-------------------------------------------------------------------------------------------------
// Motor C
#define PIN_PWM_C 5
#define PIN_MOTOR_C_1 19
#define PIN_MOTOR_C_2 18

//-------------------------------------------------------------------------------------------------
// Motor D
#define PIN_PWM_D 6
#define PIN_MOTOR_D_1 17
#define PIN_MOTOR_D_2 16

//-------------------------------------------------------------------------------------------------
// Otros
#define PIN_BOTON_1 0
#define PIN_BOTON_2 1
#define PIN_LED_DATA 9
#define PIN_MIC_GATE 13
#define PIN_MIC_ENVOLVENTE A0 // Pin digital 14
#define PIN_MIC_AUDIO A1 // Pin digital 15

#endif // AVI_PINES_H
