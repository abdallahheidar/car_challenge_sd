/*
 * car_sm.c
 *

 *  Author: Abdallah Heidar
 */ 
#include "car_sm.h"
#include "Steering.h"
#include "Us.h"

static uint8_t Sys_State = Stop;
static uint8_t g_u8_Dist = 0, g_u8_Speed = 25, g_u8_Margin = 3;

ERROR_STATUS Car_SM_Init(void)
{
	ERROR_STATUS errorStatus = E_NOK;
	Steering_Init();
	Us_Init();
	errorStatus = E_OK;
	return errorStatus;
}

ERROR_STATUS Car_SM_Update(void)
{
	ERROR_STATUS errorStatus = E_NOK;
	while(1)
	{
		// Read The Distance From The Ultrasonic Using swICU
		Us_Trigger();
		Timer_Delay_Ms(TIMER_CH0, 10);
		Us_GetDistance(&g_u8_Dist);
		
		// Decide Which State To Move Our System Into
		if(g_u8_Dist < 25 - g_u8_Margin)
			Sys_State = Back;
		else if((g_u8_Dist >= 25 - g_u8_Margin) && (g_u8_Dist < 30 + g_u8_Margin))
			Sys_State = Right;
		else if(g_u8_Dist >= 30 + g_u8_Margin)
			Sys_State = Move;
		else
			Sys_State = Move;
						
		// State-Machine Transitions
		switch(Sys_State)
		{
			case Move:
				Steering_SteerCar(CAR_FORWARD, g_u8_Speed);
				break;
			case Back:
				Steering_SteerCar(CAR_BACKWARD, g_u8_Speed);
				break;
			case Right:
				Steering_SteerCar(CAR_RIGHT, g_u8_Speed);
				break;
			case Left:
				Steering_SteerCar(CAR_LEFT, g_u8_Speed);
				break;
			default:
				Steering_SteerCar(CAR_STOP, g_u8_Speed);
				break;
		}
		Timer_Delay_Ms(TIMER_CH0, 30);
	}
	// Never Reaches!
	errorStatus = E_OK;
	return errorStatus;
}