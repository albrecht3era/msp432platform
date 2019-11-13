/*
 * state.c
 *
 *  Created on: Oct 3, 2019
 *      Author: albrechter
 */
#include "state.h"
#include "timer.h"
#include "ledbank.h"
#include "transmitter.h"
#include "receiver.h"
#include <stdio.h>

extern eSM_State state;
extern const timer_config TIMERA;
extern const timer_config RANDOM_TIMER;

void transition_idle(void){
    state = eState_IDLE;
    led_idle_mode();
    unpause_transmit();
    //printf("idling\n");
}

void transition_busy(void){
    //printf("busy\n");
    if(state == eState_IDLE){
        start_receiving();
        //receive_new_bit(1U);
    }
    state = eState_BUSY;
    stop_timer(&RANDOM_TIMER);
    start_timer(&TIMERA);
    led_busy_mode();

}

void transition_collision(void){
    state = eState_COLLISION;
    led_collision_mode();
    pause_transmit();
    //printf("collision\n");
}
