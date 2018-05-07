/*
 * sbl.h
 *
 * Created: 2018-05-07 21:20:54
 *  Author: leaf
 */ 


#ifndef _SBL_H_
#define _SBL_H_

#include <stdint.h>

#define SBL_ADR_INVALID	(UINT32_MAX)

uint16_t sbl_hal_rx(uint8_t data[], uint32_t len);
void sbl_hal_tx(uint8_t data[], uint16_t len);
void sbl_hal_init(void);

void sbl_init(void);
void sbl_task(void);



#endif /* SBL_H_ */