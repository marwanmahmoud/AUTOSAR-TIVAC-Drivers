#ifndef _PWM_H_
#define _PWM_H_
/* ---------------------------------- INCLUDES ---------------------------------- */
#include "tm4c123gh6pm.h"
#include "Std_Types.h"
#include "PWM_PCC.h"
/* ---------------------------------- PRIMITIVE TYPES ---------------------------------- */
typedef uint8_t  Pwm_ChannelType;
typedef uint16_t Pwm_PeriodType;
typedef uint8_t  Pwm_PolarityType;
typedef uint16_t Pwm_DutyCycleType;
typedef uint8_t  Pwm_IdleStateType;
typedef uint8_t  PWM_DivisorType;
/* ---------------------------------- CONSTANTS ---------------------------------- */
#define Pwm_100_Precent 	      0x8000
#define Pwm_0_Precent		        0x0000
#define SYSCTL_RCC_NOCLCKDIV    ~(1<<20)
#define SYSCTL_RCC_USEPWMDIV    0x00100000  // Enable PWM Clock Divisor
#define SYSCTL_RCC_PWMDIV_2     0x00000000  // PWM clock /2
#define SYSCTL_RCC_PWMDIV_4     0x00020000  // PWM clock /4
#define SYSCTL_RCC_PWMDIV_8     0x00040000  // PWM clock /8
#define SYSCTL_RCC_PWMDIV_16    0x00060000  // PWM clock /16
#define SYSCTL_RCC_PWMDIV_32    0x00080000  // PWM clock /32
#define SYSCTL_RCC_PWMDIV_64    0x000A0000  // PWM clock /64
#define	PORTA_BASE 									  0x40004000
#define	PORTB_BASE 										0x40005000
#define	PORTC_BASE 										0x40006000
#define	PORTD_BASE 										0x40007000
#define	PORTE_BASE  									0x40024000
#define	PORTF_BASE  									0x40025000
#define GPIO_DATA_OFFSET            	0x3FC       // NOTE : Data offset not equal 0x000 as data sheet         
#define GPIO_LOCK_OFFEST							0x520
#define GPIO_CR_OFFSET								0x524
#define GPIO_AFSEL_OFFEST							0x420
#define GPIO_PCTL_OFFSET							0x52C
#define GPIO_AMSEL_OFFEST							0x528
#define GPIO_DEN_OFFEST 							0x51C
#define GPIO_DIR_OFFSET             	0x400
#define GPIO_PUR_OFFSET								0x510
#define GPIO_PDR_OFFSET								0x514
#define GPIO_IM_OFFSET               	0x410
#define GPIO_IS_OFFSET              	0x404
#define GPIO_RIS_OFFSET               0x414
#define UNLOCK				              	0x4C4F434B
/*----------------------------------- FUNCTION-LIKE MACROS -----------------------------------*/
#define Memory(X,Y)			 	(*((volatile uint32_t*)(((uint32_t)X)+((uint32_t)Y))))
/* ---------------------------------- ENUMS ---------------------------------- */
typedef enum {
	sys_clk_div2,
  sys_clk_div4,
  sys_clk_div8,
  sys_clk_div16,
  sys_clk_div32,
  sys_clk_div64=0x7,
  sys_clk_no_div,
}PWM_DIVISOR;
typedef enum {
	PORTA = 0x40004000,
	PORTB = 0x40005000,
	PORTC = 0x40006000,
	PORTD = 0x40007000,
	PORTE = 0x40024000,
	PORTF = 0x40025000
}PORT;
typedef enum Pwm_ChannelClassType
{
	PWM_VARIABLE_PERIOD,
	PWM_FIXED_PERIOD,
	PWM_FIXED_PERIOD_SHIFTED
}Pwm_ChannelClassType;
typedef enum{
     //PWM MODULE 0
  PWM0_PB6,//G0/pin0
  PWM0_PB7,//G0/pin1
  PWM0_PB4,//G1/pin0
  PWM0_PB5,//G1/pin1
  PWM0_PE4,//G2/pin0
  PWM0_PE5,//G2/pin1
  PWM0_PC4,//G3/pin0
  PWM0_PC5,//G3/pin1
    //PWM MODULE 1
  PWM1_PD0,//G0/pin0
  PWM1_PD1,//G0/pin01
  PWM1_PA6,//G1/pin0
  PWM1_PA7,//G1/pin1
  PWM1_PF0,//G2/pin0
  PWM1_PF1,//G2/pin1
  PWM1_PF2,//G3/pin0
  PWM1_PF3 //G3/pin1
}Pwm_Channel;
typedef enum PWM_Module
{
	PWM_0 =0x40028000,
	PWM_1 =0x40029000
}PWM_Module;
typedef enum{
  PWM_LOW,
	PWM_HIGH
}Pwm_OutputStateType;
typedef enum GENERATOR{
	GENERATOR1,
	GENERATOR2,
	GENERATOR3,
	GENERATOR4,
}GENERATOR;
typedef enum DUTY{
	DUTY_CYCLE_10 = 10,
	DUTY_CYCLE_50 = 50,	
	DUTY_CYCLE_25 = 25,
	DUTY_CYCLE_30 = 30,	
	DUTY_CYCLE_40 = 40,		
	DUTY_CYCLE_60 = 60,
	DUTY_CYCLE_70 = 70,
	DUTY_CYCLE_75 = 75,
	DUTY_CYCLE_80 = 80,
	DUTY_CYCLE_90 = 90,
	DUTY_CYCLE_100 = 100,
}Pwm_DutyCycle;
typedef enum PWM_Regs{
	PWM_ENABLE_R=0x008,
	SRPWM=0x540,
	PWM_G0_CTL=0x040,
	PWM_G1_CTL=0x080,
	PWM_G2_CTL=0x0C0, 	
	PWM_G3_CTL=0x100,
	PWM_G0_LOAD_R=0x050,
	PWM_G1_LOAD_R=0x090,
	PWM_G2_LOAD_R=0x0D0,
	PWM_G3_LOAD_R=0x110,
	PWM_G0_COUNTER_R=0x054,
	PWM_G1_COUNTER_R=0x094,
	PWM_G2_COUNTER_R=0x0D4,
	PWM_G3_COUNTER_R=0x114,
	PWM_G0_CMPA_R=0x058,
	PWM_G1_CMPA_R=0x098,
	PWM_G2_CMPA_R=0x0D8,
	PWM_G3_CMPA_R=0x118,
	PWM_G0_CMPB_R=0x05C,
	PWM_G1_CMPB_R=0x08C,
	PWM_G2_CMPB_R=0x0DC,
	PWM_G3_CMPB_R=0x11C,
	PWM_G0_GENPINA_R=0x060,
	PWM_G1_GENPINA_R=0x0A0,
	PWM_G2_GENPINA_R=0x0E0,
	PWM_G3_GENPINA_R=0x120,
	PWM_G0_GENPINB_R=0x064,
	PWM_G1_GENPINB_R=0x0A4,
	PWM_G2_GENPINB_R=0x0E4,
	PWM_G3_GENPINB_R=0x124,
}PWM_Regs;
typedef enum OUTPUT_FREQUANCY{
	FREQUANCY_1HZ =1,
	FREQUANCY_1KHZ=1000,
	FREQUANCY_2KHZ=2000,
	FREQUANCY_3KHZ=3000,
	FREQUANCY_4KHZ=4000,	
	FREQUANCY_5KHZ=5000,	
	FREQUANCY_6KHZ=6000,	
	FREQUANCY_7KHZ=7000,	
	FREQUANCY_8KHZ=8000,	
	FREQUANCY_9KHZ=9000,	
	FREQUANCY_10KHZ=10000,
	FREQUANCY_11KHZ=11000,
	FREQUANCY_12KHZ=12000,	
	FREQUANCY_13KHZ=13000,
	FREQUANCY_14KHZ=14000,
	FREQUANCY_15KHZ=15000,
	FREQUANCY_16KHZ=16000,
	FREQUANCY_17KHZ=17000,
	FREQUANCY_18KHZ=18000,
	FREQUANCY_19KHZ=19000,
	FREQUANCY_20KHZ=20000,
	FREQUANCY_21KHZ=21000,
	FREQUANCY_22KHZ=22000,
	FREQUANCY_23KHZ=23000,
	FREQUANCY_50KHZ=50000,
	FREQUANCY_100KHZ=100000,
	FREQUANCY_200KHZ=200000,
	FREQUANCY_250KHZ=250000,
	FREQUANCY_80KHZ=80000,
	FREQUANCY_90KHZ=90000,
}OUTPUT_FREQUANCY;
typedef enum {
	P0,
	P1,
	P2,
	P3,
	P4,
	P5,
	P6,
	P7
}PIN;
#if ( EXTRA_FEATURES == STD_ON)
typedef enum{
    PWM_RISING_EDGE,PWM_FALLING_EDGE,PWM_BOTH_EDGES
}Pwm_EdgeNotificationType;

typedef enum{
    PWM_FIXED_PERIOD,PWM_VARIABLE_PERIOD,PWM_FIXED_PERIOD_SHIFTED
}Pwm_ChannelClassType;
#endif
/*----------------------------------API Service Id Macros ----------------------------------  */
/* Service ID for Pwm INIT */
#define PWM_INIT_SID              	  0x00
/*Service ID for Pwm DeInit*/
#define PWM_DEINIT_SID                0x01
/*Service ID for Pwm SetDutyCycle*/
#define PWM_SET_DUTY_SID         	  0x02
/*Service ID for Pwm SetPeriodAndDuty*/
#define PWM_SET_PERIOD_DUTY_SID    	  0x03
/*Service ID for Pwm SetOutputToIdle*/
#define PWM_SET_OUT_IDLE_SID       	  0x04
/*Service ID for Pwm GetGroupStatus*/
#define PWM_GET_STATUS_SID            0x10 
/* ---------------------------------- STRUCTS ---------------------------------- */
typedef struct
{
	Pwm_Channel channel;
	Pwm_PeriodType period;
	Pwm_DutyCycleType Dutycycle;
  Pwm_PolarityType polarity;
	PWM_DivisorType SysClkDiv;
	PWM_Module PWM_Module;
	#if(EXTRA_FEATURES==STD_ON)
	Pwm_ChannelClassType Class;
	Pwm_IdleStateType IdleState;
	#endif
}Pwm_Config;
/* ---------------------------------- FUNCTION DECLARATIONS ---------------------------------- */
void Pwm_Init(Pwm_Config PWM );
#if (De_init==STD_ON)
void Pwm_DeInit(Pwm_Config PWM)
#endif
void Pwm_SetDutyCycle( Pwm_Config PWM);
void Pwm_SetPeriodAndDuty( Pwm_Config PWM);
#endif