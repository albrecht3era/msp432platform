/*
 * uart.c
 *
 *  Created on: Oct 5, 2019
 *      Author: albrechter
 */

#include "uart.h"
#include "gpio.h"
#include <stdint.h>
#include <stdio.h>

extern const gpio rxd;
extern const gpio ste;
extern const gpio greenLED;
extern const gpio yellowLED;

static volatile uint16_t buffercounter;
const uint16_t buffermax = 6U;
volatile char buffer[buffermax];


void uart_access(const uint32_t uart_address, uart_register register_to_change, const uint16_t mask, const uint16_t value){
    if(value > 0U){
        *((uint16_t*)(uart_address | register_to_change)) &= ~(mask);
        *((uint16_t*)(uart_address | register_to_change)) |= (value);
    } else {
        *((uint16_t*)(uart_address | register_to_change)) &= ~mask;
    }
}

uint16_t uart_read(const uint32_t uart_address, uart_register register_to_read, const uint16_t mask){
    return *((uint16_t*)(uart_address | register_to_read)) &= mask;
}

void uart_config(const uint32_t uart_address){
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCSWRST, UCAxCTLW0__UCSWRST_ENABLE);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCSYNC, UCAxCTLW0__UCSYNC_ASYNC);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCPEN, UCAxCTLW0__UCPEN_DISABLE_PARITY);
    //uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCPAR, UCAxCTLW0__UCPAR_EVEN_PARITY);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCMSB, UCAxCTLW0__UCMSB_LSB);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UC7BIT, UCAxCTLW0__UC7BIT_8_BIT);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCSPB, UCAxCTLW0__UCSPB_1_STOP_BIT);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCMODEx, UCAxCTLW0__UCMODEx_UART_MODE);
    uart_access(uart_address, UCAxBRW, UCAxBRW__FULL, 156U);
    uart_access(uart_address, UCAxMCTLW, UCAxMCTLW__UCOS16, UCAxMCTLW__UCOS16_ENABLE);
    uart_access(uart_address, UCAxMCTLW, UCAxMCTLW__UCBRSx_2ND_MOD_STAGE, 0x4400);
    uart_access(uart_address, UCAxMCTLW, UCAxMCTLW__UCBRFx_1ST_MOD_STAGE, 0x40);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCSSELx, UCAxCTLW0__UCSSELx_SMCLK);
   // uart_access(uart_address, UCAxABCTL, UCAxABCTL__UCABDEN, UCAxABCTL__UCABDEN_ENABLE);
    //uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCRXEIE, UCAxCTLW0__UCRXEIE_ERRORS_SET_UCRXIFG);
    //uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCBRKIE, UCAxCTLW0__UCBRKIE_SET_UCRXIFG);
    uart_access(uart_address, UCAxSTATW, UCAxSTATW__UCOE, UCAxSTATW__UCOE_NO_ERROR);
    uart_read(uart_address, UCAxRXBUF, UCAxRXBUF__UCRXBUF);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCSWRST, UCAxCTLW0__UCSWRST_DISABLE);
    uart_access(uart_address, UCAxIFG, UCAxIFG__UCTXCPTIFG, UCAxIFG__UCTXCPTIFG_NO_INTERRUPT);
    uart_access(uart_address, UCAxIFG, UCAxIFG__UCSTTIFG, UCAxIFG__UCSTTIFG_NO_INTERRUPT);
    uart_access(uart_address, UCAxIFG, UCAxIFG__UCTXIFG, UCAxIFG__UCTXIFG_NO_INTERRUPT);
    uart_access(uart_address, UCAxIFG, UCAxIFG__UCRXIFG, UCAxIFG__UCRXIFG_NO_INTERRUPT);
    uart_access(uart_address, UCAxIE, UCAxIE__UCTXCPTIE, UCAxIE__UCTXCPTIE_DISABLE);
    uart_access(uart_address, UCAxIE, UCAxIE__UCSTTIE, UCAxIE__UCSTTIE_DISABLE);
    uart_access(uart_address, UCAxIE, UCAxIE__UCTXIE, UCAxIE__UCTXIE_DISABLE);
    uart_access(uart_address, UCAxIE, UCAxIE__UCRXIE, UCAxIE__UCRXIE_DISABLE);
    gpio_init(&rxd);
    gpio_access(&rxd, PxSEL0, OFF, ACTIVE_HIGH, rxd.pin_num);
    gpio_access(&rxd, PxSEL1, ON, ACTIVE_HIGH, rxd.pin_num);
    gpio_init(&ste);
    gpio_access(&ste, PxSEL0, OFF, ACTIVE_HIGH, ste.pin_num);
    gpio_access(&ste, PxSEL1, OFF, ACTIVE_HIGH, ste.pin_num);
    buffercounter = 0U;
}

void uart_start_receiving(const uint32_t uart_address){
    uart_access(uart_address, UCAxIFG, UCAxIFG__UCRXIFG, UCAxIFG__UCRXIFG_NO_INTERRUPT);
    uart_access(uart_address, UCAxIFG, UCAxIFG__UCSTTIFG, UCAxIFG__UCSTTIFG_NO_INTERRUPT);
    uart_access(uart_address, UCAxIE, UCAxIE__UCTXCPTIE, UCAxIE__UCTXCPTIE_DISABLE);
    uart_access(uart_address, UCAxIE, UCAxIE__UCSTTIE, UCAxIE__UCSTTIE_DISABLE);
    uart_access(uart_address, UCAxIE, UCAxIE__UCTXIE, UCAxIE__UCTXIE_DISABLE);
    uart_access(uart_address, UCAxIE, UCAxIE__UCRXIE, UCAxIE__UCRXIE_ENABLE);
    //uart_access(uart_address, UCAxSTATW, UCAxSTATW__UCBRK, UCAxSTATW__UCBRK_NO_BREAK);
}

void EUSCIA0_IRQHandler(void){
//    uint16_t interrupt_flags = uart_read(UART_1_ADDRESS, UCAxIFG, UCAxIFG__UCRXIFG);
//    if(interrupt_flags == UCAxIFG__UCRXIFG_INTERRUPT_PENDING){
//        uint16_t read_value = uart_read(UART_1_ADDRESS, UCAxRXBUF, UCAxRXBUF__UCRXBUF);
//    } else if (interrupt_flags == UCAxIFG__UCSTTIFG_INTERRUPT_PENDING){
//        uart_access(UART_1_ADDRESS, UCAxIFG, UCAxIFG__UCSTTIFG, UCAxIFG__UCSTTIFG_NO_INTERRUPT);
//        uart_read(UART_1_ADDRESS, UCAxRXBUF, UCAxRXBUF__UCRXBUF);
//    }
    buffer[buffercounter] = (char) uart_read(UART_1_ADDRESS, UCAxRXBUF, UCAxRXBUF__UCRXBUF);
    if(buffer[buffercounter] == '\n' || buffercounter == buffermax){
        printf("%s\n", buffer);
        buffercounter = 0U;
    } else {
        buffercounter++;
    }
}


