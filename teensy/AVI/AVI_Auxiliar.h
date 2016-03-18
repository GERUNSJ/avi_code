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

#include "AVI_Config.h"


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




/* Filtro Butterworth Lowpass
 * Orden: 5
 * FS = 16000
 * FC = 5000
 * Prewarp
 * Diseñado con: http://www.schwietering.com/jayduino/filtuino/
 * */
//Low pass butterworth filter order=5 alpha1=0.3125 
class  FilterBuLp5
{
	public:
		FilterBuLp5()
		{
			for(int i=0; i <= 5; i++)
				v[i]=0.0;
		}
	private:
		float v[6];
	public:
		float step(float x) //class II 
		{
			v[0] = v[1];
			v[1] = v[2];
			v[2] = v[3];
			v[3] = v[4];
			v[4] = v[5];
			v[5] = (1.275474894240279378e-1 * x)
				 + (-0.01597977975342930110 * v[0])
				 + (-0.14587765445368203188 * v[1])
				 + (-0.52068253004017439611 * v[2])
				 + (-1.16668554287625303445 * v[3])
				 + (-1.23229415444535450597 * v[4]);
			return 
				 (v[0] + v[5])
				+5 * (v[1] + v[4])
				+10 * (v[2] + v[3]);
		}
		
		// Filtrado offline, sobreescribe.
		void filtrar_offline(float* i_arreglo, int i_cantidad);
};



// Filtro de pre énfasis según lo hecho en Praat http://www.fon.hum.uva.nl/praat/manual/Sound__To_Formant__burg____.html
// α = exp (-2 π F Δt)
// xi = xi - α xi-1
class  FilterPreemphasis
{
	public:
		FilterPreemphasis()
		{
			alpha = exp(-2.0*M_PI*50/(float)AUDIO_FS);
			for(int i=0; i < 2; i++)
				v[i]=0.0;
		}
	private:
		float alpha;
		float v[2];
	public:
		// step para uso online
		float step(float x) //class II 
		{
			v[0] = v[1];
			v[1] = x;
			
			return v[1] - alpha*v[0];
		}
		
		// Filtrado offline, sobreescribe.
		void filtrar_offline(float* i_arreglo, int i_cantidad);
		
};


// TODO: Añadir ventana de hamming por acá?

#endif // AVI_AUXILIAR_H
