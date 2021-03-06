//=================================================================================================
// AVI_Formantes.h
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
// - https://github.com/RhysU/ar [Collomb2009.cpp]
// - https://forum.pjrc.com/
// - https://github.com/vancegroup/EigenArduino
//
//=================================================================================================
// DESCRIPCION
// - Contiene funciones relacionadas con el calculo de formantes y vocales.
//
//=================================================================================================
// COMENTARIOS GENERALES
// - Los indices del for usan uint8_t. 1 bytes contra 2 bytes de un int.
// - Si se tiene que dividir por 2*pi, se multiplica por una constante DIV_2_PI que es 1/(2*pi).
// - En Eigen: Matrix X c d
//   - X es de filas y columnas dinámicas. Se tiene que definir en el constructor.
//   - c es que los elementos son complejos.
//   - d elementos tipo double. (Queremos buena precision)
//
//=================================================================================================
// DEBUG - VECTORES PREVIAMENTE GRABADOS Y SUS PARAMETROS
// - Vector de datos (extraccion de una A en 8KHz del Edwin?) - los primeros 200 datos
// float x[200] = {-0.30732,-0.082927,0.2878,0.50244,0.48943,0.31057,-0.10244,-0.32358,-0.36585,-0.31057,-0.22602,-0.15447,-0.092683,0.14797,0.18699,0.18699,-0.030894,-0.23577,-0.34634,-0.25203,-0.11545,0.13171,0.30081,0.37561,0.37561,0.31057,0.22927,0.22927,0.17073,0.24228,0.32358,0.37886,0.50894,-0.3561,-0.57398,-0.76911,-0.80813,-0.24228,-0.017886,0.037398,0.11545,0.076423,0.004878,0.30081,0.04065,-0.40813,-0.6065,-0.8439,-0.69106,-0.10894,0.18699,0.33984,0.47967,0.23577,0.21626,0.13496,-0.017886,-0.2748,-0.5187,-0.54472,-0.36585,0.15772,0.38211,0.3626,0.12195,-0.24553,-0.37236,-0.46341,-0.40813,-0.32683,-0.26829,-0.15447,0.043902,0.12846,0.13171,-0.063415,-0.33984,-0.39187,-0.2813,-0.10244,0.18699,0.2878,0.33333,0.31382,0.24228,0.21301,0.25528,0.2813,0.40813,0.41138,0.4374,0.13496,-0.47317,-0.54146,-0.82439,-0.58374,-0.13171,0.13496,0.17398,0.2813,0.19675,0.15122,0.2813,-0.063415,-0.37561,-0.62927,-0.76585,-0.37561,0.14146,0.33008,0.46341,0.44715,0.22276,0.17073,0.004878,-0.099187,-0.29106,-0.42764,-0.43415,-0.13821,0.16748,0.34959,0.31707,-0.0081301,-0.31707,-0.43415,-0.47967,-0.38537,-0.27805,-0.21951,-0.060163,0.11545,0.14472,0.043902,-0.16748,-0.29431,-0.35285,-0.24228,-0.043902,0.14472,0.2748,0.33008,0.32033,0.24878,0.21626,0.23902,0.27805,0.32358,0.3626,0.49593,0.16748,-0.48618,-0.49268,-0.8374,-0.56423,-0.092683,0.099187,0.12846,0.21301,0.13171,0.21626,0.32033,-0.12195,-0.4374,-0.66829,-0.77236,-0.3626,0.13496,0.33984,0.46016,0.37886,0.15447,0.21626,0.066667,-0.12195,-0.33333,-0.52846,-0.52195,-0.13496,0.18699,0.33659,0.25203,-0.060163,-0.38862,-0.46667,-0.50244,-0.40488,-0.34634,-0.26179,-0.099187,0.047154,0.092683,-0.001626,-0.23577,-0.35935,-0.37886,-0.2748,-0.050407,0.17073,0.32358};
//
// - Este es con Hamming:
// float x[200] = {-0.024585,-0.006653,0.023288,0.041231,0.040948,0.026622,-0.009038,-0.029507,-0.034609,-0.030575,-0.023221,-0.016600,-0.010438,0.017491,0.023227,0.024427,-0.004247,-0.034114,-0.052752,-0.040406,-0.019477,0.023373,0.056127,0.073640,0.077327,0.067088,0.051926,0.054399,0.042402,0.062926,0.087814,0.107334,0.150385,-0.109645,-0.183996,-0.256445,-0.280025,-0.087166,-0.006676,0.014467,0.046250,0.031679,0.002091,0.133171,0.018575,-0.192339,-0.294556,-0.422043,-0.355615,-0.057643,0.101655,0.189680,0.274686,0.138427,0.130090,0.083122,-0.011272,-0.177074,-0.341549,-0.366291,-0.251080,0.110403,0.272644,0.263567,0.090250,-0.184890,-0.285150,-0.360691,-0.322682,-0.262342,-0.218518,-0.127592,0.036756,0.108951,0.113109,-0.055113,-0.298744,-0.348264,-0.252614,-0.092908,0.171197,0.265855,0.310516,0.294670,0.229195,0.202918,0.244777,0.271353,0.395890,0.401078,0.428415,0.132737,-0.467096,-0.536236,-0.818687,-0.581034,-0.131338,0.134766,0.173894,0.281285,0.196737,0.151142,0.280898,-0.063237,-0.373869,-0.624915,-0.758461,-0.370788,0.139134,0.323302,0.451807,0.433744,0.214886,0.163705,0.004647,-0.093831,-0.273295,-0.398370,-0.401035,-0.126537,0.151897,0.313942,0.281790,-0.007147,-0.275567,-0.372839,-0.406841,-0.322638,-0.229666,-0.178788,-0.048292,0.091277,0.112637,0.033620,-0.126117,-0.217804,-0.256476,-0.172868,-0.030731,0.099316,0.184786,0.217349,0.206412,0.156778,0.133195,0.143783,0.163248,0.185297,0.202386,0.269606,0.088615,-0.250186,-0.246395,-0.406693,-0.265903,-0.042351,0.043910,0.055051,0.088297,0.052764,0.083660,0.119555,-0.043876,-0.151563,-0.222830,-0.247587,-0.111648,0.039878,0.096278,0.124881,0.098402,0.038364,0.051312,0.015099,-0.026344,-0.068623,-0.103607,-0.097388,-0.023951,0.031547,0.053961,0.038387,-0.008705,-0.053419,-0.060962,-0.062410,-0.047860,-0.039006,-0.028133,-0.010190,0.004642,0.008767,-0.000148,-0.020802,-0.030804,-0.031697,-0.022550,-0.004079,0.013698,0.025886};
//
// - Parametros
// int x_n = 200; // Cantidad de Elementos del Vector de Datos
// int p = 10; // Orden del Filtro
// int Fs = 8000; // Frecuencia de Muestreo
//
//=================================================================================================

#ifndef AVI_FORMANTES_H
#define AVI_FORMANTES_H

#include <Eigen30.h>
#include <Eigen/Eigenvalues>
#include "Arduino.h"
#include "AVI_Config.h"

// Funcion de intercambio (tipo float)
void swap(float *x, float *y);

// Funcion de intercambio (tipo std::complex<float>)
void complex_swap(std::complex<float> *x, std::complex<float> *y);

// Aplica una ventanda de Hamming al vector de entrada
void hamming(float* vector, int longitud);

// Con el punto y las tolerancias, busca la vocal
int getVocal(int f1, int f2);

// Algoritmo Convencional de Burg
// Fuente: https://github.com/RhysU/ar [Collomb2009.cpp]
// En coeffs devuelve los coeficientes del filtro estimado
// x es la señal a partir de la cual se estimará un filtro de solo polos
// x_n es la cantidad de elementos de x
// p es el orden del filtro a estimar
void BurgAlgorithm(float* coeffs,  float* x , int x_n, int p, int Fs);

// Obtener formantes a partir del segmento de sonido
// x es la señal a la cual se le estimarán los formantes
// p es el orden del filtro a estimar
// en x1 y x2 se devuelven los 2 primeros formantes encontrados. Si 
// no, se devuelven 0s.
void obtener_formantes(float* x, int x_n, int p, int Fs, int* f1, int* f2);

#endif // AVI_FORMANTES_H 
