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

#include "AVI_Config.h"
#include "AVI_Modo_2.h"
#include "Arduino.h"

#define DEBUG_MODO_2 1

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
  int t_delay = 5000/M2_TS; // 5 Segundos
  int t_rojo = 4000/M2_TS; // 4 Segundos

  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_rojo = LOW;
  static boolean flag_ok = LOW; // Si se cumplio o no el objetivo
  static boolean flag_bajo = LOW;
  static boolean flag_medio = LOW;
  static boolean flag_alto = LOW;
  
  // Contadores
  static int contador = 0;

  // Otros
  int envolvente;

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
        // TODO - Mostrar Img Verde
        contador = 0;
      }
      contador++;
      if(contador >= t_verde)
      {
        flag_verde = LOW;
        // TODO - Deja de mostrar la img verde
        estado = standby;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case standby:
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      // Chequea Alto
      if(envolvente >= (umbral_max*M2_ALTO/100))
      {
        flag_ok = HIGH;
        estado = alto;
        contador = 0;
      }
      //Chequea Medio
      if((envolvente < (umbral_max*M2_ALTO/100))&&(envolvente >= (umbral_max*M2_MEDIO/100)))
      {
        flag_ok = HIGH;
        estado = medio;
        contador = 0;
      }
      //Chequea Bajo
      if((envolvente < (umbral_max*M2_MEDIO/100))&&(envolvente >= (umbral_max*M2_BAJO/100)))
      {
        flag_ok = HIGH;
        estado = bajo;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente < (umbral_max*M2_BAJO/100))
      {
        contador++;
        if(contador >= t_delay)
        {
          if(flag_ok)
          {
            estado = verde;
            flag_ok = LOW;
          }
          else
          {
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
        // TODO - Muestra Pelota Bajo
        contador = 0;
      }
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      // Chequea Alto
      if(envolvente >= (umbral_max*M2_ALTO/100))
      {
        flag_ok = HIGH;
        flag_bajo = LOW;
        estado = alto;
        contador = 0;
      }
      //Chequea Medio
      if((envolvente < (umbral_max*M2_ALTO/100))&&(envolvente >= (umbral_max*M2_MEDIO/100)))
      {
        flag_ok = HIGH;
        flag_bajo = LOW;
        estado = medio;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente < (umbral_max*M2_BAJO/100))
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
        // TODO - Muestra Pelota Medio
        contador = 0;
      }
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      // Chequea Alto
      if(envolvente >= (umbral_max*M2_ALTO/100))
      {
        flag_ok = HIGH;
        flag_medio = LOW;
        estado = alto;
        contador = 0;
      }
      //Chequea Bajo
      if((envolvente < (umbral_max*M2_MEDIO/100))&&(envolvente >= (umbral_max*M2_BAJO/100)))
      {
        flag_ok = HIGH;
        flag_medio = LOW;
        estado = bajo;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente < (umbral_max*M2_BAJO/100))
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
        // TODO - Muestra Pelota Alto
        contador = 0;
      }
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      //Chequea Medio
      if((envolvente < (umbral_max*M2_ALTO/100))&&(envolvente >= (umbral_max*M2_MEDIO/100)))
      {
        flag_ok = HIGH;
        flag_alto = LOW;
        estado = medio;
        contador = 0;
      }
      //Chequea Bajo
      if((envolvente < (umbral_max*M2_MEDIO/100))&&(envolvente >= (umbral_max*M2_BAJO/100)))
      {
        flag_ok = HIGH;
        flag_alto = LOW;
        estado = bajo;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente < (umbral_max*M2_BAJO/100))
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
        // TODO - Muestra el rojo
        contador = 0;
      }
      contador++;
      if(contador >= t_rojo)
      {
        flag_rojo = LOW;
        // TODO - No mostrar nada
        estado = verde;
      }
      break;
      //-------------------------------------------------------------------------------------------------

      default:
      // TODO- Default
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
      Serial.print(umbral_max*M2_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_ALTO/100);
      Serial.println(")");
    }
    if(estado==bajo)
    {
      Serial.print("BAJO");
      Serial.print("\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" de (");
      Serial.print(umbral_max*M2_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_ALTO/100);
      Serial.println(")");
    }
    if(estado==medio)
    {
      Serial.print("MEDIO");
      Serial.print("\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" de (");
      Serial.print(umbral_max*M2_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_ALTO/100);
      Serial.println(")");
    }
    if(estado==alto)
    {
      Serial.print("ALTO");
      Serial.print("\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" de (");
      Serial.print(umbral_max*M2_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_ALTO/100);
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
