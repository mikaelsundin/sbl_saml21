/*
 * drivers.c
 *
 * Created: 2018-05-03 19:55:29
 * Author : leaf
 */ 

#include <stdint.h>
#include <stddef.h>

#include "saml21.h"
#include "nvmctrl.h"
#include "serial.h"
#include "gpio.h"

volatile uint32_t dummy=0u;
__IO uint32_t *pchctrl = (__IO uint32_t *)(GCLK+0x80);

/* simple memcpy implementation */
void memcpy(void *dest, void *src, size_t n){
	uint8_t *csrc = (uint8_t *)src;
	uint8_t *cdest = (uint8_t *)dest;

	for (int i=0; i<n; i++){
		cdest[i] = csrc[i];
	}	
}

/* Simple memset implementation */
void *memset(void *bfr, int c, int len){
	uint8_t *ptr = bfr;

	for(int i=0;i<len;i++){
		*ptr++ = (uint8_t)c;
	}

	return bfr;
}


int main(void){
	volatile int y;
	volatile uint8_t x[64] = {1,2,3,4};

	/* Enable clock to USART1 */
	pchctrl[19] = 0x40u;	/* SERCOM1 clocked from Generator 0 */
	pchctrl[24] = 0x40u;	/* SERCOM5 clocked from Generator 0 */

	gpio_setup(PB00, GPIO_OUTPUT, GPIO_MUX_D);
	gpio_setup(PB01, GPIO_INPUT_PULLUP, GPIO_MUX_D);

	//nvmctrl_flash_write(0x1000, x);
	//nvmctrl_flash_erase(0x1000);

	serial_begin(SERCOM5, SERIAL_BAUD_115200_4MHZ, SERIAL_8E1, SERIAL_TX2_RX3);

    /* Replace with your application code */
    while (1){
		y = serial_read(SERCOM5);
		if(y >= 0){
			dummy++;
			serial_write(SERCOM5, y);
		}
    }
}
