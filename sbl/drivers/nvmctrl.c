
#include <stdint.h>
#include "saml21.h"
#include "system.h"
#include "nvmctrl.h"

/* Hardcoded values for SAM L21 */
#define NVMCTRL_PAGE_SIZE		(64u)
#define NVMCTRL_ROW_SIZE		(256u)

/* Bits in registers */
#define CTRLB_CACHEDIS	        (0x00040000ul)
#define CTRLB_MANW	            (0x00000080ul)

#define STATUS_PROGE	        (0x04u)
#define STATUS_NVME	            (0x10u)
#define STATUS_ERROR_MASK       (0x1Cu)

#define INTFLAG_IDLE	0x01
#define INTFLAG_ERROR	0x02

/* register offset in NVMCTRL */
#define NVMCTRL_CTRLA_U16		(0x00ul)
#define NVMCTRL_CTRLB_U32		(0x04ul)
#define NVMCTRL_PARM_U32		(0x08ul)
#define NVMCTRL_INTENCLR_U8		(0x0Cul)
#define NVMCTRL_INTENSET_U8		(0x10ul)
#define NVMCTRL_INTFLAG_U8		(0x14ul)
#define NVMCTRL_STATUS_U16		(0x18ul)
#define NVMCTRL_ADDR_U32		(0x1Cul)
#define NVMCTRL_LOCK_U16		(0x20ul)


static void nvmctrl_wait(void);

/**
 * @brief Wait until nvmctrl is ready
 */
inline static void nvmctrl_wait(void){
    while((ioread8(NVMCTRL + NVMCTRL_INTFLAG_U8) & INTFLAG_IDLE) == 0){}
}

/**
 * @brief execute nvmctrl action
 */
int nvmctrl_exec(enum nvm_cmd cmd, uint32_t addr){
    uint32_t ctrlb = ioread32(NVMCTRL + NVMCTRL_CTRLB_U32);

    /* Clear status and int flags */
	iowrite16(NVMCTRL + NVMCTRL_STATUS_U16, 0x1Eu);
    iowrite8(NVMCTRL + NVMCTRL_INTFLAG_U8, 0x02u);
    nvmctrl_wait();

    /* Possible EERATA bug? */
    iowrite32(NVMCTRL + NVMCTRL_CTRLB_U32, ctrlb | NVMCTRL_CTRLB_CACHEDIS);
    
    /* Address is 16bit based */
    iowrite32(NVMCTRL + NVMCTRL_ADDR_U32, addr / 2u)

    /* execute command */
    iowrite16(NVMCTRL + NVMCTRL_CTRLA_U16, (cmd | 0xA500U))
    nvmctrl_wait();

    /* Restore ctrlb */
    iowrite32(NVMCTRL + NVMCTRL_CTRLB_U32, ctrlb);

    /* Return execute status */
    return (ioread16(NVMCTRL + NVMCTRL_STATUS_U16) & STATUS_ERROR_MASK);
}

/**
 * @brief Return main memory size
 */
uint32_t nvmctrl_main_flash_size(void){
    return (ioread32(NVMCTRL + NVMCTRL_PARM_U32) & 0xFFFFu) * NVMCTRL_PAGE_SIZE
}

/**
 * @brief Return EE memory size
 */
uint32_t nvmctrl_ee_flash_size(void){
    return (FLASH_SIZE - nvmctrl_main_flash_size());
}

/**
 * @brief flash row Erase in main memory
 */
int nvmctrl_flash_erase(uint32_t address){
	return nvmctrl_exec(NVM_CMD_ERASE_MAIN, address);
}

/**
 * @brief flash row Erase in ee memory
 */
int nvmctrl_ee_erase(uint32_t address){
	return nvmctrl_exec(NVM_CMD_ERASE_EE, address);
}

/**
 * @brief Write one whole page
 * @param address address to write to, must be 64byte aligned.
 * */
int nvmctrl_cmd_write(enum nvm_cmd cmd, uint32_t adr, uint8_t data[64]){
	__IO uint16_t* mem = (__IO uint16_t*)FLASH_ADDR;
	int status = (adr % 64) ? 0 : 1; 				/* Be sure adr is 64byte aligned */

	/* clear NVM buffer on no error */
	if(status == 0){
		status = nvmctrl_exec(NVM_CMD_BUFFER_CLEAR, adr);
	}

	/* Write NVM to flash on no error */
	if(status == 0){
		/* copy to memory */
		for(uint32_t i=0u; i<64u; i+=2u){
			mem[(adr+i)/2u] = (data[i]) + (data[i+1]*256);
		}

		status = nvmctrl_exec(cmd, adr);
	}

	return status;
}

void get_nvmctrl_serial_number(uint8_t serial[16]){
	//Word 0: 0x0080A00C
	//Word 1: 0x0080A040
	//Word 2: 0x0080A044
	//Word 3: 0x0080A048


}

/**
 * @brief Write to main flash - address must be 64byte aligned.
 */
int nvmctrl_flash_write(uint32_t adr, uint8_t data[64]){
	int status = -1;

	/* Check if address is within flash area, flash always start at 0x00 at SAM L21 */
	/* Ignore if portion is dedicated to ee */
	if( adr < FLASH_SIZE){ 
		status = nvmctrl_cmd_write(NVM_CMD_WRITE_MAIN, adr, data);
	}

	return status;
}

/**
 * @brief Write to ee flash - address must be 64byte aligned.
 */
int nvmctrl_ee_write(uint32_t adr, uint8_t data[64]){
    uint32_t start = 0x00400000ul;
    uint32_t end  = 0x00400000ul + nvmctrl_ee_flash_size();
	int status = -1;

	/* Check valid address for ee area */
	if( (adr >= start) && (adr < end) ){
		status = nvmctrl_cmd_write(NVM_CMD_WRITE_EE, adr, data);
	}

	return status;
}



