#include "AVI_Motores.h"
#include "AVI_Pines.h"
#include "Arduino.h"

	  //pinMode(13, OUTPUT);
//  Serial.begin(9600);

//Serial.begin(9600);

//Motor motor_A;
//Motor motor_B;
//Motor motor_C;
//Motor motor_D;
//Motores motores;

  Motor motor_A(PIN_MOTOR_A_1, PIN_MOTOR_A_2, PIN_PWM_A);
  Motor motor_B(PIN_MOTOR_B_1, PIN_MOTOR_B_2, PIN_PWM_B);
  Motor motor_C(PIN_MOTOR_C_1, PIN_MOTOR_C_2, PIN_PWM_C);
  Motor motor_D(PIN_MOTOR_D_1, PIN_MOTOR_D_2, PIN_PWM_D);
  
  Motores motores ( motor_A , motor_B , motor_C , motor_D );

void setup()
{
  pinMode(13, OUTPUT);
	//Serial.begin(9600);
	delay(500);
//   motor_A = Motor(PIN_MOTOR_A_1, PIN_MOTOR_A_2, PIN_PWM_A);
//  motor_B = Motor(PIN_MOTOR_B_1, PIN_MOTOR_B_2, PIN_PWM_B);
//  motor_C = Motor(PIN_MOTOR_C_1, PIN_MOTOR_C_2, PIN_PWM_C);
//  motor_D = Motor(PIN_MOTOR_D_1, PIN_MOTOR_D_2, PIN_PWM_D);
//  
//  Motores motores ( motor_A , motor_B , motor_C , motor_D );
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
 
}

void loop()
{

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
