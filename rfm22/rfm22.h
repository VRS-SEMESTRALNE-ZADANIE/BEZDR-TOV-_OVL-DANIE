/*
 * rfm22.h
 *
 *  Created on: Dec 16, 2024
 *      Author: mihal
 */

#ifndef RFM22_H_
#define RFM22_H_

#include "main.h"

void rfm22_tx_init(void);
void rfm22_send(uint8_t *data, uint8_t length);





#endif /* RFM22_H_ */
