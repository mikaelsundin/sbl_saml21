/*
 * sbl.c
 *
 * Created: 2018-05-07 21:01:46
 *  Author: leaf
 */ 

#include <inttypes.h>
#include "sbl.h"

#define SBL_VERSION	(0x30u)
#define SBL_ACK		(0x79u)
#define SBL_NAK		(0x1Fu)

/* get: version + Supported commands */
/* gv:  version + readout protection(reserved 0x00) */
/* gid: device id 0x0400 */
const uint8_t sbl_info_get[15] = {SBL_ACK,11,SBL_VERSION,0x00,0x01,0x02,0x11,0x21,0x31,0x44,0x63,0x73,0x82,0x92,SBL_ACK};	
const uint8_t sbl_info_gv[5] = {SBL_ACK, SBL_VERSION, 0x00, 0x0,SBL_ACK};	
const uint8_t sbl_info_gid[5] = {SBL_ACK,0x01,0x04,0x00,SBL_ACK};			

static void sbl_command(uint8_t cmd);
static uint32_t sbl_rx_adr(void);

void sbl_init(void){
	sbl_hal_init();
}

inline void sbl_nak(){
	uint8_t val = SBL_NAK;
	sbl_hal_tx(&val, 1);
}

inline void sbl_ack(){
	uint8_t val = SBL_ACK;
	sbl_hal_tx(&val, 1);
}

void sbl_task(void){
	uint8_t rx[2];

	if(sbl_hal_rx(rx, 2) == 2){
		if( (rx[0] ^ rx[1]) == 0xff){
			sbl_command(rx[0]);
		}else{
			sbl_nak();
		}
	}
}


/**
 * @brief Read memory
 */
void sbl_command_rm(uint32_t adr){
	uint8_t rx[2];

	if(sbl_hal_rx(rx, 2) == 2){
		if(rx[0] ^ rx[1] == 0){
			uint8_t bfr[256];
			sbl_ack();

			/* output to memory */
		}else{
			sbl_nak();
		}
	}

}

/**
 * @brief Write memory
 */
void sbl_command_wm(uint32_t adr){

}

/**
 * @brief Execute program
 */
void sbl_command_go(uint32_t adr){
	sbl_ack();

	if(adr == 0){
		/* Reset MCU */
	}else{
		/* Start application */
	}
}

/**
 * @brief Extended erase memory (16bit index)
 * @note 0xFFFF : mass erase
 */
void sbl_command_eer(void){

}


void sbl_command(uint8_t cmd){
	
	switch(cmd){
	case 0x00: sbl_hal_tx(sbl_info_get, sizeof(sbl_info_get)); break;
	case 0x01: sbl_hal_tx(sbl_info_gv, sizeof(sbl_info_gv)); break;
	case 0x02: sbl_hal_tx(sbl_info_gid, sizeof(sbl_info_gid)); break;
	
	/* Memory operations */
	case 0x11: /* fall-through */ 
	case 0x21: /* fall-through */
	case 0x31:
	{
		sbl_ack();
		uint32_t adr = sbl_rx_adr();	/* get address */

		if(adr != SBL_ADR_INVALID){
			sbl_ack();	/* ack address */

			switch(cmd){
			case 0x11:sbl_command_rm(adr);break;
			case 0x21:sbl_command_go(adr);break;
			case 0x31:sbl_command_wm(adr);break;
			}
		}else{
			sbl_nak();					/* nack address */
		}
	}
	case 0x44: sbl_command_eer(); break; /* extended erase memory */
	default: sbl_nak(); break;			 /* unsupported commands */
	}
}




/* Receive single command/data */
/* uint16_t sbl_rx_u8(uint8_t *data){
	uint8_t chk;
	uint8_t len=0;

	len += sbl_hal_rx(data, 1);
	len += sbl_hal_rx(&chk, 1);



		
		if(rx[0] ^ rx[1] == 0xff){
			*data = rx[0];
		}
	}

 }
 */

 /* Receive 32bit address */
uint32_t sbl_rx_adr(void){
	uint32_t adr=SBL_ADR_INVALID;
	uint8_t rx[5];
	
	if(sbl_hal_rx(rx, 5) == 5){
		if(rx[0] ^ rx[1] ^ rx[2] ^ rx[3] ^ rx[4] == 0){
			adr =	(uint32_t)rx[0]<<24 |  
					(uint32_t)rx[1]<<16 |  
					(uint32_t)rx[2]<<8 |  
					(uint32_t)rx[3]<<0;
		}
	}

	/* TODO:Check if memory is within flash/ram */

	return adr;
}

/* Receive 16bit data address */
uint16_t sbl_rx_data16(uint16_t data[128]){

}

/* Receive 8bit data address */
uint16_t sbl_rx_data8(uint8_t data[256]){

}




 