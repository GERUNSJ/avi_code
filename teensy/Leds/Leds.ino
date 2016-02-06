#include "AVI_Pines.h"
#include "AVI_Config.h"
#include "AVI_LEDs.h"

LEDs leds;

void setup()
{
	Serial.begin(9600);
	delay(500);
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
}


void loop()
{
	leds.mostrar(IMAGENES::CIRCULO , HUE_RED );
	delay(1000);
	leds.apagar();
	delay(1000);
}

