/*
 * Steering.c
 *
 *  Author: Abdallah Heidar
 */ 
#include "Steering.h"


/****************************************************
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 ****************************************************/
ERROR_STATUS Steering_Init(void)
{
	ERROR_STATUS errorStatus = E_NOK;
	Motor_Init(MOTOR_1);
	Motor_Init(MOTOR_2);
	errorStatus = E_OK;
	return errorStatus;
}
/**************************************************************************************
 * Input: 
 * 	carDirection: The direction of the car from the predefined states of the module.
 * 	speed: The speed of the car from 0% to 100%.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This funtion controls the command and the speed of the car.
 * 							
 **************************************************************************************/
ERROR_STATUS Steering_SteerCar(uint8_t u8_Steering_CarCmd, uint8_t u8_Speed)
{
	ERROR_STATUS errorStatus = E_NOK;
	switch(u8_Steering_CarCmd)
	{
		case CAR_FORWARD:
			Motor_Direction(MOTOR_1, MOTOR_FORWARD);
			Motor_Start(MOTOR_1, u8_Speed);
			Motor_Direction(MOTOR_2, MOTOR_FORWARD);
			Motor_Start(MOTOR_2, u8_Speed);
			errorStatus = E_OK;
			break;
		case CAR_BACKWARD:
			Motor_Direction(MOTOR_1, MOTOR_BACKWARD);
			Motor_Start(MOTOR_1, u8_Speed);
			Motor_Direction(MOTOR_2, MOTOR_BACKWARD);
			Motor_Start(MOTOR_2, u8_Speed);
			errorStatus = E_OK;
			break;
		case CAR_RIGHT:	
			Motor_Direction(MOTOR_1, MOTOR_BACKWARD);
			Motor_Start(MOTOR_1, u8_Speed);
			Motor_Direction(MOTOR_2, MOTOR_FORWARD);
			Motor_Start(MOTOR_2, u8_Speed);
			errorStatus = E_OK;
			break;
		case CAR_LEFT:
			Motor_Direction(MOTOR_1, MOTOR_FORWARD);
			Motor_Start(MOTOR_1, u8_Speed);
			Motor_Direction(MOTOR_2, MOTOR_BACKWARD);
			Motor_Start(MOTOR_2, u8_Speed);
			errorStatus = E_OK;
			break;
		case CAR_STOP:
			Motor_Direction(MOTOR_1, MOTOR_STOP);
			Motor_Direction(MOTOR_2, MOTOR_STOP);
			errorStatus = E_OK;
			break;
		default:
			errorStatus = E_NOK;
			break;
	}
	return errorStatus;
}