//=================================================================================================
// AVI_Config.h
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
// - Contiene aquellas definiciones y constantes utiles para todo el programa.
//
//=================================================================================================

#ifndef AVI_CONFIG_H
#define AVI_CONFIG_H

//-------------------------------------------------------------------------------------------------
// GENERAL
#define DEBUG 0
#define ARM_MATH_CM4

//-------------------------------------------------------------------------------------------------
// AUDIO
#define AUDIO_FS 8000 // Frecuencia Muestreo [Hz]
#define AUDIO_TIEMPO_SEGMENTO 25 // Duracion del segmento de grabacion [ms] (a Fs = 8kHz, 25ms = 200 muestras)
const int AUDIO_CANT_MUESTRAS = AUDIO_TIEMPO_SEGMENTO*AUDIO_FS/1000; // Cantidad de muestras
#define UMBRAL_MINIMO 30 // Umbral Minimo de Captura

//-------------------------------------------------------------------------------------------------
// LEDS
#define LEDS_BRILLO 0.1 // De 0 a 1

//-------------------------------------------------------------------------------------------------
// MOTORES
#define MOTORES_TIEMPO_90 500 // Tiempo en milisegundos para giro 90 grados
#define MOTORES_VELOCIDAD_90 50.0 // Velocidad (en porcentaje) para el giro de 90 grados, el de 180 y el de 360

//-------------------------------------------------------------------------------------------------
// FORMANTES
#define FILTRO_PROM_N 5 // Tamaño del Filtro Promediador de Formantes
#define BURG_P 8 // Orden del Filtro AR de Burg
#define TOL_VOCALES 0 // Tolerancia de las vocales
#define TOL_MUESTRA 0 // Tolerancia de las muestras

//-------------------------------------------------------------------------------------------------
// MODOS
#define M1_PROM 5 // Tamaño del Filtro Promediador
#define M1_TS 20 // Tiempo de Muestreo [mseg]

#define M2_PORC_BAJO 25 // Porcentaje del Maximo que se considera Bajo
#define M2_PORC_MEDIO 55 // Porcentaje del Maximo que se considera Medio
#define M2_PORC_ALTO 85 // Porcentaje del Maximo que se considera Alto
#define M2_PROM 5 // Tamaño del Filtro Promediador
#define M2_TS 20 // Tiempo de Muestreo [mseg]

#define M3_TS 20 // Tiempo de Muestreo [mseg]
#define M3_PORC_BAJO 33 // Porcentaje de tiempo para mostrar la primer imagen
#define M3_PORC_MEDIO 66 // Porcentaje de tiempo para mostrar la segunda imagen

#define M4_TS 20 // Tiempo de Muestreo [mseg]

#define M5_TS 20 // Tiempo de Muestreo [mseg]

//-------------------------------------------------------------------------------------------------
// VOCALES
#define A_F1 772
#define A_F2 1305

#define E_F1 440
#define E_F2 2027

#define I_F1 295
#define I_F2 2257

#define O_F1 500
#define O_F2 880

#define U_F1 362
#define U_F2 845

//-------------------------------------------------------------------------------------------------
// TODO

#endif // AVI_CONFIG_H
