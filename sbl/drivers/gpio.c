/*
 * pin.c
 *
 * Created: 2018-05-06 18:15:54
 *  Author: leaf
 */ 

#include <stdint.h>
#include "saml21.h"
#include "system.h"
#include "gpio.h"

#define PORT0	(PORT)
#define PORT1	(PORT+0x80u)

/* Registers */
#define DIRCLR		(0x04u)
#define DIRSET		(0x08u)
#define OUTCLR		(0x14u)
#define OUTSET		(0x18u)
#define OUTTGL		(0x1Cu)
#define WRCONFIG	(0x28u)

union gpio_wrconfig{
	struct{
		uint32_t pinmask:16;
		uint32_t pmuxen:1;
		uint32_t inen:1;
		uint32_t pullen:1;
		uint32_t :3;
		uint32_t drvstr:1;
		uint32_t :1;
		uint32_t pmux:4;
		uint32_t wrpmux:1;
		uint32_t :1;
		uint32_t wrpincfg:1;
		uint32_t hwsel:1;
	};
	uint32_t u32;
};

void gpio_setup(enum gpio_names pin, enum gpio_direction dir, enum gpio_mux mux){
	union gpio_wrconfig wrconfig = {.u32 = 0u};
	uint32_t index = pin % 32;
	uint32_t base = (pin < 32u) ? PORT0 : PORT1;

	/* create config */
	wrconfig.drvstr = 1;
	wrconfig.wrpincfg = 1;
	wrconfig.wrpmux = 1;
	wrconfig.inen = (dir != GPIO_ANALOG) ? 1 : 0;
	wrconfig.hwsel = (index & 0x10) ? 1 : 0;
	wrconfig.pinmask = 1 << (index % 16);
	wrconfig.pmux =	  (mux != GPIO_MUX_NONE) ? mux : 0;
	wrconfig.pmuxen = (mux != GPIO_MUX_NONE) ? 1 : 0;
	wrconfig.pullen = (dir == GPIO_INPUT_PULLUP) ? 1 : 0;

	/* Configure GPIO */
	iowrite32(wrconfig.u32, base + WRCONFIG);

	/* Set direction */
	if(dir == GPIO_OUTPUT){
		iowrite32(1u<<index, base + DIRSET);
	}else{
		iowrite32(1u<<index, base + DIRCLR);
	}


}

void gpio_set(enum gpio_names pin){
	uint32_t index = pin % 32;
	uint32_t base = (pin < 32u) ? PORT0 : PORT1;

	iowrite32(1u<<index, base + OUTSET);
}

void gpio_clr(enum gpio_names pin){
	uint32_t index = pin % 32;
	uint32_t base = (pin < 32u) ? PORT0 : PORT1;

	iowrite32(1u<<index, base + OUTCLR);
}

