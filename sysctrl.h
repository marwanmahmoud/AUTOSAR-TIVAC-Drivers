#ifndef _SYSCTRL_H
#define _SYSCTRL_H

#include "common.h"

#define SYSCTL_PRGPIO   (*((volatile uint32_t*)0x400FEA08))
	
typedef enum{
	SYSCTRL_GPIOA				= 1 << 0,
	SYSCTRL_GPIOB				= 1 << 1,
	SYSCTRL_GPIOC				= 1 << 2,
	SYSCTRL_GPIOD				= 1 << 3,
	SYSCTRL_GPIOE				= 1 << 4,
	SYSCTRL_GPIOF				= 1 << 5,
} GPIO_SYSCTRL;

typedef enum{
	SYSCTRL_UART0				= 1 << 0,
	SYSCTRL_UART1				= 1 << 1,
	SYSCTRL_UART2				= 1 << 2,
	SYSCTRL_UART3				= 1 << 3,
	SYSCTRL_UART4				= 1 << 4,
	SYSCTRL_UART5				= 1 << 5,
	SYSCTRL_UART6				= 1 << 6,
	SYSCTRL_UART7				= 1 << 7,
} UART_SYSCTRL;

typedef enum{
	SYSCTRL_TIMER0				= 1 << 0,
	SYSCTRL_TIMER1				= 1 << 1,
	SYSCTRL_TIMER2				= 1 << 2,
	SYSCTRL_TIMER3				= 1 << 3,
  SYSCTRL_TIMER4				= 1 << 4,
  SYSCTRL_TIMER5				= 1 << 5,
} TIMER_SYSCTRL;

void SYSCTRL_initGPIO(GPIO_SYSCTRL gpioCTL);
void SYSCTRL_initUART(UART_SYSCTRL uartCTL);
void SYSCTRL_initTIMER(TIMER_SYSCTRL timerCTL);

#endif //_SYSCTRL_H
