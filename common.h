#ifndef _CAMMAN_H
#define _CAMMAN_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "tm4c123gh6pm_new.h"


#define HIGH		0xFFFFFFFF
#define LOW 		0x00000000

#define CPU_CLK     50000000U


#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100))
#define NVIC_EN1 (*((volatile uint32_t *)0xE000E104))
#define NVIC_EN2 (*((volatile uint32_t *)0xE000E108))
#define NVIC_EN3 (*((volatile uint32_t *)0xE000E10C))
	
typedef enum Pin{
	PIN0				= 0x00000001,
	PIN1				= 0x00000002,
	PIN2				= 0x00000004,
	PIN3				= 0x00000008,
	PIN4				= 0x00000010,
	PIN5				= 0x00000020,
	PIN6				= 0x00000040,
	PIN7				= 0x00000080,
  PORT				= 0x000000FF,
} Pin;

#define Log(X) ((int)log2(X))

#endif //_CAMMAN_H

