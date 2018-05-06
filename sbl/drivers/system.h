/*
 * system.h
 *
 * Created: 2018-05-05 01:19:22
 *  Author: leaf
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_

//Maximum to wait for SAM L21 iosync 
#define IOSYNC_TIMEOUT  10000


#define __IO volatile
#define __PACKED	__attribute__((packed))
#define __ALIGN4	__attribute__((aligned(4)))
#define __UNUSED	__attribute__((__unused__))



int iosync(uint32_t mask, uint32_t adr);

uint8_t ioread8(uint32_t addr);
uint16_t ioread16(uint32_t addr);
uint32_t ioread32(uint32_t addr);

void iowrite8(uint8_t value, uint32_t addr);
void iowrite16(uint16_t value, uint32_t addr);
void iowrite32(uint32_t value, uint32_t addr);



#endif /* SYSTEM_H_ */