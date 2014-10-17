#ifndef __RTOS_SERIE_H__
#define __RTOS_SERIE_H__




extern "C" {
	int RTOS_SERIE__F_Abrir(int puerto, int baudrate);
	int RTOS_SERIE__F_Leer(int puerto, char* buffer, int bytes);
	int RTOS_SERIE__F_Escribir(int puerto, char* buffer, int bytes);
	int RTOS_SERIE__F_Close(int puerto);
}
#endif
