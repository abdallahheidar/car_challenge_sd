/*
 * Us.c
 *
 *  Author: Abdallah Heidar
 */ 

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/


#include "Us.h"


/************************************************************************/
/*				   functions' prototypes	                            */
/************************************************************************/

/****************************************************************************************************
 * Function Name   : Us_Init.                                                                       *
 * Input Parameters : None.                                                                         *                                                                   *                                                                                                *
 * Output Parameters: None.                                                                         *
 * In_Out Parameters: None.                                                                         *
 * Return           : ERROR_STATUS.                                                                 *
 * Description      : This function initiate the UltraSonic by set the value of the Dio_Dirction of *
 *                    the pin trigger as an output then initiate the ICU to use it to calculate the *
 *                    On time of the ECHO signal.                                                   *
 *                                                                                                  *
 *                                                                                                  *
 ***************************************************************************************************/

ERROR_STATUS Us_Init(void)
{
	ERROR_STATUS status = E_OK;
	
	/* initialize pin3 as output */
	DIO_Cfg_s str_Dio = {
		GPIOB,
		PIN3,
		OUTPUT
	};
	status = 	DIO_init(&str_Dio);
	

	/* initialize icu on EXT INT2 and timer0 */
	Icu_cfg_s str_Icu = {
	ICU_CH2,
	ICU_TIMER_CH0
	};
	status = Icu_Init(&str_Icu);
	
	return status;
}





/**************************************************************************************************
 * Function Name    : Us_Trigger.                                                                 *
 * Input Parameters : None.                                                                       *                                                                              *                                                                                                *
 * Output Parameters: None.                                                                       *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS                                                                *
 * Description      : This function send the  pulse, to trigger pin of the UltraSonic to enhance  *
 *                    the  ECUO signal                                                            *
 *************************************************************************************************/


ERROR_STATUS Us_Trigger(void)
{
	ERROR_STATUS status = E_OK;
	/* Trigger pulse */
	status =  DIO_Write(GPIOB, PIN3, HIGH);
	softwareDelayMs(1);
	status =  DIO_Write(GPIOB, PIN3, LOW);
	return status;
}





/**************************************************************************************************
 * Function Name    : Us_GetDistance.                                                             *
 * Input Parameters : pointer to uint16 that will return the distance on it.                      *                                                                                              *                                                                                                *
 * Output Parameters: Distance.                                                                   *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS.                                                               *
 * Description      : This function get the time of high signal of ECUO pulse, then               *
 *                    use it to calculate the distance, then return the value in the              *
 *                    Distance parameter.                                                         *
 *************************************************************************************************/


ERROR_STATUS Us_GetDistance(uint8_t *Distance)
{
	ERROR_STATUS status = E_OK;
		uint8_t time = 0; 
	status =  Icu_ReadTime(ICU_TIMER_CH0, ICU_RISE_TO_FALL , &time);
		
		
		/*58 to map time to distance */
		*Distance = time / 58;
	//PORTD_DATA = *Distance;
	
	return status;
}
