#include "gpio.h"
#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100))

void GPIO_initPin(GPIO_Type *gpio, Pin pin, GPIO_config *config){
    gpio->LOCK   = UNLOCK;
    gpio->CR    |= pin;
    gpio->DEN    = (gpio->DEN & ~(pin)) | (pin & config->DIGITAL);
    gpio->DIR    = (gpio->DIR & ~(pin)) | (pin & config->DIR);
    gpio->AMSEL  = (gpio->AMSEL & ~(pin)) | (pin & config->ANALOG);
    gpio->AFSEL  = (gpio->AFSEL & ~(pin)) | (pin & config->AFSEL);
}

void GPIO_setPin(GPIO_Type *gpio, Pin pin, uint32_t val){
    gpio->DATA_Bits[pin] = val;
}

uint32_t GPIO_readPin(GPIO_Type *gpio,Pin pin){
    return gpio->DATA_Bits[pin] > 0 ? HIGH : LOW;
}

void GPIO_setPUR(GPIO_Type *gpio, Pin pin, uint32_t val){
    gpio->PUR = (gpio->PUR & ~(pin)) | ((uint8_t)pin & (uint8_t)val);
}

void GPIO_setPDR(GPIO_Type *gpio, Pin pin, uint32_t val){
    gpio->PDR = (gpio->PDR & ~(pin)) | ((uint8_t)pin & (uint8_t)val);
}

void GPIO_setODR(GPIO_Type *gpio, Pin pin, uint32_t val){
    gpio->ODR = (gpio->ODR & ~(pin)) | ((uint8_t)pin & (uint8_t)val);
}

void GPIO_setDR2R(GPIO_Type *gpio, Pin pin, uint32_t val){
    gpio->DR2R = (gpio->DR2R & ~(pin)) | ((uint8_t)pin & (uint8_t)val);
}

void GPIO_setDR4R(GPIO_Type *gpio, Pin pin, uint32_t val){
    gpio->DR4R = (gpio->DR4R & ~(pin)) | ((uint8_t)pin & (uint8_t)val);
}

void GPIO_setDR8R(GPIO_Type *gpio, Pin pin, uint32_t val){
    gpio->DR8R = (gpio->DR8R & ~(pin)) | ((uint8_t)pin & (uint8_t)val);
}

void 	GPIO_initPort(GPIO_Type *gpio, GPIO_config *config){
    GPIO_initPin(gpio, PORT, config);
}

void    GPIO_setPort(GPIO_Type *gpio, uint32_t val){
    gpio->DATA = val;
}

uint32_t GPIO_readPort(GPIO_Type *gpio){
    return gpio->DATA;
}

void 	GPIO_setPCTL(GPIO_Type *gpio, Pin pin, uint8_t func){
		uint32_t temp = gpio->PCTL & ~(0x0000000F << (Log(pin)*4));
		gpio->PCTL = temp | (func << (Log(pin)*4));
}
