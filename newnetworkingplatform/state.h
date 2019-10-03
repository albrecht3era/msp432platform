/*
 * state.h
 *
 *  Created on: Oct 3, 2019
 *      Author: albrechter
 */

#ifndef STATE_H_
#define STATE_H_

typedef enum{
    eState_IDLE,
    eState_BUSY,
    eState_COLLISION
}eSM_State;

void transition_idle(void);
void transition_busy(void);
void transition_collision(void);

#endif /* STATE_H_ */
