/*
 * usart.h
 *
 * Created: 2018-05-05 09:46:25
 *  Author: leaf
 */ 


#ifndef USART_H_
#define USART_H_

enum SERIAL_CONFIG{
	
	SERIAL_8N1		= 0x40000000ul,
	SERIAL_8E1		= 0x41000000ul,
	SERIAL_8O1		= 0x41002000ul,  

	SERIAL_8N1_MSB	= 0x00000000ul,
	SERIAL_8E1_MSB	= 0x01000000ul,
	SERIAL_8O1_MSB	= 0x01002000ul,

};

enum SERIAL_MUX{
	SERIAL_LOOPBACK	= (0x00000000ul),
	SERIAL_TX0_RX1	= (0x00100000ul),
	SERIAL_TX0_RX2	= (0x00200000ul),	
	SERIAL_TX0_RX3	= (0x00300000ul),

	SERIAL_TX2_RX0	= (0x00010000ul),
	SERIAL_TX2_RX1	= (0x00110000ul),
	SERIAL_TX2_RX3	= (0x00310000ul),

};

/* Precalculated baudrates, based on 16x oversample */
/* BAUD = 65536 * (1 - oversample*(Fbaud/freq))		*/
#define SERIAL_BAUD_115200_16MHZ	(57986u)
#define SERIAL_BAUD_57600_16MHZ		(61671u)
#define SERIAL_BAUD_19200_16MHZ		(64278u)

void serial_begin(uint32_t sercom, uint32_t baud, enum SERIAL_CONFIG config, enum SERIAL_MUX mux);
void serial_write(uint32_t sercom, uint8_t ch);
int serial_read(uint32_t sercom);



#endif /* USART_H_ */