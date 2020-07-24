#include "PWM.h"
Pwm_Config pwm_config = {
	PWM0_PB6,
	FREQUANCY_1KHZ,
	60,
  PWM_HIGH,
	sys_clk_no_div,
	PWM_0
};