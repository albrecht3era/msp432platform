/*
 * receiver.h
 *
 *  Created on: Oct 23, 2019
 *      Author: albrechter
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 255U
#define BIT_SHIFT 1U
#define LAST_BIT 7U
#define EMPTY 0U

typedef struct{
    uint8_t preamble;
    uint8_t version;
    uint8_t source;
    uint8_t destination;
    uint8_t length;
    uint8_t crc_flag;
}header;

void start_receiving(void);
uint16_t calculate_crc(void);
void receive_new_bit(uint8_t newbit);
void configure_receiver(void);

#endif /* RECEIVER_H_ */
