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

#ifndef AVI_AUXILIAR_H
#define AVI_AUXILIAR_H

// Clase Filtro Moving Average (Promediador)
class FiltroMA
{
  public:
    FiltroMA(int cant);
    void cargar(float dato);
    float promedio();
  private:
    float* _datos;
    int _cant;
    float _prom;
};

#endif // AVI_AUXILIAR_H
