#ifndef _GPIO_DRIVER_H
#define _GPIO_DRIVER_H

#include "common.h"

#define UNLOCK					0x4C4F434B

#define I2C_F					0x03
#define UART_F					0x02

typedef enum PinDir{
	INPUT		 	= 0x00000000,
	OUTPUT		 	= 0x000000FF,
} PinDir;

typedef enum InterruptEvent{
	RISING,
	FALLING,
	BOTH,
} InterruptEvent;

typedef struct{
    uint32_t             DIGITAL;       // Digital enable     (DEN)
    uint32_t             ANALOG;        // Analog mode select (AMSEL)
    uint32_t             DIR;           // Direction          (DIR)
    uint32_t             AFSEL;         // Alternative Function select
} GPIO_config;

typedef struct{
    GPIO_Type   *port;
    Pin         pin;
} GPIO_Pin;

#define GPIO_CONF_DO        &((GPIO_config){HIGH, LOW, OUTPUT, LOW}) // DIGITAL/OUTPUT
#define GPIO_CONF_DI        &((GPIO_config){HIGH, LOW, INPUT, LOW})  // DIGITAL/INPUT
#define GPIO_CONF_AN        &((GPIO_config){LOW, HIGH, INPUT, LOW})  // Analog
#define GPIO_CONF_PREPH     &((GPIO_config){HIGH, LOW, INPUT, HIGH}) // Prepheral


#define RED_LED             PIN1                                 
#define BLUE_LED            PIN2
#define GREEN_LED           PIN3
#define SW1                 PIN4
#define SW2                 PIN0


void 	 GPIO_initPin(GPIO_Type *gpio, Pin pin, GPIO_config *config);
void 	 GPIO_setPin(GPIO_Type *gpio, Pin pin, uint32_t val);
uint32_t GPIO_readPin(GPIO_Type *gpio,Pin pin);

void 	 GPIO_initPort(GPIO_Type *gpio, GPIO_config *config);
void     GPIO_setPort(GPIO_Type *gpio, uint32_t val);
uint32_t GPIO_readPort(GPIO_Type *gpio);

void 	 GPIO_setPUR(GPIO_Type *gpio, Pin pin, uint32_t val);
void 	 GPIO_setPDR(GPIO_Type *gpio, Pin pin, uint32_t val);
void 	 GPIO_setODR(GPIO_Type *gpio, Pin pin, uint32_t val);
void 	 GPIO_setDR2R(GPIO_Type *gpio, Pin pin, uint32_t val);
void 	 GPIO_setDR4R(GPIO_Type *gpio, Pin pin, uint32_t val);
void 	 GPIO_setDR8R(GPIO_Type *gpio, Pin pin, uint32_t val);

void   	 GPIO_initInterrupt(GPIO_Type *gpio, Pin pin, InterruptEvent ev, void (*callback)(void));

void 	 GPIO_setPCTL(GPIO_Type *gpio, Pin pin, uint8_t func);


#endif
