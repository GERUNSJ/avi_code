//=================================================================================================
// AVI_Motores.h
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
// - Motor: Comanda un sólo motor.
// - Motores: Contiene 4 Motor y métodos para moverlos en conjunto.
//
//=================================================================================================

#ifndef AVI_MOTORES_H
#define AVI_MOTORES_H

#include "Arduino.h"
#include "AVI_Config.h"

//#define DEBUG_MOTORES 0

// Clase Motor (Individual)
class Motor 
{
  public:
    // Constructores
    Motor();
    Motor(uint8_t i_pin_1, uint8_t i_pin_2, uint8_t i_pin_PWM);
	// Metodos
	void parar(void); // PWM en 0
	void frenar(void); // PWM en 0 y los dos pines en LOW
	void adelante(float porcentaje); // Tomando el AVI como referencia
	void atras(float porcentaje);
  private:
    // Parametros
	uint8_t mPin1;
	uint8_t mPin2;
	uint8_t mPinPWM;
};

// Clase Motores (Grupal de 4)
class Motores
{
  public:
	// Constructores
	Motores();
	Motores(Motor& i_motor_A, Motor& i_motor_B, Motor& i_motor_C, Motor& i_motor_D);
	// Metodos
	void encender(void);
	void apagar(void);
	void parar(void);
	void frenar(void);
	String getEstado(void);
	// Movimientos
	// Rectilíneos
	void desplazamientoAdelante(float porcentaje);
	void desplazamientoAtras(float porcentaje);
	void desplazamientoIzquierda(float porcentaje);
	void desplazamientoDerecha(float porcentaje);
	// Giros en el lugar
	void girarCW(float porcentaje);
	void girarCW(float porcentaje, unsigned int tiempo); // Tiempo en ms
	void girarCCW(float porcentaje);
	void girarCCW(float porcentaje, unsigned int tiempo);
	void giro90CW(void);
	void giro90CCW(void);
	void giro180(void);
	void giro360(void);
	void giro360(unsigned int veces);
	// Curvilíneos
  private:
	bool encendido = false;	// Flag de encendido. Si es false, nada se mueve, solo debug.
	String estado = "default";
	Motor mMotorA;
	Motor mMotorB;
	Motor mMotorC;
	Motor mMotorD;
};

#endif // AVI_MOTORES_H
