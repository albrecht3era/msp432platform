/*
 * state.c
 *
 *  Created on: Oct 3, 2019
 *      Author: albrechter
 */
#include "state.h"
#include "timer.h"
#include "ledbank.h"

extern eSM_State state;
extern const timer_config TIMERA;

void transition_idle(void){
    state = eState_IDLE;
    led_idle_mode();
    printf("Idle Transition\n");
}

void transition_busy(void){
    state = eState_BUSY;
    led_busy_mode();
    start_timer(&TIMERA);
    printf("Busy Transition\n");
}

void transition_collision(void){
    state = eState_COLLISION;
    led_collision_mode();
    printf("Collision Transition\n");
}
