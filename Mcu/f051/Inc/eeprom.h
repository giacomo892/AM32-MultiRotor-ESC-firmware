/*
 * bootloader.h
 *
 *  Created on: Mar. 25, 2020
 *      Author: Alka
 */
#include "main.h"
#include "eeprom_common.h"
#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_



#endif /* INC_BOOTLOADER_H_ */


void read_flash_bin(eeprom_t *data , uint32_t add ,int out_buff_len);
void save_flash_nolib(eeprom_t *data, int length, uint32_t add);
