//=================================================================================================
// AVI_Modo_2.cpp
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

#include "Arduino.h"
#include "AVI_Config.h"
#include "AVI_Pines.h"
#include "AVI_LEDs.h"
#include "AVI_Modo_2.h"

#define DEBUG_MODO_2 1

// Variables Globales
extern LEDs leds;
static bool flag_llenado_de_ceros = false;

// Funciones
void Modo2(int umbral_max)
{
  // Estados
  enum Estados
  {
    verde,
    standby,
    bajo,
    medio,
    alto,
    rojo
  };
  static Estados estado = verde;
  
  // Base de Tiempo
  static unsigned long t_anterior = 0;
  unsigned long t_actual;
  int t_verde = 2000/M2_TS; // 2 Segundos
  int t_delay = 3000/M2_TS; // 2 Segundos
  int t_rojo = 2000/M2_TS; // 2 Segundos

  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_rojo = LOW;
  static boolean flag_ok = LOW; // Si se cumplio o no el objetivo
  static boolean flag_bajo = LOW;
  static boolean flag_medio = LOW;
  static boolean flag_alto = LOW;
  static boolean flag_standby = LOW;
  
  // Contadores
  static int contador = 0;

  // Otros
  static unsigned int envolvente = 0;
  static unsigned int arreglo_envolvente[M2_PROM];
	
	
	if( !flag_llenado_de_ceros )
	{
		// Llenado de ceros
		for( int i = 0 ; i < M2_PROM ; i++ )
		{
			arreglo_envolvente[i] = 0;
		}
		flag_llenado_de_ceros = true;
	}


  t_actual = millis();
  if((t_actual - t_anterior) >= M2_TS)
  {
    t_anterior = t_actual;
    switch(estado)
    {
      //-------------------------------------------------------------------------------------------------
      case verde:
      if(!flag_verde)
      {
        flag_verde = HIGH;
        leds.mostrar(IMAGENES::circulo, c_verde);
        contador = 0;
      }
      contador++;
      if(contador >= t_verde)
      {
        flag_verde = LOW;
        estado = standby;
        contador = 0;
				
				// Llenado de ceros
				for( int i = 0 ; i < M2_PROM ; i++ )
				{
					arreglo_envolvente[i] = 0;
				}
				flag_llenado_de_ceros = true;
								
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case standby:
      if(!flag_standby)
      {
        flag_standby = HIGH;
        leds.mostrar(IMAGENES::m2_img_standby, c_azul);
      }
      
      // Actualización
			for( int i = M2_PROM-1 ; i > 0 ; i-- ) // Desde el último elemento hasta el segundo
			{
				arreglo_envolvente[i] = arreglo_envolvente[i-1];
			}
			arreglo_envolvente[0] = analogRead(PIN_MIC_ENVOLVENTE);
			//Serial.println(arreglo_envolvente[0]);
			
			// Cálculo del promedio
			envolvente = 0;
			for( int i = 0 ; i < M2_PROM ; i++ )
			{
				envolvente += arreglo_envolvente[i];  
			}
			envolvente = envolvente / M2_PROM;
      
      
      // Chequea Alto
      if(envolvente >= (umbral_max*M2_PORC_ALTO/100))
      {
        flag_ok = HIGH;
        flag_standby = LOW;
        estado = alto;
        contador = 0;
      }
      //Chequea Medio
      if((envolvente < (umbral_max*M2_PORC_ALTO/100))&&(envolvente >= (umbral_max*M2_PORC_MEDIO/100)))
      {
        flag_ok = HIGH;
        flag_standby = LOW;
        estado = medio;
        contador = 0;
      }
      //Chequea Bajo
      if((envolvente < (umbral_max*M2_PORC_MEDIO/100))&&(envolvente >= (umbral_max*M2_PORC_BAJO/100)))
      {
        flag_ok = HIGH;
        flag_standby = LOW;
        estado = bajo;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente < (umbral_max*M2_PORC_BAJO/100))
      {
        contador++;
        if(contador >= t_delay)
        {
          if(flag_ok)
          {
            estado = verde;
            flag_standby = LOW;
            flag_ok = LOW;
          }
          else
          {
            flag_standby = LOW;
            estado = rojo;
          }
        }
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case bajo:
      if(!flag_bajo)
      {
        flag_bajo = HIGH;
        leds.mostrar(IMAGENES::m2_img_bajo, c_azul);
        contador = 0;
      }
      
      
      // Actualización
			for( int i = M2_PROM-1 ; i > 0 ; i-- ) // Desde el último elemento hasta el segundo
			{
				arreglo_envolvente[i] = arreglo_envolvente[i-1];
			}
			arreglo_envolvente[0] = analogRead(PIN_MIC_ENVOLVENTE);
			//Serial.println(arreglo_envolvente[0]);
			
			// Cálculo del promedio
			envolvente = 0;
			for( int i = 0 ; i < M2_PROM ; i++ )
			{
				envolvente += arreglo_envolvente[i];  
			}
			envolvente = envolvente / M2_PROM;
      
      
      // Chequea Alto
      if(envolvente >= (umbral_max*M2_PORC_ALTO/100))
      {
        flag_ok = HIGH;
        flag_bajo = LOW;
        estado = alto;
        contador = 0;
      }
      //Chequea Medio
      if((envolvente < (umbral_max*M2_PORC_ALTO/100))&&(envolvente >= (umbral_max*M2_PORC_MEDIO/100)))
      {
        flag_ok = HIGH;
        flag_bajo = LOW;
        estado = medio;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente < (umbral_max*M2_PORC_BAJO/100))
      {
        flag_bajo = LOW;
        estado = standby;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case medio:
      if(!flag_medio)
      {
        flag_medio = HIGH;
        leds.mostrar(IMAGENES::m2_img_medio, c_azul);
        contador = 0;
      }
      
      
      // Actualización
			for( int i = M2_PROM-1 ; i > 0 ; i-- ) // Desde el último elemento hasta el segundo
			{
				arreglo_envolvente[i] = arreglo_envolvente[i-1];
			}
			arreglo_envolvente[0] = analogRead(PIN_MIC_ENVOLVENTE);
			//Serial.println(arreglo_envolvente[0]);
			
			// Cálculo del promedio
			envolvente = 0;
			for( int i = 0 ; i < M2_PROM ; i++ )
			{
				envolvente += arreglo_envolvente[i];  
			}
			envolvente = envolvente / M2_PROM;
      
      
      // Chequea Alto
      if(envolvente >= (umbral_max*M2_PORC_ALTO/100))
      {
        flag_ok = HIGH;
        flag_medio = LOW;
        estado = alto;
        contador = 0;
      }
      //Chequea Bajo
      if((envolvente < (umbral_max*M2_PORC_MEDIO/100))&&(envolvente >= (umbral_max*M2_PORC_BAJO/100)))
      {
        flag_ok = HIGH;
        flag_medio = LOW;
        estado = bajo;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente < (umbral_max*M2_PORC_BAJO/100))
      {
        flag_medio = LOW;
        estado = standby;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case alto:
      if(!flag_alto)
      {
        flag_alto = HIGH;
        leds.mostrar(IMAGENES::m2_img_alto, c_azul);
        contador = 0;
      }
      
      
      // Actualización
			for( int i = M2_PROM-1 ; i > 0 ; i-- ) // Desde el último elemento hasta el segundo
			{
				arreglo_envolvente[i] = arreglo_envolvente[i-1];
			}
			arreglo_envolvente[0] = analogRead(PIN_MIC_ENVOLVENTE);
			//Serial.println(arreglo_envolvente[0]);
			
			// Cálculo del promedio
			envolvente = 0;
			for( int i = 0 ; i < M2_PROM ; i++ )
			{
				envolvente += arreglo_envolvente[i];  
			}
			envolvente = envolvente / M2_PROM;
      
      
      //Chequea Medio
      if((envolvente < (umbral_max*M2_PORC_ALTO/100))&&(envolvente >= (umbral_max*M2_PORC_MEDIO/100)))
      {
        flag_ok = HIGH;
        flag_alto = LOW;
        estado = medio;
        contador = 0;
      }
      //Chequea Bajo
      if((envolvente < (umbral_max*M2_PORC_MEDIO/100))&&(envolvente >= (umbral_max*M2_PORC_BAJO/100)))
      {
        flag_ok = HIGH;
        flag_alto = LOW;
        estado = bajo;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente < (umbral_max*M2_PORC_BAJO/100))
      {
        flag_alto = LOW;
        estado = standby;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case rojo:
      if(!flag_rojo)
      {
        flag_rojo = HIGH;
        leds.mostrar(IMAGENES::circulo, c_rojo);
        contador = 0;
      }
      contador++;
      if(contador >= t_rojo)
      {
        flag_rojo = LOW;
        estado = verde;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      default:
      // Reinicia
      flag_verde = LOW;
      flag_rojo = LOW;
      flag_ok = LOW; // Si se cumplio o no el objetivo
      flag_bajo = LOW;
      flag_medio = LOW;
      flag_alto = LOW;
      flag_standby = LOW;
      contador = 0;
      estado = verde;
      break;
    }
    #if DEBUG_MODO_2 == 1
    if(estado==verde)
    {
      Serial.print("VERDE\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_verde);
    }
    if(estado==standby)
    {
      Serial.print("STANDBY\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_delay);
      Serial.print("\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" de (");
      Serial.print(umbral_max*M2_PORC_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_ALTO/100);
      Serial.println(")");
    }
    if(estado==bajo)
    {
      Serial.print("BAJO");
      Serial.print("\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" de (");
      Serial.print(umbral_max*M2_PORC_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_ALTO/100);
      Serial.println(")");
    }
    if(estado==medio)
    {
      Serial.print("MEDIO");
      Serial.print("\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" de (");
      Serial.print(umbral_max*M2_PORC_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_ALTO/100);
      Serial.println(")");
    }
    if(estado==alto)
    {
      Serial.print("ALTO");
      Serial.print("\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" de (");
      Serial.print(umbral_max*M2_PORC_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_ALTO/100);
      Serial.println(")");
    }
    if(estado==rojo)
    {
      Serial.print("ROJO\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_rojo);
    }
    #endif
  }
}
