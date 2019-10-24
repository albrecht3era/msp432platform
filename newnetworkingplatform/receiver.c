/*
 * receiver.c
 *
 *  Created on: Oct 23, 2019
 *      Author: albrechter
 */

#include "receiver.h"
#include <stdint.h>
#include <stdbool.h>

volatile static bool receiving; /** receiving in progress or not **/
volatile static uint8_t receiving_storage[BUFFER_SIZE] = {}; /** rotating buffer storing a max of 256 bytes **/
volatile static uint8_t receive_buffer; /** buffer currently receiving **/
volatile static uint8_t buffer_bit_counter;
volatile static uint8_t current_index;

void configure_receiver(void){
    //incoming_header = {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY};
    receiving = false;
    receive_buffer = EMPTY;
    buffer_bit_counter = EMPTY;
    current_index = EMPTY;
}

void start_receiving(void){
    receiving = true;
    buffer_bit_counter = EMPTY;
    receive_buffer = EMPTY;
    current_index = EMPTY;
}

void receive_new_bit(uint8_t newbit){
    if(buffer_bit_counter == LAST_BIT){
        receive_buffer |= newbit;
        receiving_storage[current_index] = receive_buffer;
        current_index++;
        buffer_bit_counter = EMPTY;
        receive_buffer = EMPTY;
    } else {
        receive_buffer |= newbit;
        receive_buffer = (receive_buffer << BIT_SHIFT);
        buffer_bit_counter++;
    }
}

