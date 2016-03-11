//=================================================================================================
// AVI_Modo_5.cpp
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
#include "AVI_Modo_5.h"

#define DEBUG_MODO_5 0

// Variables Globales
extern LEDs leds;

// Funciones
void Modo5()
{
  // Estados
  enum Estados
  {
    verde,
    standby,
    vocal_a,
    vocal_e,
    vocal_i,
    vocal_o,
    vocal_u
  };
  static Estados estado = verde;
  
  // Base de Tiempo
  static unsigned long t_anterior = 0;
  unsigned long t_actual;
  int t_verde = 2000/M5_TS; // 2 Segundos
  
  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_standby = LOW;
  static boolean flag_a = LOW;
  static boolean flag_e = LOW;
  static boolean flag_i = LOW;
  static boolean flag_o = LOW;
  static boolean flag_u = LOW;
  
  // Contadores
  static int contador = 0;

  // Otros
  int vocalObtenida = 0;
  randomSeed(micros()); // Microsegundos asegura un Seed aleatorio

  t_actual = millis();
  if((t_actual - t_anterior) >= M5_TS)
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
        flag_standby = HIGH;
        leds.apagar();
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: DETECCION DE VOCALES!
      //-------------------------------------------------------------------------------------------------

      switch(vocalObtenida)
      {
        // Case A
        case 0:
        estado = vocal_a;
        flag_standby = LOW;
        break;
        // Case E
        case 1:
        estado = vocal_e;
        flag_standby = LOW;
        break;
        // Case I
        case 2:
        estado = vocal_i;
        flag_standby = LOW;
        break;
        // Case O
        case 3:
        estado = vocal_o;
        flag_standby = LOW;
        break;
        // Case U
        case 4:
        estado = vocal_u;
        flag_standby = LOW;
        break;
        // Si no está dentro del rango, no muestra nada y repite.
        default:
        flag_standby = LOW;
        leds.apagar();
        break;
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case vocal_a:
      if(!flag_a)
      {
        flag_a = HIGH;
        leds.mostrar(IMAGENES::a_img, c_naranja);
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: REACCION EN A!
      //-------------------------------------------------------------------------------------------------

      //-------------------------------------------------------------------------------------------------
      // TODO: Volver a STANDBY!
      //-------------------------------------------------------------------------------------------------
      
      break;

      //-------------------------------------------------------------------------------------------------
      case vocal_e:
      if(!flag_e)
      {
        flag_e = HIGH;
        leds.mostrar(IMAGENES::e_img, c_naranja);
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: REACCION EN E!
      //-------------------------------------------------------------------------------------------------

      //-------------------------------------------------------------------------------------------------
      // TODO: Volver a STANDBY!
      //-------------------------------------------------------------------------------------------------
      
      break;

      //-------------------------------------------------------------------------------------------------
      case vocal_i:
      if(!flag_i)
      {
        flag_i = HIGH;
        leds.mostrar(IMAGENES::i_img, c_naranja);
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: REACCION EN I!
      //-------------------------------------------------------------------------------------------------

      //-------------------------------------------------------------------------------------------------
      // TODO: Volver a STANDBY!
      //-------------------------------------------------------------------------------------------------
      
      break;

      //-------------------------------------------------------------------------------------------------
      case vocal_o:
      if(!flag_o)
      {
        flag_o = HIGH;
        leds.mostrar(IMAGENES::o_img, c_naranja);
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: REACCION EN O!
      //-------------------------------------------------------------------------------------------------

      //-------------------------------------------------------------------------------------------------
      // TODO: Volver a STANDBY!
      //-------------------------------------------------------------------------------------------------
      
      break;

      //-------------------------------------------------------------------------------------------------
      case vocal_u:
      if(!flag_u)
      {
        flag_u = HIGH;
        leds.mostrar(IMAGENES::u_img, c_naranja);
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: REACCION EN A!
      //-------------------------------------------------------------------------------------------------

      //-------------------------------------------------------------------------------------------------
      // TODO: Volver a STANDBY!
      //-------------------------------------------------------------------------------------------------
      
      break;

      //-------------------------------------------------------------------------------------------------
      default:
      // Reinicia
      flag_verde = LOW;
      flag_standby = LOW;
      flag_a = LOW;
      flag_e = LOW;
      flag_i = LOW;
      flag_o = LOW;
      flag_u = LOW;
      estado = verde;
      contador = 0;
      break;
    }

    #if DEBUG_MODO_5 == 1
    if(estado==verde)
    {
      Serial.print("VERDE\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_verde);
    }
    if(estado==standby)
    {
      Serial.print("STANDBY\tVOCAL_OBTENIDA:\t");
      Serial.println(vocalObtenida);
    }
    if(estado==vocal_a)
    {
      Serial.println("OBTENIDO\tA");
    }
    if(estado==vocal_e)
    {
      Serial.println("OBTENIDO\tE");
    }
    if(estado==vocal_i)
    {
      Serial.println("OBTENIDO\tI");
    }
    if(estado==vocal_o)
    {
      Serial.println("OBTENIDO\tO");
    }
    if(estado==vocal_u)
    {
      Serial.println("OBTENIDO\tU");
    }
    #endif
  }
}
