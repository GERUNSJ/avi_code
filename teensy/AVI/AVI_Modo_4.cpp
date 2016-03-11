//=================================================================================================
// AVI_Modo_4.cpp
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
#include "AVI_Modo_4.h"

#define DEBUG_MODO_4 0

// Variables Globales
extern LEDs leds;

// Funciones
void Modo4()
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
  int t_verde = 2000/M4_TS; // 2 Segundos
  int t_cara = 3000/M4_TS; // 3 Segundos
  int t_rojo = 4000/M4_TS; // 4 Segundos
  int t_delay = 5000/M4_TS; // 5 Segundos
  
  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_rojo = LOW;
  static boolean flag_cara = LOW;
  static boolean flag_standby = LOW;
  
  // Contadores
  static int contador = 0;

  // Otros
  int vocalRandom = 0;
  int vocalObtenida = 0;
  randomSeed(micros()); // Microsegundos asegura un Seed aleatorio

  t_actual = millis();
  if((t_actual - t_anterior) >= M4_TS)
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
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case standby:
      if(!flag_standby)
      {
        // Selecciona una vocal para mostrar
        flag_standby = HIGH;
        vocalRandom = floor(random(5));
        contador = 0;
        switch(vocalRandom)
        {
          // Caso A
          case 0:
          leds.mostrar(IMAGENES::a_img, c_naranja);
          break;
          // Caso E
          case 1:
          leds.mostrar(IMAGENES::a_img, c_naranja);
          break;
          // Caso I
          case 2:
          leds.mostrar(IMAGENES::a_img, c_naranja);
          break;
          // Caso O
          case 3:
          leds.mostrar(IMAGENES::a_img, c_naranja);
          break;
          // Caso U
          case 4:
          leds.mostrar(IMAGENES::a_img, c_naranja);
          break;
          // Si no está dentro del rango, no muestra nada y repite.
          default:
          leds.apagar();
          flag_standby = LOW;
          break;
        }
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: DETECCION DE VOCALES!
      //-------------------------------------------------------------------------------------------------
      

      if(vocalObtenida == vocalRandom)
      {
        estado = cara;
        flag_standby = LOW;
        contador = 0;
      }
      contador++;
      if(contador >= t_delay)
      {
        estado = rojo;
        flag_standby = LOW;
        contador = 0;
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case cara:
      if(!flag_cara)
      {
        flag_cara = HIGH;
        leds.mostrar(IMAGENES::cara, c_azul);
        contador = 0;
      }
      contador++;
      if(contador >= t_cara)
      {
        estado = verde;
        flag_cara = LOW;
        contador = 0;
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
      contador = 0;
      estado = verde;
      break;
    }
    
    #if DEBUG_MODO_4 == 1
    if(estado==verde)
    {
      Serial.print("VERDE\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_verde);
    }
    if(estado==standby)
    {
      Serial.print("STANDBY\tVOCAL_RANDOM:\t");
      Serial.print(vocalRandom);
      Serial.print("\tVOCAL_OBTENIDA:\t");
      Serial.print(vocalObtenida);
      Serial.print("\tContador ");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_delay);
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
