/*
 * receiver.c
 *
 *  Created on: Oct 23, 2019
 *      Author: albrechter
 */

#include "receiver.h"
#include "message.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

volatile static bool receiving; /** receiving in progress or not **/
volatile static uint8_t receiving_storage[BUFFER_SIZE] = {}; /** rotating buffer storing a max of 256 bytes **/
volatile static uint8_t receive_buffer; /** buffer currently receiving **/
volatile static uint8_t buffer_bit_counter; /** This counts the current bit being entered. 1st bit always 0. **/
volatile static uint8_t current_index; /** The current byte being stored. **/
volatile static eReceiver_Status receiver_status; /** status of the receiver **/
volatile static eReceiver_Ignore_Status receiver_ignore_status; /** The status of whether an interrupt was ignored or not. **/
volatile static eBit_Received last_bit; /** This was the last bit recorded **/
volatile static eBit first_reception = eBit_FIRST;

/**
 * This method configures the receiver to be ready for receiving.
 * TODO configure for the collision bouncing in and out. Does random number have to be implemented?
 */
void configure_receiver(void){
    //incoming_header = {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY};
    receive_buffer = EMPTY;
    buffer_bit_counter = 1U;
    current_index = EMPTY;
    receiver_status = eReceiver_DONE;
    receiver_ignore_status = eReceiver_CONTINUE;
    last_bit = eBit_ZERO;

}

/**
 * This method starts a new receiving, and clears the buffer variables.
 */
void start_receiving(void){
    if(receiver_status != eReceiver_RUNNING) {
        receiver_status = eReceiver_RUNNING;
        receiver_ignore_status = eReceiver_CONTINUE;
    }
}

/**
 * If receiving was paused, this will continue it.
 */
void continue_receiving(void){
    if(receiver_status == eReceiver_PAUSED) {
        receiver_status = eReceiver_RUNNING;
    }
}

/**
 * This will pause receiving if collision is entered.
 */
void pause_receiving(void){
    receiver_status = eReceiver_PAUSED;
}

/**
 * If the GPIO interrupt is seen in the middle of the bit period, this is called.
 */
void receive_half_bit(void){
    receiver_ignore_status = eReceiver_IGNORED;
}

eReceiver_Ignore_Status get_receive_half_bit(void){
    return receiver_ignore_status;
}

/**
 * This records the next bit, and records it based on the previous bit and the GPIO Interrupt.
 */
void receive_new_bit(uint8_t new_bit){
    if(receiver_status == eReceiver_RUNNING) {
        //printf("Bit: %x\n", new_bit);
        if(buffer_bit_counter == LAST_BIT){
            receive_buffer |= new_bit;
            //printf("%x\n", receive_buffer);
            receiving_storage[current_index] = receive_buffer;
            ++current_index;
            if(current_index == BUFFER_SIZE){
                finish_receiving();
            }
            buffer_bit_counter = EMPTY;
            receive_buffer = EMPTY;
        } else {
            receive_buffer |= new_bit;
            receive_buffer = (receive_buffer << BIT_SHIFT);
            ++buffer_bit_counter;
        }
        receiver_ignore_status = eReceiver_CONTINUE;
        if(first_reception == eBit_FIRST){
            receive_buffer |= 1U;
            receive_buffer = (receive_buffer << BIT_SHIFT);
            ++buffer_bit_counter;
            first_reception = eBit_MANY;
        }
    }
}

/**
 * This finishes the receiving, closes the buffer, and ensures a newline is present to print.
 */
void finish_receiving(void){
//    if(receiver_status == eReceiver_RUNNING) {
        receiver_status = eReceiver_DONE;
        if(buffer_bit_counter != EMPTY){
            if(current_index < BUFFER_SIZE){
                receiving_storage[current_index] = receive_buffer;
                current_index++;
            }
        }
        if(current_index == BUFFER_SIZE){
            receiving_storage[BUFFER_SIZE-1] = '\0';
        } else {
            receiving_storage[current_index] = '\0';
        }
        buffer_bit_counter = 1U;
        receive_buffer = EMPTY;
        current_index = EMPTY;
        last_bit = eBit_ZERO;
        receiver_ignore_status = eReceiver_CONTINUE;
//    }
    if(receiving_storage[3] == SOURCE_ADDRESS) {
        printf("Received: Preamble: 0x%.2x Version: 0x%.2x Source: 0x%.2x Destination: 0x%.2x Length: 0x%.2x CRC: 0x%.2x Message: | ", receiving_storage[0], receiving_storage[1], receiving_storage[2], receiving_storage[3], receiving_storage[4], receiving_storage[5]);
        int i = 0;
        int length = receiving_storage[4];
        for(i = 0; i < length; i++){
            printf("%c", receiving_storage[6+i]);
        }
        printf(" | Trailer: 0x%.2x\n", receiving_storage[6 + length]);
    }
}

