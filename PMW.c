#include "PWM.h"
uint32_t Port;
uint8_t Pin;
uint8_t portNum;
void setPortPin(uint8_t Channel){
	switch (Channel)
	{
		case PWM0_PB6 :
			Port = PORTB ; 
			Pin  = P6;
			portNum = 1;
			break;
		case PWM0_PB7 :
			Port = PORTB ; 
			Pin  = P7;
			portNum = 1;
			break;
		case PWM0_PB4 :
			Port = PORTB ; 
			Pin  = P4;
			portNum = 1;
			break;
		case PWM0_PB5 :
			Port = PORTB ; 
			Pin  = P5;
			portNum = 1;
			break;
		case PWM0_PE4 :
			Port = PORTE; 
			Pin  = P4;
			portNum = 4;	
			break;
		case PWM0_PE5 :
			Port = PORTE; 
			Pin  = P5;
			portNum = 4;
			break; 
		case PWM0_PC4 :
			Port = PORTC; 
			Pin  = P4;
			portNum = 2;
			break;
		case PWM0_PC5 :
			Port = PORTC; 
			Pin  = P5;
			portNum = 2;
			break;
    // PWM MODULE 1
		case PWM1_PD0 :
			Port = PORTD; 
			Pin  = P0;
			portNum = 3;
			break;
		case PWM1_PD1 :
			Port = PORTD; 
			Pin  = P1;
			portNum = 3;
			break;
		case PWM1_PA6 :
			Port = PORTA; 
			Pin  = P6;
			portNum = 0;
			break;
		case PWM1_PA7 :
			Port = PORTA; 
			Pin  = P7;
			portNum = 0;
			break;
		case PWM1_PF0 :
			Port = PORTF; 
			Pin  = P0;
			portNum = 5;
			break;
		case PWM1_PF1 :
			Port = PORTF; 
			Pin  = P1;
			portNum = 5;
			break;
		case PWM1_PF2 :
			Port = PORTF; 
			Pin  = P2;
			portNum = 5;
			break;
		case PWM1_PF3 :
			Port = PORTF; 
			Pin  = P3;
			portNum = 5;
			break;
	}
}
void Pwm_Init(Pwm_Config PWM )
{
	setPortPin(PWM.channel);
	uint8_t PWM_module = PWM.channel / 8; // which pwm module
	uint8_t PWM_GEN = PWM.channel / 2;
	uint8_t PWM_OUTPUT_PIN = PWM.channel % 2 ;
	if(	PWM_GEN > 3)
		PWM_GEN -= 4;
	if(PWM.SysClkDiv==sys_clk_no_div)
		SYSCTL_RCC_R &= ~(1<<20) ;	
	else
		SYSCTL_RCC_R = (PWM.SysClkDiv << 17)|(1<<20);
	SYSCTL_RCGCPWM_R |=(1<<PWM_module);
	while(!(SYSCTL_PRPWM_R & (1<<PWM_module)));
	SYSCTL_RCGCGPIO_R |= (1<<portNum);
	while(!(SYSCTL_PRGPIO_R & (1<<portNum)));
	Memory(Port,GPIO_LOCK_OFFEST) = UNLOCK ;
	Memory(Port,GPIO_CR_OFFSET)  |= (1<< Pin) ;
	Memory(Port,GPIO_DEN_OFFEST) |= (1<<Pin);
	Memory(Port,GPIO_DIR_OFFSET) |= (1<<Pin);
	Memory(Port,GPIO_AMSEL_OFFEST) &= ~(1<<Pin);
	Memory(Port,GPIO_AFSEL_OFFEST) |= (1<<Pin) ;
	Memory(Port,GPIO_PCTL_OFFSET)  |= (4<<(Pin*4));
	Memory( PWM.PWM_Module , ( PWM_G0_CTL + 4 * PWM_GEN ) ) = 0;
	if(PWM.polarity == PWM_HIGH)
		Memory( PWM.PWM_Module,( PWM_G0_GENPINA_R + 4 * PWM_OUTPUT_PIN + 64 * PWM_GEN )) = 0x0000008C;
	else
		Memory( PWM.PWM_Module,( PWM_G0_GENPINA_R + 4 * PWM_OUTPUT_PIN + 64 * PWM_GEN )) = 0x000000C8;
	Memory( PWM.PWM_Module,( PWM_G0_LOAD_R + 4 * PWM_GEN))=(PWM.period);
	Memory( PWM.PWM_Module,( PWM_G0_CMPA_R +4 * PWM_OUTPUT_PIN+64*PWM_GEN))=((( 100 - PWM.Dutycycle )) * (Memory( PWM.PWM_Module, ( PWM_G0_LOAD_R + 4 * PWM_GEN )))) / 100;	
	Memory( PWM.PWM_Module,( PWM_G0_CTL + 4 * PWM_GEN))=1;
	Memory( PWM.PWM_Module,PWM_ENABLE_R ) = ( 1 << ( PWM_GEN + 4 * PWM_module ));
}
#if (De_init==STD_ON)
void Pwm_DeInit(Pwm_Config PWM)
{
	uint8_t PWM_module = PWM.channel/8; // which pwm module
	uint8_t PWM_GEN = PWM.channel/2;
	uint8_t PWM_OUTPUT_PIN = PWM.channel%2 ;
	//Pwm_ConfigType* ConfigPtr;
	//(*RCGC_PWM)=0;
	//ConfigPtr->IdleState=PWM_SET_OUT_IDLE_SID ;
	Memory(PWM.PWM_Module,(PWM_G0_CTL + 4*PWM_GEN))=0;
	Memory(PWM.PWM_Module,PWM_ENABLE_R)=0x0;
}
#endif
void Pwm_SetDutyCycle( Pwm_Config PWM)
{
	uint8_t PWM_module = PWM.channel/8; // which pwm module
	uint8_t PWM_GEN = PWM.channel/2;
	uint8_t PWM_OUTPUT_PIN = PWM.channel%2 ;
	Memory(PWM.PWM_Module,(PWM_G0_CMPA_R +4*PWM_OUTPUT_PIN+64*PWM_GEN))=(((100-PWM.Dutycycle))*(Memory(PWM.PWM_Module,(PWM_G0_LOAD_R + 4*PWM_GEN))))/100;	
}
void Pwm_SetPeriodAndDuty( Pwm_Config PWM)
{
	uint8_t PWM_module = PWM.channel/8; // which pwm module
	uint8_t PWM_GEN = PWM.channel/2;
	uint8_t PWM_OUTPUT_PIN = PWM.channel%2 ;
	Memory(PWM.PWM_Module,(PWM_G0_LOAD_R + 4*PWM_GEN))=PWM.period;
	Memory(PWM.PWM_Module,(PWM_G0_CMPA_R +4*PWM_OUTPUT_PIN+64*PWM_GEN))=(((100-PWM.Dutycycle))*(Memory(PWM.PWM_Module,(PWM_G0_LOAD_R + 4*PWM_GEN))))/100;	
}