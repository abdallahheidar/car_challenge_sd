/*
 * Steering.c
 *
 *  Author: Abdallah Heidar
 */ 

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "Steering.h"



/************************************************************************/
/*		      STEERING FUNCTIONS' PROTOTYPES		        */
/************************************************************************/


/**
 * Input: 
 * Output:
 * In/Out: 
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */

ERROR_STATUS Steering_Init(void){
	
	ERROR_STATUS status = E_OK;
	
	status = Motor_Init(MOTOR_1);
	status = Motor_Init(MOTOR_2);
	
	return status;
}

/**
 * Input: 
 * 	carDirection: The direction of the car from the predefined states of the module.
 * 	speed: The speed of the car from 0% to 100%.
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This funtion controls the command and the speed of the car.
 * 							
 */
ERROR_STATUS Steering_SteerCar(uint8_t Steering_direction,
							   uint8_t speed){
					
			ERROR_STATUS	status = E_NOK;		   
								
				  switch (Steering_direction) {
									    
					case CAR_STOP:
							Motor_Stop(MOTOR_1);
							Motor_Stop(MOTOR_2);
							
							break;
							
					case CAR_FORWARD:
							Motor_Direction(MOTOR_1,MOTOR_FORWARD);
							Motor_Direction(MOTOR_2,MOTOR_FORWARD);
							
							break;
							
					case CAR_BACKWARD:
							Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
							Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
							
							break;
					
				    case CAR_RIGHT:
							Motor_Direction(MOTOR_1,MOTOR_BACKWARD);
							Motor_Direction(MOTOR_2,MOTOR_FORWARD);
							
	     					break;

					case CAR_LEFT:
							Motor_Direction(MOTOR_1,MOTOR_FORWARD);
							Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
								
							break;
							
					default:
							status = E_NOK;
				  }
	  return status;
	}



