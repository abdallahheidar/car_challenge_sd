/*
 *      ICU.h
 *
 *      Created on: Dec 21, 2019
 *      Author: Wave 7
 *      Version: 1
 */

#ifndef _ICU_H_
#define _ICU_H_

/************************************************************************/
/*				               Includes                                 */
/************************************************************************/

#include "std_types.h"
#include "DIO.h"
#include "Timer.h"
#include "registers.h"
#include "interrupt.h"

/************************************************************************/
/*				               Constants                                */
/************************************************************************/
#define ICU_CH0			(0)			/* defines External Interrupt 0 */
#define ICU_CH1			(1)       	/* defines External Interrupt 1 */
#define ICU_CH2			(2)			/* defines External Interrupt 2 */

#define ICU_TIMER_CH0	(0)			/* defines Timer 0 */
#define ICU_TIMER_CH1	(1)			/* defines Timer 1 */
#define ICU_TIMER_CH2	(2)			/* defines Timer 2 */

#define ICU_RISE_TO_RISE	(0)
#define ICU_RISE_TO_FALL	(1)
#define ICU_FALE_TO_RISE	(2)

#define ICU_CH0_GPIO	GPIOD
#define ICU_CH1_GPIO	GPIOD
#define ICU_CH2_GPIO	GPIOB

#define ICU_CH0_BIT		BIT2
#define ICU_CH1_BIT		BIT3
#define ICU_CH2_BIT		BIT2


/************************************************************************/
/*				               Structures                               */
/************************************************************************/

typedef struct Icu_cfg_s{
	uint8_t ICU_Ch_No;		/* To choose the External Interrupt number */
	uint8_t ICU_Ch_Timer;     /* To choose the Timer number */
}Icu_cfg_s;

typedef enum EN_SwICU_Edge_t{
	SwICU_EdgeFalling  = 2,
	SwICU_EdgeRising   = 3,
	SwICU_AllEdges     = 4
}EN_SwICU_Edge_t;

/************************************************************************/
/*				          Functions' Prototypes                         */
/************************************************************************/


/**************************************************************************
 * Function 	: Icu_Init                                                *
 * Input 		: Icu_cfg : pointer to structure of type Icu_cfg_s        *
 * Return 		: value of type ERROR_STATUS							  *
 * 				  which is one of the following values:					  *
 * 				  - E_OK  : initialized successfully					  *
 *				  - E_NOK : not initialized successfully				  *
 * Description  : Initializes the ICU by initializing the timer			  *
 * 				  and enabling the global interrupt						  *
 **************************************************************************/
extern ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg);

/***************************************************************************
 * Function		: Icu_ReadTime
 * Input		: 
 *				Icu_Channel --> ICU timer channel
 *									- ICU_TIMER_CH0
 *									- ICU_TIMER_CH1
 *									- ICU_TIMER_CH2
 *				Icu_EdgeToEdge -- > edges to calculate pusle time between:
 *									- ICU_RISE_TO_RISE
 *									- ICU_RISE_TO_FALL
 *									- ICU_FALE_TO_RISE					   *
 * Output 		: Icu_Time : pointer to uint32 variable to give the time   *
 * 				  from falling edge to rising edge						   *
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between 2 edges				       *
 ***************************************************************************/
extern ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time);


extern void Us_Read(uint8_t* a_dist);

#endif /* _ICU_H_ */
