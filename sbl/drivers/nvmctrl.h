#ifndef _NVMCTRL_H_
#define _NVMCTRL_H_

#include <stdint.h>
#include "system.h"


enum nvm_cmd{
	NVM_CMD_ERASE_MAIN		= 0x02U,
	NVM_CMD_WRITE_MAIN		= 0x04U,

	NVM_CMD_ERASE_AUX		= 0x05U,
	NVM_CMD_WRITE_AUX		= 0x06U,

	NVM_CMD_ERASE_EE		= 0x1AU,
	NVM_CMD_WRITE_EE		= 0x1CU,

	NVM_CMD_LOCK_REGION		= 0x40U,
	NVM_CMD_UNLOCK_REGION	= 0x41U,

	NVM_CMD_ENTER_POWERDOWN	= 0x42U,
	NVM_CMD_EXIT_POWERDOWN	= 0x43U,

	NVM_CMD_BUFFER_CLEAR	= 0x44U,
	NVM_CMD_SET_SECURITY	= 0x45U,
	NVM_CMD_INVALIDATE		= 0x46U
};

int nvmctrl_flash_erase(uint32_t address);
int nvmctrl_ee_erase(uint32_t address);

int nvmctrl_flash_write(uint32_t adr, uint8_t data[64]);
int nvmctrl_ee_write(uint32_t adr, uint8_t data[64]);


#endif
