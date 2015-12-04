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

//-------------------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------------------

//Sonido
int snd_env[5]; // Envolvente
float snd_env_prom = 0;
int snd_inf = 10; // Umbral de Sonido Inferior - VER RANGOS!
int snd_sup = 300;

//Imagen
int leds = 0;
int led_min = 1;
int led_max = 20;

//Base de Tiempo
unsigned long t_actual = 0;
unsigned long t_anterior = 0;
unsigned long t_intervalo = 0;

//-------------------------------------------------------------------------------------------------
// SETUP
//-------------------------------------------------------------------------------------------------

void setup()
{
  //PINES - TODO
  pinMode(13, OUTPUT);
  //pinMode(PIN_ENVOLVENTE, INPUT);
  
  //COMUNICACION
  Serial.begin(9600);
  delay(1000);
  Serial.println("--- INICIO ---");

  //INICIALIZACION
  for(uint8_t i=0; i<5; i++)
  {
    snd_env[i] = 0;
  }
}

//-------------------------------------------------------------------------------------------------
// LOOP
//-------------------------------------------------------------------------------------------------

void loop()
{
  t_actual = millis();
  t_intervalo = t_actual - t_anterior; //Periodo de Muestreo
  if(t_intervalo >= 20)
  {
    //Loop corre a 20 [mseg]
    t_anterior = t_actual;

    //Comienzo del Algoritmo de Nivel 2
    for(uint8_t i=3; i>=0; i--)
    {
      snd_env[i+1]=snd_env[i];
    }    
    snd_env[0] = analogRead(A0);

    //Promedio de Envolventes
    for(uint8_t i=0; i<5; i++)
    {
      snd_env_prom += snd_env[i];
    }
    snd_env_prom /= 5;
    
    leds = map(snd_env_prom,snd_inf,snd_sup,led_min,led_max);

    Serial.print(snd_env_prom);
    Serial.print("\t");
    Serial.print(leds);
    Serial.println();
  }
}
