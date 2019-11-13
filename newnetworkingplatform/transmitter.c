/*
 * transmitter.c
 *
 *  Created on: Oct 6, 2019
 *      Author: albrechter
 */

#include <stdbool.h>
#include <stdint.h>
#include "timer.h"
#include "transmitter.h"
#include "gpio.h"
#include "state.h"
#include <time.h>
#include <stdlib.h>

extern const timer_config MANCHESTER_TIMER;
extern const timer_config RANDOM_TIMER;
extern const gpio encoding_out;
extern bool ready_to_transmit;
extern eState state;


uint8_t current_char;
uint8_t current_bit;
volatile uint16_t buffer_size_used;
volatile char* current_message;
volatile eTransmit_Status transmitting = eTransmit__DONE;
volatile bool on_interval = true;

volatile uint8_t int_left = 0U;
volatile uint16_t remainder = 0U;

bool load_buffer(volatile char* new_message, uint16_t size){
    if(transmitting == eTransmit__DONE) {
        buffer_size_used = size - 1U;
        current_message = new_message;
        return true;
    } else {
        return false;
    }
}

void pause_transmit(void){
    if(transmitting == eTransmit__STARTED){
        transmitting = eTransmit__PAUSED;
    }
}

void start_transmit(void){
    if(state == eState_IDLE) {
        if(transmitting == eTransmit__DONE) {
            on_interval = true;
            current_char = 0U;
            current_bit = 0U;
        }
        transmitting = eTransmit__STARTED;
        ready_to_transmit = false;
        start_timer(&MANCHESTER_TIMER);
    } else {
        transmitting = eTransmit__PAUSED;
        on_interval = true;
        current_char = 0U;
        current_bit = 0U;
        ready_to_transmit = false;
    }
}

void unpause_transmit(void){
    if(transmitting == eTransmit__PAUSED){
        //start_transmit();
        time_t t;
        srand((unsigned) time(&t));
        uint32_t random_result = (rand() % 3000000U);
        //uint32_t random_result = 1U;
        int_left = random_result / 0xFFFFU + 1U;
        remainder = random_result % 0xFFFFU + 1U;
        if(int_left > 1U){
            set_timer_compare(&RANDOM_TIMER, CCR0, 0xFFFF);
        } else {
            set_timer_compare(&RANDOM_TIMER, CCR0, remainder);
        }
        timer_access(&RANDOM_TIMER, TAxCCTL0, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);
        start_timer(&RANDOM_TIMER);
    }
}

void TA2_0_IRQHandler(void){
    stop_timer(&RANDOM_TIMER);
    timer_access(&RANDOM_TIMER, TAxCCTL0, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);
    --int_left;
    if(int_left > 0U) {
        if(int_left > 1U){
            set_timer_compare(&RANDOM_TIMER, CCR0, 0xFFFF);
        } else if(int_left == 1U){
            set_timer_compare(&RANDOM_TIMER, CCR0, remainder);
        }
        start_timer(&RANDOM_TIMER);
    } else {
        if(state == eState_IDLE){
            start_transmit();
        }
    }

}

void TA1_0_IRQHandler(void){
    timer_access(&MANCHESTER_TIMER, TAxCCTL0, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);
    if(transmitting == eTransmit__PAUSED){
        stop_timer(&MANCHESTER_TIMER);
    } else {
        if(on_interval){
            if(current_bit == BITS_PER_CHAR){
                current_bit = 0U;
                current_char++;
            }
            if(current_char < buffer_size_used && current_message[current_char] != '\n'){
                uint8_t bit = (current_message[current_char] & (0x80 >> current_bit));
                current_bit++;
                if(bit > 0U){
                    gpio_clear(&encoding_out);
                } else {
                    gpio_set(&encoding_out);
                }
            } else {
                stop_timer(&MANCHESTER_TIMER);
                gpio_set(&encoding_out);
                transmitting = eTransmit__DONE;
            }
            on_interval = false;
        } else {
            gpio_toggle(&encoding_out);
            on_interval = true;
        }
    }
}
