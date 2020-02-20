/*
 * TimerDelay.h
 *
 *  Author: Abdallah Heidar
 */ 


#ifndef TIMERDELAY_H_
#define TIMERDELAY_H_

#include "Timer.h"

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
extern ERROR_STATUS Timer_Delay_Ms(uint8_t Timer_CH_NO, uint16_t Delay_Ms);
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
extern ERROR_STATUS Timer_Delay_Us(uint8_t Timer_CH_NO, uint16_t Delay_Us);


#endif /* TIMERDELAY_H_ */