/*
 * newCar.c
 *
 * Author : Abdallah Heidar
 */ 

#include "car_sm.h"


int main(void)
{
		
		 Car_SM_Init();
    /* Replace with your application code */
    while (1) 
    {
		Car_SM_Update();
    }
}

