/*
 * message.c
 *
 *  Created on: Nov 11, 2019
 *      Author: albrechter
 */

#include <message.h>
#include <string.h>
#include <stdio.h>

/**
 * This method sets up a message with correct information to be sent.
 */
void message_setup(message* new_message, uint8_t* message_buffer, uint8_t length){
    new_message->preamble = (uint8_t) PREAMBLE;
    new_message->source = (uint8_t) SOURCE_ADDRESS;
    new_message->destination = (uint8_t) DESTINATION_ADDRESS;
    new_message->crc = (uint8_t) CRC;
    new_message->version = (uint8_t) VERSION;
    new_message->length = length;
    memcpy(message_buffer, (uint8_t*) new_message, MESSAGE_HEADER_SIZE);
    message_buffer[MESSAGE_HEADER_SIZE + length] = (uint8_t) TRAILER;
    message_buffer[MESSAGE_HEADER_SIZE + length + 1U] = '\n';
}
