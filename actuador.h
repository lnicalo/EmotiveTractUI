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
#ifndef _ACTUADOR_H
#define _ACTUADOR_H
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ *
 * -------------------------- INCLUDE FILES ------------------------- *
 * ------------------------------------------------------------------ */
#include "t_tipos_basicos.h"


/* ------------------------------------------------------------------ *
 * ---------------------------- CONSTANTS --------------------------- *
 * ------------------------------------------------------------------ */
#define CT_ACTUADOR_GIRO_MAX_DIR 4500 /* 30º */


/* ------------------------------------------------------------------ *
 * ------------------------------ TYPES ----------------------------- *
 * ------------------------------------------------------------------ */
typedef enum{
	ACT_Error_OK,
	ACT_Error_ERROR = -1,
	ACT_Error_NO_CFG = -100,
	ACT_Error_O_PORT
} DT_ACT_Error;

typedef struct{
	DT_SLong Puerto;
	DT_ULong Invertir;
	DT_UWord BAMS_Max;
	DT_UWord BAMS_Min;
	DT_SLong P_Max;
	DT_SLong P_Ctrl;
	DT_SLong P_Min;
	DT_SLong K_Max;
	DT_SLong K_Med;
	DT_SLong K_Min;
	DT_SLong S_Max;
	DT_SLong S_Min;
	DT_SLong Rampa;
} XC_ACT_Cfg;

typedef struct {
	DT_ULong Config;
	DT_ULong Calibracion;
	DT_LReal Pend_Pos;
	DT_LReal Pend_Neg;
	DT_UWord Cons_BAMS;
	DT_SLong Cons_ADC;
	DT_UWord Pos_BAMS;
	DT_SLong Pos_ADC;
	DT_ULong Timeout;
} XC_ACT_Valores;

typedef struct{
	XC_ACT_Cfg      Cfg;
	XC_ACT_Valores  Valores;
} XC_ACT_Info;



/* ------------------------------------------------------------------ *
 * ------------------------- GLOBAL VARIABLES ----------------------- *
 * ------------------------------------------------------------------ */



/* ------------------------------------------------------------------ *
 * ------------------------ INTERNAL FUNCTIONS ---------------------- *
 * ------------------------------------------------------------------ */


/* ------------------------------------------------------------------ *
 * ---------------------------- FUNCTIONS --------------------------- *
 * ------------------------------------------------------------------ */




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
DT_ACT_Error ACTUADOR__P_Set_Direccion(DT_UWord Pos_BAMS);






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
DT_ACT_Error ACTUADOR__P_Inicia(XC_ACT_Cfg Cfg_Act);



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
DT_ACT_Error ACTUADOR__P_Fin(void);









/* ------------------------------------------------------------------ */
#endif
