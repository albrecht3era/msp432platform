/*
 * gpio_config.c
 *
 *  Created on: Oct 2, 2019
 *      Author: albrechter
 */
#include "msp.h"
#include "gpio.h"
#include "state.h"
#include "timer.h"
#include <stdio.h>
#include "transmitter.h"
#include "receiver.h"

extern eSM_State state;
extern const timer_config TIMERA;

const gpio redLED = {PIN0, PIN0_SHIFT, PORT1_ADDR, ACTIVE_HIGH, OUTPUT};
const gpio LEDTURNOFF_R = {PIN0, PIN0_SHIFT, PORT2_ADDR, ACTIVE_HIGH, OUTPUT};
const gpio greenLED = {PIN1, PIN1_SHIFT, PORT2_ADDR, ACTIVE_HIGH, OUTPUT};
const gpio encoding_out = {PIN4, PIN4_SHIFT, PORT2_ADDR, ACTIVE_HIGH, OUTPUT};
const gpio yellowLED = {PIN5, PIN5_SHIFT, PORT1_ADDR, ACTIVE_LOW, OUTPUT};
const gpio manchester = {PIN6, PIN6_SHIFT, PORT2_ADDR, ACTIVE_HIGH, INPUT};
const gpio rxd = {PIN2, PIN2_SHIFT, PORT1_ADDR, ACTIVE_HIGH, INPUT};
//const gpio ste = {PIN0, PIN0_SHIFT, PORT1_ADDR, ACTIVE_HIGH, INPUT};

void PORT1_IRQHandler(void){
    printf("Why is this happening\n");
}

void PORT2_IRQHandler(void){
    __disable_interrupt();
    uint8_t ifg_read = P2IFG;
    if((ifg_read & PIN6) > 0) {
        stop_timer(&TIMERA);
        uint32_t current_count = timer_read(&TIMERA, TAxR, TAxR__FULL);
        gpio_set_interrupt(&manchester, TOGGLE);
        eReceiver_Ignore_Status status = get_receive_half_bit();
        switch(state){
            case eState_IDLE:
                transition_busy();
                break;
            case eState_BUSY:
                if( current_count > RECEIVE_RATE || (current_count < RECEIVE_RATE && status == eReceiver_IGNORED)){
                    receive_new_bit((gpio_read(&manchester) ^ 0x1));
                } else if(current_count < RECEIVE_RATE){
                    receive_half_bit();
                }
                start_timer(&TIMERA);
                break;
            case eState_COLLISION:
                transition_busy();
                break;
            default:
                break;
        }

    } else {
        //printf("This shouldn't be happening\n");
        //printf("yikes\n");
    }
    P2IFG = 0U;
    __enable_interrupt();
}

