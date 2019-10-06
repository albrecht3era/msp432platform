/*
 * uart.c
 *
 *  Created on: Oct 5, 2019
 *      Author: albrechter
 */

#include "uart.h"
#include <stdint.h>

void uart_access(const uint32_t uart_address, uart_register register_to_change, const uint16_t mask, const uint16_t value){
    if(value > 0U){
        uint16_t* temp_pointer = (uint16_t*) (uart_address | register_to_change);
        uint16_t tempvar = mask | value;
        *((uint16_t*)(uart_address | register_to_change)) &= ~(mask);
        *((uint16_t*)(uart_address | register_to_change)) |= (value);
    } else {
        *((uint16_t*)(uart_address | register_to_change)) &= ~mask;
    }
}

void uart_config(const uint32_t uart_address){
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCSWRST, UCAxCTLW0__UCSWRST_ENABLE);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCSYNC, UCAxCTLW0__UCSYNC_ASYNC);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCPEN, UCAxCTLW0__UCPEN_ENABLE_PARITY);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCPAR, UCAxCTLW0__UCPAR_EVEN_PARITY);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCMSB, UCAxCTLW0__UCMSB_LSB);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UC7BIT, UCAxCTLW0__UC7BIT_8_BIT);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCSPB, UCAxCTLW0__UCSPB_2_STOP_BITS);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCMODEx, UCAxCTLW0__UCMODEx_UART_MODE_BAUD_DETECT_MODE);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCSSELx, UCAxCTLW0__UCSSELx_ACLK);
    uart_access(uart_address, UCAxABCTL, UCAxABCTL__UCABDEN, UCAxABCTL__UCABDEN_ENABLE);
    uart_access(uart_address, UCAxCTLW0, UCAxCTLW0__UCSWRST, UCAxCTLW0__UCSWRST_DISABLE);
    uart_access(uart_address, UCAxIFG, UCAxIFG__UCTXCPTIFG, UCAxIFG__UCTXCPTIFG_NO_INTERRUPT);
    uart_access(uart_address, UCAxIFG, UCAxIFG__UCSTTIFG, UCAxIFG__UCSTTIFG_NO_INTERRUPT);
    uart_access(uart_address, UCAxIFG, UCAxIFG__UCTXIFG, UCAxIFG__UCTXIFG_NO_INTERRUPT);
    uart_access(uart_address, UCAxIFG, UCAxIFG__UCRXIFG, UCAxIFG__UCRXIFG_NO_INTERRUPT);
    uart_access(uart_address, UCAxIE, UCAxIE__UCTXCPTIE, UCAxIE__UCTXCPTIE_DISABLE);
    uart_access(uart_address, UCAxIE, UCAxIE__UCSTTIE, UCAxIE__UCSTTIE_DISABLE);
    uart_access(uart_address, UCAxIE, UCAxIE__UCTXIE, UCAxIE__UCTXIE_DISABLE);
    uart_access(uart_address, UCAxIE, UCAxIE__UCRXIE, UCAxIE__UCRXIE_DISABLE);
}
