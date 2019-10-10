/*
 * timer.c
 *
 *  Created on: Oct 2, 2019
 *      Author: albrechter
 */

#include "timer.h"
#include "gpio.h"
#include "msp.h"

/**
 * Used for accessing everything related to normal output function.
 */
void timer_access(const timer_config* timer_io, timer_register register_to_change, uint16_t timer_register_mask, uint16_t timer_register_value){
    if(timer_register_value > 0U){
        *((uint16_t*)(timer_io->port_address | register_to_change)) &= ~(timer_register_mask);
        *((uint16_t*)(timer_io->port_address | register_to_change)) |= (timer_register_value);
    } else {
        *((uint16_t*)(timer_io->port_address | register_to_change)) &= ~timer_register_mask;
    }
}

void enable_timer_interrupt(const timer_config* timer_io, CCTL_register cctl, IRQn_Type type){
    timer_access(timer_io, TAxCTL, TAxCTL__MC, TAxCTL__MC_STOP);
    timer_access(timer_io, cctl, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);
    NVIC_EnableIRQ(type);
    timer_access(timer_io, cctl, TAxCCTL__CCIE, TAxCCTL__CCIE_ENABLE_INTERRUPT);

}

void set_timer_compare(const timer_config* timer_io, CCR_register ccr, uint16_t compare){
    timer_access(timer_io, (timer_register) ccr, TAxCCR__FULL, compare);
}

void start_timer(const timer_config* timer_io){
    timer_access(timer_io, TAxR, TAxCCR__FULL, 0U);
    timer_access(timer_io, TAxCTL, TAxCTL__MC, timer_io->mc);
}

void stop_timer(const timer_config* timer_io){
    timer_access(timer_io, TAxCTL, TAxCTL__MC, TAxCTL__MC_STOP);
}

void timer_init(const timer_config* timer_io){
    timer_access(timer_io, TAxCTL, TAxCTL__CLK, timer_io->clk);
    timer_access(timer_io, TAxCTL, TAxCTL__ID, timer_io->id);
    timer_access(timer_io, TAxCTL, TAxCTL__MC, TAxCTL__MC_STOP);
    timer_access(timer_io, TAxCTL, TAxCTL__IE, TAxCTL__IE_DISABLE_INTERRUPT);
    timer_access(timer_io, TAxCTL, TAxCTL__IFG, TAxCTL__IFG_NO_INTERRUPT);
    timer_access(timer_io, TAxCCTL0, TAxCCTL__CCIE, TAxCCTL__CCIE_DISABLE_INTERRUPT);
    timer_access(timer_io, TAxCCTL1, TAxCCTL__CCIE, TAxCCTL__CCIE_DISABLE_INTERRUPT);
    timer_access(timer_io, TAxCCTL2, TAxCCTL__CCIE, TAxCCTL__CCIE_DISABLE_INTERRUPT);
    timer_access(timer_io, TAxCCTL3, TAxCCTL__CCIE, TAxCCTL__CCIE_DISABLE_INTERRUPT);
    timer_access(timer_io, TAxCCTL4, TAxCCTL__CCIE, TAxCCTL__CCIE_DISABLE_INTERRUPT);
    timer_access(timer_io, TAxCCTL5, TAxCCTL__CCIE, TAxCCTL__CCIE_DISABLE_INTERRUPT);
    timer_access(timer_io, TAxCCTL6, TAxCCTL__CCIE, TAxCCTL__CCIE_DISABLE_INTERRUPT);
    timer_access(timer_io, TAxCCTL0, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);
    timer_access(timer_io, TAxCCTL1, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);
    timer_access(timer_io, TAxCCTL2, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);
    timer_access(timer_io, TAxCCTL3, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);
    timer_access(timer_io, TAxCCTL4, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);
    timer_access(timer_io, TAxCCTL5, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);
    timer_access(timer_io, TAxCCTL6, TAxCCTL__CCIFG, TAxCCTL__CCIFG_NO_INTERRUPT);

}
