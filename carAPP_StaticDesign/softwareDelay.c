/*
 * softwareDelay.c
 *
 *  Author: Abdallah Heidar
 */ 
#include "softwareDelay.h"
#include "std_types.h"

void softwareDelayMs(uint32_t u32_delay_in_ms)
{
  uint32_t ticks = 2290, i, j;
  for(j=0; j<u32_delay_in_ms; j++)
  {
    for(i=0; i<ticks; i++)
    { }
  }
}
