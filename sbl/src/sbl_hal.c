/*
 * sbl_hal.c
 *
 * Created: 2018-05-07 21:21:48
 *  Author: leaf
 */ 

#include <inttypes.h>
#include "sbl.h"
#include "saml21.h"
#include "serial.h"

#define SBL_SERCOM	SERCOM5


void sbl_hal_init(void){
	serial_begin(SBL_SERCOM, SERIAL_BAUD_115200_4MHZ, SERIAL_8E1, SERIAL_TX2_RX3);

}

void sbl_hal_tx(uint8_t data[], uint16_t len){
	disable_serial_rx(SBL_SERCOM);

	for(uint16_t i=0;i<len;i++){
		serial_write(SBL_SERCOM, data[i]);
	}
	
	enable_serial_rx(SBL_SERCOM);
}


uint16_t sbl_hal_rx(uint8_t data[], uint32_t len){
	uint32_t received=0;

	//TODO:implement timeout
	do{
		if(serial_available(SBL_SERCOM) > 0){
			data[received++] = serial_read(SBL_SERCOM);
		}
	}while(received < len);

	return received;
}