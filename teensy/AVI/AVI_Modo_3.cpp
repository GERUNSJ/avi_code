//=================================================================================================
// AVI_Modo_3.cpp
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
#include "AVI_Modo_3.h"
#include "Arduino.h"

#define DEBUG_MODO_3 1

void Modo3(int umbral, int segundos)
{
  // Estados
  enum Estados
  {
    verde,
    bajo,
    medio,
    alto,
    cara,
    rojo
  };
  static Estados estado = verde;
  
  // Base de Tiempo
  static unsigned long t_anterior = 0;
  unsigned long t_actual;
  int t_verde = 2000/M3_TS; // 2 Segundos
  int t_fail = 6000/M3_TS; // 6 Segundos
  int t_rojo = 4000/M3_TS; // 4 Segundos
  int t_cara = 2000/M3_TS; // 2 Segundos

  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_bajo = LOW;
  static boolean flag_medio = LOW;
  static boolean flag_alto = LOW;
  static boolean flag_cara = LOW;
  static boolean flag_rojo = LOW;
  
  // Contadores
  static int contador = 0;

  // Otros
  int envolvente = 0;

  t_actual = millis();
  if((t_actual - t_anterior) >= M3_TS)
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
        estado = bajo;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case bajo:
      if(!flag_bajo)
      {
        flag_bajo = HIGH;
        // TODO - Mostrar Img Bajo
      }
      contador++;
      if(contador < t_fail)
      {
        envolvente = analogRead(PIN_MIC_ENVOLVENTE);
        // Chequeo Medio
        if((envolvente < umbral) && (envolvente >= (umbral*M3_MEDIO/100)))
        {
          flag_bajo = LOW;
          estado = medio;
        }
        // Chequeo Alto
        if(envolvente >= umbral)
        {
          flag_bajo = LOW;
          estado = alto;
        }
      }
      else
      {
        flag_bajo = LOW;
        estado = rojo;
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case medio:
      if(!flag_medio)
      {
        flag_medio = HIGH;
        // TODO - Mostrar Img Medio
      }
      contador++;
      if(contador < t_fail)
      {
        envolvente = analogRead(PIN_MIC_ENVOLVENTE);
        // Chequeo Bajo
        if(envolvente < (umbral*M3_MEDIO/100))
        {
          flag_medio = LOW;
          estado = bajo;
        }
        // Chequeo Alto
        if(envolvente >= umbral)
        {
          flag_medio = LOW;
          estado = alto;
        }
      }
      else
      {
        flag_medio = LOW;
        estado = rojo;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case alto:
      if(!flag_alto)
      {
        flag_alto = HIGH;
        // TODO - Mostrar Img Alto
        contador = 0;
      }
      contador++;
      if(contador >= segundos*1000/M3_TS)
      {
        flag_alto = LOW;
        estado = cara;
        contador = 0;
      }
      else
      {
        envolvente = analogRead(PIN_MIC_ENVOLVENTE);
        // Chequeo Bajo
        if(envolvente < (umbral*M3_MEDIO/100))
        {
          flag_alto = LOW;
          estado = bajo;
          contador = 0;
        }
        // Chequeo Medio
        if((envolvente < umbral) && (envolvente >= (umbral*M3_MEDIO/100)))
        {
          flag_alto = LOW;
          estado = medio;
          contador = 0;
        }
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case cara:
      if(!flag_cara)
      {
        flag_cara = HIGH;
        // TODO - Muestra el rojo
        contador = 0;
      }
      contador++;
      if(contador >= t_cara)
      {
        flag_cara = LOW;
        // TODO - No mostrar nada
        estado = verde;
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
    #if DEBUG_MODO_3 == 1
    if(estado==verde)
    {
      Serial.print("VERDE\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_verde);
    }
    if(estado==bajo)
    {
      Serial.print("BAJO\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_fail);
      Serial.print(" para Fail\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" de (");
      Serial.print(umbral*M3_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==medio)
    {
      Serial.print("MEDIO\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_fail);
      Serial.print(" para Fail\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" de (");
      Serial.print(umbral*M3_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==alto)
    {
      Serial.print("ALTO\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(segundos*1000/M3_TS);
      Serial.print(" para Success\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" de (");
      Serial.print(umbral*M3_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==cara)
    {
      Serial.print("CARA\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_cara);
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
