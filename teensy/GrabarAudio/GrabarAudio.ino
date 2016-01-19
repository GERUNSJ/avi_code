#include "AVI_Formantes.h"
#include "AVI_Config.h"
#include <FlexiTimer2.h>
#include <Eigen30.h>
#include <arm_math.h>

// Para evitar problemas. Ver https://forum.pjrc.com/archive/index.php/t-28181.html
void abort()
{
  while(1);
}

// Variables
float datos[AUDIO_CANT_MUESTRAS]; // Vector de Muestras
int indice = 0; // Indice del Vector de Muestras

// Variables Auxiliares
float maximo = 0;
float minimo = 1024;
int f1 = 0; // Primer Formante
int f2 = 0; // Segundo Formante

// Funciones Auxiliares
void medir()
{
  datos[indice] = analogRead(A0);
  indice++;
}

void setup()
{
  pinMode(13, OUTPUT);
  delay(1000);
  
  // Limpia el vector datos
  for(int n=0; n<AUDIO_CANT_MUESTRAS; n++)
  {
    datos[n]=0;
  }
  
  // FlexiTimer2
  FlexiTimer2::set(1, 1.0/AUDIO_FS, medir);
  FlexiTimer2::start();
  
  digitalWrite(13, HIGH);
}

void loop()
{
  if(indice >= AUDIO_CANT_MUESTRAS)
  {
    // Finaliza el ciclo de muestreo y comienza el de calculo
    FlexiTimer2::stop();
    digitalWrite(13, LOW);
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

    // Imprimir los resultados
    Serial.begin(115200);
    Serial.print("F1 =\t");
    Serial.print(f1);
    Serial.print("\tF2 =\t");
    Serial.println(f2);
    Serial.end();

    // Fin del ciclo de calculo
    digitalWrite(13, HIGH);
    FlexiTimer2::start();
  }
}
