//=================================================================================================
// Nivel1Test
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
// Testeo del Nivel Basico 1
// Presencia de sonido.
// - Se utiliza la luz para mostrar la presencia de cualquier sonido.
//
//=================================================================================================
// COMENTARIOS GENERALES
// - Se lee la envolvente de la señal de audio.
// - Si la envolvente es mayor a un objetivo, se levanta el flag de deteccion.
// - La imagen dura mientras dure el flag de deteccion.
// - En el flanco de caida de la intensidad respecto al objetivo, comienza a contar tiempo.
// - Luego de un tiempo n caida la intensidad, apaga la imagen.
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
int snd_env; // Envolvente

//
int snd_obj = 150; // Umbral de Sonido Objetivo - VER RANGOS!

//Imagen
boolean f_img = false;
int c_img = 0;
int t_img = 10;
boolean imagen = false;

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

    //Comienzo del Algoritmo de Nivel 1
    snd_env = analogRead(A0);
    if(snd_env>=snd_obj)
    {
      f_img = true;
      c_img = 0;
    }
    else
    {
      if(f_img)
      {
        c_img++;
        if(c_img>=t_img)
        {
          f_img = false;
          c_img = 0;
        }
      }
    }

    Serial.print(snd_env);
    Serial.print("\t");
    Serial.print(snd_obj);
    Serial.print("\t");
    Serial.print(f_img);
    Serial.print("\t");
    Serial.print(c_img);
    Serial.println();
  }
}
