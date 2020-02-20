/*
 * TimerDelay.c
 *
 *  Author: Abdallah Heidar
 */ 

#include "TimerDelay.h"

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to perform the delay.
 *  u16_Delay_Ms: The delay time required (in milli-seconds)
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to HALT the CPU for a specific time delay (in ms).
 * 							
 */


ERROR_STATUS Timer_Delay_Ms(uint8_t Timer_CH_NO, uint16_t u16_Delay_Ms)
{
	ERROR_STATUS errorStatus = E_NOK;
	bool Timer_CMP_Flag = FALSE;
	Timer_cfg_s Delay_Timer;
	Delay_Timer.Timer_Mode = TIMER_MODE;
	Delay_Timer.Timer_Polling_Or_Interrupt = TIMER_POLLING_MODE;
	Delay_Timer.Timer_Prescaler = TIMER_PRESCALER_64;
	switch(Timer_CH_NO)
	{
		case TIMER_CH0:
			Delay_Timer.Timer_CH_NO = TIMER_CH0;
			break;
		case TIMER_CH1:
			Delay_Timer.Timer_CH_NO = TIMER_CH1;
			break;
		case TIMER_CH2:
			Delay_Timer.Timer_CH_NO = TIMER_CH2;
			break;
		default:
			break;
	}
	Timer_Init(&Delay_Timer);
	Timer_Start(Delay_Timer.Timer_CH_NO, 250);
	while(u16_Delay_Ms > 0)
	{
		// Poll For TMR0 Compare Match Flag Bit
		while(!Timer_CMP_Flag)
		{
			Timer_GetStatus(Delay_Timer.Timer_CH_NO, &Timer_CMP_Flag);
		}
		// Set The Flag Bit To Clear It
		switch(Delay_Timer.Timer_CH_NO)
		{
			case TIMER_CH0:
				TIFR |= Timer0_TIFR_OCBit;
				break;
			case TIMER_CH1:
				TIFR |= Timer1_TIFR_OCBit;
				break;
			case TIMER_CH2:
				TIFR |= Timer2_TIFR_OCBit;
				break;
			default:
				break;
		}
		Timer_CMP_Flag = FALSE;
		u16_Delay_Ms--;
	}
	Timer_Stop(Delay_Timer.Timer_CH_NO);
	errorStatus = E_OK;
	
	return errorStatus;
}

/**
 * Input: 
 * 	Timer_CH_NO: The channel number of the timer needed to perform the delay.
 *  u16_Delay_Us: The delay time required (in micro-seconds)
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function is used to HALT the CPU for a specific time delay (in us).
 * 							
 */

ERROR_STATUS Timer_Delay_Us(uint8_t Timer_CH_NO, uint16_t u16_Delay_Us)
{
	ERROR_STATUS errorStatus = E_NOK;
	uint16_t u16_Delay_Usec = u16_Delay_Us >> 2;
	bool Timer_CMP_Flag = FALSE;
	Timer_cfg_s Delay_Timer;
	Delay_Timer.Timer_Mode = TIMER_MODE;
	Delay_Timer.Timer_Polling_Or_Interrupt = TIMER_POLLING_MODE;
	Delay_Timer.Timer_Prescaler = TIMER_PRESCALER_8;
	switch(Timer_CH_NO)
	{
		case TIMER_CH0:
			Delay_Timer.Timer_CH_NO = TIMER_CH0;
			break;
		case TIMER_CH1:
			Delay_Timer.Timer_CH_NO = TIMER_CH1;
			break;
		case TIMER_CH2:
			Delay_Timer.Timer_CH_NO = TIMER_CH2;
			break;
		default:
			break;
	}
	Timer_Init(&Delay_Timer);
	Timer_Start(Delay_Timer.Timer_CH_NO, 3);
	while(u16_Delay_Usec > 0)
	{
		// Poll For TMR0 Compare Match Flag Bit
		while(!Timer_CMP_Flag)
		{
			Timer_GetStatus(Delay_Timer.Timer_CH_NO, &Timer_CMP_Flag);
		}
		// Set The Flag Bit To Clear It
		switch(Delay_Timer.Timer_CH_NO)
		{
			case TIMER_CH0:
				TIFR |= Timer0_TIFR_OCBit;
				break;
			case TIMER_CH1:
				TIFR |= Timer1_TIFR_OCBit;
				break;
			case TIMER_CH2:
				TIFR |= Timer2_TIFR_OCBit;
				break;
			default:
				break;
		}
		Timer_CMP_Flag = FALSE;
		u16_Delay_Usec--;
	}
	Timer_Stop(Delay_Timer.Timer_CH_NO);
	errorStatus = E_OK;
	
	return errorStatus;
}