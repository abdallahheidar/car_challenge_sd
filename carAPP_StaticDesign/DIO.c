/*
 * DIO.c
 *
 *  Author: Abdallah Heidar
 */ 


/************************************************************************/
/*				 INCLUDES										        */
/************************************************************************/


#include "DIO.h"





/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/

/* for testing */

 struct DIO_Cfg_s dio = 
{
	GPIOA,
	FULL_PORT,
	OUTPUT
};

/************************************************************************/
/*		         TIMER FUNCTIONS' implementation				        */
/************************************************************************/


/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info){
	
	ERROR_STATUS status = E_OK;
	
	if (DIO_info == NULL)
	{
		status = E_NOK;
	}else{
		switch(DIO_info->GPIO){
			
			case 0:
			       if ( DIO_info->dir == INPUT )
			       {
			       	PORTA_DIR &= ~(DIO_info->pins); //clear the bits to be inputs
			       }
			       else{
			       	PORTA_DIR |= DIO_info->pins;
			       }
				   
			       break;
				   
			case 1:
			       if ( DIO_info->dir == INPUT )
			       {
				       PORTB_DIR &= ~(DIO_info->pins); //clear the bits to be inputs
			       }
			       else{
				       PORTB_DIR |= DIO_info->pins;
			       }
			
					break;
			
			case 2:
			      if ( DIO_info->dir == INPUT )
			      {
			      	PORTC_DIR &= ~(DIO_info->pins); //clear the bits to be inputs
			      }
			      else{
			      	PORTC_DIR |= DIO_info->pins;
			      }
			
					break;
			
			case 3:
			      if ( DIO_info->dir == INPUT )
			      {
			      	PORTD_DIR &= ~(DIO_info->pins); //clear the bits to be inputs
			      }
			      else{
			      	PORTD_DIR |= DIO_info->pins;
			      }
			      
				  break;
			
			default:
					status = E_NOK;
		}
		
	}/* END OF ELSE */
	
	return status;
}


/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: No output
*In/Out: No In/Out
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t u8_pins, uint8_t u8_value){
	
		ERROR_STATUS status = E_OK;
		
			if (!(GPIO >=0 && GPIO <=3) || !(u8_pins >=0 && u8_pins <=7))
			{
				status = E_NOK;
				
			}else{
				
	       switch(GPIO){
		      
		      case 0:
					 PORTA_DATA &= ~(u8_pins);
					 if (u8_value != LOW)
					  {
					  	PORTA_DATA |= u8_pins;
					  }
					  break;
					  
		      case 1:
		             PORTB_DATA &= ~(u8_pins);
		             if (u8_value != LOW)
		             {
		             	PORTB_DATA |= u8_pins;
		             }
		             break;
					 
		      case 2:
		            PORTC_DATA &= ~(u8_pins);
		            if (u8_value != LOW)
		            {
		            	PORTC_DATA |= u8_pins;
		            }
		            break;
					
		      case 3:
		            PORTD_DATA &= ~(u8_pins);
		            if (u8_value != LOW)
		            {
			            PORTD_DATA |= u8_pins;
		            }
		            break;
					
		      default: 
					status = E_NOK;
	  }
	  
	 } /* end of else */
	return status;	
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: data -> the acquired data wether it was PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t u8_pins, uint8_t *data){
	
	
	ERROR_STATUS status = E_OK;
		
		if (!(GPIO >=0 && GPIO <=3) || !(u8_pins >=0 && u8_pins <=7))
		{
			status = E_NOK;
			
		}else{
			
		switch(GPIO){
			
			case 0:
					*data =	 (PORTA_PIN & u8_pins ) ;
					break;
			
			case 1:
					*data =	 (PORTB_PIN & u8_pins ) ;
					break;
			
			case 2:
					*data =	 (PORTC_PIN & u8_pins ) ;
					break;
			case 3:
					*data =	(PORTD_PIN & u8_pins ) ;
					break;
			default: 
			   status = E_NOK;
		}
	} /*end of else */
		return status;
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*    				- FULL_PORT
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t u8_pins){
	
	ERROR_STATUS status = E_OK;
		
		if (!(GPIO >=0 && GPIO <=3) || !(u8_pins >=0 && u8_pins <=7))
		{
			status = E_NOK;
			
			}
			else{
	
	             switch(GPIO){
	             	
	             	case 0:
	             			PORTA_DATA ^= u8_pins;
	             			break;
	             	
	             	case 1:
	             			PORTB_DATA ^= u8_pins;
	             			break;
	             	
	             	case 2:
	             			PORTC_DATA ^= u8_pins;
	             			break;
	             	
	             	case 3:
	             			PORTD_DATA ^= u8_pins;
	             			break;
	             	default: 
	             			status = E_NOK;
	             }
			}/*end of else */
				 
	return status;
}
