//=================================================================================================
// AVI.ino
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
//
//=================================================================================================

//=================================================================================================
// DEPENDENCIAS
// Inclusión de Librerías externas y archivos propios.
//=================================================================================================
#include "AVI_Auxiliar.h"
#include "AVI_Config.h"
#include "AVI_Formantes.h"
#include "AVI_Interfaz.h"
#include "AVI_LEDs.h"
#include "AVI_Modos.h"
#include "AVI_Motores.h"
#include "AVI_Pines.h"

#include <FastLED.h>
#include <FlexiTimer2.h>
#include <Eigen30.h>
#include <arm_math.h>

//=================================================================================================
// VARIABLES GLOBALES
// Los otros archivos deben llamarlas via 'extern' en su respectivo header.
//=================================================================================================
// Tira de LED (WS2812B)
LEDs leds;

// Motores (150:1 Micro Metal Gearmotor MP)
Motor motor_A(PIN_MOTOR_A_1, PIN_MOTOR_A_2, PIN_PWM_A);
Motor motor_B(PIN_MOTOR_B_1, PIN_MOTOR_B_2, PIN_PWM_B);
Motor motor_C(PIN_MOTOR_C_1, PIN_MOTOR_C_2, PIN_PWM_C);
Motor motor_D(PIN_MOTOR_D_1, PIN_MOTOR_D_2, PIN_PWM_D);
Motores motores(motor_A, motor_B, motor_C, motor_D);

//-------------------------------------------------------------------------------------------------
// Audio
float audioDatos[AUDIO_CANT_MUESTRAS]; // Vector de Muestras
int audioIndice = 0; // Indice del Vector de Muestras
float audioMax = 0;
float audioMin = 1024; // Minimo y maximo para normalizar

//-------------------------------------------------------------------------------------------------
// Formantes - Filtros Promediadores
int f1 = 0; // Primer Formante
int f2 = 0; // Segundo Formante
FiltroMA formante1MA(10);
FiltroMA formante2MA(10);
int vocal = -1; // Vocal Resultado

//-------------------------------------------------------------------------------------------------
// Modos
Modos modoSeleccionado;
  
//=================================================================================================
// FUNCIONES AUXILIARES
// Funciones de apoyo para Setup y Loop.
//=================================================================================================
// Para evitar problemas. Ver https://forum.pjrc.com/archive/index.php/t-28181.html
void abort()
{
  while(1);
}

// Funcion de FlexiTimer2
void medir()
{
  if(analogRead(PIN_MIC_ENVOLVENTE)>=50)
  {
    audioDatos[audioIndice] = analogRead(PIN_MIC_AUDIO);
    audioIndice++;
  }
}

//=================================================================================================
// SETUP
// Inicio del programa. Configuración y definicion de pines.
//=================================================================================================
void setup()
{
  // Comunicacion
  delay(1000);
  Serial.begin(9600);
  Serial.println("AVI Inicio");

  // Configuración de Pines
  Serial.println("Configuracion de Pines");
  pinInit();
  
  // Inicializaciones
  Serial.println("Encendido de Motores");
  motores.encender();
  Serial.println("Apaga Leds");
  leds.apagar();

  Serial.println("Limpia Datos");
  // Limpieza del Vector de Datos
  for(int n=0; n<AUDIO_CANT_MUESTRAS; n++)
  {
    audioDatos[n]=0;
  }

  Serial.println("Setea Flexitimer");
  // FlexiTimer2
  FlexiTimer2::set(1, 1.0/AUDIO_FS, medir);

  //-------------------------------------------------------------------------------------------------
  // Fin de configuración, comienza el programa.
  Serial.println("Eleccion de Modo");
  modoSeleccionado = elegir_modo();
}

//=================================================================================================
// LOOP
// Bucle del programa.
//=================================================================================================
void loop()
{
  //
  switch(modoSeleccionado)
  {
    case Modos::modo1:
    // Modo 1 Seleccionado
    
    delay(1000);
    break;

    case Modos::modo2:
    // Modo 2 Seleccionado
    
    delay(1000);
    break;

    case Modos::modo3:
    // Modo 3 Seleccionado
    
    delay(1000);
    break;

    case Modos::modo4:
    // Modo 4 Seleccionado
    
    delay(1000);
    break;

    case Modos::modo5:
    // Modo 5 Seleccionado
    
    delay(1000);
    break;

    default:
    // No debería entrar acá. Error y reseteo.
    motores.parar();
    motores.apagar();
    FlexiTimer2::stop();
    while(1)
    {
      leds.mostrar(IMAGENES::x_img, c_rojo);
      delay(1000);
      leds.apagar();
      delay(1000);
    }
    break;
  }
}
