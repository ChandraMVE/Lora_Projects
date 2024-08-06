/*
 * filter_hp_rst_on_int.h
 *
 *  Created on: Aug 2, 2024
 *      Author: ADMIN
 */

#ifndef FILTER_HP_RST_ON_INT_H_
#define FILTER_HP_RST_ON_INT_H_




int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
void tx_com(uint8_t *tx_buffer, uint16_t len);
void platform_delay(uint32_t ms);
void platform_init(void);
void lis2de12_filter_hp_rst_on_int(void);



#endif /* FILTER_HP_RST_ON_INT_H_ */


