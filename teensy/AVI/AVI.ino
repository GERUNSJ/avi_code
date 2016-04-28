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
#include "AVI_Pines.h"
#include "AVI_Formantes.h"
#include "AVI_LEDs.h"
#include "AVI_Motores.h"
#include "AVI_Modos.h"
#include "AVI_Motores.h"
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
    datos[indice] = analogRead(PIN_MIC_AUDIO);
    indice++;
  }
}
//=================================================================================================
// SETUP
// Inicio del programa. Configuración y definicion de pines.
//=================================================================================================
void setup()
{
  // Comunicacion
  Serial.begin(9600);
  Serial.println("AVI Inicio");

  // Configuración de Pines
  pinInit();
  
  // Inicializaciones
  motores.encender();
  leds.apagar();
  
  // Limpieza del Vector de Datos
  for(int n=0; n<AUDIO_CANT_MUESTRAS; n++)
  {
    datos[n]=0;
  }

  // FlexiTimer2
  FlexiTimer2::set(1, 1.0/AUDIO_FS, medir);
}

//=================================================================================================
// LOOP
// Bucle del programa.
//=================================================================================================
void loop()
{
  //
}






void loop()
{
  if(indice >= AUDIO_CANT_MUESTRAS)
  {
    // Finaliza el ciclo de muestreo y comienza el de calculo
    FlexiTimer2::stop();
    //digitalWrite(13, LOW);
    indice = 0;

    // Resta del valor medio y busca max/min
    for(int n=0; n<AUDIO_CANT_MUESTRAS; n++)
    {
      datos[n] -= 511.5;
      if(datos[n]>maximo)
      {
        maximo = datos[n];
      }
      if(datos[n]<minimo)
      {
        minimo = datos[n];
      }
    }
    
    // Busca el maximo en valor absoluto
    if(abs(minimo)>maximo)
    {
      maximo = abs(minimo);
    }

    // Normalizacion de los datos
    for(int n=0; n<AUDIO_CANT_MUESTRAS; n++)
    {
      datos[n] /= maximo;
    }

    // Filtrado y Obtencion de Formantes
    hamming(datos, AUDIO_CANT_MUESTRAS);
    obtener_formantes(datos, AUDIO_CANT_MUESTRAS, FILTRO_PROM_N, AUDIO_FS, &f1, &f2);
    formante1MA.cargar(f1);
    formante2MA.cargar(f2);
    
    vocal = getVocal(formante1MA.promedio(), formante2MA.promedio());
    
    // Imprimir los resultados
    Serial.begin(115200);
    Serial.print("F1 =\t");
    Serial.print(formante1MA.promedio());
    Serial.print("\tF2 =\t");
    Serial.print(formante2MA.promedio());
    Serial.print("\tVocal =\t");
    Serial.println(vocal);
    Serial.end();

    // Fin del ciclo de calculo
    //digitalWrite(13, HIGH);
    FlexiTimer2::start();
  }
}
#endif // D_GRABAR_AUDIO


