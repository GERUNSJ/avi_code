//=================================================================================================
// AVI_Interfaz.cpp
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

#include "AVI_Interfaz.h"
#include "Arduino.h"
#include "AVI_Config.h"
#include "AVI_Pines.h"
#include "AVI_LEDs.h"

#define CON_TECLADO 0 // '1' apreta el boton1, 'q' lo suelta. '2' apreta el boton2, 'w' lo suelta.
#define DEBUG_INTERFAZ 0

#define CANTIDAD_DE_MODOS 5


extern LEDs leds;


MODOS elegir_modo(void)
{
	static bool boton1_actual = 0;
	static bool boton1_anterior = 0;
	static bool boton1_ha_sido_apretado = false;
	static bool boton1_ha_sido_soltado = false;
	
	static bool boton2_actual = 0;
	static bool boton2_anterior = 0;
	static bool boton2_ha_sido_apretado = false;
	static bool boton2_ha_sido_soltado = false;
	
	static bool decision_tomada = false;
	
	static int modo_seleccionado = (int) MODOS::modo1; // El cast puede ser implícito también
	
	while( decision_tomada == false )
	{
		
		mostrar_modo_seleccionado( (MODOS) modo_seleccionado ); // Cast explícito de int a enum
		
		// Actualización y Lectura ( HIGH == TRUE, LOW == FALSE )
		boton1_anterior = boton1_actual;
		boton2_anterior = boton2_actual;
					
		
#if CON_TECLADO == 0
		boton1_actual = digitalRead( PIN_BOTON_1 );
		boton2_actual = digitalRead( PIN_BOTON_2 );
#endif

#if CON_TECLADO == 1
		char letra = Serial.read();
		if( letra == '1' )
			boton1_actual = 1;
		else if( letra == 'q' )
			boton1_actual = 0;
		if( letra == '2' )
			boton2_actual = 1;
		else if( letra == 'w' )
			boton2_actual = 0;
#endif
		
		// Evaluación
		if( boton1_actual && !boton1_anterior )
		{
			boton1_ha_sido_apretado = true;
			boton1_ha_sido_soltado = false;
		}
		else if( !boton1_actual && boton1_anterior )
		{
			boton1_ha_sido_soltado = true;
			boton1_ha_sido_apretado = false;
		}
		if( boton2_actual && !boton2_anterior )
		{
			boton2_ha_sido_apretado = true;
			boton2_ha_sido_soltado = false;
		}
		else if( !boton2_actual && boton2_anterior )
		{
			boton2_ha_sido_soltado = true;
			boton2_ha_sido_apretado = false;
		}
		
		//
		if( boton1_ha_sido_soltado )
		{
			boton1_ha_sido_soltado = false;
			
			// Avanzar 1
			modo_seleccionado ++;
			if( modo_seleccionado >= CANTIDAD_DE_MODOS )
				modo_seleccionado = 0;
		}
		else if( boton2_ha_sido_soltado )
		{
			boton2_ha_sido_soltado = false;
			
			// Retroceder 1
			modo_seleccionado --;
			if( modo_seleccionado < 0 )
				modo_seleccionado = CANTIDAD_DE_MODOS -1 ;
		}
		else if( boton1_ha_sido_apretado && boton2_ha_sido_apretado )
		{
			boton1_ha_sido_apretado = false;
			boton2_ha_sido_apretado = false;
			
			// Tomar decision
			decision_tomada = true;
		}
		
#if DEBUG_INTERFAZ == 1
		Serial.print("boton1_actual = ");
		Serial.println((int)boton1_actual);
		Serial.print("boton2_actual = ");
		Serial.println((int)boton2_actual);
		
		Serial.print("boton1_ha_sido_apretado = ");
		Serial.println((int)boton1_ha_sido_apretado);
		Serial.print("boton1_ha_sido_soltado = ");
		Serial.println((int)boton1_ha_sido_soltado);
		Serial.print("boton2_ha_sido_apretado = ");
		Serial.println((int)boton2_ha_sido_apretado);
		Serial.print("boton2_ha_sido_soltado = ");
		Serial.println((int)boton2_ha_sido_soltado);
		Serial.print("decision_tomada = ");
		Serial.println((int)decision_tomada);
		Serial.print("modo_seleccionado = ");
		Serial.println((int)modo_seleccionado);
	
		delay(2000);
#endif
		
	}
	
	return (MODOS) modo_seleccionado; // Cast explícito de int a enum
}





void mostrar_modo_seleccionado( MODOS modo_seleccionado )
{
	if( modo_seleccionado == MODOS::modo1 )
		leds.mostrar( IMAGENES::numero_1, c_azul );
	else if( modo_seleccionado == MODOS::modo2 )
		leds.mostrar( IMAGENES::numero_2, c_azul );
	else if( modo_seleccionado == MODOS::modo3 )
		leds.mostrar( IMAGENES::numero_3, c_azul );
	else if( modo_seleccionado == MODOS::modo4 )
		leds.mostrar( IMAGENES::numero_4, c_azul );
	else if( modo_seleccionado == MODOS::modo5 )
		leds.mostrar( IMAGENES::numero_5, c_azul );
	
	return;
}
