#include "pwm.h"
void Pwm_Init( const Pwm_ConfigType* ConfigPtr )
{
	if(ConfigPtr->SysClkDiv==sys_clk_no_div)
	{
		(* RCC_PWM)&=SYSCTL_RCC_NOCLCKDIV ;	
	}
	else{
	(*RCC_PWM)=((ConfigPtr->SysClkDiv)<<17)|(1<<20);
	}
	uint8_t PWM_module =((ConfigPtr->channel)/8); // which pwm module
	uint8_t PWM_GEN = ((ConfigPtr->channel)/2);
	if(	PWM_GEN > 3)
		PWM_GEN -= 4;
	uint8_t PWM_OUTPUT_PIN =((ConfigPtr->channel)%2);
	(*RCGC_PWM)|=(1<<PWM_module);
	Memory(ConfigPtr->PWM_MODULE,(PWM_G0_CTL + 4*PWM_GEN))=0;
	if(ConfigPtr->polarity==PWM_HIGH)
	Memory(ConfigPtr->PWM_MODULE,(PWM_G0_GENPINA_R +4*PWM_OUTPUT_PIN+64*PWM_GEN)) =0x0000008C;
	else if(ConfigPtr->polarity==PWM_LOW)
			Memory(ConfigPtr->PWM_MODULE,(PWM_G0_GENPINA_R +4*PWM_OUTPUT_PIN+64*PWM_GEN)) =0x000000C8;
	Memory(ConfigPtr->PWM_MODULE,(PWM_G0_LOAD_R + 4*PWM_GEN))=1/(ConfigPtr->period);
	Memory(ConfigPtr->PWM_MODULE,(PWM_G0_CMPA_R +4*PWM_OUTPUT_PIN+64*PWM_GEN))=(((100-ConfigPtr->Dutycycle))*(Memory(ConfigPtr->PWM_MODULE,(PWM_G0_LOAD_R + 4*PWM_GEN))))/100;	
		Memory(ConfigPtr->PWM_MODULE,(PWM_G0_CTL + 4*PWM_GEN))=1;
	Memory(ConfigPtr->PWM_MODULE,PWM_ENABLE_R)=(1<<(PWM_GEN+4*PWM_module));
}