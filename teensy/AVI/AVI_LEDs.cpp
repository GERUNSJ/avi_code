//=================================================================================================
// AVI_LEDs.cpp
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
// - Contiene todo lo utilizado por las tiras de LED WS2812B.
// 
//=================================================================================================

#include "AVI_LEDs.h"

#define DEBUG_LEDS 0

// Constructor de LEDs
LEDs::LEDs(void)
{
  FastLED.addLeds<WS2812B, PIN_LED_DATA> (leds, 50);
  FastLED.setCorrection(0xB0FFF0); // GRB TypicalSMD5050
  FastLED.setTemperature(Halogen);
	brillo = LEDS_BRILLO;
}

// Apagar todo. Escribe NEGRO en todos los LEDs
void LEDs::apagar()
{
	this->mostrar(IMAGENES::circulo, 0x000000, 0x000000);
	return;
}

// Mostrar Imagen indicada en el color indicado
void LEDs::mostrar(IMAGENES img, long color, long color_b)
{
	//CHSV aux(0,0,brillo);
	//uint8_t color;
	
	switch(img)
	{
		case IMAGENES::circulo:
		{
			#if DEBUG_LEDS == 1
			estado = "circulo";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = circulo;
      a_mostrar_b = circulo;
			break;
		}
		
		case IMAGENES::cara:
		{
			#if DEBUG_LEDS == 1
			estado = "cara";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = cara;
      a_mostrar_b = cara;
			break;
		}
		
		case IMAGENES::m2_img_standby:
		{
			#if DEBUG_LEDS == 1
			estado = "m2_img_standby";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = m2_img_standby;
      a_mostrar_b = m2_img_standby;
			break;
		}
		
		case IMAGENES::m2_img_bajo:
		{
			#if DEBUG_LEDS == 1
			estado = "m2_img_bajo";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = m2_img_bajo;
      a_mostrar_b = m2_img_bajo;
			break;
		}
		
    case IMAGENES::m2_img_medio:
    {
      #if DEBUG_LEDS == 1
      estado = "m2_img_medio";
      Serial.println("---- LEDs: Mostrando: "  + estado);
      #endif // DEBUG_LEDS == 1
      
      a_mostrar = m2_img_medio;
      a_mostrar_b = m2_img_medio;
      break;
    }

    case IMAGENES::m2_img_alto:
    {
      #if DEBUG_LEDS == 1
      estado = "m2_img_alto";
      Serial.println("---- LEDs: Mostrando: "  + estado);
      #endif // DEBUG_LEDS == 1
      
      a_mostrar = m2_img_alto;
      a_mostrar_b = m2_img_alto;
      break;
    }

    case IMAGENES::m3_img_standby:
    {
      #if DEBUG_LEDS == 1
      estado = "m3_img_standby";
      Serial.println("---- LEDs: Mostrando: "  + estado);
      #endif // DEBUG_LEDS == 1
      
      a_mostrar = m3_img_standby;
      a_mostrar_b = m3_img_standby;
      break;
    }
    
    case IMAGENES::m3_img_bajo:
    {
      #if DEBUG_LEDS == 1
      estado = "m3_img_bajo";
      Serial.println("---- LEDs: Mostrando: "  + estado);
      #endif // DEBUG_LEDS == 1
      
      a_mostrar = m3_img_bajo_a;
      a_mostrar_b = m3_img_bajo_b;
      break;
    }
    
    case IMAGENES::m3_img_medio:
    {
      #if DEBUG_LEDS == 1
      estado = "m3_img_medio";
      Serial.println("---- LEDs: Mostrando: "  + estado);
      #endif // DEBUG_LEDS == 1
      
      a_mostrar = m3_img_medio_a;
      a_mostrar_b = m3_img_medio_b;
      break;
    }

    case IMAGENES::m3_img_alto:
    {
      #if DEBUG_LEDS == 1
      estado = "m3_img_alto";
      Serial.println("---- LEDs: Mostrando: "  + estado);
      #endif // DEBUG_LEDS == 1
      
      a_mostrar = m3_img_alto_a;
      a_mostrar_b = m3_img_alto_b;
      break;
    }
		
		case IMAGENES::a_img:
		{
			#if DEBUG_LEDS == 1
			estado = "a_img";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = a_img;
      a_mostrar_b = a_img;
			break;
		}
		
		case IMAGENES::e_img:
		{
			#if DEBUG_LEDS == 1
			estado = "e_img";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = e_img;
      a_mostrar_b = e_img;
			break;
		}
		
		case IMAGENES::i_img:
		{
			#if DEBUG_LEDS == 1
			estado = "i_img";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = i_img;
      a_mostrar_b = i_img;
			break;
		}
		
		case IMAGENES::o_img:
		{
			#if DEBUG_LEDS == 1
			estado = "o_img";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = o_img;
      a_mostrar_b = o_img;
			break;
		}
		
		case IMAGENES::u_img:
		{
			#if DEBUG_LEDS == 1
			estado = "u_img";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = u_img;
      a_mostrar_b = u_img;
			break;
		}
		
		case IMAGENES::numero_1:
		{
			#if DEBUG_LEDS == 1
			estado = "numero_1";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = numero_1;
      a_mostrar_b = numero_1;
			break;
		}
		
		case IMAGENES::numero_2:
		{
			#if DEBUG_LEDS == 1
			estado = "numero_2";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = numero_2;
      a_mostrar_b = numero_2;
			break;
		}
		
		case IMAGENES::numero_3:
		{
			#if DEBUG_LEDS == 1
			estado = "numero_3";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = numero_3;
      a_mostrar_b = numero_3;
			break;
		}
		
		case IMAGENES::numero_4:
		{
			#if DEBUG_LEDS == 1
			estado = "numero_4";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = numero_4;
      a_mostrar_b = numero_4;
			break;
		}
		
		case IMAGENES::numero_5:
		{
			#if DEBUG_LEDS == 1
			estado = "numero_5";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = numero_5;
      a_mostrar_b = numero_5;
			break;
		}
		
		case IMAGENES::full_led:
		{
			#if DEBUG_LEDS == 1
			estado = "full_estado";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = full_led;
      a_mostrar_b = full_led;
			break;
		}
		
		default:
		{
			#if DEBUG_LEDS == 1
			estado = "DEFAULT";
			Serial.println("---- LEDs: Mostrando: "  + estado);
			#endif // DEBUG_LEDS == 1
			
			a_mostrar = circulo;
      a_mostrar_b = circulo;
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
  
	
	// Máscara //GRB
	for(unsigned int i = 0 ; i < 50 ; i++)
	{
    leds[i].r = (long)((((a_mostrar[i] & color) | (a_mostrar_b[i] & color_b)) & 0xFF0000) >> 16 ) * brillo;
    leds[i].g = (long)((((a_mostrar[i] & color) | (a_mostrar_b[i] & color_b)) & 0x00FF00) >> 8  ) * brillo;
    leds[i].b = (long)((((a_mostrar[i] & color) | (a_mostrar_b[i] & color_b)) & 0x0000FF) >> 0  ) * brillo;
    //Serial.println(leds[i].g,HEX);
    //leds[i] = (a_mostrar[i] & color) * (float)brillo/255;
	}
	
	FastLED.show();
}
