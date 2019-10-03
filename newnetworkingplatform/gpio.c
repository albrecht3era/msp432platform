/*
 * gpio.c
 *
 *  Created on: Oct 2, 2019
 *      Author: albrechter
 */
#include "gpio.h"
#include "stdint.h"

/**
 * Used for accessing everything related to normal output function.
 */
void gpio_access(const gpio* io, eRegister io_register, eState state, eActiveConfig active_config, uint8_t register_value){
    if(state != TOGGLE) {
        if(state == ON){
            if(active_config == ACTIVE_HIGH){
                *((uint8_t*)(io->port_address | io_register)) |= register_value;
            } else {
                *((uint8_t*)(io->port_address | io_register)) &= ~register_value;
            }
        } else {
            if(active_config == ACTIVE_HIGH){
                *((uint8_t*)(io->port_address | io_register)) &= ~register_value;
            } else {
                *((uint8_t*)(io->port_address | io_register)) |= register_value;
            }
        }
    } else {
        *((uint8_t*)io->port_address + io_register) ^= register_value;
    }
}

void gpio_init(const gpio* io){
    gpio_access(io, PxDIR, io->direction, ACTIVE_HIGH, io->pin_num);
    gpio_access(io, PxIES, OFF, ACTIVE_HIGH, io->pin_num);
    gpio_access(io, PxIE, OFF, ACTIVE_HIGH, io->pin_num);
    gpio_access(io, PxIFG, OFF, ACTIVE_HIGH, io->pin_num);
}

void gpio_set(const gpio* io){
    gpio_access(io, PxOUT, ON, io->active_config, io->pin_num);
}

void gpio_clear(const gpio* io){
    gpio_access(io, PxOUT, OFF, io->active_config, io->pin_num);
}

void gpio_set_interrupt(const gpio* io, eState state){
    gpio_access(io, PxIFG, OFF, ACTIVE_HIGH, io->pin_num);
    if(state != TOGGLE) {
        if(io->active_config == ACTIVE_HIGH){
            if(state == ON){
                gpio_access(io, PxIES, RISING_EDGE, io->active_config, io->pin_num);
            } else {
                gpio_access(io, PxIES, FALLING_EDGE, io->active_config, io->pin_num);
            }
        } else {
            if(state == ON){
                gpio_access(io, PxIES, FALLING_EDGE, io->active_config, io->pin_num);
            } else {
                gpio_access(io, PxIES, RISING_EDGE, io->active_config, io->pin_num);
            }
        }
    } else {
        gpio_access(io, PxIES, TOGGLE, io->active_config, io->pin_num);
    }
    gpio_access(io, PxIE, ON, ACTIVE_HIGH, io->pin_num);
}

void gpio_toggle(const gpio* io){
    gpio_access(io, PxOUT, TOGGLE, ACTIVE_HIGH, io->pin_num);
}

eState gpio_read(const gpio* io){
    uint8_t returnval = (*((uint8_t*)io->port_address + PxIN) & io->pin_num);
    eState state;
    if(io->active_config == ACTIVE_HIGH){
        if(returnval > 0){
            state = ON;
        } else {
            state = OFF;
        }
    } else {
        if(returnval > 0){
            state = OFF;
        } else {
            state = ON;
        }
    }
    return state;
    //return (eState) (*((uint8_t*)io->port_address + PxIN) & (io->pin_num) >> (io->pin_shift));
}
