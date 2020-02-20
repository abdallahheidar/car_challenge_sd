/*
 * SwICU.c
 *
 *  Author: Abdallah Heidar
 */ 

#include "ICU.h"
#include "Timer.h"
#include "DIO.h"
#include "registers.h"

/*-----------------[ Static Globals ]--------------*/

volatile static uint16_t g_TMR2OVF_C  = 0;
volatile static uint8_t  g_distance   = 0;
volatile static EN_SwICU_Edge_t  g_SwICU_Edge = 0;

/**************************************************************************
 * Function 	: Icu_Init                                                *
 * Input 		: Icu_cfg : pointer to structure of type Icu_cfg_s        *
 * Return 		: value of type ERROR_STATUS							  *
 * 				  which is one of the following values:					  *
 * 				  - E_OK  : initialized successfully					  *
 *				  - E_NOK : not initialized successfully				  *
 * Description  : Initializes the ICU by initializing the timer			  *
 * 				  and enabling the global interrupt						  *
 **************************************************************************/
ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg)
{
	ERROR_STATUS errorStatus = E_NOK;
	Timer_cfg_s ICU_TMR;
	DIO_Cfg_s ICU_Pin;
	g_SwICU_Edge = SwICU_EdgeRising;
	
	// Configure The ICU IO Pin
	ICU_Pin.GPIO = ICU_CH2_GPIO;
	ICU_Pin.pins = ICU_CH2_BIT;
	ICU_Pin.dir = INPUT;
	DIO_init(&ICU_Pin);
	
	// Configure The Timer Dedicated To swICU
	ICU_TMR.Timer_CH_NO = Icu_Cfg->ICU_Ch_Timer;
	ICU_TMR.Timer_Mode = TIMER_MODE;
	ICU_TMR.Timer_Prescaler = TIMER_PRESCALER_8;
	ICU_TMR.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
	
	// Set The Interrupt Trigger Edge For The ICU Input Signal
	switch(g_SwICU_Edge)
	{
		case SwICU_EdgeRising:
				SET_BIT(MCUCSR, 6);
				break;
		case SwICU_EdgeFalling:
				CLEAR_BIT(MCUCSR, 6);
				break;
		default:
		        break;
	}
	
	// Enable The External INT
	GICR |= 0x20;
	SREG |= (0x80);
	
	// Initialize & Start The ICU Timer Module
	Timer_Init(&ICU_TMR);
	Timer_Start(ICU_TMR.Timer_CH_NO, 255);
	errorStatus = E_OK;
	
	return errorStatus;
}
/***************************************************************************
 * Function		: Icu_ReadTime
 * Input		: 
 *				Icu_Channel --> ICU timer channel
 *									- ICU_TIMER_CH0
 *									- ICU_TIMER_CH1
 *									- ICU_TIMER_CH2
 *				Icu_EdgeToEdge -- > edges to calculate pusle time between:
 *									- ICU_RISE_TO_RISE
 *									- ICU_RISE_TO_FALL
 *									- ICU_FALE_TO_RISE					   *
 * Output 		: Icu_Time : pointer to uint32 variable to give the time   *
 * 				  from falling edge to rising edge						   *
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between 2 edges				       *
 ***************************************************************************/
ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time)
{
	ERROR_STATUS errorStatus = E_NOK;
	uint16_t ticks = 0;
	
	// Get The Total Timer Ticks
	Timer_GetValue(TIMER_CH2, &ticks);
	ticks += (g_TMR2OVF_C << 8);
	*Icu_Time = (ticks >> 1);
	Timer_Stop(TIMER_CH2);
	
	// Calculate & Update The Distance (To Be Used By The Ultrasonic Module)
	g_distance = *Icu_Time / 58.0;
	errorStatus = E_OK;
	
	return errorStatus;
}

void Us_Read(uint8_t* a_dist)
{
	*a_dist = g_distance;
}

/*****************************************
*				ISR Handlers			 *
******************************************/

ISR(TIMER2_COMP_vect){
	TCNT2 = 0x00;
	g_TMR2OVF_C++;
}

ISR(INT2_vect)
{
	if(g_SwICU_Edge == SwICU_EdgeRising)
	{
		MCUCSR ^= (1 << 6);
		g_SwICU_Edge = SwICU_EdgeFalling;
		g_TMR2OVF_C = 0;
		Timer_Start(TIMER_CH2, 255);
	}
	else if(g_SwICU_Edge == SwICU_EdgeFalling)
	{
		MCUCSR ^= (1 << 6);
		g_SwICU_Edge = SwICU_EdgeRising;
		Timer_Stop(TIMER_CH2);
	}
}
