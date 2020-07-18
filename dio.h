#ifndef _DIO_H_
#define _DIO_H_
#include "TM4C123GH6PM.h"

/*
 * Dio.h
 *
 *  Created on: Jul 18, 2020
 *      Author: moh1969
 */
//#include <Std_Types.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t Dio_ChannelType;   // 37 pins [0 .... 36]
typedef uint8_t Dio_PortType;      // A-B-C-D-E-F [ 0 ... 5]
typedef uint8_t Dio_LevelType;     // STD_LOW - STD_HIGH
#define STD_LOW  0x00
#define STD_HIGH 0x01

typedef uint8_t Dio_PortLevelType; // 8-bit port

typedef struct{
    uint8_t mask;
    uint8_t offset;
    Dio_PortType port;

}Dio_ChannelGroupType;

typedef enum{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
	  PORT_E,
    PORT_F

}PortId;
typedef enum{
    PA0 ,
    PA1 ,
    PA2 ,
    PA3 ,
    PA4 ,
    PA5 ,
    PA6 ,
    PA7 ,
	  PB0 ,
    PB1 ,
    PB2 ,
    PB3 ,
    PB4 ,
    PB5 ,
    PB6 ,
    PB7 ,
	  PC0 ,
    PC1 ,
    PC2 ,
    PC3 ,
    PC4 ,
    PC5 ,
    PC6 ,
    PC7 ,
		PD0 ,
    PD1 ,
    PD2 ,
    PD3 ,
    PD4 ,
    PD5 ,
    PD6 ,
    PD7 ,
		PE0 ,
    PE1 ,
    PE2 ,
    PE3 ,
    PE4 ,
    PE5 ,
	  PF0 ,
    PF1 ,
    PF2 ,
    PF3 ,
    PF4 ,

}ChannelId;


Dio_LevelType Dio_ReadChannel ( Dio_ChannelType ChannelId );
void Dio_WriteChannel ( Dio_ChannelType ChannelId, Dio_LevelType Level );

Dio_PortLevelType Dio_ReadPort ( Dio_PortType PortId );
void Dio_WritePort ( Dio_PortType PortId, Dio_PortLevelType Level );

Dio_PortLevelType Dio_ReadChannelGroup ( const Dio_ChannelGroupType* ChannelGroupIdPtr );
void Dio_WriteChannelGroup ( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level );



#endif /* DIO_H_ */

