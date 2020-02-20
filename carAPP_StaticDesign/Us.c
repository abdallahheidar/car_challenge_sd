/*
 * Us.c
 *
 *  Author: Abdallah Heidar
 */ 
#include "Us.h"

/*--------------[ Static Globals ]-------------*/

static DIO_Cfg_s Trig_Pin, Echo_Pin;


/*--------------[ Functions' Definitions ]-------------*/

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
	ERROR_STATUS errorStatus = E_NOK;
	Icu_cfg_s Us_ICU;
	
	Us_ICU.ICU_Ch_No = ICU_CH2;
	Us_ICU.ICU_Ch_Timer = TIMER_CH2;
	
	Trig_Pin.GPIO = GPIOB;
	Trig_Pin.pins = BIT1;
	Trig_Pin.dir = OUTPUT;
	
	Echo_Pin.GPIO = GPIOB;
	Echo_Pin.pins = BIT2;
	Echo_Pin.dir = INPUT;
	
	DIO_init(&Trig_Pin);
	DIO_init(&Echo_Pin);
	Icu_Init(&Us_ICU);
	
	errorStatus = E_OK;
	return errorStatus;
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
	ERROR_STATUS errorStatus = E_NOK;
	DIO_Write(Trig_Pin.GPIO, Trig_Pin.pins, HIGH);
	Timer_Delay_Us(TIMER_CH0, 20);
	DIO_Write(Trig_Pin.GPIO, Trig_Pin.pins, LOW);
	errorStatus = E_OK;
	return errorStatus;
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

ERROR_STATUS Us_GetDistance(uint8_t* Distance)
{
	ERROR_STATUS errorStatus = E_NOK;
	uint32_t time = 0;
 	Icu_ReadTime(ICU_CH2, ICU_FALE_TO_RISE, &time);
	Us_Read(Distance);
	errorStatus = E_OK;
	return errorStatus;
}