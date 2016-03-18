//=================================================================================================
// AVI_Modo_1.cpp
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

#include "AVI_Modo_1.h"

#define DEBUG_MODO_1 0

// Funciones
void Modo1(int umbral)
{
  // Estados
  enum Estados
  {
    verde,
    standby,
    cara,
    rojo
  };
  static Estados estado = verde;
  
  // Base de Tiempo
  static unsigned long t_anterior = 0;
  unsigned long t_actual;
  int t_verde = 2000/M1_TS; // 2 Segundos
  int t_delay = 5000/M1_TS; // 5 Segundos
  int t_cara = 3000/M1_TS; // 3 Segundos
  int t_rojo = 4000/M1_TS; // 4 Segundos

  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_rojo = LOW;
  static boolean flag_cara = LOW;
  static boolean flag_standby = LOW;
  static boolean flag_ok = LOW; // Si se cumplio o no el objetivo

  // Contadores
  static int contador = 0;

  // Otros
  static FiltroMA envolvente(M1_PROM);

  t_actual = millis();
  if((t_actual - t_anterior) >= M1_TS)
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
        envolvente.reiniciar();
      }
      contador++;
      if(contador >= t_verde)
      {
        flag_verde = LOW;
        estado = standby;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case standby:
      if(!flag_standby)
      {
        flag_standby = HIGH;
        leds.apagar();
      }
      envolvente.cargar(analogRead(PIN_MIC_ENVOLVENTE));
      if(envolvente.promedio() >= umbral)
      {
        flag_ok = HIGH;
        contador = 0;
        estado = cara;
      }
      else
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
      case cara:
      if(!flag_cara)
      {
        flag_cara = HIGH;
        leds.mostrar(IMAGENES::cara, c_azul);
      }
      envolvente.cargar(analogRead(PIN_MIC_ENVOLVENTE));
      if(envolvente.promedio() >= umbral)
      {
        contador = 0;
      }
      else
      {
        contador++;
        if(contador >= t_cara)
        {
          estado = standby;
          flag_cara = LOW;
          contador = 0;
        }
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
      flag_cara = LOW;
      flag_standby = LOW;
      flag_ok = LOW;
      contador = 0;
      estado = verde;
      break;
    }
    #if DEBUG_MODO_1 == 1
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
      Serial.print("\tEnvolvente Promedio: ");
      Serial.print(envolvente.promedio());
      Serial.print(" (");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==cara)
    {
      Serial.print("CARA\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_cara);
      Serial.print("\tEnvolvente Promedio: ");
      Serial.print(envolvente.promedio());
      Serial.print(" (");
      Serial.print(umbral);
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

