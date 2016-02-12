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
// COMENTARIOS GENERALES
// - Se usa define para constantes numericas y "const" para formulas y arreglos.
// - Si se tiene que dividir por 2*pi, se multiplica por una constante DIV_2_PI que es 1/(2*pi).
// - La constante PI_2 es 2*pi para simplificar calculo.
// - En Eigen: Matrix X c d
//   - X es de filas y columnas dinámicas. Se tiene que definir en el constructor.
//   - c es que los elementos son complejos.
//   - d elementos tipo double. (Queremos buena precision)
//
//=================================================================================================
// TODO
//
// LEDS
// MOTORES
// MODOS
// - umbrales
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
#define LEDS_BRILLO 128	//0-255

//-------------------------------------------------------------------------------------------------
// MOTORES
#define MOTORES_TIEMPO_90	500	// Tiempo en milisegundos para giro 90 grados
#define MOTORES_VELOCIDAD_90	50.0	// Velocidad (en porcentaje) para el giro de 90 grados, el de 180 y el de 360

//-------------------------------------------------------------------------------------------------
// FORMANTES
#define FILTRO_PROM_N 10 // Tamaño del Filtro Promediador de Formantes
#define BURG_P 10 // Orden del Filtro AR de Burg
#define TOL_VOCALES 0 // Tolerancia de las vocales
#define TOL_MUESTRA 0 // Tolerancia de las muestras

//-------------------------------------------------------------------------------------------------
// MODOS
#define M1_PROM 5 // Tamaño del Filtro Promediador
#define M1_TS 20 // Tiempo de Muestreo [mseg]

#define M2_ALTO 85 // Porcentaje del Maximo que se considera Alto
#define M2_MEDIO 55 // Porcentaje del Maximo que se considera Medio
#define M2_BAJO 25 // Porcentaje del Maximo que se considera Bajo
#define M2_PROM 5 // Tamaño del Filtro Promediador
#define M2_TS 20 // Tiempo de Muestreo [mseg]

#define M3_TS 20 // Tiempo de Muestreo [mseg]
#define M3_MEDIO 60 // Sobre que Porcentaje del Umbral se considera Medio

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
