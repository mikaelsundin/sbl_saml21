/*
 * pin.h
 *
 * Created: 2018-05-06 18:16:02
 *  Author: leaf
 */ 


#ifndef _GPIO_H_
#define _GPIO_H_

enum gpio_mux{
	GPIO_MUX_A,
	GPIO_MUX_B,
	GPIO_MUX_C,
	GPIO_MUX_D,
	GPIO_MUX_E,
	GPIO_MUX_F,
	GPIO_MUX_G,
	GPIO_MUX_H,
	GPIO_MUX_I,
	GPIO_MUX_NONE
};

enum gpio_direction{
	/* Arduino numbering */
	GPIO_INPUT			= 0x00,
	GPIO_OUTPUT			= 0x01,
	GPIO_INPUT_PULLUP	= 0x02,
	GPIO_ANALOG			= 0x03, /* Turn of digital input */
};

enum gpio_names{
	PA00 = 0,
	PA01,
	PA02,
	PA03,
	PA04,
	PA05,
	PA06,
	PA07,

	PA08,
	PA09,
	PA10,
	PA11,
	RESERVED_PA12,	//Not available on SAM21E
	RESERVED_PA13,	//Not available on SAM21E
	PA14,
	PA15,

	PA16,
	PA17,
	PA18,
	PA19,
	RESERVED_PA20,	//Not available on SAM21E
	RESERVED_PA21,	//Not available on SAM21E
	PA22,
	PA23,

	PA24,
	PA25,
	RESERVED_PA26,	//Not available on SAM21E
	PA27,
	RESERVED_PA28,	//Not available on SAM21E
	RESERVED_PA29,	//Not available on SAM21E
	PA30,
	PA31,

	PB00,
	PB01,
};

void gpio_setup(enum gpio_names pin, enum gpio_direction dir, enum gpio_mux mux);
void gpio_set(enum gpio_names pin);
void gpio_clr(enum gpio_names pin);

void gpio_write(enum gpio_names pin, uint32_t val);
uint32_t gpio_read(enum gpio_names pin);

#endif /* PIN_H_ */