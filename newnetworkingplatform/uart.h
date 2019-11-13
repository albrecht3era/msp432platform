/*
 * uart.h
 *
 *  Created on: Oct 5, 2019
 *      Author: albrechter
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

typedef enum{
    UCAxCTLW0=0x0U, // Control Word 0
    UCAxCTLW1=0x2U, // Control Word 1
    UCAxBRW=0x6U, // Baud Rate Control Word
    UCAxMCTLW=0x8U, // Modulation Control Word
    UCAxSTATW=0xAU, // Status
    UCAxRXBUF=0xCU, // Receive Buffer
    UCAxTXBUF=0xEU, // Transmit Buffer
    UCAxABCTL=0x10U, // Auto Baud Rate Control
    UCAxIRCTL=0x12U, // IrDA Control
    UCAxIE=0x1AU, // Interrupt Enable
    UCAxIFG=0x1CU, // Interrupt Flag
    UCAxIV=0x1EU // Interrupt Vector
}uart_register;

typedef enum{
    UCAxCTLW0__UCPEN=0x8000U,
    UCAxCTLW0__UCPAR=0x4000U,
    UCAxCTLW0__UCMSB=0x2000U,
    UCAxCTLW0__UC7BIT=0x1000U,
    UCAxCTLW0__UCSPB=0x800U,
    UCAxCTLW0__UCMODEx=0x600U,
    UCAxCTLW0__UCSYNC=0x100U,
    UCAxCTLW0__UCSSELx=0xC0U,
    UCAxCTLW0__UCRXEIE=0x20U,
    UCAxCTLW0__UCBRKIE=0x10U,
    UCAxCTLW0__UCDORM=0x8U,
    UCAxCTLW0__UCTXADDR=0x4U,
    UCAxCTLW0__UCTXBRK=0x2U,
    UCAxCTLW0__UCSWRST=0x1U
}UCAxCTLW0_mask;

typedef enum{
    UCAxCTLW1__UCGLITx=0x3U
}UCAxCTLW1_UCGLITx_mask;

typedef enum{
    UCAxBRW__FULL=0xFFFFU
}UCAxBRW_mask;

typedef enum{
    UCAxMCTLW__UCBRSx_2ND_MOD_STAGE=0xFF00U,
    UCAxMCTLW__UCBRFx_1ST_MOD_STAGE=0xF0U,
    UCAxMCTLW__UCOS16=0x1U
}UCAxMCTLW_mask;

typedef enum{
    UCAxSTATW__UCLISTEN=0x80U,
    UCAxSTATW__UCFE=0x40U,
    UCAxSTATW__UCOE=0x20U,
    UCAxSTATW__UCPE=0x10U,
    UCAxSTATW__UCBRK=0x8U,
    UCAxSTATW__UCRXERR=0x4U,
    UCAxSTATW__UCADDR_UCIDLE=0x2U,
    UCAxSTATW__UCBUSY=0x1U
}UCAxSTATW_mask;

typedef enum {
    UCAxRXBUF__UCRXBUF=0xFFU
}UCAxRXBUF_mask;

typedef enum {
    UCAxTXBUF__UCTXBUF=0xFFU
}UCAxTXBUF_mask;

typedef enum{
    UCAxABCTL__UCDELIMx=0x30U,
    UCAxABCTL__UCSTOE=0x8U,
    UCAxABCTL__UCBTOE=0x4U,
    UCAxABCTL__UCABDEN=0x1U
}UCAxABCTL_mask;

typedef enum{
    UCAxIE__UCTXCPTIE=0x8U,
    UCAxIE__UCSTTIE=0x4u,
    UCAxIE__UCTXIE=0x2U,
    UCAxIE__UCRXIE=0x1U
}UCAxIE_mask;

typedef enum{
    UCAxIFG__UCTXCPTIFG=0x8U,
    UCAxIFG__UCSTTIFG=0x4U,
    UCAxIFG__UCTXIFG=0x2U,
    UCAxIFG__UCRXIFG=0x1U
}UCAxIFG_mask;

/**--------------------------------------------------------------------**/

/** Control Word Values **/

typedef enum{
    UCAxCTLW0__UCPEN_DISABLE_PARITY=0x0U,
    UCAxCTLW0__UCPEN_ENABLE_PARITY=0x8000U
}UCAxCTLW0_UCPEN_value;

typedef enum{
    UCAxCTLW0__UCPAR_ODD_PARITY=0x0U,
    UCAxCTLW0__UCPAR_EVEN_PARITY=0x4000U
}UCAxCTLW0_UCPAR_value;

typedef enum{
    UCAxCTLW0__UCMSB_LSB=0x0U,
    UCAxCTLW0__UCMSB_MSB=0x2000U
}UCAxCTLW0_UCMSB_value;

typedef enum{
    UCAxCTLW0__UC7BIT_8_BIT=0x0U,
    UCAxCLTW0__UC7BIT_7_BIT=0x1000U
}UCAxCTLW0_UC7BIT_value;

typedef enum{
    UCAxCTLW0__UCSPB_1_STOP_BIT=0x0U,
    UCAxCTLW0__UCSPB_2_STOP_BITS=0x800U
}UCAxCTLW0_UCSPB_value;

typedef enum{
    UCAxCTLW0__UCMODEx_UART_MODE=0x0U,
    UCAxCTLW0__UCMODEx_IDLE_LINE_MULTI_PROC_MODE=0x200U,
    UCAxCTLW0__UCMODEx_ADDR_BIT_MULTI_PROC_MODE=0x400U,
    UCAxCTLW0__UCMODEx_UART_MODE_BAUD_DETECT_MODE=0x300U
}UCAxCTLW0_UCMODEx_value;

typedef enum{
    UCAxCTLW0__UCSYNC_ASYNC=0x0U,
    UCAxCTLW0__UCSYNC_SYNCH=0x100U
}UCAxCTLW0_UCSYNC_value;

typedef enum{
    UCAxCTLW0__UCSSELx_UCLK=0x0U,
    UCAxCTLW0__UCSSELx_ACLK=0x40U,
    UCAxCTLW0__UCSSELx_SMCLK=0x80U,
    UCAxCTLW0__UCSSELx_SMCLK_2=0xC0U
}UCAxCTLW0_UCSSELx_value;

typedef enum{
    UCAxCTLW0__UCRXEIE_ERRORS_IGNORE_UCRXIFG=0x0U,
    UCAxCTLW0__UCRXEIE_ERRORS_SET_UCRXIFG=0x20U
}UCAxCTLW0_UCRXEIE_value;

typedef enum{
    UCAxCTLW0__UCBRKIE_IGNORE_UCRXIFG=0x0U,
    UCAxCTLW0__UCBRKIE_SET_UCRXIFG=0x10U
}UCAxCTLW0_UCBRKIE_value;

typedef enum{
    UCAxCTLW0__UCDORM_NOT_DORMANT=0x0U,
    UCAxCTLW0__UCDORM_DORMANT=0x8U
}UCAxCTLW0_UCDORM_value;

typedef enum{
    UCAxCTLW0__UCTXADDR_DATA=0x0U,
    UCAxCTLW0__UCTXADDR_ADDR=0x4U
}UCAxCTLW0_UCTXADDR_value;

typedef enum{
    UCAxCTLW0__UCTXBRK_NOT_BREAK=0x0U,
    UCAxCTLW0__UCTXBRK_BREAK=0x2U
}UCAxCTL;

typedef enum{
    UCAxCTLW0__UCSWRST_DISABLE=0x0U,
    UCAxCTLW0__UCSWRST_ENABLE=0x1U
}UCAxCTLW0_UCSWRST_value;

/**----------------------------------------------------------------**/

typedef enum{
    UCAxCTLW1__UCGLITx_5_NS=0x0U,
    UCAxCTLW1__UCGLITx_20_NS=0x1U,
    UCAxCTLW1__UCGLITx_30_NS=0x2U,
    UCAxCTLW1__UCGLITx_50_NS=0x3U
}UCAxCTLW1_value;

/**--------------------------------------------------------------------**/

typedef enum{
    UCAxMCTLW__UCOS16_DISABLE=0x0U,
    UCAxMCTLW__UCOS16_ENABLE=0x1U
}UCAxMCTLW_OVERSAMPLE_value;

/**-------------------------------------------------------------------------**/

typedef enum{
    UCAxSTATW__UCLISTEN_DISABLE=0x0U,
    UCAxSTATW__UCLISTEN_ENABLE=0x80U
}UCAxSTATW_UCLISTEN_value;

typedef enum{
    UCAxSTATW__UCFE_NO_ERROR=0x0U,
    UCAxSTATW__UCFE_LOW_STOP_BIT=0x40U
}UCAxSTATW_UCFE_value;

typedef enum{
    UCAxSTATW__UCOE_NO_ERROR=0x0U,
    UCAxSTATW__UCOE_OVERRUN=0x20U
}UCAxSTATW_UCOE_value;

typedef enum{
    UCAxSTATW__UCPE_NO_ERROR=0x0U,
    UCAxSTATW__UCPE_PARITY_ERROR=0x10U
}UCAxSTATW_UCPE_value;

typedef enum{
    UCAxSTATW__UCBRK_NO_BREAK=0x0U,
    UCAxSTATW__UCBRK_BREAK=0x8U
}UCAxSTATW_UCBRK_value;

typedef enum{
    UCAxSTATW__UCRXERR_NO_ERROR=0x0U,
    UCAxSTATW__UCRXERR_RECEIVE_ERROR=0x4U
}UCAxSTATW_UCRXERR_value;

typedef enum{
    UCAxSTATW__UCADDR_UCIDLE_DATA=0x0U,
    UCAxSTATW__UCADDR_UCIDLE_ADDR=0x2U
}UCAxSTATW_UCADDR_UCIDLE_value;

typedef enum{
    UCAxSTATW__UCBUSY_INACTIVE=0x0U,
    UCAxSTATW__UCBUSY_ACTIVE=0x1U
}UCAxSTATW_UCBUSY_value;

/**----------------------------------------------------------------**/

typedef enum{
    UCAxABCTL__UCDELIMx_1_BIT=0x0U,
    UCAxABCTL__UCDELIMx_2_BIT=0x10U,
    UCAxABCTL__UCDELIMx_3_BIT=0x20U,
    UCAxABCTL__UCDELIMx_4_BIT=0x30U
}UCAxABCTL_UCDELIMx_value;

typedef enum{
    UCAxABCTL__UCSTOE_NO_ERROR=0x0U,
    UCAxABCTL__UCSTOE_SYNCH_FIELD_ERROR=0x8U
}UCAxABCTL_UCSTOE_value;

typedef enum{
    UCAxABCTL__UCBTOE_NO_ERROR=0x0U,
    UCAxABCTL__UCBTOE_BREAK_FIELD_ERROR=0x4U
}UCAxABCTL_UCBTOE_value;

typedef enum{
    UCAxABCTL__UCABDEN_DISABLE=0x0U,
    UCAxABCTL__UCABDEN_ENABLE=0x1U
}UCAxABCTL_UCABDEN_value;

/**------------------------------------------------------------------------**/

typedef enum{
    UCAxIE__UCTXCPTIE_DISABLE=0x0U,
    UCAxIE__UCTXCPTIE_ENABLE=0x8U
}UCAxIE_UCTXCPTIE_value;

typedef enum{
    UCAxIE__UCSTTIE_DISABLE=0x0U,
    UCAxIE__UCSTTIE_ENABLE=0x4U
}UCAxIE_UCSTTIE_value;

typedef enum{
    UCAxIE__UCTXIE_DISABLE=0x0U,
    UCAxIE__UCTXIE_ENABLE=0x2U
}UCAxIE_UCTXIE_value;

typedef enum{
    UCAxIE__UCRXIE_DISABLE=0x0U,
    UCAxIE__UCRXIE_ENABLE=0x1U
}UCAxIE_UCRXIE_value;

/*******************************************************************************/

typedef enum{
    UCAxIFG__UCTXCPTIFG_NO_INTERRUPT=0x0U,
    UCAxIFG__UCTXCPTIFG_INTERRUPT_PENDING=0x8U
}UCAxIE_UCTXCPTIFG_value;

typedef enum{
    UCAxIFG__UCSTTIFG_NO_INTERRUPT=0x0U,
    UCAxIFG__UCSTTIFG_INTERRUPT_PENDING=0x4U
}UCAxIE_UCSTTIFG_value;

typedef enum{
    UCAxIFG__UCTXIFG_NO_INTERRUPT=0x0U,
    UCAxIFG__UCTXIFG_INTERRUPT_PENDING=0x2U
}UCAxIE_UCTXIFG_value;

typedef enum{
    UCAxIFG__UCRXIFG_NO_INTERRUPT=0x0U,
    UCAxIFG__UCRXIFG_INTERRUPT_PENDING=0x1U
}UCAxIE_UCRXIFG_value;

/*********************************************************************************/

#define UART_1_ADDRESS 0x40001000
#define BUFFER_COUNTER_INIT 6U
#define BUFFER_MAX (256U + BUFFER_COUNTER_INIT + 2U)


void uart_config(const uint32_t uart_address);
void uart_access(const uint32_t uart_address, uart_register register_to_change, const uint16_t mask, const uint16_t value);
void uart_start_receiving(const uint32_t uart_address);
uint16_t uart_read(const uint32_t uart_address, uart_register register_to_read, const uint16_t mask);

#endif /* UART_H_ */
