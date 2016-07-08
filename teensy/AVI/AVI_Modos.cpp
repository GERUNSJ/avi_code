//=================================================================================================
// AVI_Modos.cpp
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

#include "AVI_Modos.h"

#define DEBUG_MODO_1 0
#define DEBUG_MODO_2 0
#define DEBUG_MODO_3 0
#define DEBUG_MODO_4 0
#define DEBUG_MODO_5 0

extern LEDs leds;

//-------------------------------------------------------------------------------------------------
// Funciones
void Modo1(int umbral)
{
  // Estados
  enum Estados
  {
    verde,
    standby,
    cara,
    rojo
  };
  static Estados estado = verde;
  
  // Base de Tiempo
  static unsigned long t_anterior = 0;
  unsigned long t_actual;
  int t_verde = 2000/M1_TS; // 2 Segundos
  int t_delay = 5000/M1_TS; // 5 Segundos
  int t_cara = 3000/M1_TS; // 3 Segundos
  int t_rojo = 4000/M1_TS; // 4 Segundos

  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_rojo = LOW;
  static boolean flag_cara = LOW;
  static boolean flag_standby = LOW;
  static boolean flag_ok = LOW; // Si se cumplio o no el objetivo

  // Contadores
  static int contador = 0;

  // Otros
  static FiltroMA envolvente(M1_PROM);

  t_actual = millis();
  if((t_actual - t_anterior) >= M1_TS)
  {
    t_anterior = t_actual;
    switch(estado)
    {
      //-------------------------------------------------------------------------------------------------
      case verde:
      if(!flag_verde)
      {
        flag_verde = HIGH;
        leds.mostrar(IMAGENES::circulo, c_verde);
        contador = 0;
        envolvente.reiniciar();
      }
      contador++;
      if(contador >= t_verde)
      {
        flag_verde = LOW;
        estado = standby;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case standby:
      if(!flag_standby)
      {
        flag_standby = HIGH;
        leds.apagar();
      }
      envolvente.cargar(analogRead(PIN_MIC_ENVOLVENTE));
      if(envolvente.promedio() >= umbral)
      {
        flag_ok = HIGH;
        contador = 0;
        estado = cara;
      }
      else
      {
        contador++;
        if(contador >= t_delay)
        {
          if(flag_ok)
          {
            estado = verde;
            flag_ok = LOW;
          }
          else
          {
            estado = rojo;
          }
        }
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case cara:
      if(!flag_cara)
      {
        flag_cara = HIGH;
        leds.mostrar(IMAGENES::cara, c_azul);
      }
      envolvente.cargar(analogRead(PIN_MIC_ENVOLVENTE));
      if(envolvente.promedio() >= umbral)
      {
        contador = 0;
      }
      else
      {
        contador++;
        if(contador >= t_cara)
        {
          estado = standby;
          flag_cara = LOW;
          contador = 0;
        }
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case rojo:
      if(!flag_rojo)
      {
        flag_rojo = HIGH;
        leds.mostrar(IMAGENES::circulo, c_rojo);
        contador = 0;
      }
      contador++;
      if(contador >= t_rojo)
      {
        flag_rojo = LOW;
        estado = verde;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      default:
      // Reinicia
      flag_verde = LOW;
      flag_rojo = LOW;
      flag_cara = LOW;
      flag_standby = LOW;
      flag_ok = LOW;
      contador = 0;
      estado = verde;
      break;
    }
    #if DEBUG_MODO_1 == 1
    if(estado==verde)
    {
      Serial.print("VERDE\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_verde);
    }
    if(estado==standby)
    {
      Serial.print("STANDBY\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_delay);
      Serial.print("\tEnvolvente Promedio: ");
      Serial.print(envolvente.promedio());
      Serial.print(" (");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==cara)
    {
      Serial.print("CARA\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_cara);
      Serial.print("\tEnvolvente Promedio: ");
      Serial.print(envolvente.promedio());
      Serial.print(" (");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==rojo)
    {
      Serial.print("ROJO\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_rojo);
    }
    #endif
  }
}

//-------------------------------------------------------------------------------------------------
void Modo2(int umbral_max)
{
  // Estados
  enum Estados
  {
    verde,
    standby,
    bajo,
    medio,
    alto,
    rojo
  };
  static Estados estado = verde;
  
  // Base de Tiempo
  static unsigned long t_anterior = 0;
  unsigned long t_actual;
  int t_verde = 2000/M2_TS; // 2 Segundos
  int t_delay = 5000/M2_TS; // 5 Segundos
  int t_rojo = 4000/M2_TS; // 4 Segundos

  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_rojo = LOW;
  static boolean flag_ok = LOW; // Si se cumplio o no el objetivo
  static boolean flag_bajo = LOW;
  static boolean flag_medio = LOW;
  static boolean flag_alto = LOW;
  static boolean flag_standby = LOW;
  
  // Contadores
  static int contador = 0;

  // Otros
  static FiltroMA envolvente(M2_PROM);

  t_actual = millis();
  if((t_actual - t_anterior) >= M2_TS)
  {
    t_anterior = t_actual;
    switch(estado)
    {
      //-------------------------------------------------------------------------------------------------
      case verde:
      if(!flag_verde)
      {
        flag_verde = HIGH;
        leds.mostrar(IMAGENES::circulo, c_verde);
        contador = 0;
        envolvente.reiniciar();
      }
      contador++;
      if(contador >= t_verde)
      {
        flag_verde = LOW;
        estado = standby;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case standby:
      if(!flag_standby)
      {
        flag_standby = HIGH;
        leds.mostrar(IMAGENES::m2_img_standby, c_azul);
      }
      envolvente.cargar(analogRead(PIN_MIC_ENVOLVENTE));
      // Chequea Alto
      if(envolvente.promedio() >= (umbral_max*M2_PORC_ALTO/100))
      {
        flag_ok = HIGH;
        flag_standby = LOW;
        estado = alto;
        contador = 0;
      }
      //Chequea Medio
      if((envolvente.promedio() < (umbral_max*M2_PORC_ALTO/100))&&(envolvente.promedio() >= (umbral_max*M2_PORC_MEDIO/100)))
      {
        flag_ok = HIGH;
        flag_standby = LOW;
        estado = medio;
        contador = 0;
      }
      //Chequea Bajo
      if((envolvente.promedio() < (umbral_max*M2_PORC_MEDIO/100))&&(envolvente.promedio() >= (umbral_max*M2_PORC_BAJO/100)))
      {
        flag_ok = HIGH;
        flag_standby = LOW;
        estado = bajo;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente.promedio() < (umbral_max*M2_PORC_BAJO/100))
      {
        contador++;
        if(contador >= t_delay)
        {
          if(flag_ok)
          {
            estado = verde;
            flag_standby = LOW;
            flag_ok = LOW;
          }
          else
          {
            flag_standby = LOW;
            estado = rojo;
          }
        }
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case bajo:
      if(!flag_bajo)
      {
        flag_bajo = HIGH;
        leds.mostrar(IMAGENES::m2_img_bajo, c_azul);
        contador = 0;
      }
      envolvente.cargar(analogRead(PIN_MIC_ENVOLVENTE));
      // Chequea Alto
      if(envolvente.promedio() >= (umbral_max*M2_PORC_ALTO/100))
      {
        flag_ok = HIGH;
        flag_bajo = LOW;
        estado = alto;
        contador = 0;
      }
      //Chequea Medio
      if((envolvente.promedio() < (umbral_max*M2_PORC_ALTO/100))&&(envolvente.promedio() >= (umbral_max*M2_PORC_MEDIO/100)))
      {
        flag_ok = HIGH;
        flag_bajo = LOW;
        estado = medio;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente.promedio() < (umbral_max*M2_PORC_BAJO/100))
      {
        flag_bajo = LOW;
        estado = standby;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case medio:
      if(!flag_medio)
      {
        flag_medio = HIGH;
        leds.mostrar(IMAGENES::m2_img_medio, c_azul);
        contador = 0;
      }
      envolvente.cargar(analogRead(PIN_MIC_ENVOLVENTE));
      // Chequea Alto
      if(envolvente.promedio() >= (umbral_max*M2_PORC_ALTO/100))
      {
        flag_ok = HIGH;
        flag_medio = LOW;
        estado = alto;
        contador = 0;
      }
      //Chequea Bajo
      if((envolvente.promedio() < (umbral_max*M2_PORC_MEDIO/100))&&(envolvente.promedio() >= (umbral_max*M2_PORC_BAJO/100)))
      {
        flag_ok = HIGH;
        flag_medio = LOW;
        estado = bajo;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente.promedio() < (umbral_max*M2_PORC_BAJO/100))
      {
        flag_medio = LOW;
        estado = standby;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case alto:
      if(!flag_alto)
      {
        flag_alto = HIGH;
        leds.mostrar(IMAGENES::m2_img_alto, c_azul);
        contador = 0;
      }
      envolvente.cargar(analogRead(PIN_MIC_ENVOLVENTE));
      //Chequea Medio
      if((envolvente.promedio() < (umbral_max*M2_PORC_ALTO/100))&&(envolvente.promedio() >= (umbral_max*M2_PORC_MEDIO/100)))
      {
        flag_ok = HIGH;
        flag_alto = LOW;
        estado = medio;
        contador = 0;
      }
      //Chequea Bajo
      if((envolvente.promedio() < (umbral_max*M2_PORC_MEDIO/100))&&(envolvente.promedio() >= (umbral_max*M2_PORC_BAJO/100)))
      {
        flag_ok = HIGH;
        flag_alto = LOW;
        estado = bajo;
        contador = 0;
      }
      //Chequea Nada
      if(envolvente.promedio() < (umbral_max*M2_PORC_BAJO/100))
      {
        flag_alto = LOW;
        estado = standby;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case rojo:
      if(!flag_rojo)
      {
        flag_rojo = HIGH;
        leds.mostrar(IMAGENES::circulo, c_rojo);
        contador = 0;
      }
      contador++;
      if(contador >= t_rojo)
      {
        flag_rojo = LOW;
        estado = verde;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      default:
      // Reinicia
      flag_verde = LOW;
      flag_rojo = LOW;
      flag_ok = LOW; // Si se cumplio o no el objetivo
      flag_bajo = LOW;
      flag_medio = LOW;
      flag_alto = LOW;
      flag_standby = LOW;
      contador = 0;
      estado = verde;
      break;
    }
    #if DEBUG_MODO_2 == 1
    if(estado==verde)
    {
      Serial.print("VERDE\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_verde);
    }
    if(estado==standby)
    {
      Serial.print("STANDBY\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_delay);
      Serial.print("\tEnvolvente Promedio: ");
      Serial.print(envolvente.promedio());
      Serial.print(" de (");
      Serial.print(umbral_max*M2_PORC_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_ALTO/100);
      Serial.println(")");
    }
    if(estado==bajo)
    {
      Serial.print("BAJO");
      Serial.print("\tEnvolvente Promedio: ");
      Serial.print(envolvente.promedio());
      Serial.print(" de (");
      Serial.print(umbral_max*M2_PORC_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_ALTO/100);
      Serial.println(")");
    }
    if(estado==medio)
    {
      Serial.print("MEDIO");
      Serial.print("\tEnvolvente Promedio: ");
      Serial.print(envolvente.promedio());
      Serial.print(" de (");
      Serial.print(umbral_max*M2_PORC_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_ALTO/100);
      Serial.println(")");
    }
    if(estado==alto)
    {
      Serial.print("ALTO");
      Serial.print("\tEnvolvente Promedio: ");
      Serial.print(envolvente.promedio());
      Serial.print(" de (");
      Serial.print(umbral_max*M2_PORC_BAJO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_MEDIO/100);
      Serial.print("/");
      Serial.print(umbral_max*M2_PORC_ALTO/100);
      Serial.println(")");
    }
    if(estado==rojo)
    {
      Serial.print("ROJO\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_rojo);
    }
    #endif
  }
}

//-------------------------------------------------------------------------------------------------
void Modo3(int umbral, int tiempo)
{
  // Estados
  enum Estados
  {
    verde,
    img_standby,
    img_bajo,
    img_medio,
    img_alto,
    cara,
    rojo
  };
  static Estados estado = verde;
  
  // Base de Tiempo
  static unsigned long t_anterior = 0;
  unsigned long t_actual;
  int t_verde = 2000/M3_TS; // 2 Segundos
  int t_cara = 3000/M3_TS; // 3 Segundos
  int t_rojo = 4000/M3_TS; // 4 Segundos
  int t_delay = 5000/M3_TS; // 5 Segundos
  int t_obj = (tiempo*1000)/M3_TS; // Tiempo debe estar en segundos

  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_rojo = LOW;
  static boolean flag_cara = LOW;
  static boolean flag_standby = LOW;
  static boolean flag_bajo = LOW;
  static boolean flag_medio = LOW;
  static boolean flag_alto = LOW;

  // Contadores
  static int contador = 0;

  // Otros
  int envolvente = 0;

  t_actual = millis();
  if((t_actual - t_anterior) >= M3_TS)
  {
    t_anterior = t_actual;
    switch(estado)
    {
      //-------------------------------------------------------------------------------------------------
      case verde:
      if(!flag_verde)
      {
        flag_verde = HIGH;
        leds.mostrar(IMAGENES::circulo, c_verde);
        contador = 0;
      }
      contador++;
      if(contador >= t_verde)
      {
        flag_verde = LOW;
        estado = img_standby;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case img_standby:
      if(!flag_standby)
      {
        flag_standby = HIGH;
        leds.mostrar(IMAGENES::m3_img_standby, c_naranja);
      }
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      if(envolvente >= umbral)
      {
        estado = img_bajo;
        flag_standby = LOW;
        contador = 0;
      }
      contador++;
      if(contador >= t_delay)
      {
        estado = rojo;
        flag_standby = LOW;
        contador = 0;
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case img_bajo:
      if(!flag_bajo)
      {
        flag_bajo = HIGH;
        leds.mostrar(IMAGENES::m2_img_bajo, c_naranja, c_azul);
      }
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      if(envolvente >= umbral)
      {
        contador++;
        if(contador >= t_obj*M3_PORC_BAJO/100)
        {
          estado = img_medio;
          flag_bajo = LOW;
        }
      }
      else
      {
        estado = img_standby;
        flag_bajo = LOW;
        contador = 0;
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case img_medio:
      if(!flag_medio)
      {
        flag_medio = HIGH;
        leds.mostrar(IMAGENES::m2_img_medio, c_naranja, c_azul);
      }
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      if(envolvente >= umbral)
      {
        contador++;
        if(contador >= t_obj*M3_PORC_MEDIO/100)
        {
          estado = img_alto;
          flag_medio = LOW;
        }
      }
      else
      {
        estado = img_standby;
        flag_medio = LOW;
        contador = 0;
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case img_alto:
      if(!flag_alto)
      {
        flag_alto = HIGH;
        leds.mostrar(IMAGENES::m2_img_alto, c_naranja, c_azul);
      }
      envolvente = analogRead(PIN_MIC_ENVOLVENTE);
      if(envolvente < umbral)
      {
        estado = cara;
        flag_alto = LOW;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case cara:
      if(!flag_cara)
      {
        flag_cara = HIGH;
        leds.mostrar(IMAGENES::cara, c_azul);
      }
      contador++;
      if(contador >= t_cara)
      {
        estado = verde;
        flag_cara = LOW;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case rojo:
      if(!flag_rojo)
      {
        flag_rojo = HIGH;
        leds.mostrar(IMAGENES::circulo, c_rojo);
        contador = 0;
      }
      contador++;
      if(contador >= t_rojo)
      {
        flag_rojo = LOW;
        estado = verde;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      default:
      // Reinicia
      flag_verde = LOW;
      flag_rojo = LOW;
      flag_cara = LOW;
      flag_standby = LOW;
      flag_bajo = LOW;
      flag_medio = LOW;
      flag_alto = LOW;
      contador = 0;
      estado = verde;
      break;
    }
    
    #if DEBUG_MODO_3 == 1
    if(estado==verde)
    {
      Serial.print("VERDE\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_verde);
    }
    if(estado==img_standby)
    {
      Serial.print("IMG_INICIO\t(|------)\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_delay);
      Serial.print("\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" (");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==img_bajo)
    {
      Serial.print("IMG_BAJO\t(|||----)\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_obj);
      Serial.print(" (");
      Serial.print(t_obj*M3_PORC_BAJO/100);
      Serial.print(" / ");
      Serial.print(t_obj*M3_PORC_MEDIO/100);
      Serial.print(")\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" (");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==img_medio)
    {
      Serial.print("IMG_MEDIO\t(|||||--)\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_obj);
      Serial.print(" (");
      Serial.print(t_obj*M3_PORC_BAJO/100);
      Serial.print(" / ");
      Serial.print(t_obj*M3_PORC_MEDIO/100);
      Serial.print(")\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" (");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==img_alto)
    {
      Serial.print("IMG_ALTO\t(|||||||)\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.print(t_obj);
      Serial.print(" (");
      Serial.print(t_obj*M3_PORC_BAJO/100);
      Serial.print(" / ");
      Serial.print(t_obj*M3_PORC_MEDIO/100);
      Serial.print(")\tEnvolvente: ");
      Serial.print(envolvente);
      Serial.print(" (");
      Serial.print(umbral);
      Serial.println(")");
    }
    if(estado==cara)
    {
      Serial.print("CARA\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_cara);
    }
    if(estado==rojo)
    {
      Serial.print("ROJO\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_rojo);
    }
    #endif
  }
}

//-------------------------------------------------------------------------------------------------
void Modo4()
{
  // Estados
  enum Estados
  {
    verde,
    standby,
    cara,
    rojo
  };
  static Estados estado = verde;
  
  // Base de Tiempo
  static unsigned long t_anterior = 0;
  unsigned long t_actual;
  int t_verde = 2000/M4_TS; // 2 Segundos
  int t_cara = 3000/M4_TS; // 3 Segundos
  int t_rojo = 4000/M4_TS; // 4 Segundos
  int t_delay = 5000/M4_TS; // 5 Segundos
  
  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_rojo = LOW;
  static boolean flag_cara = LOW;
  static boolean flag_standby = LOW;
  
  // Contadores
  static int contador = 0;

  // Otros
  int vocalRandom = 0;
  int vocalObtenida = 0;
  randomSeed(micros()); // Microsegundos asegura un Seed aleatorio

  t_actual = millis();
  if((t_actual - t_anterior) >= M4_TS)
  {
    t_anterior = t_actual;
    switch(estado)
    {
      //-------------------------------------------------------------------------------------------------
      case verde:
      if(!flag_verde)
      {
        flag_verde = HIGH;
        leds.mostrar(IMAGENES::circulo, c_verde);
        contador = 0;
      }
      contador++;
      if(contador >= t_verde)
      {
        flag_verde = LOW;
        estado = standby;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case standby:
      if(!flag_standby)
      {
        // Selecciona una vocal para mostrar
        flag_standby = HIGH;
        vocalRandom = floor(random(5));
        contador = 0;
        switch(vocalRandom)
        {
          // Caso A
          case 0:
          leds.mostrar(IMAGENES::a_img, c_naranja);
          break;
          // Caso E
          case 1:
          leds.mostrar(IMAGENES::a_img, c_naranja);
          break;
          // Caso I
          case 2:
          leds.mostrar(IMAGENES::a_img, c_naranja);
          break;
          // Caso O
          case 3:
          leds.mostrar(IMAGENES::a_img, c_naranja);
          break;
          // Caso U
          case 4:
          leds.mostrar(IMAGENES::a_img, c_naranja);
          break;
          // Si no está dentro del rango, no muestra nada y repite.
          default:
          leds.apagar();
          flag_standby = LOW;
          break;
        }
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: DETECCION DE VOCALES!
      //-------------------------------------------------------------------------------------------------
      

      if(vocalObtenida == vocalRandom)
      {
        estado = cara;
        flag_standby = LOW;
        contador = 0;
      }
      contador++;
      if(contador >= t_delay)
      {
        estado = rojo;
        flag_standby = LOW;
        contador = 0;
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case cara:
      if(!flag_cara)
      {
        flag_cara = HIGH;
        leds.mostrar(IMAGENES::cara, c_azul);
        contador = 0;
      }
      contador++;
      if(contador >= t_cara)
      {
        estado = verde;
        flag_cara = LOW;
        contador = 0;
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case rojo:
      if(!flag_rojo)
      {
        flag_rojo = HIGH;
        leds.mostrar(IMAGENES::circulo, c_rojo);
        contador = 0;
      }
      contador++;
      if(contador >= t_rojo)
      {
        flag_rojo = LOW;
        estado = verde;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      default:
      // Reinicia
      flag_verde = LOW;
      flag_rojo = LOW;
      flag_cara = LOW;
      flag_standby = LOW;
      contador = 0;
      estado = verde;
      break;
    }
    
    #if DEBUG_MODO_4 == 1
    if(estado==verde)
    {
      Serial.print("VERDE\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_verde);
    }
    if(estado==standby)
    {
      Serial.print("STANDBY\tVOCAL_RANDOM:\t");
      Serial.print(vocalRandom);
      Serial.print("\tVOCAL_OBTENIDA:\t");
      Serial.print(vocalObtenida);
      Serial.print("\tContador ");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_delay);
    }
    if(estado==cara)
    {
      Serial.print("CARA\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_cara);
    }
    if(estado==rojo)
    {
      Serial.print("ROJO\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_rojo);
    }
    #endif
  }
}

//-------------------------------------------------------------------------------------------------
void Modo5()
{
  // Estados
  enum Estados
  {
    verde,
    standby,
    vocal_a,
    vocal_e,
    vocal_i,
    vocal_o,
    vocal_u
  };
  static Estados estado = verde;
  
  // Base de Tiempo
  static unsigned long t_anterior = 0;
  unsigned long t_actual;
  int t_verde = 2000/M5_TS; // 2 Segundos
  
  // Flags
  static boolean flag_verde = LOW;
  static boolean flag_standby = LOW;
  static boolean flag_a = LOW;
  static boolean flag_e = LOW;
  static boolean flag_i = LOW;
  static boolean flag_o = LOW;
  static boolean flag_u = LOW;
  
  // Contadores
  static int contador = 0;

  // Otros
  int vocalObtenida = 0;
  randomSeed(micros()); // Microsegundos asegura un Seed aleatorio

  t_actual = millis();
  if((t_actual - t_anterior) >= M5_TS)
  {
    t_anterior = t_actual;
    switch(estado)
    {
      //-------------------------------------------------------------------------------------------------
      case verde:
      if(!flag_verde)
      {
        flag_verde = HIGH;
        leds.mostrar(IMAGENES::circulo, c_verde);
        contador = 0;
      }
      contador++;
      if(contador >= t_verde)
      {
        flag_verde = LOW;
        estado = standby;
        contador = 0;
      }
      break;
      
      //-------------------------------------------------------------------------------------------------
      case standby:
      if(!flag_standby)
      {
        flag_standby = HIGH;
        leds.apagar();
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: DETECCION DE VOCALES!
      //-------------------------------------------------------------------------------------------------

      switch(vocalObtenida)
      {
        // Case A
        case 0:
        estado = vocal_a;
        flag_standby = LOW;
        break;
        // Case E
        case 1:
        estado = vocal_e;
        flag_standby = LOW;
        break;
        // Case I
        case 2:
        estado = vocal_i;
        flag_standby = LOW;
        break;
        // Case O
        case 3:
        estado = vocal_o;
        flag_standby = LOW;
        break;
        // Case U
        case 4:
        estado = vocal_u;
        flag_standby = LOW;
        break;
        // Si no está dentro del rango, no muestra nada y repite.
        default:
        flag_standby = LOW;
        leds.apagar();
        break;
      }
      break;

      //-------------------------------------------------------------------------------------------------
      case vocal_a:
      if(!flag_a)
      {
        flag_a = HIGH;
        leds.mostrar(IMAGENES::a_img, c_naranja);
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: REACCION EN A!
      //-------------------------------------------------------------------------------------------------

      //-------------------------------------------------------------------------------------------------
      // TODO: Volver a STANDBY!
      //-------------------------------------------------------------------------------------------------
      
      break;

      //-------------------------------------------------------------------------------------------------
      case vocal_e:
      if(!flag_e)
      {
        flag_e = HIGH;
        leds.mostrar(IMAGENES::e_img, c_naranja);
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: REACCION EN E!
      //-------------------------------------------------------------------------------------------------

      //-------------------------------------------------------------------------------------------------
      // TODO: Volver a STANDBY!
      //-------------------------------------------------------------------------------------------------
      
      break;

      //-------------------------------------------------------------------------------------------------
      case vocal_i:
      if(!flag_i)
      {
        flag_i = HIGH;
        leds.mostrar(IMAGENES::i_img, c_naranja);
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: REACCION EN I!
      //-------------------------------------------------------------------------------------------------

      //-------------------------------------------------------------------------------------------------
      // TODO: Volver a STANDBY!
      //-------------------------------------------------------------------------------------------------
      
      break;

      //-------------------------------------------------------------------------------------------------
      case vocal_o:
      if(!flag_o)
      {
        flag_o = HIGH;
        leds.mostrar(IMAGENES::o_img, c_naranja);
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: REACCION EN O!
      //-------------------------------------------------------------------------------------------------

      //-------------------------------------------------------------------------------------------------
      // TODO: Volver a STANDBY!
      //-------------------------------------------------------------------------------------------------
      
      break;

      //-------------------------------------------------------------------------------------------------
      case vocal_u:
      if(!flag_u)
      {
        flag_u = HIGH;
        leds.mostrar(IMAGENES::u_img, c_naranja);
      }

      //-------------------------------------------------------------------------------------------------
      // TODO: REACCION EN A!
      //-------------------------------------------------------------------------------------------------

      //-------------------------------------------------------------------------------------------------
      // TODO: Volver a STANDBY!
      //-------------------------------------------------------------------------------------------------
      
      break;

      //-------------------------------------------------------------------------------------------------
      default:
      // Reinicia
      flag_verde = LOW;
      flag_standby = LOW;
      flag_a = LOW;
      flag_e = LOW;
      flag_i = LOW;
      flag_o = LOW;
      flag_u = LOW;
      estado = verde;
      contador = 0;
      break;
    }

    #if DEBUG_MODO_5 == 1
    if(estado==verde)
    {
      Serial.print("VERDE\t");
      Serial.print(contador);
      Serial.print(" de ");
      Serial.println(t_verde);
    }
    if(estado==standby)
    {
      Serial.print("STANDBY\tVOCAL_OBTENIDA:\t");
      Serial.println(vocalObtenida);
    }
    if(estado==vocal_a)
    {
      Serial.println("OBTENIDO\tA");
    }
    if(estado==vocal_e)
    {
      Serial.println("OBTENIDO\tE");
    }
    if(estado==vocal_i)
    {
      Serial.println("OBTENIDO\tI");
    }
    if(estado==vocal_o)
    {
      Serial.println("OBTENIDO\tO");
    }
    if(estado==vocal_u)
    {
      Serial.println("OBTENIDO\tU");
    }
    #endif
  }
}
