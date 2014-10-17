/* ------------------------------------------------------------------ *
 *                                                                   
 *  Autor: sagarcia
 *  
 *  Fecha: 25/11/2008
 *
 *  Source: actuador.c                                                         
 *
 *  Header: actuador.h
 *
 *  Proyecto: sistema_guiado_2
 * 
 *  Descripcion:
 *
 *    Paquete que gestiona la comunicacion con la caja que controla la 
 *    direccion del tractor. 
 *  
 *  Versiones:
 *
 *    1.0, 25Nov2008, Paquete creado, sagarcia
 *
 */
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ *
 * -------------------------- INCLUDE FILES ------------------------- *
 * ------------------------------------------------------------------ */
#include "stdafx.h"
#include "actuador.h"
#include "rtos_serie.h"

/* #pragma comment(lib, "../lib/rtos_serie.lib")
#pragma comment(lib, "../lib/cvisupp.lib")
#pragma comment(lib, "../lib/cvirt.lib")*/




/* ------------------------------------------------------------------ *
 * ---------------------------- CONSTANTS --------------------------- *
 * ------------------------------------------------------------------ */
#define CT_ACT_Timeout    5

#define CT_ACT_BaudRate   9600
#define CT_ACT_DataBits    8
#define CT_ACT_StopBits    1
#define CT_ACT_Paridad     0
#define CT_ACT_SndBuffer   256
#define CT_ACT_RcvBuffer   256

#define CT_ACT_Length_FFC  15
#define CT_ACT_Length_FFD  15
#define CT_ACT_Length_FFA  12
#define CT_ACT_Length_FFB  12



/* ------------------------------------------------------------------ *
 * ------------------------------ TYPES ----------------------------- *
 * ------------------------------------------------------------------ */

	
	
	

/* ------------------------------------------------------------------ *
 * ------------------------- GLOBAL VARIABLES ----------------------- *
 * ------------------------------------------------------------------ */
static XC_ACT_Info V_ACT_Info;


/* ------------------------------------------------------------------ *
 * ------------------------ INTERNAL FUNCTIONS ---------------------- *
 * ------------------------------------------------------------------ */


/* ------------------------------------------------------------------ *
 * ---------------------------- FUNCTIONS --------------------------- *
 * ------------------------------------------------------------------ */




/* ------------------------------------------------------------------ *
 *
 * Function: ACTUADOR__P_ACT_TO_BAMS
 * 
 * Description:
 *
 *   Funcion que convierte un angulo de direccion del actuador en BAMS.
 * 
 * Inputs:
 * 
 * Outputs:
 *
 */
DT_UWord ACTUADOR__F_ACT_TO_BAMS(DT_SLong Pos){
	DT_LReal pendiente=0.0;
	DT_UWord pos_bams=0;
	
	if((Pos > V_ACT_Info.Cfg.P_Ctrl) && (Pos < V_ACT_Info.Cfg.P_Max)){
		pos_bams = static_cast<DT_UWord>(V_ACT_Info.Valores.Pend_Pos * (Pos - V_ACT_Info.Cfg.P_Ctrl));
	}
	else{
		if(Pos < V_ACT_Info.Cfg.P_Ctrl && Pos > V_ACT_Info.Cfg.P_Min){
			pos_bams = static_cast<DT_UWord>(V_ACT_Info.Valores.Pend_Neg * (Pos - V_ACT_Info.Cfg.P_Ctrl ));
		}
		else pos_bams = 0;
	}
	return pos_bams;
}



/* ------------------------------------------------------------------ *
 *
 * Function: ACTUADOR__P_BAMS_TO_ACT
 * 
 * Description:
 *
 *   Funcion que convierte un angulo en BAMS a un angulo de direccion 
 *   del actuador.
 * 
 * Inputs:
 * 
 * Outputs:
 *
 */
DT_UWord ACTUADOR__F_BAMS_TO_ACT(DT_UWord Pos_BAMS){
	DT_LReal pendiente=0.0;
	DT_SLong pos=0;
	
	if ((DT_SWord)Pos_BAMS > (DT_SWord)V_ACT_Info.Cfg.BAMS_Max) Pos_BAMS = V_ACT_Info.Cfg.BAMS_Max;
	if ((DT_SWord)Pos_BAMS < (DT_SWord)V_ACT_Info.Cfg.BAMS_Min) Pos_BAMS = V_ACT_Info.Cfg.BAMS_Min;
	if((DT_SWord)Pos_BAMS >= 0){
		pos = static_cast<DT_UWord>((DT_SWord)Pos_BAMS / V_ACT_Info.Valores.Pend_Pos + V_ACT_Info.Cfg.P_Ctrl);
	}
	else{
		if((DT_SWord)Pos_BAMS < 0){
		  pos = static_cast<DT_UWord>((DT_SWord)Pos_BAMS / V_ACT_Info.Valores.Pend_Neg  + V_ACT_Info.Cfg.P_Ctrl);
		}
	}
	return static_cast<DT_UWord>(pos);
}





/* ------------------------------------------------------------------ *
 *
 * Function: ACTUADOR__P_Set_Direccion
 * 
 * Description:
 *
 *   Funcion que introduce un angulo de direccion en el actuador
 * 
 * Inputs:
 * 
 * Outputs:
 *
 */
DT_ACT_Error ACTUADOR__P_Set_Direccion(DT_UWord Pos_BAMS){
	char buffer[128];
	DT_SWord Pos;
	
	if(V_ACT_Info.Valores.Config == FALSE) return ACT_Error_NO_CFG;
	
	Pos = ACTUADOR__F_BAMS_TO_ACT(Pos_BAMS);
	sprintf_s(buffer,"FFB%04d00000",Pos);
	RTOS_SERIE__F_Escribir(V_ACT_Info.Cfg.Puerto, buffer, CT_ACT_Length_FFB);  

	V_ACT_Info.Valores.Cons_ADC = Pos;
	V_ACT_Info.Valores.Cons_BAMS = Pos_BAMS;
	
	return ACT_Error_OK;
}






/* ------------------------------------------------------------------ *
 *
 * Function: ACTUADOR__P_Inicia
 * 
 * Description:
 *
 *   Funcion que inicializa el actuador
 * 
 * Inputs:
 * 
 * Outputs:
 *
 */
DT_ACT_Error ACTUADOR__P_Inicia(XC_ACT_Cfg Cfg_Act){
	int er = 0;
	// DT_SLong aux;
	char buffer[128];
	DT_SLong inv_rampa;
	
	V_ACT_Info.Cfg = Cfg_Act;
	V_ACT_Info.Valores.Config = FALSE;
	V_ACT_Info.Valores.Cons_ADC = 0;
	V_ACT_Info.Valores.Cons_BAMS = 0;
	V_ACT_Info.Valores.Pos_ADC = 0;
	V_ACT_Info.Valores.Pos_BAMS = 0;
	
	er = RTOS_SERIE__F_Abrir(V_ACT_Info.Cfg.Puerto, CT_ACT_BaudRate);
	if(er < 0) return ACT_Error_O_PORT;
	
	if(V_ACT_Info.Cfg.Invertir == FALSE){
	  V_ACT_Info.Valores.Pend_Pos = ((DT_SWord)V_ACT_Info.Cfg.BAMS_Max) / (DT_LReal)(V_ACT_Info.Cfg.P_Max - V_ACT_Info.Cfg.P_Ctrl);
	  V_ACT_Info.Valores.Pend_Neg = ((DT_SWord)V_ACT_Info.Cfg.BAMS_Min) / (DT_LReal)(V_ACT_Info.Cfg.P_Min - V_ACT_Info.Cfg.P_Ctrl);
	}
	else{
	  V_ACT_Info.Valores.Pend_Pos = ((DT_SWord)V_ACT_Info.Cfg.BAMS_Min) / (DT_LReal)(V_ACT_Info.Cfg.P_Max - V_ACT_Info.Cfg.P_Ctrl);
		V_ACT_Info.Valores.Pend_Neg = ((DT_SWord)V_ACT_Info.Cfg.BAMS_Max) / (DT_LReal)(V_ACT_Info.Cfg.P_Min - V_ACT_Info.Cfg.P_Ctrl);
	}
	
	if(V_ACT_Info.Valores.Calibracion == FALSE){
	
		sprintf_s(buffer,"FFE%03d%03d%03d",V_ACT_Info.Cfg.P_Min, V_ACT_Info.Cfg.P_Max, V_ACT_Info.Cfg.P_Ctrl);
	  RTOS_SERIE__F_Escribir(V_ACT_Info.Cfg.Puerto, buffer, strlen(buffer));  
		//Delay(0.2);

	  sprintf_s(buffer,"FFA%03d%03d%03d",V_ACT_Info.Cfg.K_Min, V_ACT_Info.Cfg.K_Med, V_ACT_Info.Cfg.K_Max);
	  RTOS_SERIE__F_Escribir(V_ACT_Info.Cfg.Puerto, buffer, strlen(buffer));  
		//Delay(0.2);
	
		sprintf_s(buffer,"FFG%03d%03d000",V_ACT_Info.Cfg.S_Max, V_ACT_Info.Cfg.S_Min);
	  RTOS_SERIE__F_Escribir(V_ACT_Info.Cfg.Puerto, buffer, strlen(buffer));  
		//Delay(0.2);
	
	  inv_rampa = 10000 / V_ACT_Info.Cfg.Rampa;
	  inv_rampa = inv_rampa % 1000;
	  sprintf_s(buffer,"FFK%03d%03d000",V_ACT_Info.Cfg.Rampa, inv_rampa);
	  RTOS_SERIE__F_Escribir(V_ACT_Info.Cfg.Puerto, buffer, strlen(buffer));  
		//Delay(0.2);
	
		sprintf_s(buffer,"FFB%04d00000", V_ACT_Info.Cfg.P_Ctrl);
		
							/* Activacion del muestreo. Para desactivar, comentar estas dos lineas*/ 
					//sprintf(buffer, "FFF000000000");
	        //RTOS_SERIE__F_Escribir(V_ACT_Info.Cfg.Puerto, buffer, strlen(buffer));  

	}
		
	V_ACT_Info.Valores.Config = TRUE;

	
	return ACT_Error_OK;
}





/* ------------------------------------------------------------------ *
 *
 * Function: ACTUADOR__P_Fin
 * 
 * Description:
 *
 *   Funcion que inicializa el actuador
 * 
 * Inputs:
 * 
 * Outputs:
 *
 */
DT_ACT_Error ACTUADOR__P_Fin(void){
	char buffer[128];

	sprintf_s(buffer,"FFB%04d00000",V_ACT_Info.Cfg.P_Ctrl);
	if(V_ACT_Info.Cfg.Puerto != 0)
	  RTOS_SERIE__F_Escribir(V_ACT_Info.Cfg.Puerto, buffer,CT_ACT_Length_FFB); 
	//Delay(0.2);
	V_ACT_Info.Valores.Config = FALSE;
	if(V_ACT_Info.Cfg.Puerto != 0)
		RTOS_SERIE__F_Close(V_ACT_Info.Cfg.Puerto);
	return static_cast<DT_ACT_Error>(0);
}






