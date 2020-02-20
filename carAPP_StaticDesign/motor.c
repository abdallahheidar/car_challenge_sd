/*
 * motor.c
 *
 *  Author: Abdallah Heidar
 */ 


/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/


#include "motor.h"


/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/


uint8_t gu8_initState[MOTORS_NUMBER]= {NOT_INITIALIZED, NOT_INITIALIZED};

 extern struct Pwm_Cfg_s pwm_cfg;


 struct DIO_Cfg_s gstr_Motor1_EN =
 {
	 MOTOR_EN_1_GPIO,
	 MOTOR_EN_1_BIT,
	 OUTPUT
 };
 
  struct DIO_Cfg_s gstr_Motor1_A =
  {
	  MOTOR_OUT_1A_GPIO,
	  MOTOR_OUT_1A_BIT,
	  OUTPUT
  };
  
   struct DIO_Cfg_s gstr_Motor1_B =
   {
	   MOTOR_OUT_1B_GPIO,
	   MOTOR_OUT_1B_BIT,
	   OUTPUT
   };
 
 
  struct DIO_Cfg_s gstr_Motor2_EN =
  {
	  MOTOR_EN_2_GPIO,
	  MOTOR_EN_2_BIT,
	  OUTPUT
  };
  
  struct DIO_Cfg_s gstr_Motor2_A =
  {
	  MOTOR_OUT_2A_GPIO,
	  MOTOR_OUT_2A_BIT,
	  OUTPUT
  };
  
  struct DIO_Cfg_s gstr_Motor2_B =
  {
	  MOTOR_OUT_2B_GPIO,
	  MOTOR_OUT_2B_BIT,
	  OUTPUT
  };


/************************************************************************/
/*		         TIMER FUNCTIONS' implementation				        */
/************************************************************************/


/**
 * Func			: Motor_Init
 * Input		: motorNumber
 *	  	  		  #def
 *	  	  		  number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 */
 ERROR_STATUS Motor_Init(uint8_t Motor_Number){
	 
	 ERROR_STATUS status = E_OK;
	 
	 Pwm_Init(&pwm_cfg);
	 
	 if(Motor_Number > MOTORS_NUMBER){
		 
		 status = E_NOK;
	 }else
	 {
		 
	 switch (Motor_Number) {
		 
		 case (MOTOR_1):
		 
		   			 DIO_init(&gstr_Motor1_EN);
					 DIO_init(&gstr_Motor1_A);
					 DIO_init(&gstr_Motor1_B);
					 gu8_initState [MOTOR_1] = INITIALIZED;
					 break;
					 
		 case (MOTOR_2):
		 
					 DIO_init(&gstr_Motor2_EN);
					 DIO_init(&gstr_Motor2_A);
					 DIO_init(&gstr_Motor2_B);
					 gu8_initState [MOTOR_2] = INITIALIZED;

					 break;
		 default:
					status = E_NOK;	 
	  }
	 }/* end of else */
	 return status;
 }
 
/**
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
*/
ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction){
	
	ERROR_STATUS status = E_NOK;
	
	 if(Motor_Number > MOTORS_NUMBER){
		 
		 status = E_NOK;
	 }else
	 {

	switch (Motor_Number) {
		
		case (MOTOR_1):
		            switch (Motor_Direction) {
						
		            	case MOTOR_STOP:
		            			DIO_Write(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
		            			DIO_Write(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
		            			break;
		            	
						case MOTOR_FORWARD:
		            			DIO_Write(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, HIGH);
		            			DIO_Write(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
								Motor_Start(MOTOR_1,20 );
		            			break;
		            	
						case MOTOR_BACKWARD:
		            			DIO_Write(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
		            			DIO_Write(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, HIGH);
								Motor_Start(MOTOR_1,20 );

		            			break;
		            	
						default:	
								status = E_NOK;
		            }
		            break;
		            
		case (MOTOR_2):
		                switch (Motor_Direction) {
			                case MOTOR_STOP:
									DIO_Write(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
							 		DIO_Write(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
									break;
			                
							case MOTOR_FORWARD:
									DIO_Write(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, HIGH);
								    DIO_Write(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
									Motor_Start(MOTOR_2,20 );
									 break;
			               
						    case MOTOR_BACKWARD:
									 DIO_Write(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
									 DIO_Write(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, HIGH);
	 								 Motor_Start(MOTOR_2,20 );
									break;
			               
						    default:
									status = E_NOK;
		                }
		                break;
						
		                default:
									status = E_NOK;
	  } /* outer switch */
	}/*end of else */
	
	return status;
}



/**
 * Fun		 : Motor_Start
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: Start the motor.
*/
ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed){
	
	ERROR_STATUS status = E_OK;
	
	if(Motor_Number > MOTORS_NUMBER){
		
		status = E_NOK;
	}else
	{
	  if(gu8_initState[Motor_Number] != INITIALIZED)
	  {
	  	status = E_NOK;	
	  }
	  else
	  {
        switch(Motor_Number)
        {
        	case (MOTOR_1):
        			Pwm_Start(PWM_CH1B, Mot_Speed, MOTOR_FREQUENCY);
        			break;
			
        	case (MOTOR_2):
        			Pwm_Start(PWM_CH1B, Mot_Speed, MOTOR_FREQUENCY);
        			break;
			
        	default:
        		status = E_NOK;
        }	
	}
  }
	return status;	
}

/**
 * Fun		 : Motor_SpeedUpdate
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: Controls the motor speed from getting the motor number and the speed.
*/

ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed){
	
	
	ERROR_STATUS status = E_OK;
	// to do 
	// check it is started at first 
	
	if(Motor_Number > MOTORS_NUMBER){
		
		status = E_NOK;
	}else
	{
		if(gu8_initState[Motor_Number] != INITIALIZED)
		{
			status = E_NOK;
		}
		else
		{
			switch(Motor_Number)
			{
				case (MOTOR_1):
				Pwm_Start(PWM_CH1B, Speed, MOTOR_FREQUENCY);
				break;
				
				case (MOTOR_2):
				Pwm_Start(PWM_CH1B, Speed, MOTOR_FREQUENCY);
				break;
				
				default:
				status = E_NOK;
			}
		}
	}
	return status;
}

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: stop the motor.
*/

ERROR_STATUS Motor_Stop(uint8_t Motor_Number){
	
	ERROR_STATUS status = E_NOK;
		
		if(Motor_Number > MOTORS_NUMBER){
			
			status = E_NOK;
		}else
		{
		
	switch (Motor_Number) {
		
		case (MOTOR_1):
		
			DIO_Write(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
			DIO_Write(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
			break;
			
		case (MOTOR_2):
		
			DIO_Write(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
			DIO_Write(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
			break;
			
			default:
			status = E_NOK;
		}/* outer switch */
	}
	return status;
}

 /**
 * Func			: Motor_GetStatus
 * Input		: Motor_Number
 *	  	  		 #def
 *	  	  		 number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: Initialization_STATUS
 * Description	: Returns status of the motor whether initialized or not
 */
 ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status){
	 
	 ERROR_STATUS status = E_NOK;
	 
		if(Motor_Number > MOTORS_NUMBER){
			
			status = E_NOK;
		}else
		{
	 switch (Motor_Number) {
		 
		 case (MOTOR_1):
		 
			*Mot_status = gu8_initState[MOTOR_1];
		 
		 break;
		 
		 case (MOTOR_2):
		 
			*Mot_status = gu8_initState[MOTOR_2];

		 break;
		 
		 default:
				 status = E_NOK;
		 }/* outer switch */
	  }
	 return status; 
 }