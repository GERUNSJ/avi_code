//=================================================================================================
// Nivel3Test
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
// Testeo del Nivel Basico 3
// Mantenimiento.
// - La voz debe mantenerse un tiempo determinado.
//
//=================================================================================================
// COMENTARIOS GENERALES
// - Se lee la envolvente de la señal de audio.
// - Cuando la envolvente llega a un limite, arranca un contador.
// - Cuando se salga del limite, detiene el contador e indica error.
// - Cuando el contador llega a un valor, se indica exito.
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
int snd_limite = 150; //VER RANGOS

//Deteccion
boolean f_detect = false;
int c_tiempo = 0;
int objetivo = 100; //1=20ms

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
  //pinMode(PIN_AUDIO, INPUT);

  //COMUNICACION
  Serial.begin(9600);
  delay(1000);
  Serial.println("--- INICIO SETUP ---");

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

    //Comienzo del Algoritmo de Nivel 3
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

    //Chequeo del Nivel
    if((snd_env_prom>=0.85*snd_limite)&&(snd_env_prom<=1.25*snd_limite))
    {
      if(f_detect)
      {
        c_tiempo++;
      }
      else
      {
        f_detect = true;
        c_tiempo = 0;
      }
    }
    else
    {
      if(f_detect)
      {
        f_detect = false;
        if(c_tiempo>=objetivo)
        {
          //Mostrar cosa bien
          
        }
        else
        {
          //Mostrar cosa mal
        }
        c_tiempo = 0;
      }
    }
  }
}
