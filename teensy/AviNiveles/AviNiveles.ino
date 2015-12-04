//=================================================================================================
// Avi nivels
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
// Nivel Basico
// - Nivel 1: Presencia de sonido.
//   - Se utiliza la luz para mostrar la presencia de cualquier sonido.
// - Nivel 2: Intensidad.
//   - Según el volumen de la voz del niño cambia la velocidad y durabilidad de la luz.
// - Nivel 3: Durabilidad de la Voz.
//   - Ayuda a controla la respiración.
//   - Según la duración de la voz será la distancia del recorrido o la iluminación del A.V.I.
// Nivel Medio
// - Interacción con vocales. Reproducción de vocales de manera pausada y controlada.
// Nivel Superior
// - Libre. Reproducción de vocales de manera libre. Combina Nivel básico 1, 2 y 3.
//
//=================================================================================================
// TODO
// - TODO
//
//=================================================================================================
// COMENTARIOS GENERALES
// - Nivel 1 necesita leer la envolvente del audio (pin de placa microfono).
// Si es mayor al umbral predefinido, se activa la luz correspondiente por un tiempo X. Si no se
// detecta nada en un tiempo Y, mandar los circulos.
//
// - Nivel 2 necesita leer la envolvente del audio (pin de placa microfono).
// Enviar luz correspondiente al nivel de audio leido. Umbral objetivo? Si se alcanza mostrar cara.
//
// - Nivel 3 necesita leer la envolvente del audio (pin de placa microfono).
// Si el audio supera un umbral, arranca el contador. El contador dura hasta que el tiempo es satisfactorio
// o bien que el umbral caiga. Se muestran los leds acorde.
//
// - Nivel Medio necesita leer el audio
// Se muestra una vocal random. Lee el audio y determina la vocal. Si es la indicada, hace algo.
// Luego de ese algo, repite el procedimiento
//
// - Nivel Superior lee el audio, determina vocal y duracion y mueve el avi acorde.
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// DEPENDENCIAS Y DEFINICIONES
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------------------

int nivel = 1; //De 1 a 5: B1, B2, B3, M, S.
int vocal; //De 1 a 5: A, E, I, O, U.
int snd_env; // Envolvente
int snd_obj = 512; // Umbral de Sonido Objetivo
int snd; // Audio

boolean flagNivelB1 = false;

// Base de Tiempo
unsigned long t_actual = 0;
unsigned long t_anterior = 0;
unsigned long t_intervalo = 0;
unsigned long t_umbral = 2000; // Dos segundos [mseg]

//-------------------------------------------------------------------------------------------------
// FUNCIONES AUXILIARES
//-------------------------------------------------------------------------------------------------

// Devuelve un numero aleatorio diferente cada vez (del 1 al 5)
int getVocal()
{
  int numero;
  static int numero_anterior = 0;
  do
  {
    numero = random(1,6);
  } while(numero==numero_anterior);
  numero_anterior = numero;
  return numero;
}

//-------------------------------------------------------------------------------------------------
// SETUP
//-------------------------------------------------------------------------------------------------

void setup()
{
  // PINES - TODO
  pinMode(13, OUTPUT);
  //pinMode(PIN_ENVOLVENTE, INPUT);
  //pinMode(PIN_AUDIO, INPUT);

  // COMUNICACION
  Serial.begin(9600);
  delay(1000);
  Serial.println("--- INICIO SETUP ---");

  // INICIALIZACIONES
  randomSeed(micros());
}

//-------------------------------------------------------------------------------------------------
// LOOP
//-------------------------------------------------------------------------------------------------

void loop()
{
  // TODO - BUSCAR UNA FORMA MENOS CHANTA DE ELEGIR NIVELES!!!
  // O sea hace asi nomas y listo???
  
  // NIVEL BASICO 1
  if(nivel==1)
  {
    // Lee la Envolvente. Una vez que supere el umbral, comienza el contador.
    snd_env = analogRead(PIN_ENVOLVENTE);
    if((snd_env >= snd_obj)&&(!flagNivelB1))
    {
      flagNivelB1 = true;
    }

    if(flagNivelB1)
    {
      t_actual = millis();
      t_intervalo = t_actual - t_anterior;
      if(t_intervalo < t_umbral)
      {
        
      }
    }

    
    t_actual = millis();
    t_intervalo = t_actual - t_anterior;
    if(t_intervalo < t_)
    
    // Leer Pin Envolvente
    // envolvente > umbral?
    // Si: Muestra algo por un tiempo determinado.
    // No: Rutina de fail!
  }

  // NIVEL BASICO 2
  if(nivel==2)
  {
    // Aca va la rutina del nivel basico 2
  }

  // NIVEL BASICO 3
  if(nivel==3)
  {
    // Aca va la rutina del nivel basico 3
  }

  // NIVEL MEDIO
  if(nivel==4)
  {
    // Aca va la rutina del nivel medio
  }

  // NIVEL SUPERIOR
  if(nivel==5)
  {
    // Aca va la rutina del nivel superior
  }
}
