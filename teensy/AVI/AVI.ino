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
// DEBUG POR BLOQUES
// Se debe descomentar solo uno y trabajar
//
//#define D_MOTORES
//#define D_LEDs
//#define D_MODO_1
//#define D_MODO_2
//#define D_MODO_3
//#define D_MODO_4
//#define D_MODO_5
//#define D_FORMANTES
//#define D_GRABAR_AUDIO
//#define D_FILTROMA
  #define D_INTERFAZ
//#define D_MOTOR_LED // Prueba Motores junto con LED. 15/04/16
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
#include "AVI_Interfaz.h"
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
// Los otros archivos deben llamarlas via 'extern' en su respectivo header
//=================================================================================================
// Tira de LED (WS2812B)
LEDs leds;

//=================================================================================================
// DEBUG POR BLOQUES
// D_MOTORES
//=================================================================================================
// Motores (150:1 Micro Metal Gearmotor MP)
#ifdef D_MOTORES
Motor motor_A(PIN_MOTOR_A_1, PIN_MOTOR_A_2, PIN_PWM_A);
Motor motor_B(PIN_MOTOR_B_1, PIN_MOTOR_B_2, PIN_PWM_B);
Motor motor_C(PIN_MOTOR_C_1, PIN_MOTOR_C_2, PIN_PWM_C);
Motor motor_D(PIN_MOTOR_D_1, PIN_MOTOR_D_2, PIN_PWM_D);

Motores motores ( motor_A , motor_B , motor_C , motor_D );

//   Motor motor_A;
//   Motor motor_B;
//   Motor motor_C;
//   Motor motor_D;
//   Motores motores;

void setup()
{
  pinMode(13, OUTPUT);
  //Serial.begin(9600);
  delay(500);
//   motor_A = Motor(PIN_MOTOR_A_1, PIN_MOTOR_A_2, PIN_PWM_A);
//   motor_B = Motor(PIN_MOTOR_B_1, PIN_MOTOR_B_2, PIN_PWM_B);
//   motor_C = Motor(PIN_MOTOR_C_1, PIN_MOTOR_C_2, PIN_PWM_C);
//   motor_D = Motor(PIN_MOTOR_D_1, PIN_MOTOR_D_2, PIN_PWM_D);
//   
//   Motores motores ( motor_A , motor_B , motor_C , motor_D );
  digitalWrite(13, HIGH);
  delay(500);
  motores.encender();
  digitalWrite(13, LOW);
  delay(500);
}

void loop()
{
  Serial.println(motores.getEstado());
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  motores.desplazamientoAdelante(50);
  delay(500);
  motores.desplazamientoAtras(50);
  delay(500);
  motores.girarCCW(50, 700);
  delay(500);
}
#endif // D_MOTORES

//=================================================================================================
// DEBUG POR BLOQUES
// D_LEDs
//=================================================================================================
#ifdef D_LEDs

void setup()
{
  pinMode(13, OUTPUT);
	Serial.begin(9600);
	delay(500);
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(13, LOW);
	delay(500);

  leds.mostrar(IMAGENES::circulo , CRGB::Blue );
  delay(1000);
//  for( int i = 0 ; i<50 ; i++)
//  {
//    Serial.println(leds.leds[i]);
//  }
  leds.apagar();
  delay(1000);

  Serial.print("Khaki es : "); Serial.println((long)CRGB::Khaki,HEX);

}


void loop()
{
  //digitalWrite(13, HIGH); // Este es un pin de Audio, no se deberia tocar.
  delay(500);
  //digitalWrite(13, LOW);
  delay(500);
  
	leds.mostrar(IMAGENES::circulo , long(0x2084B7));
	delay(1000);
	leds.apagar();
	delay(1000);

  leds.mostrar(IMAGENES::o_img , 0x00FF00 ); // rojo
  delay(1000);
  leds.apagar();
  delay(1000);

  leds.mostrar(IMAGENES::m2_img_medio , 0x66FF00, 0x0066FF); // naranja
  delay(1000);
  leds.apagar();
  delay(1000);

  leds.mostrar(IMAGENES::o_img , 0xFFFF00 ); //amarillo
  delay(1000);
  leds.apagar();
  delay(1000);
  leds.brillo = (leds.brillo + 0.1);
  if(leds.brillo > 1)
    leds.brillo = 0.1;
}


#endif // D_LEDs

//=================================================================================================
// DEBUG POR BLOQUES
// D_MODO_1
//=================================================================================================
#ifdef D_MODO_1
void setup()
{
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
  Modo1(512);
}
#endif // D_MODO_1

//=================================================================================================
// DEBUG POR BLOQUES
// D_MODO_2
//=================================================================================================
#ifdef D_MODO_2
void setup()
{
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
  Modo2(1024);
}

#endif // D_MODO_2

//=================================================================================================
// DEBUG POR BLOQUES
// D_MODO_3
//=================================================================================================
#ifdef D_MODO_3
void setup()
{
  //COMUNICACION
  Serial.begin(9600);
  delay(1000);
  Serial.println("--- INICIO ---");
}

void loop()
{
  Modo3(240, 6);
}
#endif // D_MODO_3

//=================================================================================================
// DEBUG POR BLOQUES
// D_MODO_4
//=================================================================================================
#ifdef D_MODO_4
void setup()
{
  //COMUNICACION
  Serial.begin(9600);
  delay(1000);
  Serial.println("--- INICIO ---");
}

void loop()
{
  Modo4();
}
#endif // D_MODO_4

//=================================================================================================
// DEBUG POR BLOQUES
// D_MODO_5
//=================================================================================================
#ifdef D_MODO_5
void setup()
{
  //COMUNICACION
  Serial.begin(9600);
  delay(1000);
  Serial.println("--- INICIO ---");
}

void loop()
{
  Modo5();
}
#endif // D_MODO_5

//=================================================================================================
// DEBUG POR BLOQUES
// D_FORMANTES
//=================================================================================================
#ifdef D_FORMANTES
#include <Eigen30.h>
// Para evitar problemas. Ver https://forum.pjrc.com/archive/index.php/t-28181.html
void abort()
{
  while(1);
}

int main()
{
  // SETUP
  Serial.begin(9600);
  delay(1000);
  
  // Variables
  int f1 = 0; // Primer Formante
  int f2 = 0; // Segundo Formante
  //Vector de datos (con Hamming)
  float x[200] = {-0.024585,-0.006653,0.023288,0.041231,0.040948,0.026622,-0.009038,-0.029507,-0.034609,-0.030575,-0.023221,-0.016600,-0.010438,0.017491,0.023227,0.024427,-0.004247,-0.034114,-0.052752,-0.040406,-0.019477,0.023373,0.056127,0.073640,0.077327,0.067088,0.051926,0.054399,0.042402,0.062926,0.087814,0.107334,0.150385,-0.109645,-0.183996,-0.256445,-0.280025,-0.087166,-0.006676,0.014467,0.046250,0.031679,0.002091,0.133171,0.018575,-0.192339,-0.294556,-0.422043,-0.355615,-0.057643,0.101655,0.189680,0.274686,0.138427,0.130090,0.083122,-0.011272,-0.177074,-0.341549,-0.366291,-0.251080,0.110403,0.272644,0.263567,0.090250,-0.184890,-0.285150,-0.360691,-0.322682,-0.262342,-0.218518,-0.127592,0.036756,0.108951,0.113109,-0.055113,-0.298744,-0.348264,-0.252614,-0.092908,0.171197,0.265855,0.310516,0.294670,0.229195,0.202918,0.244777,0.271353,0.395890,0.401078,0.428415,0.132737,-0.467096,-0.536236,-0.818687,-0.581034,-0.131338,0.134766,0.173894,0.281285,0.196737,0.151142,0.280898,-0.063237,-0.373869,-0.624915,-0.758461,-0.370788,0.139134,0.323302,0.451807,0.433744,0.214886,0.163705,0.004647,-0.093831,-0.273295,-0.398370,-0.401035,-0.126537,0.151897,0.313942,0.281790,-0.007147,-0.275567,-0.372839,-0.406841,-0.322638,-0.229666,-0.178788,-0.048292,0.091277,0.112637,0.033620,-0.126117,-0.217804,-0.256476,-0.172868,-0.030731,0.099316,0.184786,0.217349,0.206412,0.156778,0.133195,0.143783,0.163248,0.185297,0.202386,0.269606,0.088615,-0.250186,-0.246395,-0.406693,-0.265903,-0.042351,0.043910,0.055051,0.088297,0.052764,0.083660,0.119555,-0.043876,-0.151563,-0.222830,-0.247587,-0.111648,0.039878,0.096278,0.124881,0.098402,0.038364,0.051312,0.015099,-0.026344,-0.068623,-0.103607,-0.097388,-0.023951,0.031547,0.053961,0.038387,-0.008705,-0.053419,-0.060962,-0.062410,-0.047860,-0.039006,-0.028133,-0.010190,0.004642,0.008767,-0.000148,-0.020802,-0.030804,-0.031697,-0.022550,-0.004079,0.013698,0.025886};
  int x_n = 200; // Cantidad de Elementos del Vector de Datos
  int p = 10; // Orden del Filtro
  int Fs = 8000; // Frecuencia de Muestreo

  float a[10]={0.572674, 0.923660, 0.481029, 0.147713, 0.034214, 0.948993, 0.755289, 0.974128, 0.753004, 0.124419};

  Serial.println("Vector A antes de Hamming:");
  for(uint8_t i=0; i<10; i++)
  {
    Serial.println(a[i],6);
  }
  Serial.println();
  hamming(a,10);
  Serial.println("Vector A despues de Hamming:");
  for(uint8_t i=0; i<10; i++)
  {
    Serial.println(a[i],6);
  }
  Serial.println();  

  obtener_formantes(x, x_n, p, Fs, &f1, &f2);
  
  Serial.print("F1 =\t");
  Serial.println(f1);
  Serial.print("F2 =\t");
  Serial.println(f2);
  
  return 0;
}
#endif // D_FORMANTES

//=================================================================================================
// DEBUG POR BLOQUES
// D_GRABAR_AUDIO
//=================================================================================================
#ifdef D_GRABAR_AUDIO
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
int vocal = -1;
FiltroMA formante1MA(10);
FiltroMA formante2MA(10);

// Funciones Auxiliares
void medir()
{
  if(analogRead(PIN_MIC_ENVOLVENTE)>=50)
  {
    datos[indice] = analogRead(PIN_MIC_AUDIO);
    indice++;
  }
}

void setup()
{
  pinMode(PIN_MIC_ENVOLVENTE, INPUT);
  delay(1000);
  
  // Limpia el vector datos
  for(int n=0; n<AUDIO_CANT_MUESTRAS; n++)
  {
    datos[n]=0;
  }
  
  // FlexiTimer2
  FlexiTimer2::set(1, 1.0/AUDIO_FS, medir);
  FlexiTimer2::start();
  
  //digitalWrite(13, HIGH);
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

//=================================================================================================
// DEBUG POR BLOQUES
// D_FILTROMA
//=================================================================================================
#ifdef D_FILTROMA

void setup()
{
  Serial.begin(9600);
  FiltroMA filtro(3);
  delay(1000);
  
  Serial.println("Prueba FiltroMA");
  
  Serial.print("datos[3]={1,0,0}\tPromedio:\t");
  filtro.cargar(1);
  Serial.println(filtro.promedio());
  
  Serial.print("datos[3]={1,1,0}\tPromedio:\t");
  filtro.cargar(1);
  Serial.println(filtro.promedio());
  
  Serial.print("datos[3]={1,1,1}\tPromedio:\t");
  filtro.cargar(1);
  Serial.println(filtro.promedio());
  
  Serial.print("datos[3]={2,1,1}\tPromedio:\t");
  filtro.cargar(2);
  Serial.println(filtro.promedio());
  
  Serial.print("datos[3]={3,2,1}\tPromedio:\t");
  filtro.cargar(3);
  Serial.println(filtro.promedio());
  
  Serial.print("datos[3]={0,3,2}\tPromedio:\t");
  filtro.cargar(0);
  Serial.println(filtro.promedio());
}

void loop()
{
  //
}

#endif // D_FILTROMA

//=================================================================================================
// DEBUG POR BLOQUES
// D_MOTOR_LED
//=================================================================================================
#ifdef D_MOTOR_LED

Motor motor_A(PIN_MOTOR_A_1, PIN_MOTOR_A_2, PIN_PWM_A);
Motor motor_B(PIN_MOTOR_B_1, PIN_MOTOR_B_2, PIN_PWM_B);
Motor motor_C(PIN_MOTOR_C_1, PIN_MOTOR_C_2, PIN_PWM_C);
Motor motor_D(PIN_MOTOR_D_1, PIN_MOTOR_D_2, PIN_PWM_D);

Motores motores ( motor_A , motor_B , motor_C , motor_D );

void setup()
{
  Serial.begin(9600);
  delay(500);
  
  // USAR SOLO SI EL MICROFONO NO ESTÁ CONECTADO AL PIN 13
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  motores.encender();

  leds.mostrar(IMAGENES::circulo , CRGB::Blue );
  delay(2000);
  
  leds.apagar();
  delay(1000);
  
  motores.desplazamientoAdelante(50);
}


void loop()
{
  leds.mostrar(IMAGENES::a_img , c_rojo);
  delay(1000);
  
  leds.mostrar(IMAGENES::e_img , c_azul);
  delay(1000);
  
  leds.mostrar(IMAGENES::i_img , c_amarillo);
  delay(1000);
  
  leds.mostrar(IMAGENES::o_img , c_violeta);
  delay(1000);
  
  leds.mostrar(IMAGENES::u_img , c_verde);
  delay(1000);
  
  leds.mostrar(IMAGENES::cara , c_naranja);
  delay(1000);
}

#endif // D_MOTOR_LED

//=================================================================================================
// DEBUG POR BLOQUES
// D_INTERFAZ
//=================================================================================================
#ifdef D_INTERFAZ
#include <FastLED.h>
#include <FlexiTimer2.h>
#include <Eigen30.h>
#include <arm_math.h>

//=================================================================================================
// VARIABLES GLOBALES
// Los otros archivos deben llamarlas via 'extern' en su respectivo header.
//=================================================================================================
// Tira de LED (WS2812B)
// LEDs leds;

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
#endif
