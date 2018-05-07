/*
 * usart.c
 *
 * Minimal implementan for using only one sercom
 */ 

#include <stdint.h>
#include "system.h"
#include "saml21.h"
#include "serial.h"

/* all registers on usart */
#define USART_CTRLA			(0x00ul)
#define USART_CTRLB			(0x04ul)
#define USART_BAUD			(0x0Cul)
#define USART_RXPL			(0x0Eul)
#define USART_INTENCLR		(0x14ul)
#define USART_INTENSET		(0x16ul)
#define USART_INTFLAG		(0x18ul)
#define USART_STATUS		(0x1Aul)
#define USART_SYNCBUSY		(0x1Cul)
#define USART_DATA			(0x28ul)
#define USART_DBGCTRL		(0x30ul)

#define SYNCBUSY_RESET	(0x01ul)
#define SYNCBUSY_ENABLE	(0x02ul)
#define SYNCBUSY_CTRLB	(0x04ul)

/* Bits in registers */
#define CTRLA_RESET			(0x00000001ul)
#define CTRLA_ENABLE		(0x00000002ul)
#define CTRLA_INT_CLK		(0x00000004ul)
#define CTRLB_TXEN			(0x00010000ul)
#define CTRLB_RXEN			(0x00020000ul)

#define INTFLAG_TXC			(0x02u)
#define INTFLAG_RXC			(0x04u)
#define INTFLAG_DRE			(0x01u)

	
void serial_begin(uint32_t sercom, uint32_t baud, enum SERIAL_CONFIG config, enum SERIAL_MUX mux){
	uint32_t ctrla = (config & 0xFFFF0000ul) | mux | CTRLA_INT_CLK;
	uint32_t ctrlb = (config & 0x0000FFFFul) | CTRLB_TXEN | CTRLB_RXEN;
	
	/* perform reset */
	iowrite32(CTRLA_RESET, sercom + USART_CTRLA);
	iosync(SYNCBUSY_RESET, sercom + USART_SYNCBUSY);

	/* Write settings */
	iowrite32(ctrlb, sercom + USART_CTRLB);
	iowrite32(ctrla, sercom + USART_CTRLA);
	iowrite16(baud, sercom+USART_BAUD);
	iosync(SYNCBUSY_CTRLB, sercom + USART_SYNCBUSY);

	/* enable usart */
	iowrite32(ctrla | CTRLA_ENABLE, sercom+USART_CTRLA);
	iosync(SYNCBUSY_ENABLE, sercom + USART_SYNCBUSY);
}

/**
 * @brief send one byte payload
 */
void serial_write(uint32_t sercom, uint8_t data){
	while( (ioread8(sercom+USART_INTFLAG) & INTFLAG_DRE) == 0){}
	iowrite16(data, sercom+USART_DATA);
}

/**
 * @brief wait until all data is transmitted
 */
void serial_flush(uint32_t sercom){
	while( (ioread8(sercom+USART_INTFLAG) & INTFLAG_TXC) == 0){}
}

/**
 * @brief Disable serial RX
 */
void disable_serial_rx(uint32_t sercom){
	uint32_t ctrlb =  ioread32(sercom + USART_CTRLB);
	iowrite32(ctrlb & (uint32_t)(~CTRLB_RXEN), sercom + USART_CTRLB);
}

/**
 * @brief Enable serial RX
 */
void enable_serial_rx(uint32_t sercom){
	uint32_t ctrlb =  ioread32(sercom + USART_CTRLB);
	iowrite32(ctrlb | (uint32_t)(CTRLB_RXEN), sercom + USART_CTRLB);
}

/**
 * @brief get number of bytes available
 */
int serial_available(uint32_t sercom){
	return ((ioread8(sercom+USART_INTFLAG) & INTFLAG_RXC) != 0u) ? 1 : 0;
}

/**
 * @brief read serial port
 */
uint8_t serial_read(uint32_t sercom){
	return ioread16(sercom+USART_DATA);
}