#include "AVI_Config.h"
#include "AVI_Modo_2.h"
#include "Arduino.h"

void Modo2(int umbral_inf, int umbral_sup)
{
  //Imagen
  int leds = 0;
  int led_min = 1;
  int led_max = 20;

  // Base de Tiempo
  unsigned long t_actual = 0;
  static unsigned long t_anterior = 0;

  // Sonido
  static int snd_env[M2_PROM];
  float snd_prom = 0;

  // Lazo a M2_TS mseg
  t_actual = millis();
  if((t_actual - t_anterior) >= 20)
  {
    t_anterior = t_actual;
    
    // Desplaza los elementos y lee el nuevo
    for(uint8_t i=M2_PROM-2; i>=0; i--)
    {
      snd_env[i+1]=snd_env[i];
    }
    snd_env[0] = analogRead(A1);

    // Promedio
    for(uint8_t i=0; i<M2_PROM; i++)
    {
      snd_prom += snd_env[i];
    }
    snd_prom /= M2_PROM;

    // Imagenes
    //leds = map(snd_prom,umbral_inf,umbral_sup,led_min,led_max);

    //Serial.print("Imagen = ");
    //Serial.print(leds);
  }
}

