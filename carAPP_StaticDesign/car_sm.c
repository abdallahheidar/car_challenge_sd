/*
 * car_sm.c
 *
 *  Author: Abdallah heidar
 */ 

/************************************************************************/
/*				 INCLUDES										        */
/************************************************************************/

#include <stdlib.h>
#include "car_sm.h"
#include "DIO.h"



/************************************************************************/
/*				 Global / Static Variables						       */
/************************************************************************/

static uint8_t gu8_State = Stop;
static uint8_t gu8_Distance = 0, gu8_Speed = 25;


/************************************************************************/
/*		         TIMER FUNCTIONS' implementation				        */
/************************************************************************/

/*
 * Fun----------: ERROR_STATUS Car_SM_Init(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: Initiate the car state machine with state"forward at speed 80%",
 * -------------- And initiate steering and ultrasonic functions
*/
ERROR_STATUS Car_SM_Init(void)
{
	ERROR_STATUS status = E_OK;
	
		/* initialize steering and Ultrasonic */
		status = Steering_Init();
		status = Us_Init();
	
	return status;
}

/*
 * Fun----------: ERROR_STATUS Car_SM_Update(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: changes car state according to the ultrasonic input
 * -------------- And represents the motors output for each state
*/



ERROR_STATUS Car_SM_Update(void)
{
	ERROR_STATUS status = E_OK;
	
			/*DIO_Cfg_s fio={
				GPIOC,
				FULL_PORT,
				OUTPUT
			};
			DIO_init(&fio);
*/

	while(1)
	{
		/* Read The Distance From The Ultrasonic Using swICU */
		
		Us_Trigger();
		softwareDelayMs(1);
		 
		 Us_GetDistance(&gu8_Distance);
		
		//DIO_Write(GPIOC, FULL_PORT, gu8_Distance );
		
		/* Decide Which State To Move Our System Into */
		
		if(gu8_Distance < 30 )
			gu8_State = Back;
		
		else if((gu8_Distance >= 30) && (gu8_Distance <= 35))
		gu8_State = Right;
		
		else if(gu8_Distance >= 35 )
		gu8_State = Move;
		
		else
		gu8_State = Stop;
		
		/* State-Machine Transitions */
		
		switch(gu8_State)
		{
			case Move:
					Steering_SteerCar(CAR_FORWARD, gu8_Speed);
					break;
			
			case Back:
					Steering_SteerCar(CAR_BACKWARD, gu8_Speed);
					break;
			
			case Right:
					Steering_SteerCar(CAR_RIGHT, gu8_Speed);
					break;
			
			case Left:
					Steering_SteerCar(CAR_LEFT, gu8_Speed);
					break;
			
			default:
					Steering_SteerCar(CAR_STOP, gu8_Speed);
			
		}
		softwareDelayMs(30);
	}
	// Never Reaches!
	
	return status;
}