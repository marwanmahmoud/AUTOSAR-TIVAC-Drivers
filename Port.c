#include "Port.h"
void init_DIO (Port_ConfigType ConfigPtr)
{
	uint8_t port = (ConfigPtr.Pin)/8;
	uint8_t pin  = (ConfigPtr.Pin)%8;
	(*SYSCTL_RCGCGPIO)=(1<<port);
	Memory(((PORT_A_BASE)+port*0x1000),AFSEL)&=~(1<<pin);
	if(ConfigPtr.signal==PIN_DIGITAL)
	{
	Memory(((PORT_A_BASE)+port*0x1000),DEN)|=(1<<pin);
	Memory(((PORT_A_BASE)+port*0x1000),AMSEL)&=~(1<<pin);	
	}
	else if (ConfigPtr.signal==PIN_ANALOGE)
	{
	Memory(((PORT_A_BASE)+port*0x1000),AMSEL)=(1<<pin);
	Memory(((PORT_A_BASE)+port*0x1000),DEN)&=~(1<<pin);
	}
	Memory(((PORT_A_BASE)+port*0x1000),DIR)=(ConfigPtr.PinDirection  & ~(1<<pin)) | ((1<<pin) & ConfigPtr.PinDirection);
	
}
void init_PWM0 (Port_ConfigType ConfigPtr)
{
}
void init_PWM1 (Port_ConfigType ConfigPtr)
{
}
void init_UART (Port_ConfigType ConfigPtr)
{
}




void Port_Init( Port_ConfigType ConfigPtr)
{
if( ConfigPtr.Pin_Mode==PWM0_Mode)
{
	init_PWM0 ( ConfigPtr);
}
else if (ConfigPtr.Pin_Mode==PWM1_Mode)
{
	init_PWM1 ( ConfigPtr);
}
else if (ConfigPtr.Pin_Mode==DIO_Mode)
{
	init_DIO (ConfigPtr);
}
else if (ConfigPtr.Pin_Mode==UART_Mode)
{
}
}