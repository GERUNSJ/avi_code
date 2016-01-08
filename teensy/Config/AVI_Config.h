#ifndef AVI_CONFIG_H
#define AVI_CONFIG_H

//=================================================================================================
// TODO
//
// LEDS
// MOTORES
// MODOS
// - umbrales
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// DEBUG
#define DEBUG 0

//-------------------------------------------------------------------------------------------------
// AUDIO
#define AUDIO_FS 8000 // Frecuencia Muestreo [Hz]
#define AUDIO_TIEMPO_SEGMENTO 25 // Duracion del segmento de grabacion [ms] (a Fs = 8kHz, 25ms = 200 muestras)
const int AUDIO_CANT_MUESTRAS = AUDIO_TIEMPO_SEGMENTO*1000/AUDIO_FS; // Cantidad de muestras
#define UMBRAL_MINIMO 30 // Umbral Minimo de Captura

//-------------------------------------------------------------------------------------------------
// FORMANTES
#define FILTRO_PROM_N 10 // Tamaño del Filtro Promediador de Formantes
#define BURG_P 10 // Orden del Filtro AR de Burg
#define TOL_VOCALES 0 // Tolerancia de las vocales
#define TOL_MUESTRA 0 // Tolerancia de las muestras

// Vocales
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


#endif
