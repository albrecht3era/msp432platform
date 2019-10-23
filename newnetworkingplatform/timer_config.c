/*
 * timer_config.c
 *
 *  Created on: Oct 3, 2019
 *      Author: albrechter
 */

#include "timer.h"
#include "gpio.h"
#include "state.h"

extern const gpio redLED;
extern const gpio greenLED;
extern const gpio yellowLED;
extern const gpio manchester;

const timer_config TIMERA = {TIMER_A_ADDR, TAxCTL__CLK_SMCLK, TAxCTL__ID_1, TAxCTL__MC_UP};
const timer_config MANCHESTER_TIMER = {TIMER_A_1_ADDR, TAxCTL__CLK_SMCLK, TAxCTL__ID_1, TAxCTL__MC_UP};

void TA0_0_IRQHandler(void){
    stop_timer(&TIMERA);
    timer_access(&TIMERA, TAxCCTL0, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);
    if(gpio_read(&manchester) == ON){
        transition_idle();
    } else {
        transition_collision();
    }
}


