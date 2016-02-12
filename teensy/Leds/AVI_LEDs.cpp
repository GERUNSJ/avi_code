#include "AVI_LEDs.h"


LEDs::LEDs(void)
{
	FastLED.addLeds<WS2812B, PIN_LED_DATA> (leds, 50);
  FastLED.setCorrection(  0xB0FFF0 ); // GRB  TypicalSMD5050
 // FastLED.setTemperature( Halogen );
	brillo = LEDS_BRILLO;
}


void LEDs::apagar()
{
	fill_solid(leds, 50, CHSV(0, 0, 0) );
	return;
}


void LEDs::mostrar(IMAGENES img, long color)
{
	//CHSV aux(0,0,brillo);
	//uint8_t color;
	
	switch( img )
	{
		case IMAGENES::CIRCULO:
		{
			#ifdef DEBUG_LEDS
			estado = "CIRCULO";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = CIRCULO;
			break;
		}
		
		case IMAGENES::CARA:
		{
			#ifdef DEBUG_LEDS
			estado = "CARA";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = CARA;
			break;
		}
		
		case IMAGENES::VOL_LOW:
		{
			#ifdef DEBUG_LEDS
			estado = "VOL_LOW";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = VOL_LOW;
			break;
		}
		
		case IMAGENES::VOL_MID:
		{
			#ifdef DEBUG_LEDS
			estado = "VOL_MID";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = VOL_MID;
			break;
		}
		
		case IMAGENES::VOL_HIGH:
		{
			#ifdef DEBUG_LEDS
			estado = "VOL_HIGH";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = VOL_HIGH;
			break;
		}
		
		case IMAGENES::A_IMG:
		{
			#ifdef DEBUG_LEDS
			estado = "A_IMG";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = A_IMG;
			break;
		}
		
		case IMAGENES::E_IMG:
		{
			#ifdef DEBUG_LEDS
			estado = "E_IMG";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = E_IMG;
			break;
		}
		
		case IMAGENES::I_IMG:
		{
			#ifdef DEBUG_LEDS
			estado = "I_IMG";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = I_IMG;
			break;
		}
		
		case IMAGENES::O_IMG:
		{
			#ifdef DEBUG_LEDS
			estado = "O_IMG";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = O_IMG;
			break;
		}
		
		case IMAGENES::U_IMG:
		{
			#ifdef DEBUG_LEDS
			estado = "U_IMG";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = U_IMG;
			break;
		}
		
		case IMAGENES::TIME_SH_A:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_SH_A";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_SH_A;
			break;
		}
		
		case IMAGENES::TIME_SH_B:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_SH_B";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_SH_B;
			break;
		}
		
		case IMAGENES::TIME_MID_A:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_MID_A";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_MID_A;
			break;
		}
		
		case IMAGENES::TIME_MID_B:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_MID_B";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_MID_B;
			break;
		}
		
		case IMAGENES::TIME_LO_A:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_LO_A";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_LO_A;
			break;
		}
		
		case IMAGENES::TIME_LO_B:
		{
			#ifdef DEBUG_LEDS
			estado = "TIME_LO_B";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_LO_B;
			break;
		}
		default:
		{
			#ifdef DEBUG_LEDS
			estado = "DEFAULT";
			Serial.println("Mostrando: " + estado);
			#endif
			
			a_mostrar = TIME_LO_B;
			break;
		}
	}

//  for( int i = 0 ; i<50 ; i++)
//  {
//    Serial.println(leds.leds[i]);
//  }
  
	//void 	fill_solid (struct CHSV *targetArray, int numToFill, const struct CHSV &hsvColor)
//	CRGB auxrgb;
//	CHSV auxhsv(color, 255, brillo);
//	hsv2rgb_rainbow( auxhsv, auxrgb);
//	fill_solid(leds, 50, auxrgb );
  
	
	// Máscara
	for(unsigned int i = 0 ; i < 50 ; i++)
	{
      leds[i].r = (long)((a_mostrar[i] & 0xFF0000 & color) * brillo) >> 16;
      leds[i].g = (long)((a_mostrar[i] & 0x00FF00 & color) * brillo ) >> 8;
      leds[i].b = (long)((a_mostrar[i] & 0x0000FF & color) * brillo ) >> 0;
      Serial.println(leds[i].g,HEX);
      //leds[i] = (a_mostrar[i] & color) * (float)brillo/255;
	}
	
	
	FastLED.show();
}
