//=================================================================================================
// AVI_Motores.cpp
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
// DESCRIPCION
// - Contiene todo lo utilizado por los motores.
// 
//=================================================================================================
// CLASES:
// - FiltroMA: Filtro Promediador de Media Movil
//
//=================================================================================================

#include "AVI_Motores.h"

//=================================================================================================
// Motor
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructores
Motor::Motor(void)
{
  // Constructor vacío
}

Motor::Motor(uint8_t i_pin_1, uint8_t i_pin_2, uint8_t i_pin_PWM)
{
  mPin1 = i_pin_1;
  mPin2 = i_pin_2;
  mPinPWM = i_pin_PWM;

  pinMode(mPin1, OUTPUT);
  pinMode(mPin2, OUTPUT);
  pinMode(mPinPWM, OUTPUT);
  
  digitalWrite(mPin1, LOW);
  digitalWrite(mPin2, LOW);
  analogWrite(mPinPWM, 0);
}

//-------------------------------------------------------------------------------------------------
// Metodos
void Motor::parar(void)
{
  analogWrite(mPinPWM, 0);
}

void Motor::frenar(void)
{
  // Utiliza el frenado segun indica el driver.
  digitalWrite(mPin1, LOW);
  digitalWrite(mPin2, LOW);
  analogWrite(mPinPWM, 0);
}

void Motor::adelante(float porcentaje)
{
  digitalWrite(mPin1, HIGH);
  digitalWrite(mPin2, LOW);
  analogWrite(mPinPWM, (int)porcentaje*255/100);
}

void Motor::atras(float porcentaje)
{
  digitalWrite(mPin1, LOW);
  digitalWrite(mPin2, HIGH);
  analogWrite(mPinPWM, (int)porcentaje*255/100);
}

//=================================================================================================
// Motores
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructores
Motores::Motores()
{
  // Constructor vacío
}

Motores::Motores(Motor& i_motor_A, Motor& i_motor_B, Motor& i_motor_C, Motor& i_motor_D)
{
  encendido = false;
  
  #ifdef DEBUG_MOTORES
  estado = "Apagados";
  #endif
  
  mMotorA = i_motor_A;
  mMotorB = i_motor_B;
  mMotorC = i_motor_C;
  mMotorD = i_motor_D;
}

//-------------------------------------------------------------------------------------------------
// Metodos
void Motores::encender(void)
{
  encendido = true;
  #ifdef DEBUG_MOTORES
  estado = "Encendidos";
  Serial.println("Motores: " + estado);
  #endif
}

void Motores::apagar(void)
{
  encendido = false;
  #ifdef DEBUG_MOTORES
  estado = "Apagados";
  Serial.println("Motores: " + estado);
  #endif
  
  mMotorA.frenar();
  mMotorB.frenar();
  mMotorC.frenar();
  mMotorD.frenar();
}

void Motores::parar(void)
{
  #ifdef DEBUG_MOTORES
  estado = "Parar";
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    mMotorA.parar();
    mMotorB.parar();
    mMotorC.parar();
    mMotorD.parar();
  }
}

void Motores::frenar(void)
{
  #ifdef DEBUG_MOTORES
  estado = "Frenar";
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    mMotorA.frenar();
    mMotorB.frenar();
    mMotorC.frenar();
    mMotorD.frenar();
  }
}

String Motores::getEstado(void)
{
	return estado;
}

//-------------------------------------------------------------------------------------------------
// Movimientos

// Rectilíneos
void Motores::desplazamientoAdelante(float porcentaje)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Recto Adelante";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    mMotorA.adelante(porcentaje);
    mMotorB.adelante(porcentaje);
    mMotorC.adelante(porcentaje);
    mMotorD.adelante(porcentaje);
  }
}

void Motores::desplazamientoAtras(float porcentaje)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Recto Atras";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    mMotorA.atras(porcentaje);
    mMotorB.atras(porcentaje);
    mMotorC.atras(porcentaje);
    mMotorD.atras(porcentaje);
  }
}

void Motores::desplazamientoIzquierda(float porcentaje)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Recto Izquierda";
  }
  Serial.println("Motores: " + estado);
  #endif
  if(encendido)
  {
    mMotorA.adelante(porcentaje);
    mMotorB.atras(porcentaje);
    mMotorC.atras(porcentaje);
    mMotorD.adelante(porcentaje);
  }
}

void Motores::desplazamientoDerecha(float porcentaje)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Recto Derecha";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    mMotorA.atras(porcentaje);
    mMotorB.adelante(porcentaje);
    mMotorC.adelante(porcentaje);
    mMotorD.atras(porcentaje);
  }
}

// Giros en el lugar
void Motores::girarCW(float porcentaje)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Giro CW";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    mMotorA.adelante(porcentaje);
    mMotorB.atras(porcentaje);
    mMotorC.adelante(porcentaje);
    mMotorD.atras(porcentaje);
  }
}

void Motores::girarCW(float porcentaje, unsigned int tiempo)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Giro CW";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    girarCW(porcentaje);
    delay(tiempo);
    frenar();
  }
}

void Motores::girarCCW(float porcentaje)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Giro CCW";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    mMotorA.atras(porcentaje);
    mMotorB.adelante(porcentaje);
    mMotorC.atras(porcentaje);
    mMotorD.adelante(porcentaje);
  }
}

void Motores::girarCCW(float porcentaje, unsigned int tiempo)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Giro CCW";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    girarCCW(porcentaje);
    delay(tiempo);
    frenar();
  }
}

void Motores::giro90CW(void)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Giro 90 CW";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    girarCW(MOTORES_VELOCIDAD_90);
    delay(MOTORES_TIEMPO_90);
    frenar();
  }
}

void Motores::giro90CCW(void)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Giro 90 CCW";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
	girarCCW(MOTORES_VELOCIDAD_90);
	delay(MOTORES_TIEMPO_90);
	frenar();
  }
}

void Motores::giro180(void)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Giro 180";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    if(random(1)) // Gira aleatoriamente CW o CCW
    {
      giro90CCW();
      giro90CCW();
    }
    else
    {
      giro90CW();
      giro90CW();
    }
  }
}

void Motores::giro360(void)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Giro 360";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    if(random(1)) // Gira aleatoriamente CW o CCW
    {
      giro90CCW();
      giro90CCW();
      giro90CCW();
      giro90CCW();
    }
    else
    {
      giro90CW();
      giro90CW();
      giro90CW();
      giro90CW();
    }
  }
}

void Motores::giro360(unsigned int veces)
{
  #ifdef DEBUG_MOTORES
  if(encendido)
  {
    estado = "Giro 360" + " x " + veces + " veces";
  }
  Serial.println("Motores: " + estado);
  #endif
  
  if(encendido)
  {
    for(uint8_t i=0; i<veces; i++)
    {
      giro360();
    }
  }
}
