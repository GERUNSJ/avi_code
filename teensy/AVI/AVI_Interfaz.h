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

#ifndef AVI_INTERFAZ_H
#define AVI_INTERFAZ_H


enum class MODOS
{
	modo1 = 0,
	modo2 = 1,
	modo3 = 2,
	modo4 = 3,
	modo5 = 4
};

/* Esta función elige un modo. El modo elegido será procesado en el programa principal, para llamar a
 * las funciones del modo correspondiente.
 * 
 * Oprimiendo y soltando un botón se circula entre los modos, que serán mostrados en la matriz. 
 * Un botón avanza el número, el otro retrocede. Oprimiendo y soltando los dos botones se elige el modo.
 * No se implementan configuraciones de parámetros, ya que hay que verificar cuáles son los que DEBEN
 * ser configurables. */

MODOS elegir_modo(void);


void mostrar_modo_seleccionado( MODOS modo_seleccionado );


#endif // AVI_INTERFAZ_H
 
