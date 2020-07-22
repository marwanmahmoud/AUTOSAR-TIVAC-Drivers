#include "PWM(1).h"
void delayMs(int n)
{    int i, j;    for(i = 0 ; i < n; i++)        for(j = 0; j < 3180; j++)            {}  /* do nothing for 1 ms */}
uint32_t Port;
uint8_t Pin_;
Pwm_Config config = {
	PWM0_PB6,
	FREQUANCY_1KHZ,
  90,
  PWM_HIGH,
	sys_clk_no_div,
	PWM_0
};
void setPortPin(uint8_t Channel){
	switch (Channel)
	{
		case PWM0_PB6 :
			Port = PORTB ; 
			Pin_ = P6;
			break;
		case PWM0_PB7 :
			Port = PORTB ; 
			Pin_  = P7;
			break;
		case PWM0_PB4 :
			Port = PORTB ; 
			Pin_ = P4;
			break;
		case PWM0_PB5 :
			Port = PORTB ; 
			Pin_ = P5;
			break;
		case PWM0_PE4 :
			Port = PORTE; 
			Pin_  = P4;
			break;
		case PWM0_PE5 :
			Port = PORTE; 
			Pin_  = P5;
			break; 
		case PWM0_PC4 :
			Port = PORTC; 
			Pin_  = P4;
			break;
		case PWM0_PC5 :
			Port = PORTC; 
			Pin_  = P5;
			break;
    // PWM MODULE 1
		case PWM1_PD0 :
			Port = PORTD; 
			Pin_  = P0;
			break;
		case PWM1_PD1 :
			Port = PORTD; 
			Pin_ = P1;
			break;
		case PWM1_PA6 :
			Port = PORTA; 
			Pin_  = P6;
			break;
		case PWM1_PA7 :
			Port = PORTA; 
		Pin_  = P7;
			break;
		case PWM1_PF0 :
			Port = PORTF; 
		Pin_  = P0;
			break;
		case PWM1_PF1 :
			Port = PORTF; 
			Pin_  = P1;
			break;
		case PWM1_PF2 :
			Port = PORTF; 
			Pin_  = P2;
			break;
		case PWM1_PF3 :
			Port = PORTF; 
			Pin_  = P3;
			break;
	}
}
void Pwm_Init(Pwm_Config PWM )
{
	setPortPin(PWM.Pwm_Channel);
	uint8_t portNum = (Port % GPIOA_BASE ) / (0x1000);
	switch(Port)
	{
		case PORTE :
			portNum = 4;
			break;
		case PORTF :
			portNum = 5;
			break;
	}
	//uint8_t portNum =5;
	uint8_t PWM_module = PWM.Pwm_Channel/8; // which pwm module
	uint8_t PWM_GEN = PWM.Pwm_Channel/2;
	uint8_t PWM_OUTPUT_PIN = PWM.Pwm_Channel%2 ;
	
	if(	PWM_GEN > 3)
		PWM_GEN -= 4;
	
	if(PWM.SysClkDiv==sys_clk_no_div)
		SYSCTL_RCC_R &= ~(1<<20) ;	
	else
		SYSCTL_RCC_R = (PWM.SysClkDiv << 17)|(1<<20);
	SYSCTL_RCGCPWM_R |=(1<<PWM_module);
	while(!(SYSCTL_PRPWM_R & (1<<PWM_module)));
	SYSCTRL_initGPIO(SYSCTRL_GPIOB);
	GPIO_initPin(GPIOB, PIN6, GPIO_CONF_PREPH);
	GPIO_setPCTL(GPIOB, PIN6, 4);
	Memory(PWM.PWM_Module,(PWM_G0_CTL + 4*PWM_GEN))=0;
	if(PWM.polarity==PWM_HIGH)
		Memory(PWM.PWM_Module,(PWM_G0_GENPINA_R +4*PWM_OUTPUT_PIN+64*PWM_GEN)) =0x0000008C;
	else if(PWM.polarity==PWM_LOW)
		Memory(PWM.PWM_Module,(PWM_G0_GENPINA_R +4*PWM_OUTPUT_PIN+64*PWM_GEN)) =0x000000C8;
	Memory(PWM.PWM_Module,(PWM_G0_LOAD_R + 4*PWM_GEN))=(PWM.period);
	Memory(PWM.PWM_Module,(PWM_G0_CMPA_R +4*PWM_OUTPUT_PIN+64*PWM_GEN))=(((100-PWM.Dutycycle))*(Memory(PWM.PWM_Module,(PWM_G0_LOAD_R + 4*PWM_GEN))))/100;	
	Memory(PWM.PWM_Module,(PWM_G0_CTL + 4*PWM_GEN))=1;
	Memory(PWM.PWM_Module,PWM_ENABLE_R)=(1<<(PWM_GEN+4*PWM_module));
}
#if (De_init==STD_ON)
void Pwm_DeInit(void)
{
	uint8_t PWM_module = config.Pwm_Channel/8; // which pwm module
	uint8_t PWM_GEN = config.Pwm_Channel/2;
	uint8_t PWM_OUTPUT_PIN = config.Pwm_Channel%2 ;
	//Pwm_ConfigType* ConfigPtr;
//	(*RCGC_PWM)=0;
	//ConfigPtr->IdleState=PWM_SET_OUT_IDLE_SID ;
	Memory(config.PWM_Module,(PWM_G0_CTL + 4*PWM_GEN))=0;
	Memory(config.PWM_Module,PWM_ENABLE_R)=0x0;
}
#endif
void Pwm_SetDutyCycle( Pwm_ChannelType ChannelNumber, uint16_t DutyCycle )
{
	uint8_t PWM_module = ChannelNumber/8; // which pwm module
	uint8_t PWM_GEN = ChannelNumber/2;
	uint8_t PWM_OUTPUT_PIN = ChannelNumber%2 ;
	Memory(config.PWM_Module,(PWM_G0_CMPA_R +4*PWM_OUTPUT_PIN+64*PWM_GEN))=(((100-DutyCycle))*(Memory(config.PWM_Module,(PWM_G0_LOAD_R + 4*PWM_GEN))))/100;	
}
void Pwm_SetPeriodAndDuty( Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16_t DutyCycle )
{
	uint8_t PWM_module = ChannelNumber/8; // which pwm module
	uint8_t PWM_GEN = ChannelNumber/2;
	uint8_t PWM_OUTPUT_PIN = ChannelNumber%2 ;
	Memory(config.PWM_Module,(PWM_G0_LOAD_R + 4*PWM_GEN))=Period;
	Memory(config.PWM_Module,(PWM_G0_CMPA_R +4*PWM_OUTPUT_PIN+64*PWM_GEN))=(((100-DutyCycle))*(Memory(config.PWM_Module,(PWM_G0_LOAD_R + 4*PWM_GEN))))/100;	
}
int main ()
{
	Pwm_Init(config);
	delayMs(1000);
	//Pwm_DeInit();
	//Pwm_SetDutyCycle(PWM0_PB6,10);
	//Pwm_SetPeriodAndDuty(PWM0_PB6,10000,10);
}
//  Memory(Port,GPIO_CR_OFFSET)  |= (1<< Pin) ;
//	Memory(Port,GPIO_DEN_OFFEST) |= (1<< Pin) ;
//	Memory(Port,GPIO_AMSEL_OFFEST) &= ~(1<<Pin)   ;
//	Memory(Port,GPIO_AFSEL_OFFEST) |= (1<<Pin)  ;
//	Memory(Port,GPIO_PCTL_OFFSET) |= (5<<(4*Pin));
//	Memory(PWM.PWM_Module,PWM_G0_CTL + 4*PWM_GEN ) = 0;