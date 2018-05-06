/*
 * system.c
 *
 */ 

#include "stdint.h"
#include "system.h"

/**
 * @brief Sync registers
 * @return non zero on error
 */
inline int iosync(uint32_t mask, uint32_t adr){
	uint32_t timeout = IOSYNC_TIMEOUT;
	do{
        timeout--;
    }while( (timeout > 0u) && ((ioread32(adr) & mask) != 0u));
    return (timeout == 0u) ? 1 : 0;
 }

/**
 * @brief Read 8bit IO register
 */
inline uint8_t ioread8(uint32_t addr){
	return *(uint8_t *)addr;
}

/**
 * @brief Read 16bit IO register
 */
inline uint16_t ioread16(uint32_t addr){
	return *(uint16_t *)addr;
}

/**
 * @brief Read 32bit IO register
 */
inline uint32_t ioread32(uint32_t addr){
	return *(uint32_t *)addr;
}

/**
 * @brief Write 8bit IO register
 */
inline void iowrite8(uint8_t value, uint32_t addr){
	*(uint8_t *)addr = value;
}

/**
 * @brief Write 16bit IO register
 */
inline void iowrite16(uint16_t value, uint32_t addr){
	*(uint16_t *)addr = value;
}

/**
 * @brief Write 32bit IO register
 */
inline void iowrite32(uint32_t value, uint32_t addr) {
	*(uint32_t *)addr = value;
}