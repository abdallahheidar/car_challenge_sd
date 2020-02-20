/*
 * PWM.c
 *
 * Author: Abdallah Heidar
 */ 

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "PWM.h"

/************************************************************************/
/*				 Global / Static Variables						       */
/************************************************************************/


uint16_t gu16_Prescaler;

 
  struct Pwm_Cfg_s pwm_cfg =
 {
	 PWM_CH1B,
	TIMER_PRESCALER_64
 };
 

/************************************************************************/
/*		         TIMER FUNCTIONS' implementation				        */
/************************************************************************/

/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);                           */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/
 ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg){
	
	ERROR_STATUS status = E_OK;
	
	if (Pwm_Cfg == NULL)
	{
		status = E_NOK;
	}else
	{
		
	switch(Pwm_Cfg->Channel){
		
		case PWM_CH0:
				 
				 switch(Pwm_Cfg->Prescaler){
					 
					 case TIMER_NO_CLOCK:
					 TCCR0 |= TIMER_NO_CLOCK;
					 break;
					 
					 case TIMER_PRESCALER_NO:
					 TCCR0 |= TIMER_PRESCALER_NO;
					 
					 break;
					 
					 case TIMER_PRESCALER_8:
					 TCCR0 |= TIMER_PRESCALER_8;
					 break;
					 
					 case TIMER_PRESCALER_64:
					 /* prescaler64 is mapped to 3 which is 32 in our defines*/
					 TCCR0 |=TIMER_PRESCALER_32;
					 break;
					 
					 case TIMER_PRESCALER_256:
					 /* prescaler256 is mapped to 4 which is 64 in our defines*/
					 TCCR0 |=TIMER_PRESCALER_64;
					 break;
					 
					 case TIMER_PRESCALER_1024:
					 /* prescaler1024 is mapped to 5 which is 32 in our defines*/
					 TCCR0 |=TIMER_PRESCALER_128;
					 break;
					 default:
						status = E_NOK;
				 }
				 
				 TCCR0 |= (WGM00); /* phase correct */
				 TCCR0 |= (COM00); /* TOGGLE PIN */
				 TCNT0 = 0 ;	  
					break;
			
		case PWM_CH1B:
				
				/* mode 8 */ 
				TCCR1B |= (WGM13);
				
				/* wave Pin */
				
				TCCR1A |= (COM1B1) | (COM1A1);
				TCNT1 = 0;
				
				/* making the pins output */
				struct DIO_Cfg_s pwm_io =
				{
					GPIOD,
					BIT4|BIT5,
					OUTPUT
				};
				
				DIO_init(&pwm_io);
				
				/* setting the prescaler */
				
			  	switch(Pwm_Cfg->Prescaler){
				  	
				  	case TIMER_NO_CLOCK:
				  	TCCR1B |= TIMER_NO_CLOCK; 
				  	break;
				  	
				  	case TIMER_PRESCALER_NO:
				  	TCCR1B |= TIMER_PRESCALER_NO;
					  gu16_Prescaler = 1;
				  	break;
				  	
				  	case TIMER_PRESCALER_8:
				  	TCCR1B |= TIMER_PRESCALER_8;
					  gu16_Prescaler = 8;
				  	break;
				  	
				  	case TIMER_PRESCALER_64:
				  	/* prescaler64 is mapped to 3 which is 32 in our defines*/
				  	TCCR1B |=TIMER_PRESCALER_32;
					  gu16_Prescaler = 64;
				  	break;
				  	
				  	case TIMER_PRESCALER_256:
				  	/* prescaler256 is mapped to 4 which is 64 in our defines*/
				  	TCCR1B |=TIMER_PRESCALER_64;
					  gu16_Prescaler = 256;
				  	break;
				  	
				  	case TIMER_PRESCALER_1024:
				  	/* prescaler1024 is mapped to 5 which is 32 in our defines*/
				  	TCCR1B |=TIMER_PRESCALER_128;
					  gu16_Prescaler = 1024;
				  	break;
				  	default:
				  			status = E_NOK;
			  	}
				  
				 // Timer_Start(1,0);
		break;
		case PWM_CH2:
		
		switch(Pwm_Cfg->Prescaler){
			
			case TIMER_NO_CLOCK:
				TCCR2 |= TIMER_NO_CLOCK;
				break;
			
			case TIMER_PRESCALER_NO:
				TCCR2 |= TIMER_PRESCALER_NO;
				break;
			
			case TIMER_PRESCALER_8:
				TCCR2 |= TIMER_PRESCALER_8;
				break;
			
			case TIMER_PRESCALER_32:
				TCCR2 |= TIMER_PRESCALER_32;
				break;
			
			case TIMER_PRESCALER_64:
				TCCR2 |= TIMER_PRESCALER_64;
				break;
			
			case TIMER_PRESCALER_128:
				TCCR2 |= TIMER_PRESCALER_128;
				break;
			
			case TIMER_PRESCALER_256:
				TCCR2 |= TIMER_PRESCALER_256;
				break;
			
			case TIMER_PRESCALER_1024:
				TCCR2 |= TIMER_PRESCALER_1024;
				break;
			
			default:
				status = E_NOK;
		}
		TCCR2 |= WGM20;
		TCNT2 = 0 ;
		break;
		
		default:
				status = E_NOK;
	  }
	}/* end of else */
	return status;
}

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: starts the PWM on the dedicated channel with the required duty   */
/*				cycle and frequency                                              */
/*-------------------------------------------------------                        */
/*(IN timer 0) there are only 5 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*--------------------------------------------------------                       */
/*(IN timer 2) there are only 7 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 32) --> 980HZ                                             */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 128) --> 245HZ                                            */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*-------------------------------------------------------                        */
/*((all this calculations are for phase correct mode))                           */
/*all this calculation for F_CPU 16MHz                                           */
/*********************************************************************************/
 ERROR_STATUS Pwm_Start(uint8_t Channel, uint8_t Duty, uint32_t Frequncy){
	 
		 ERROR_STATUS status = E_OK;
		 
		  uint32_t period;
		  uint32_t onTime;
		  
		  
		 switch(Channel){
			 
			 case PWM_CH0:
			 
			 break;
			 
			 case PWM_CH1B:
			 
			
			 period = FCPU / (2 * gu16_Prescaler * Frequncy);
			 
			 /* initializing the timer values */
			 
			 onTime = period * (Duty /100.00);
			 ICR1 = period;
			 OCR1A = onTime;
			 OCR1B = onTime;
			 
			 /* starting the timer */
			 if (gu16_Prescaler == 64 )
			 {
			  	/* prescaler64 is mapped to 3 which is 32 in our defines*/
				 TCCR1B |= TIMER_PRESCALER_32;
			 }
			 else if (gu16_Prescaler == 256)
			 {
				 /* prescaler256 is mapped to 4 which is 64 in our defines*/
				 TCCR1B |=TIMER_PRESCALER_64;
			 }
			 else{
				/* prescaler1024 is mapped to 5 which is 32 in our defines*/
				TCCR1B |=TIMER_PRESCALER_128;
			 }
			 
			 break;
			 case PWM_CH2:
			 
			 break;
			 
			 default:
			 status = E_NOK;
		 }
		 return status;
 }	 

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/
 ERROR_STATUS Pwm_Update(uint8_t Channel, uint8_t Duty, uint32_t Frequncy){
	 
	  ERROR_STATUS status = E_OK;
	  
	  uint32_t period;
	  uint32_t onTime;
	  
	  
	  switch(Channel){
		  
		  case PWM_CH0:
		  
		  break;
		  
		  case PWM_CH1B:
		  
		  
		  period = FCPU / (2 * gu16_Prescaler * Frequncy);
		  
		  /* initializing the timer values */
		  
		  onTime = period * (Duty /100.00);
		  ICR1 = period;
		  OCR1A = onTime;
		  OCR1B = onTime;
		  
		  /* starting the timer */
		  if (gu16_Prescaler == 64 )
		  {
			  /* prescaler64 is mapped to 3 which is 32 in our defines*/
			  TCCR1B |= TIMER_PRESCALER_32;
		  }
		  else if (gu16_Prescaler == 256)
		  {
			  /* prescaler256 is mapped to 4 which is 64 in our defines*/
			  TCCR1B |=TIMER_PRESCALER_64;
		  }
		  else{
			  /* prescaler1024 is mapped to 5 which is 32 in our defines*/
			  TCCR1B |=TIMER_PRESCALER_128;
		  }
		  
		  break;
		  case PWM_CH2:
		  
		  break;
		  
		  default:
		  status = E_NOK;
	  }
	  return status;
	 
 }

/*********************************************************************************/
/* Function: Error_State Pwm_Stop(uint8_t channel);                              */
/* Type: public                                                                  */
/* Input parameters: channel ID                                                  */
/* Return type : Error state                                                     */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the prescaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/
 ERROR_STATUS Pwm_Stop(uint8_t Channel){
	 
	 ERROR_STATUS status = E_OK;
	 
	 switch(Channel){
		 
		 case PWM_CH0:
		 
				TCCR0 &= TIMER_NO_CLOCK;
				TCCR0 = 0;
				break;
		 
		 case PWM_CH1B:
		 
			TCCR1B &= TIMER_NO_CLOCK;
			ICR1 = 0 ;
			 break;
			 
		 case PWM_CH2:
		 
			 TCCR2 &= TIMER_NO_CLOCK;
			 TCCR2 = 0;
			 break;
		 
		 default:
				 status = E_NOK;
	 }
	 return status;
 }
