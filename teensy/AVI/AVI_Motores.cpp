#include "AVI_Motores.h"


//=================================================================================================
// MOTOR

//-------------------------------------------------------------------------------------------------
Motor::Motor(uint8_t i_pin_1, uint8_t i_pin_2, uint8_t i_pin_PWM)
{
	pin_1 = i_pin_1;
	pin_2 = i_pin_2;
	pin_PWM = i_pin_PWM;

  pinMode(pin_1, OUTPUT);
  pinMode(pin_2, OUTPUT);
  pinMode(pin_PWM, OUTPUT);

  
	digitalWrite(pin_1, LOW);
	digitalWrite(pin_2, LOW);
	analogWrite(pin_PWM, 0);
}



//-------------------------------------------------------------------------------------------------
Motor::Motor(void)
{
}



//-------------------------------------------------------------------------------------------------
void Motor::parar(void)
{
	analogWrite(pin_PWM, 0);
}


//-------------------------------------------------------------------------------------------------
void Motor::frenar(void)
{
	digitalWrite(pin_1, LOW);
	digitalWrite(pin_2, LOW);
	analogWrite(pin_PWM, 0);
}


//-------------------------------------------------------------------------------------------------
void Motor::adelante(float porcentaje)
{
	digitalWrite(pin_1, HIGH);
	digitalWrite(pin_2, LOW);
	analogWrite(pin_PWM, (int)porcentaje*255/100);
}


//-------------------------------------------------------------------------------------------------
void Motor::atras(float porcentaje)
{
	digitalWrite(pin_1, LOW);
	digitalWrite(pin_2, HIGH);
	analogWrite(pin_PWM, (int)porcentaje*255/100);
}



//=================================================================================================
// MOTORES


//-------------------------------------------------------------------------------------------------
Motores::Motores()
{
}


//-------------------------------------------------------------------------------------------------
Motores::Motores(Motor& i_motor_A, Motor& i_motor_B, Motor& i_motor_C, Motor& i_motor_D)
{
  //Serial.println("CREANDO");
  //delay(1000);
	encendido = false;
	
#ifdef DEBUG_MOTORES
	estado = "apagados";
	// Serial.println("Motores: " + estado);  // Esto no puede estar porque si construimos global todavía no hay Serial y se cuelga.
#endif
	
	motor_A = i_motor_A;
	motor_B = i_motor_B;
	motor_C = i_motor_C;
	motor_D = i_motor_D;
	
}


//-------------------------------------------------------------------------------------------------
// ESTADO

void Motores::encender(void)
{
	encendido = true;
#ifdef DEBUG_MOTORES
	estado = "encendidos";
	Serial.println("Motores: " + estado);
#endif
}


//-------------------------------------------------------------------------------------------------
void Motores::apagar(void)
{
	encendido = false;
#ifdef DEBUG_MOTORES
	estado = "apagados";
	Serial.println("Motores: " + estado);
#endif
	
	motor_A.frenar();
	motor_B.frenar();
	motor_C.frenar();
	motor_D.frenar();
}


//-------------------------------------------------------------------------------------------------
String Motores::getEstado(void)
{
	return estado;
}


//-------------------------------------------------------------------------------------------------
// Rectos

void Motores::desplazamientoAdelante(float porcentaje)
{
#ifdef DEBUG_MOTORES
	estado = "desplazando adelante";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		motor_A.adelante(porcentaje);
		motor_B.adelante(porcentaje);
		motor_C.adelante(porcentaje);
		motor_D.adelante(porcentaje);
	}
}


//-------------------------------------------------------------------------------------------------
void Motores::desplazamientoAtras(float porcentaje)
{
#ifdef DEBUG_MOTORES
	estado = "desplazando atras";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		motor_A.atras(porcentaje);
		motor_B.atras(porcentaje);
		motor_C.atras(porcentaje);
		motor_D.atras(porcentaje);
	}	
}


//-------------------------------------------------------------------------------------------------
void Motores::desplazamientoIzquierda(float porcentaje)
{
#ifdef DEBUG_MOTORES
	estado = "desplazando izquierda";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		motor_A.adelante(porcentaje);
		motor_B.atras(porcentaje);
		motor_C.atras(porcentaje);
		motor_D.adelante(porcentaje);
	}
}


//-------------------------------------------------------------------------------------------------
void Motores::desplazamientoDerecha(float porcentaje)
{
#ifdef DEBUG_MOTORES
	estado = "desplazando derecha";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		motor_A.atras(porcentaje);
		motor_B.adelante(porcentaje);
		motor_C.adelante(porcentaje);
		motor_D.atras(porcentaje);
	}
}



//-------------------------------------------------------------------------------------------------
// En el lugar

void Motores::girarCW(float porcentaje)
{
#ifdef DEBUG_MOTORES
	estado = "girando cw";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		motor_A.adelante(porcentaje);
		motor_B.atras(porcentaje);
		motor_C.adelante(porcentaje);
		motor_D.atras(porcentaje);
	}
}


//-------------------------------------------------------------------------------------------------
void Motores::girarCW(float porcentaje, unsigned int tiempo)
{
#ifdef DEBUG_MOTORES
	estado = "girando cw";
	Serial.println("Motores: " + estado);
#endif
	
	//static unsigned long t, t_antes;
	
	if( encendido )
	{
		girarCW(porcentaje);
		delay(tiempo);
		frenar();
	}
}


//-------------------------------------------------------------------------------------------------
void Motores::girarCCW(float porcentaje)
{
#ifdef DEBUG_MOTORES
	estado = "girando ccw";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		motor_A.atras(porcentaje);
		motor_B.adelante(porcentaje);
		motor_C.atras(porcentaje);
		motor_D.adelante(porcentaje);
	}
}


//-------------------------------------------------------------------------------------------------
void Motores::girarCCW(float porcentaje, unsigned int tiempo)
{
#ifdef DEBUG_MOTORES
	estado = "girando ccw";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		girarCCW(porcentaje);
		delay(tiempo);
		frenar();
	}
}


//-------------------------------------------------------------------------------------------------
void Motores::giro90CW(void)
{
#ifdef DEBUG_MOTORES
	estado = "girando 90 cw";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		girarCW(MOTORES_VELOCIDAD_90);
		delay(MOTORES_TIEMPO_90);
		frenar();
	}
}


//-------------------------------------------------------------------------------------------------
void Motores::giro90CCW(void)
{
#ifdef DEBUG_MOTORES
	estado = "girando 90 ccw";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		girarCCW(MOTORES_VELOCIDAD_90);
		delay(MOTORES_TIEMPO_90);
		frenar();
	}
}


//-------------------------------------------------------------------------------------------------
void Motores::giro180(void)
{
#ifdef DEBUG_MOTORES
	estado = "girando 180";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		if(random(1))	// Aleatorio CCW/CW
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


//-------------------------------------------------------------------------------------------------
void Motores::giro360(void)
{
#ifdef DEBUG_MOTORES
	estado = "girando 360";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		if(random(1))	// Aleatorio CCW/CW
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


//-------------------------------------------------------------------------------------------------
void Motores::giro360(unsigned int veces)
{
#ifdef DEBUG_MOTORES
	estado = "girando 360 - " + String(veces) + " veces";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		for( unsigned int i = 0 ; i < veces ; i++ )
		{
			giro360();
		}
	}
}



//-------------------------------------------------------------------------------------------------

// Curva


//-------------------------------------------------------------------------------------------------
// Otros

void Motores::parar(void)
{
#ifdef DEBUG_MOTORES
	estado = "Parar";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		motor_A.parar();
		motor_B.parar();
		motor_C.parar();
		motor_D.parar();
	}
}


//-------------------------------------------------------------------------------------------------
void Motores::frenar(void)
{
#ifdef DEBUG_MOTORES
	estado = "Frenar";
	Serial.println("Motores: " + estado);
#endif
	
	if( encendido )
	{
		motor_A.frenar();
		motor_B.frenar();
		motor_C.frenar();
		motor_D.frenar();
	}
}
