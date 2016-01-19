#ifndef AVI_General
#define AVI_General

// Includes


// Defines



// ------------------------

// Main 
void main{
	int modo = 1;

// Chequeos de hardware

// Detección de modo
//   Leer entradas

	switch (modo)
	{
		case 1:
			while(1)
			AVI_Modo1();
			break;
		case 2:
			while(1)
			AVI_Modo2();
			break;
		case 3:
			while(1)
			AVI_Modo3();
			break;
		case 4:
			while(1)
			AVI_Modo4();
			break;
		case 5:
			while(1)
			AVI_modo5();
			break;
			
	}



} // Main

#endif