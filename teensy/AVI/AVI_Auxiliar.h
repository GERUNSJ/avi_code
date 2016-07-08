//=================================================================================================
// AVI_Auxiliar.h
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
// - Contiene clases y métodos auxiliares.
// 
//=================================================================================================
// CLASES:
// - FiltroMA: Filtro Promediador de Media Movil.
//
//=================================================================================================
// METODOS AUXILIARES:
// - pinInit() Inicializacion de Pines.
//
//=================================================================================================

#ifndef AVI_AUXILIAR_H
#define AVI_AUXILIAR_H

// Clase Filtro Moving Average (Promediador)
class FiltroMA
{
  public:
    // Constructor
    FiltroMA(int cant);
    // Metodos
    void cargar(float dato);
    void reiniciar();
    float promedio();
  private:
    // Parametros
    float* _datos;
    int _cant;
};

// Metodos Auxiliares
void pinInit();

#endif // AVI_AUXILIAR_H
