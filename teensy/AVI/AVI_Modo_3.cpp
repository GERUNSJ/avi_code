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

#include "Arduino.h"
#include "AVI_Config.h"
#include "AVI_Pines.h"
#include "AVI_LEDs.h"
#include "AVI_Modo_3.h"

#define DEBUG_MODO_3 0

// Variables Globales
extern LEDs leds;

// Funciones
void Modo3(int umbral, int tiempo)
{
  // Estados
  enum Estados
  {
    verde,
    img_standby,
    img_bajo,
    img_medio,
    img_alto,
    cara,
    rojo
  };
  static Estados estado = verde;
  
  // Base de Tiempo
  static unsigned long t_anterior = 0;
  unsigned long t_actual;
  int t_verde = 2000/M3_TS; // 2 Segundos
  int t_cara = 3000/M3_TS; // 3 Segundos
  int t_rojo = 4000/M3_TS; // 4 Segundos
  int t_delay = 5000/M3_TS; // 5 Segundos
  int t_obj = (tiempo*1000)/M3_TS; // Tiempo debe estar en segundos

  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_rojo = LOW;
  static boolean flag_cara = LOW;
  static boolean flag_standby = LOW;
  static boolean flag_bajo = LOW;
  static boolean flag_medio = LOW;
  static boolean flag_alto = LOW;

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
        leds.mostrar(IMAGENES::circulo, c_verde);
        contador = 0;
      }
      contador++;
      if(contador >= t_verde)
      {
        flag_verde = LOW;
        estado = img_standby;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case img_standby:
      if(!flag_standby)
      {
        flag_standby = HIGH;
        leds.mostrar(IMAGENES::m3_img_standby, c_naranja);
      }
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      if(envolvente >= umbral)
      {
        estado = img_bajo;
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
      case img_bajo:
      if(!flag_bajo)
      {
        flag_bajo = HIGH;
        leds.mostrar(IMAGENES::m2_img_bajo, c_naranja, c_azul);
      }
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      if(envolvente >= umbral)
      {
        contador++;
        if(contador >= t_obj*M3_PORC_BAJO/100)
        {
          estado = img_medio;
          flag_bajo = LOW;
        }
      }
      else
      {
        estado = img_standby;
        flag_bajo = LOW;
        contador = 0;
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case img_medio:
      if(!flag_medio)
      {
        flag_medio = HIGH;
        leds.mostrar(IMAGENES::m2_img_medio, c_naranja, c_azul);
      }
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      if(envolvente >= umbral)
      {
        contador++;
        if(contador >= t_obj*M3_PORC_MEDIO/100)
        {
          estado = img_alto;
          flag_medio = LOW;
        }
      }
      else
      {
        estado = img_standby;
        flag_medio = LOW;
        contador = 0;
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case img_alto:
      if(!flag_alto)
      {
        flag_alto = HIGH;
        leds.mostrar(IMAGENES::m2_img_alto, c_naranja, c_azul);
      }
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      if(envolvente < umbral)
      {
        estado = cara;
        flag_alto = LOW;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case cara:
      if(!flag_cara)
      {
        flag_cara = HIGH;
        leds.mostrar(IMAGENES::cara, c_azul);
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
      flag_bajo = LOW;
      flag_medio = LOW;
      flag_alto = LOW;
      contador = 0;
      estado = verde;
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
    if(estado==img_standby)
    {
      Serial.print("IMG_INICIO\t(|------)\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_delay);
      Serial.print("\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" (");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==img_bajo)
    {
      Serial.print("IMG_BAJO\t(|||----)\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_obj);
      Serial.print(" (");
      Serial.print(t_obj*M3_PORC_BAJO/100);
      Serial.print(" / ");
      Serial.print(t_obj*M3_PORC_MEDIO/100);
      Serial.print(")\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" (");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==img_medio)
    {
      Serial.print("IMG_MEDIO\t(|||||--)\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_obj);
      Serial.print(" (");
      Serial.print(t_obj*M3_PORC_BAJO/100);
      Serial.print(" / ");
      Serial.print(t_obj*M3_PORC_MEDIO/100);
      Serial.print(")\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" (");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==img_alto)
    {
      Serial.print("IMG_ALTO\t(|||||||)\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_obj);
      Serial.print(" (");
      Serial.print(t_obj*M3_PORC_BAJO/100);
      Serial.print(" / ");
      Serial.print(t_obj*M3_PORC_MEDIO/100);
      Serial.print(")\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" (");
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
