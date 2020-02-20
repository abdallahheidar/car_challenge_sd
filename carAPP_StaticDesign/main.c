/*
 * carAPP_StaticDesign.c
 *
 * Author : Abdallah Heidar
 */ 

//#include <avr/io.h>
#include "Timer.h"
#include "DIO.h"
#include "PWM.h"
#include "ICU.h"

#include "car_sm.h"


extern struct DIO_Cfg_s dio;
extern struct DIO_Cfg_s pwm_io;
extern struct Pwm_Cfg_s pwm_cfg;
extern struct Icu_cfg_s Icu_Cfg;



int main(void)
{
	
	//Pwm_Start(PWM_CH1B, 5 ,50 );
	//DIO_init(&dio);
	//DIO_Write(0, FULL_PORT, HIGH);
	/*
	uint8_t *time_count = 0 ;
	Icu_Init(&Icu_Cfg);

		 Icu_ReadTime(TIMER_CH0, EXT_INT2_FALLING_EDGE, time_count);
		while(1){
			

		}
		*/
	
	Car_SM_Init();
	
	//Icu_Init(&Icu_Cfg);
	
	//uint32_t  dist = 0 ;
	/*MCUCSR |= 0x40;
	GICR |= 0x20;
	PORTB_DIR &= ~(1<<2);
	sei();*/
//	Icu_ReadTime(0, ICU_RISE_TO_FALL, &dist);
	
	//EXT_INT_SetEdge(EXT_INT2_RISING_EDGE);
	//EXT_INT_Enable(EXT_INT2);
	//Pwm_Init(&pwm_cfg);
			
	while (1)
	{
		//Icu_RiseToFall(dist);
		//		DIO_Write(0, FULL_PORT, *dist);

		
		//Pwm_Start(PWM_CH1B, 50,50);
		Car_SM_Update();
		
	}
	
}

/*
ISR(INT2_vect)
{
		PORTA_DIR = 0xff;
		PORTA_DATA = 0xff;
		//DIO_Write(0, FULL_PORT, HIGH);
}
*/


