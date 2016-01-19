//=================================================================================================
// Nivel2Test
//
// Mas, German Emilio
//
// Año 2015
//
// Fuentes:
// - Métodos de interacción para el aprendizaje AVI 1.0
//
//=================================================================================================
// Descripcion
// Testeo del Nivel Basico 2
// Intensidad.
// - Según el volumen de la voz del niño cambia la velocidad y durabilidad de la luz.
//
//=================================================================================================
// COMENTARIOS GENERALES
// - Se lee la envolvente de la señal de audio.
// - Se mapea la envolvente entre unos limites predefinidos.
// - Ese mapeado va hacia los LEDs.
// NOTACION
// - prefijo "f_" indica Flag
// - prefijo "c_" indica Contador
// - prefijo "t_" indica Tiempo
//
//=================================================================================================

#include "AVI_Config.h"
#include "AVI_Pines.h"
#include "AVI_Modo_2.h"

//-------------------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// SETUP
//-------------------------------------------------------------------------------------------------

void setup()
{
  //COMUNICACION
  Serial.begin(9600);
  delay(1000);
  Serial.println("--- INICIO ---");
}

//-------------------------------------------------------------------------------------------------
// LOOP
//-------------------------------------------------------------------------------------------------

void loop()
{
  //Modo2(0,1024);
  Serial.println("okk");
}
