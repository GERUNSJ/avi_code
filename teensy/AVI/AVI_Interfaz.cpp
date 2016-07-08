//=================================================================================================
// AVI_Interfaz.cpp
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
// - Contiene las funciones relacionadas al interfaz de usuario.
// 
//=================================================================================================

#include "AVI_Interfaz.h"

#define DEBUG_INTERFAZ 1 // Muestra el estado de los botones.
#define DEBUG_SERIE 0 // Muestra por LEDs (0) o Serie (1).

// Simula los botones via Serie (1). Si los botones están implementados físicamente, igualar a 0.
// Boton 1: Tecla '1' aprieta y 'q' suelta.
// Boton 2: Tecla '2' aprieta y 'w' suelta.
#define CON_TECLADO 0

#define CANTIDAD_DE_MODOS 5

// Variables Globales externas
extern LEDs leds;

//-------------------------------------------------------------------------------------------------
// Elección de Modo. Cuidado que devuelve 'Modos'
Modos elegir_modo(void)
{
  // Variables Auxiliares
  // Boton 1
  static bool boton1_actual = 0;
  static bool boton1_anterior = 0;
  static bool boton1_ha_sido_apretado = false;
  static bool boton1_ha_sido_soltado = false;
  // Boton 2
  static bool boton2_actual = 0;
  static bool boton2_anterior = 0;
  static bool boton2_ha_sido_apretado = false;
  static bool boton2_ha_sido_soltado = false;
  // Misc
  static bool decision_tomada = false;
  static int modo_seleccionado = (int)Modos::modo1; // El cast puede ser implícito también

  // Loop de seleccion. No sale hasta elegir un modo.
  // Nota: Antirrebote implementado por Hardware. Sino deberia tener un muestreo.
  while( decision_tomada == false )
  {
    mostrar_modo_seleccionado((Modos)modo_seleccionado); // Cast explícito de int a enum
    // Actualización y Lectura (HIGH == TRUE, LOW == FALSE)
    boton1_anterior = boton1_actual;
    boton2_anterior = boton2_actual;
    
    #if CON_TECLADO == 0
    // Botones implementados en Hardware
    boton1_actual = !digitalRead( PIN_BOTON_1 );
    boton2_actual = !digitalRead( PIN_BOTON_2 );
    #endif // CON_TECLADO == 0
    
    #if CON_TECLADO == 1
    if(Serial.available())
    {
      char letra = Serial.read();
      
      // Chequea Boton 1
      if(letra == '1')
      {
        boton1_actual = 1;
      }
      else if( letra == 'q' )
      {
        boton1_actual = 0;
      }
      
      // Chequea Boton 2
      if(letra == '2')
      {
        boton2_actual = 1;
      }
      else if( letra == 'w' )
      {
        boton2_actual = 0;
      }
    }
    #endif // CON_TECLADO == 1
    
    // Estado del Boton 1
    if(boton1_actual && !boton1_anterior)
    {
      boton1_ha_sido_apretado = true;
      boton1_ha_sido_soltado = false;
    }
    else if(!boton1_actual && boton1_anterior)
    {
      boton1_ha_sido_soltado = true;
      boton1_ha_sido_apretado = false;
    }
    
    // Estado del Boton 2
    if( boton2_actual && !boton2_anterior )
    {
      boton2_ha_sido_apretado = true;
      boton2_ha_sido_soltado = false;
    }
    else if( !boton2_actual && boton2_anterior )
    {
      boton2_ha_sido_soltado = true;
      boton2_ha_sido_apretado = false;
    }

    // Evaluación de Accion
    if(boton1_ha_sido_soltado)
    {
      // Avanzar 1
      boton1_ha_sido_soltado = false;
      modo_seleccionado ++;
      if(modo_seleccionado > CANTIDAD_DE_MODOS)
        modo_seleccionado = 1;
    }
    else if(boton2_ha_sido_soltado)
    {
      // Retroceder 1
      boton2_ha_sido_soltado = false;
      modo_seleccionado --;
      if(modo_seleccionado < 1)
        modo_seleccionado = CANTIDAD_DE_MODOS;
    }
    else if(boton1_ha_sido_apretado && boton2_ha_sido_apretado)
    {
      // Tomar decision
      boton1_ha_sido_apretado = false;
      boton2_ha_sido_apretado = false;
      decision_tomada = true;
    }

    #if DEBUG_INTERFAZ == 1
    Serial.print("boton1_actual = ");
    Serial.println((int)boton1_actual);
    Serial.print("boton2_actual = ");
    Serial.println((int)boton2_actual);
    Serial.print("boton1_ha_sido_apretado = ");
    Serial.println((int)boton1_ha_sido_apretado);
    Serial.print("boton1_ha_sido_soltado = ");
    Serial.println((int)boton1_ha_sido_soltado);
    Serial.print("boton2_ha_sido_apretado = ");
    Serial.println((int)boton2_ha_sido_apretado);
    Serial.print("boton2_ha_sido_soltado = ");
    Serial.println((int)boton2_ha_sido_soltado);
    Serial.print("decision_tomada = ");
    Serial.println((int)decision_tomada);
    Serial.print("modo_seleccionado = ");
    Serial.println((int)modo_seleccionado);
    delay(500);
    #endif // DEBUG_INTERFAZ
  }
  
return (Modos)modo_seleccionado; // Cast explícito de int a enum
}

//-------------------------------------------------------------------------------------------------
// Muestra el modo en LEDs o Serie, segun la constante de Debug indicada.
void mostrar_modo_seleccionado( Modos modo_seleccionado )
{
  #if DEBUG_SERIE == 0
  
  // Muestra mediante LEDs
  if(modo_seleccionado == Modos::modo1)
    leds.mostrar(IMAGENES::numero_1, c_azul);
    
  else if(modo_seleccionado == Modos::modo2)
    leds.mostrar(IMAGENES::numero_2, c_azul);
    
  else if(modo_seleccionado == Modos::modo3)
    leds.mostrar(IMAGENES::numero_3, c_azul);
    
  else if(modo_seleccionado == Modos::modo4)
    leds.mostrar(IMAGENES::numero_4, c_azul);
  
  else if(modo_seleccionado == Modos::modo5)
    leds.mostrar(IMAGENES::numero_5, c_azul);
  
  #else

  // Muestra por Serie
  Serial.print("Seleccionado Modo ");
  Serial.println((int)modo_seleccionado);
  
  #endif // DEBUG_SERIE
  
  return;
}
