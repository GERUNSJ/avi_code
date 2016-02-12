#ifndef AVI_MOTORES_H
#define AVI_MOTORES_H

#include "Arduino.h"
#include "AVI_Config.h"

 #define DEBUG_MOTORES


//=================================================================================================



class Motor 
{
public:
	Motor(uint8_t i_pin_1, uint8_t i_pin_2, uint8_t i_pin_PWM);
	Motor();
	//~Motor();
	
	void parar(void);	// PWM en 0
	void frenar(void);	// PWM en 0 y los dos pines en LOW
	void adelante(float porcentaje);	// Girar hacia adelante (tomando el AVI como referencia)
	void atras(float porcentaje);		// Girar hacia atras
	
private:
	uint8_t pin_1;
	uint8_t pin_2;
	uint8_t pin_PWM;
};



//=================================================================================================



class Motores
{
public:
	//bool ocupado = false;	// flag para cuando está girando por tiempo.
	
	Motores(Motor& i_motor_A, Motor& i_motor_B, Motor& i_motor_C, Motor& i_motor_D);
	Motores();
	//~Motores();
	
	// Estado
	void encender(void);
	void apagar(void);
	String getEstado(void);
	
	// Rectos
	void desplazamientoAdelante(float porcentaje);
	void desplazamientoAtras(float porcentaje);
	void desplazamientoIzquierda(float porcentaje);
	void desplazamientoDerecha(float porcentaje);
	
	// En el lugar
	void girarCW(float porcentaje);
	void girarCW(float porcentaje, unsigned int tiempo);	// Tiempo en ms
	void girarCCW(float porcentaje);
	void girarCCW(float porcentaje, unsigned int tiempo);
	void giro90CW(void);
	void giro90CCW(void);
	void giro180(void);
	void giro360(void);
	void giro360(unsigned int veces);
	
	// Curva
	
	// Otros
	void parar(void);
	void frenar(void);
	//void setVelocidad_default(float porcentaje);
private:
	//unsigned int velocidad_default = 0;
	bool encendido = false;	// Flag de encendido. Si es false, nada se mueve, solo debug.
	String estado;
	Motor motor_A;
	Motor motor_B;
	Motor motor_C;
	Motor motor_D;
};


//-------------


#endif // AVI_MOTORES_H
