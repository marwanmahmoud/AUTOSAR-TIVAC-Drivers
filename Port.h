#ifndef _Port_H_
#define _Port_H_
/* ---------------------------------- INCLUDES ---------------------------------- */
#include "gpio.h"
#include "tm4c123gh6pm_new.h"
/*==========================API Service Id Macros=============================*/
/* Service ID for Port INIT */
#define PORT_INIT_SID           			  0x00
/*Service ID for Port Set Pin Direction*/
#define PORT_SET_PIN_DIRECTION_SID            0x01
/*Service ID for Port Set Pin Direction*/
#define PORT_Refresh_PORT_DIRECTION_SID       0x02
/*Service ID for Set Pin Mode*/
#define PORT_SET_PIN_MODE_SID           	  0x04
/*=========================  DET Error Codes ===================================*/
//Invalid Port Pin ID requested
#define PORT_E_PARAM_PIN 0x0A
//Port Pin not configured as changeable
#define PORT_E_DIRECTION_UNCHANGEABLE 0x0B
//API Port_SetPinMode service called when mode is unchangeable.
#define PORT_E_MODE_UNCHANGEABLE 0x0E
//API service called without module initialization
#define PORT_E_UNINIT 0x0F
//APIs called with a Null Pointer
#define PORT_E_PARAM_POINTER 0x10
/*=========================  Constans ===================================*/
#define    PORT_A_PIN_0                 0
#define    PORT_A_PIN_1                 1
#define    PORT_A_PIN_2                 2
#define    PORT_A_PIN_3                 3
#define    PORT_A_PIN_4                 4
#define    PORT_A_PIN_5                 5
#define    PORT_A_PIN_6                 6
#define    PORT_A_PIN_7                 7

#define    PORT_B_PIN_0                 8
#define    PORT_B_PIN_1                 9
#define    PORT_B_PIN_2                 10
#define    PORT_B_PIN_3                 11
#define    PORT_B_PIN_4                 12
#define    PORT_B_PIN_5                 13
#define    PORT_B_PIN_6                 14
#define    PORT_B_PIN_7                 15

#define    PORT_C_PIN_0                 16
#define    PORT_C_PIN_1                 17
#define    PORT_C_PIN_2                 18
#define    PORT_C_PIN_3                 19
#define    PORT_C_PIN_4                 20
#define    PORT_C_PIN_5                 21
#define    PORT_C_PIN_6                 22
#define    PORT_C_PIN_7                 23

#define    PORT_D_PIN_0                 24
#define    PORT_D_PIN_1                 25
#define    PORT_D_PIN_2                 26
#define    PORT_D_PIN_3                 27
#define    PORT_D_PIN_4                 28
#define    PORT_D_PIN_5                 29
#define    PORT_D_PIN_6                 30
#define    PORT_D_PIN_7                 31

#define    PORT_E_PIN_0                 32
#define    PORT_E_PIN_1                 33
#define    PORT_E_PIN_2                 34
#define    PORT_E_PIN_3                 35
#define    PORT_E_PIN_4                 36
#define    PORT_E_PIN_5                 37

#define    PORT_F_PIN_0                 40
#define    PORT_F_PIN_1                 41
#define    PORT_F_PIN_2                 42
#define    PORT_F_PIN_3                 43
#define    PORT_F_PIN_4                 44

#define    PORT_A_BASE                 0x40004000
#define    UNLOCK                    0x4C4F434B  
#define SYSCTL_RCGCGPIO 		((volatile uint32_t*)0x400FE608)
#define RCGC2_REG_GPIO	    ((volatile uint32_t*)0x400FE108)	
/*----------------------------------- FUNCTION-LIKE MACROS -----------------------------------*/
#define Memory(X,Y)			 	(*((volatile uint32_t*)(((uint32_t)X)+((uint32_t)Y))))
/* ---------------------------------- PRIMITIVE TYPES ---------------------------------- */
typedef uint8_t Port_PinType ;
typedef uint8_t Port_PinModeType;
/* ---------------------------------- ENUMS ---------------------------------- */
typedef enum {
PORT_PIN_IN=0x00000000,
PORT_PIN_OUT=0x00000001,	
}Port_PinDirectionType;

typedef enum {
PORTA,
PORTB,
PORTC,
PORTD,
PORTE,
PORTF,
}PORT__;
typedef enum {
PIN_DIGITAL=0,
PIN_ANALOGE=1,
}Pin_SignalType;
typedef enum {
PWM0_Mode,
PWM1_Mode,
DIO_Mode,
UART_Mode,
}Pin_Mode;
#if(EXTRA_FEATURES==STD_ON)
//Possible pull-up resistors configurations of a port pin.
typedef enum {
	PULL_UP ,
	PULL_DOWN,
    NO_PULL
}Port_PullConfigType ;

//Possible pin Changeable (directions or modes) configurations of a port pin.
typedef enum{
	NOT_CHANGEABLE,
    CHANGEABLE
}Port_PinChangeableType;

//Port status
typedef enum {
    PORT_NOT_INITIALIZED,
    PORT_INITIALIZED  
}Port_PortStatusType;
#endif
/*=============================Specific Implimintation=======================*/
typedef enum{
	DATA=0x00,
	DIR = 0x400,
	ODR =0x50C,
	PUR =0x510,
	PDR = 0x514,
	DEN =0x51C,
	LOCK =0x520,
	CR   =0x524,
  AMSEL =0x528,
	PCTL=0x52C,
	AFSEL =0x420,
}GPIO_REG;

/*=============================Structs=======================*/

typedef struct Port_ConfigType {
	
Port_PinType Pin;  //the configured port
Port_PinModeType Pin_Mode;   //mode of the configured pin (dio, uart, ?)
Port_PinDirectionType PinDirection  ;  //direction of the configured pin(input/output) 
Pin_SignalType signal;// signal of pin (analoge/digital)
#if(EXTRA_FEATURES==STD_ON)
    uint8_t PinIntitLevel;  //initial output value of the configured pin
    Port_PullConfigType PullConfig;  //activating internal pull-up resistors
    //indicates if the pin direction can be changed in runtime. 
    Port_PinChangeableType PinDirChangeable;  
    //indicates if the pin mode can be changed in runtime. 
    Port_PinChangeableType PinModeChangeable;  
    Port_PortStatusType Port_PortStatus;  //used for error checking and handling
#endif
}Port_ConfigType;
void Port_Init(const Port_ConfigType ConfigPtr);
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
void Port_RefreshPortDirection(void);
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);

#endif

