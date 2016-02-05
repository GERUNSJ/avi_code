#include "AVI_LEDs.h"

LEDs::LEDs(void)
{
	FastLED.addLeds<WS2812B, PIN_LED_DATA> (leds, 50);
}


LEDs::mostrar(IMAGENES img)
{
	switch( img )
	{
		case IMAGENES::CIRCULO:
		{
			#ifdef DEBUG_LEDS
			estado = "CIRCULO";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = CIRCULO;
			break;
		}
		
		case IMAGENES::CARA:
		{
			#ifdef DEBUG_LEDS
			estado = "CARA";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = CARA;
			break;
		}
		
		case IMAGENES::VOL_LOW:
		{
			#ifdef DEBUG_LEDS
			estado = "VOL_LOW";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = VOL_LOW;
			break;
		}
		
		case IMAGENES::VOL_MID:
		{
			#ifdef DEBUG_LEDS
			estado = "VOL_MID";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = VOL_MID;
			break;
		}
		
		case IMAGENES::VOL_HIGH:
		{
			#ifdef DEBUG_LEDS
			estado = "VOL_HIGH";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = VOL_HIGH;
			break;
		}
		
		case IMAGENES::A_IMG:
		{
			#ifdef DEBUG_LEDS
			estado = "A_IMG";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = A_IMG;
			break;
		}
		
		case IMAGENES::E_IMG:
		{
			#ifdef DEBUG_LEDS
			estado = "E_IMG";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = E_IMG;
			break;
		}
		
		case IMAGENES::I_IMG:
		{
			#ifdef DEBUG_LEDS
			estado = "I_IMG";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = I_IMG;
			break;
		}
		
		case IMAGENES::O_IMG:
		{
			#ifdef DEBUG_LEDS
			estado = "O_IMG";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = O_IMG;
			break;
		}
		
		case IMAGENES::U_IMG:
		{
			#ifdef DEBUG_LEDS
			estado = "U_IMG";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = U_IMG;
			break;
		}
		
		case IMAGENES::TIME_SH_A:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_SH_A";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_SH_A;
			break;
		}
		
		case IMAGENES::TIME_SH_B:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_SH_B";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_SH_B;
			break;
		}
		
		case IMAGENES::TIME_MID_A:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_MID_A";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_MID_A;
			break;
		}
		
		case IMAGENES::TIME_MID_B:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_MID_B";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_MID_B;
			break;
		}
		
		case IMAGENES::TIME_LO_A:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_LO_A";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_LO_A;
			break;
		}
		
		case IMAGENES::TIME_LO_B:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_LO_B";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_LO_B;
			break;
		}
		default:
		{
			#ifdef DEBUG_LEDS
			estado = "DEFAULT";
			println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_LO_B;
			break;
		}
	}
	
	
	for(unsigned int i = 0 ; i < 50 ; i++)
	{
		leds[i] = a_mostrar[i];
	}
	
	
	FastLED.show();
}
