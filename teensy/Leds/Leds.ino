#include "AVI_Pines.h"
#include "AVI_Config.h"
#include "AVI_LEDs.h"

LEDs leds;

void setup()
{
  pinMode(13, OUTPUT);
	Serial.begin(9600);
	delay(500);
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(13, LOW);
	delay(500);

  leds.mostrar(IMAGENES::CIRCULO , CRGB::Blue );
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
 // LEDs leds;
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  
	leds.mostrar(IMAGENES::CIRCULO , long(0x2084B7));
	delay(1000);
	leds.apagar();
	delay(1000);

   leds.mostrar(IMAGENES::O_IMG , 0x00FF00 ); // rojo
  delay(1000);
  leds.apagar();
  delay(1000);

     leds.mostrar(IMAGENES::O_IMG , 0x66FF00 ); // naranja
  delay(1000);
  leds.apagar();
  delay(1000);

       leds.mostrar(IMAGENES::O_IMG , 0xFFFF00 ); //amarillo
  delay(1000);
  leds.apagar();
  delay(1000);
  leds.brillo = (leds.brillo + 0.1);
  if(leds.brillo > 1)
    leds.brillo = 0.1;
}

