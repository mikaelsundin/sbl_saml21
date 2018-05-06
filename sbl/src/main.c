/*
 * drivers.c
 *
 * Created: 2018-05-03 19:55:29
 * Author : leaf
 */ 

#include <stdint.h>
#include "saml21.h"
#include "nvmctrl.h"
#include "serial.h"

volatile uint32_t dummy=0u;
__IO uint32_t *pchctrl = (__IO uint32_t *)(GCLK+0x80);

int main(void){
	volatile uint32_t x = 64;

	/* Enable clock to USART1 */
	pchctrl[19] = 0x40u;	/* SERCOM1 clocked from Generator 0 */
    
	//nvmctrl_flash_write(0x2000, &x);
	//nvmctrl_flash_erase(0x2000);

	//serial_begin(SERCOM1, SERIAL_BAUD_115200_16MHZ, SERIAL_8E1, SERIAL_TX0_RX1);

    /* Replace with your application code */
    while (1){
		dummy++;
		//serial_write(SERCOM1, 0x42);

		//if(serial_read(SERCOM1) >= 0){
		//	dummy++;
		//}
    }
}
