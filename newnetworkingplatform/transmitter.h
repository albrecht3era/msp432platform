/*
 * transmitter.h
 *
 *  Created on: Oct 6, 2019
 *      Author: albrechter
 */

#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

#include <stdbool.h>

typedef enum{
    eTransmit__STARTED,
    eTransmit__PAUSED,
    eTransmit__DONE,
    eTransmit__WAITING,
    eTransmit__RESTART
}eTransmit_Status;

//#define ONE_TIME_LOAD

#define BITS_PER_CHAR 8U

bool load_buffer(volatile char* new_message, uint16_t size);
void start_transmit(void);
void pause_transmit(void);
void unpause_transmit(void);

#endif /* TRANSMITTER_H_ */
