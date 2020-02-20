/*
 * Motor.c
 *
 *  Author: Abdallah Heidar
 */ 

#include "motor.h"


/***********************************************************************
 * Func			: Motor_Init
 * Input		: motorNumber
 *	  	  		  #def
 *	  	  		  number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 ***********************************************************************/
ERROR_STATUS Motor_Init(uint8_t u8_Motor_Number)
{
	ERROR_STATUS errorStatus = E_NOK;
	DIO_Cfg_s Motor_En, Motor_Dir1, Motor_Dir2;
	switch(u8_Motor_Number)
	{
		case MOTOR_1:
			Motor_En.GPIO = M1EN_GPIO;
			Motor_En.pins = M1EN_BIT;
			Motor_En.dir = OUTPUT;
			DIO_init(&Motor_En);
			Motor_Dir1.GPIO = M1D1_GPIO;
			Motor_Dir1.pins = M1D1_BIT;
			Motor_Dir1.dir = OUTPUT;
			DIO_init(&Motor_Dir1);
			Motor_Dir2.GPIO = M1D2_GPIO;
			Motor_Dir2.pins = M1D2_BIT;
			Motor_Dir2.dir = OUTPUT;
			DIO_init(&Motor_Dir2);
			errorStatus = E_OK;
			break;
		case MOTOR_2:
			Motor_En.GPIO = M2EN_GPIO;
			Motor_En.pins = M2EN_BIT;
			Motor_En.dir = OUTPUT;
			DIO_init(&Motor_En);
			Motor_Dir1.GPIO = M2D1_GPIO;
			Motor_Dir1.pins = M2D1_BIT;
			Motor_Dir1.dir = OUTPUT;
			DIO_init(&Motor_Dir1);
			Motor_Dir2.GPIO = M2D2_GPIO;
			Motor_Dir2.pins = M2D2_BIT;
			Motor_Dir2.dir = OUTPUT;
			DIO_init(&Motor_Dir2);
			errorStatus = E_OK;
			break;
		default:
			errorStatus = E_NOK;
			break;
	}
	return errorStatus;
}
/******************************************************************************************
 * Fun		 : Motor_Direction
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2

			   @param Motor_Direction
			   #define
			   Stop, Forward, Backword
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Controls the motor direction from getting the motor number and the direction.
*******************************************************************************************/
ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction)
{
	ERROR_STATUS errorStatus = E_NOK;
	switch(Motor_Number)
	{
		case MOTOR_1:
			switch(Motor_Direction)
			{
				case MOTOR_FORWARD:
					DIO_Write(M1D1_GPIO, M1D1_BIT, HIGH);
					DIO_Write(M1D2_GPIO, M1D2_BIT, LOW);
					break;
				case MOTOR_BACKWARD:
					DIO_Write(M1D1_GPIO, M1D1_BIT, LOW);
					DIO_Write(M1D2_GPIO, M1D2_BIT, HIGH);
					break;
				case MOTOR_STOP:
					DIO_Write(M1D1_GPIO, M1D1_BIT, LOW);
					DIO_Write(M1D2_GPIO, M1D2_BIT, LOW);
					break;
				default:
					break;
			}
			errorStatus = E_OK;
			break;
		case MOTOR_2:
			switch(Motor_Direction)
			{
				case MOTOR_FORWARD:
					DIO_Write(M2D1_GPIO, M2D1_BIT, HIGH);
					DIO_Write(M2D2_GPIO, M2D2_BIT, LOW);
					break;
				case MOTOR_BACKWARD:
					DIO_Write(M2D1_GPIO, M2D1_BIT, LOW);
					DIO_Write(M2D2_GPIO, M2D2_BIT, HIGH);
					break;
				case MOTOR_STOP:
					DIO_Write(M2D1_GPIO, M2D1_BIT, LOW);
					DIO_Write(M2D2_GPIO, M2D2_BIT, LOW);
					break;
				default:
					break;
			}
			errorStatus = E_OK;
			break;
		default:
			errorStatus = E_NOK;
			break;
	}
	return errorStatus;
}
/******************************************************************************
 * Fun		 : Motor_Start
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Start the motor.
*******************************************************************************/
ERROR_STATUS Motor_Start(uint8_t u8_Motor_Number, uint8_t u8_Mot_Speed)
{
	ERROR_STATUS errorStatus = E_NOK;
	Pwm_Cfg_s a_Motor_PWM;
	switch(u8_Motor_Number)
	{
		case MOTOR_1:
			a_Motor_PWM.Channel = PWM_CH1A;
			Pwm_Init(&a_Motor_PWM);
			Pwm_Start(a_Motor_PWM.Channel, u8_Mot_Speed, Fpwm);
			errorStatus = E_OK;
			break;
		case MOTOR_2:
			a_Motor_PWM.Channel = PWM_CH1B;
			Pwm_Init(&a_Motor_PWM);
			Pwm_Start(a_Motor_PWM.Channel, u8_Mot_Speed, Fpwm);
			errorStatus = E_OK;
		default:
			errorStatus = E_NOK;
			break;
	}
	return errorStatus;
}