#ifndef _PWM_H_
#define _PWM_H_
/* ---------------------------------- INCLUDES ---------------------------------- */
#include "TM4C123GH6PM.h"
#include "Std_Types.h"
/* ---------------------------------- PRIMITIVE TYPES ---------------------------------- */
typedef uint8_t Pwm_ChannelType;
typedef uint16_t Pwm_PeriodType;
typedef uint8_t Pwm_PolarityType;
typedef uint16_t Pwm_DutyCycle;
typedef uint8_t Pwm_IdleStateType;
/* ---------------------------------- ENUMS ---------------------------------- */

typedef enum Pwm_OutputStateType
{
	PWM_LOW =0x00,
	PWM_HIGH =0x01
	
}Pwm_OutputStateType;

typedef enum Pwm_EdgeNotificationType
{
	PWM_RISING_EDGE,
	PWM_FALLING_EDGE,
	PWM_BOTH_EDGES
	
}Pwm_EdgeNotificationType;

typedef enum Pwm_ChannelClassType
{
	PWM_VARIABLE_PERIOD,
	PWM_FIXED_PERIOD,
	PWM_FIXED_PERIOD_SHIFTED
}Pwm_ChannelClassType;
/* ---------------------------------- STRUCTS ---------------------------------- */

typedef struct
{
	Pwm_ChannelType HW_channel;
	Pwm_PeriodType period;
	Pwm_DutyCycle Dutycycle;
  Pwm_PolarityType polarity;
	Pwm_IdleStateType IdleState;
	Pwm_ChannelClassType Class;
	
}Pwm_ConfigType;
/*----------------------------------- FUNCTION-LIKE MACROS -----------------------------------*/
#define Memory(X,Y)			 	(*((volatile uint32_t*)(((uint32_t)X)+((uint32_t)Y))))
/* ---------------------------------- FUNCTION DECLARATIONS ---------------------------------- */
void Pwm_Init( const Pwm_ConfigType* ConfigPtr );
#endif