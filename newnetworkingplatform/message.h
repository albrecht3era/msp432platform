/*
 * message.h
 *
 *  Created on: Nov 11, 2019
 *      Author: albrechter
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <stdint.h>

#define PREAMBLE 0x55
#define VERSION 0x1
#define CRC 0x0
#define SOURCE_ADDRESS 0xA3U
#define DESTINATION_ADDRESS 0xA3U
#define TRAILER 0x0

#define PREAMBLE_INDEX 0U
#define VERSION_INDEX 1U
#define SOURCE_INDEX 2U
#define DESTINATION_INDEX 3U
#define LENGTH_INDEX 4U
#define CRC_INDEX 5U

#define MESSAGE_HEADER_SIZE 6U

typedef struct{
    uint8_t preamble;
    uint8_t version;
    uint8_t source;
    uint8_t destination;
    uint8_t length;
    uint8_t crc;
}message;

void message_setup(message* new_message, uint8_t* message_buffer, uint8_t length);


#endif /* MESSAGE_H_ */
