//=================================================================================================
// AVI_Formantes.cpp
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
// FUENTES
// - https://github.com/RhysU/ar [Collomb2009.cpp]
// - https://forum.pjrc.com/
// - https://github.com/vancegroup/EigenArduino
//
//=================================================================================================
// DESCRIPCION
// - Contiene funciones relacionadas con el calculo de formantes y vocales.
//
//=================================================================================================
// COMENTARIOS GENERALES
// - Los indices del for usan uint8_t. Es mas chico, a menos que sea necesario mayor tamaño.
// - Si se tiene que dividir por 2*pi, se multiplica por una constante DIV_2_PI que es 1/(2*pi).
// - La constante PI_2 es 2*pi para simplificar calculo.
// - En Eigen: Matrix X c d
//   - X es de filas y columnas dinámicas. Se tiene que definir en el constructor.
//   - c es que los elementos son complejos.
//   - d elementos tipo double. (Queremos buena precision)
//
//=================================================================================================

#include "Arduino.h"
#include "AVI_Formantes.h"
#include "AVI_Config.h"
#include <Eigen30.h>
#include <Eigen/Eigenvalues>

#define DIV_2_PI 0.15915494f // 1/2*PI
#define PI_2 6.28318530717959f // 2*PI

using namespace Eigen;
using namespace std;

//-------------------------------------------------------------------------------------------------
// Funcion de intercambio (tipo float)
void swap(float *x, float *y)
{
  float temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

//-------------------------------------------------------------------------------------------------
// Funcion de intercambio (tipo std::complex<float>)
void complex_swap(complex<float> *x, complex<float> *y)
{
  complex<float> temp;
  temp.real(x->real());
  temp.imag(x->imag());
  x->real(y->real());
  x->imag(y->imag());
  y->real(temp.real());
  y->imag(temp.imag());
}

//-------------------------------------------------------------------------------------------------
// Aplica una ventana de Hamming al vector de entrada
void hamming(float* vector, int longitud)
{
// Generamos la ventana de Hamming de N puntos
// Implementacion basica.  
  // w = zeros(N,1);
  // for i=1:N
  // w(i) = 0.54 - 0.46*cos(2*pi*(i-1)/(N-1));
  // end
  
  for( int i = 0; i < longitud; i++  )
  {
    vector[i] = vector[i] * (0.54 - 0.46*cos(PI_2*i/(longitud-1)));
  }
  return;
}

//-------------------------------------------------------------------------------------------------
// Obtiene la vocal con los formantes y tolerancias
char getVocal(int f1, int f2)
{
  double dist[5], minimo;
  int resultado = 0;
  char vocal;
  for(uint8_t i=0; i<5; i++)
  {
    dist[i] = 0;
  }
  dist[0] = sqrt(pow(f1-A_F1, 2) + pow(f2-A_F2, 2));
  dist[1] = sqrt(pow(f1-E_F1, 2) + pow(f2-E_F2, 2));
  dist[2] = sqrt(pow(f1-I_F1, 2) + pow(f2-I_F2, 2));
  dist[3] = sqrt(pow(f1-O_F1, 2) + pow(f2-O_F2, 2));
  dist[4] = sqrt(pow(f1-U_F1, 2) + pow(f2-U_F2, 2));
  minimo = dist[0];
  resultado = 1;
  for(uint8_t i=0; i<5; i++)
  {
    if(dist[i] < minimo)
    {
      minimo = dist[i];
      resultado = i+1;
    }
  }
  switch(resultado)
    {
      case 1:
      vocal = 'A';
      break;
      case 2:
      vocal = 'E';
      break;
      case 3:
      vocal = 'I';
      break;
      case 4:
      vocal = 'O';
      break;
      case 5:
      vocal = 'U';
      break;
      default:
      vocal = 'X';
      break;
    }
  return vocal;
}

//-------------------------------------------------------------------------------------------------
// Algoritmo Convencional de Burg
// Fuente: https://github.com/RhysU/ar [Collomb2009.cpp]
// En coeffs devuelve los coeficientes del filtro estimado
// x es la señal a partir de la cual se estimará un filtro de solo polos
// x_n es la cantidad de elementos de x
// p es el orden del filtro a estimar
void BurgAlgorithm(float* coeffs, float* x, int x_n, int p)
{
  // Initializar Datos
  int x_length = x_n - 1; // Input Size
  int m = p; // Coefficient Size

  // Inicializar Ak
  float Ak[m+1];
  for(int n=0; n<m+1; n++)
  {
    Ak[n] = 0.0;
  }
  Ak[0] = 1.0;

  // Inicializar f y b
  float f[x_n]; // Ambos de la misma longitud de Datos
  float b[x_n];
  for(int n=0; n<x_n; n++) // Iguala ambos con los datos
  {
    f[n] = x[n];
    b[n] = x[n];
  }
  // Inicializa Dk (Denominador de mu)
  float Dk = 0.0;
  for(int j=0; j<=x_length; j++)
  {
    Dk += 2.0 * f[j] * f[j];
  }
  Dk -= f[0] * f[0] + b[x_length] * b[x_length];

  // Recursion de Burg
  for(int k=0; k<m; k++)
  {
    // Computo de mu
    float mu = 0.0;
    for(int n=0; n<=x_length-k-1; n++)
    {
      mu += f[n+k+1] * b[n];
    }
    mu *= -2.0 / Dk;

    // Actualiza Ak
    for(int n=0; n<=(k+1)/2; n++)
    {
      float t1 = Ak[n] + mu * Ak[k+1-n];
      float t2 = Ak[k+1-n] + mu * Ak[n];
      Ak[n] = t1;
      Ak[k+1-n] = t2;
    }

    // Actualiza f y b
    for(int n=0; n<=x_length-k-1; n++)
    {
      float t1 = f[n+k+1] + mu * b[n];
      float t2 = b[n] + mu * f[n+k+1];
      f[n+k+1] = t1;
      b[n] = t2;
    }

    // Actualiza Dk
    Dk = (1.0 - mu*mu)*Dk - f[k+1]*f[k+1] - b[x_length-k-1]*b[x_length-k-1];
  }

  //Asigna Coeficientes
  for(int n=0; n<m+1; n++)
  {
    coeffs[n] = Ak[n];
  }
}

//-------------------------------------------------------------------------------------------------
// Obtener formantes a partir del segmento de sonido
void obtener_formantes(float* x, int x_n, int p, int Fs, int* f1, int* f2)
{
  using namespace Eigen;
  using namespace std;

  
  // PRIMERA PARTE - BURG
  float coeffs[p+1]; //Coeficientes de Burg
  BurgAlgorithm(coeffs, x, x_n, p); //Calcula los Coeficientes

  #if DEBUG == 1
  Serial.println("Coeficientes obtenidos:");
  for(uint8_t i = 0; i < p+1; i++)
  {
   Serial.println(coeffs[i],8);
  }
  Serial.println();
  #endif

  // SEGUNDA PARTE - RAICES
  MatrixXd Mat_coeffs(p,p);

  // Construye la Companion Matrix del polinomio.
  // Ver https://en.wikipedia.org/wiki/Companion_matrix
  // Usamos los coeficientes en la primer fila. El resultado es el mismo.
  
  // Primer fila de la Companion Matrix
  for(uint8_t j=0; j<p; j++)
  {
    Mat_coeffs(0,j)=-coeffs[j+1]/coeffs[0];
  }
  
  // Resto de la Companion Matrix
  for(uint8_t i=1; i<p; i++)
  {
    for(uint8_t j=0; j<p; j++)
    {
      if(i==(j+1))
      {
        Mat_coeffs(i,j)=1;
      }
      else
      {
        Mat_coeffs(i,j)=0;
      }
    }
  }

  // Los autovalores de la companion matrix son las raices del polinomio
  EigenSolver<MatrixXd> es(Mat_coeffs,false); // false porque no necesitamos autovectores
  MatrixXcd Mat_roots;  
  complex<float> roots[p];

  // Calcula los autovalores y los quita de la matriz diagonal
  Mat_roots = es.eigenvalues().asDiagonal();
  for(uint8_t i=0; i<p; i++)
  {
    for(uint8_t j=0; j<p; j++)
    {
      if(i==j)
      {
        roots[i].real(Mat_roots(i,j).real());
        roots[i].imag(Mat_roots(i,j).imag());
      }
    }
  }

  #if DEBUG == 1
  Serial.println("Raices:");
  for(uint8_t i=0; i<p; i++)
  {
    Serial.print(roots[i].real(), 8);
    Serial.print(" + ");
    Serial.print(roots[i].imag(), 8);
    Serial.println("i");
  }
  Serial.println();
  #endif

  // TERCERA PARTE - FILTRADO DE LAS RAICES
  
  // Raices reales y complejas con imag>0
  uint8_t pp = 0; // Nuevo Indice
  
  for(uint8_t i=0; i<p; i++)
  {
    // Cuenta cuantas raices reales y complejas con imag>0 hay
    if(roots[i].imag()>=0)
    {
      pp += 1;
    }
  }
  
  // Si no encontró raices, termina
  if (pp == 0)
	{
		*f1 = 0;
		*f2 = 0;
		return;
	}
  
  // Con el indice creamos y cargamos el nuevo arreglo de raices
  complex<float> roots_real[pp];
  pp = 0;
  for(uint8_t i=0; i<p; i++)
  {
    if(roots[i].imag()>=0)
    {
      roots_real[pp].real(roots[i].real());
      roots_real[pp].imag(roots[i].imag());
      pp++;
    }
  }

  #if DEBUG == 1
  Serial.println("Raices Reales e Imag>0:");
  for(uint8_t i=0; i<pp; i++)
  {
   Serial.print(roots_real[i].real(), 8);
   Serial.print(" + ");
   Serial.print(roots_real[i].imag(), 8);
   Serial.println("i");
  }
  Serial.println();
  #endif

  // CUARTA PARTE - ANGULOS DE CADA RAIZ
  // Obtiene el angulo de cada raiz.
  float frqs[pp];
  for(uint8_t i=0; i<pp; i++)
  {
    frqs[i] = atan2(roots_real[i].imag(), roots_real[i].real())*(Fs*DIV_2_PI);
  }

  #if DEBUG == 1
  Serial.println("freqs[i]:");
  for(uint8_t i=0; i<pp; i++)
  {
    Serial.println(frqs[i], 8);
  }
  Serial.println();
  #endif

  // Ordena los arreglos segun sus angulos.
  // De paso ordena las raices (Bubble Sort).
  for(uint8_t i=0; i<(pp-1); i++)
  {
    for(uint8_t j=0; j<(pp-(i+1)); j++)
    {
      if(frqs[j] > frqs[j+1])
      {
        swap(&frqs[j], &frqs[j+1]);
        complex_swap(&roots_real[j], &roots_real[j+1]);
      }
    }
  }

  // QUINTA PARTE - BANDWIDTH
  float bw[pp];
  for(uint8_t i=0; i<pp; i++)
  {
    // abs de complex se solapa con abs de valor absoluto y trae problemas
    bw[i] = (-0.5)*(Fs*DIV_2_PI)*log(sqrt(roots_real[i].real()*roots_real[i].real()+roots_real[i].imag()*roots_real[i].imag()));
  }

  #if DEBUG == 1
  Serial.println("bw[i]:");
  for(uint8_t i=0; i<pp; i++)
  {
    Serial.println(bw[i],5);
  }
  Serial.println();
  #endif

  // SEXTA PARTE - FORMANTES

  // Eliminamos todas los polos menores a 50 Hz o que tengan anchos de banda mayores
  // a 400 Hz. Esto es un criterio empírico. En la ayuda de Matlab dice > 90 Hz, 
  // Praat 5.4 dice > 50 Hz.
  
  // ff será el índice del arreglo de formantes válidos. Reuso el arreglo de frqs para
  // ahorrar recursos? Pistola.
  // Luego habrá que chequear si efectivamente se habáan encontrado frqs/formantes o no
  // y ver que hacer en caso de que no.
  
  float formantes[3]; // Si solo usamos 2...
  uint8_t ff = 0;	
  for(uint8_t i=0; i<pp; i++)
  {
    if((frqs[i] > 50)&&(bw[i] < 400))
    {
      formantes[ff] = frqs[i];
      ff++;
    }
    // Como solo queremos 2 formantes..
    if(ff == 3)
    {
      break;
    }
  }

  #if DEBUG == 1
  Serial.println("Los formantes encontrados son:");
  for(uint8_t i=0; i<3; i++)
  {
   Serial.println(formantes[i]);
  }
  Serial.println();
  #endif
  
  if (ff >= 2) // Si hay dos o más formantes, guardo los dos primeros como F1 y F2.
  {
    *f1 = round(formantes[0]);
    *f2 = round(formantes[1]);
    return;
  }
  else
  {
    *f1 = 0;
	  *f2 = 0;
    return;
  }
}

