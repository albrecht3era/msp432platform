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

typedef enum{
    eReceiver_DONE,
    eReceiver_READY,
    eReceiver_PAUSED,
    eReceiver_RUNNING
}eReceiver_Status;

typedef enum{
    eReceiver_IGNORED,
    eReceiver_CONTINUE
}eReceiver_Ignore_Status;

typedef enum{
    eBit_ZERO=0x0U,
    eBit_ONE=0x1U
}eBit_Received;

typedef enum{
    eBit_FIRST,
    eBit_MANY
}eBit;

void start_receiving(void);
void pause_receiving(void);
void continue_receiving(void);
void finish_receiving(void);
void receive_half_bit(void);
void receive_new_bit(uint8_t new_bit);
void configure_receiver(void);
eReceiver_Ignore_Status get_receive_half_bit(void);

#endif /* RECEIVER_H_ */
