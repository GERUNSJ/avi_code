#include "AVI_Formantes.h"
#include <FlexiTimer2.h>
#include <Eigen30.h>

#define ARM_MATH_CM4
#include <arm_math.h>


// Para evitar problemas. Ver https://forum.pjrc.com/archive/index.php/t-28181.html
void abort()
{
  while(1);
}

// Variables
const int cantidad = 200; // Muestras a tomar
int Fs = 8000; // Frecuencia de Muestreo
float datos[cantidad];
int indice = 0;
float maximo = 0;
float minimo = 1024;

int f1 = 0; // Primer Formante
int f2 = 0; // Segundo Formante
  

void medir()
{
  datos[indice] = analogRead(A0);
  indice++;
}

void setup()
{
  // SETUP
  //Serial.begin(9600);
  pinMode(13, OUTPUT);
  delay(1000);

  // Limpia el vector datos
  for(int n=0; n<cantidad; n++)
  {
    datos[n]=0;
  }
  
  // FlexiTimer2
  FlexiTimer2::set(1, 1.0/Fs, medir);
  FlexiTimer2::start();
  
  digitalWrite(13, HIGH);
}
  
  // Loop
  //while(true)
  void loop()
  {
    if(indice >= cantidad)
    {
      FlexiTimer2::stop();
      digitalWrite(13, LOW);
      indice = 0;

      // Resta del valor medio y busca max/min
      for(int n=0; n<cantidad; n++)
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
      for(int n=0; n<cantidad; n++)
      {
        datos[n] /= maximo;
      }

      hamming(datos, cantidad);
      obtener_formantes(datos, cantidad, 10, Fs, &f1, &f2);
      
      
      //delay(1000);
      Serial.begin(115200);
      
      Serial.print("F1 =\t");
      Serial.print(f1);
      Serial.print("\tF2 =\t");
      Serial.println(f2);
      
      //Serial.print("datos = [");
      //delay(1);
      //for(int n=0; n<cantidad-1; n++)
      //{
        //Serial.print(datos[n]);
        //delay(1);
        //Serial.print(", ");
        //delay(1);
      //}
      //Serial.print(datos[cantidad-1]);
      //delay(1);
      //Serial.println("];");
      //delay(1);

      //delay(1000);
      Serial.end();
      digitalWrite(13, HIGH);

      
      FlexiTimer2::start();
    }
  }
  
  //return 0;
//}
