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

extern eSM_State state;
extern const timer_config TIMERA;

const gpio redLED = {PIN0, PIN0_SHIFT, PORT1_ADDR, ACTIVE_HIGH, OUTPUT};
const gpio LEDTURNOFF_R = {PIN0, PIN0_SHIFT, PORT2_ADDR, ACTIVE_HIGH, OUTPUT};
const gpio greenLED = {PIN1, PIN1_SHIFT, PORT2_ADDR, ACTIVE_HIGH, OUTPUT};
const gpio LEDTURNOFF_B = {PIN2, PIN2_SHIFT, PORT2_ADDR, ACTIVE_HIGH, OUTPUT};
const gpio yellowLED = {PIN5, PIN5_SHIFT, PORT1_ADDR, ACTIVE_LOW, OUTPUT};
const gpio manchester = {PIN5, PIN5_SHIFT, PORT2_ADDR, ACTIVE_HIGH, INPUT};

void PORT1_IRQHandler(void){

}

void PORT2_IRQHandler(void){
    P2IFG = 0U;
    gpio_set_interrupt(&manchester, TOGGLE);
    switch(state){
        case eState_IDLE:
            transition_busy();
            break;
        case eState_BUSY:
            stop_timer(&TIMERA);
            start_timer(&TIMERA);
            break;
        case eState_COLLISION:
            transition_busy();
            break;
        default:
            break;
    }
}
