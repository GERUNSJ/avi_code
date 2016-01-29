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

#ifndef AVI_FORMANTES_H
#define AVI_FORMANTES_H

// Funcion de intercambio (tipo float)
void swap(float *x, float *y);

// Funcion de intercambio (tipo std::complex<float>)
void complex_swap(std::complex<float> *x, std::complex<float> *y);

// Aplica una ventanda de Hamming al vector de entrada
void hamming(float* vector, int longitud);

// Con el punto y las tolerancias, busca la vocal
char getVocal(int f1, int f2);

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
