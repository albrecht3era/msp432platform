/*
 * timer.h
 *
 *  Created on: Oct 2, 2019
 *      Author: albrechter
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

typedef enum{
    TAxCTL=0x0U,
    TAxCCTL0=0x2U,
    TAxCCTL1=0x4U,
    TAxCCTL2=0x6U,
    TAxCCTL3=0x8U,
    TAxCCTL4=0xAU,
    TAxCCTL5=0xCU,
    TAxCCTL6=0xEU,
    TAxR=0x10U,
    TAxCCR0=0x12U,
    TAxCCR1=0x14U,
    TAxCCR2=0x16U,
    TAxCCR3=0x18U,
    TAxCCR4=0x1AU,
    TAxCCR5=0x1CU,
    TAxCCR6=0x1EU,
    TAxIV=0x2EU,
    TAxEX0=0x20U
}timer_register;

typedef enum{
    CCTL0=TAxCCTL0,
    CCTL1=TAxCCTL1,
    CCTL2=TAxCCTL2,
    CCTL3=TAxCCTL3,
    CCTL4=TAxCCTL4,
    CCTL5=TAxCCTL5,
    CCTL6=TAxCCTL6
}CCTL_register;

typedef enum{
    CCR0=TAxCCR0,
    CCR1=TAxCCR1,
    CCR2=TAxCCR2,
    CCR3=TAxCCR3,
    CCR4=TAxCCR4,
    CCR5=TAxCCR5,
    CCR6=TAxCCR6
}CCR_register;

typedef enum{
    TAxCCR__FULL=0xFFFFU,
}TAxCCR_mask;

typedef enum{
    TIMER_A_ADDR=0x40000000
}eTimerAddress;

typedef enum{
    TAxCTL__CLK=0x300U,
    TAxCTL__ID=0xC0U,
    TAxCTL__MC=0x30U,
    TAxCTL__CLR=0x4U,
    TAxCTL__IE=0x2U,
    TAxCTL__IFG=0x1U
}TAxCTL_mask;

typedef enum{
    TAxCTL__CLK_TACLK=0x0U,
    TAxCTL__CLK_ACLK=0x100U,
    TAxCTL__CLK_SMCLK=0x200U,
    TAxCTL__CLK_INCLK=0x300U
}TAxCTL_CLK_value;

typedef enum{
    TAxCTL__ID_1=0x0U,
    TAxCTL__ID_2=0x40U,
    TAxCTL__ID_4=0x80U,
    TAxCTL__ID_8=0xC0U
}TAxCTL_ID_value;

typedef enum{
    TAxCTL__MC_STOP=0x0U,
    TAxCTL__MC_UP=0x10U,
    TAxCTL__MC_CONT=0x20U,
    TAxCTL__MC_UP_DOWN=0x30U
}TAxCTL_MC_value;

typedef enum{
    TAxCTL__CLR_DISABLE_CLEAR=0x0U,
    TAxCTL__CLR_ENABLE_CLEAR=0x4U
}TAxCTL_CLR_value;

typedef enum{
    TAxCTL__IE_DISABLE_INTERRUPT=0x0U,
    TAxCTL__IE_ENABLE_INTERRUPT=0x2U
}TAxCTL_IE_value;

typedef enum{
    TAxCTL__IFG_NO_INTERRUPT=0x0U,
    TAxCTL__IFG_INTERRUPT_PENDING=0x1U
}TAxCTL_IFG_value;

typedef enum{
    TAxCCTL__CM=0xC000U,
    TAxCCTL__CCIS=0x3000U,
    TAxCCTL__CAP=0x100U,
    TAxCCTL__OUTMOD=0xE0U,
    TAxCCTL__CCIE=0x10U,
    TAxCCTL__CCI=0x8U,
    TAxCCTL__OUT=0x4U,
    TAxCCTL__COV=0x2U,
    TAxCCTL__CCIFG=0x1U
}TAxCCTL_mask;

typedef enum{
    TAxCCTL__CM_NO_CAPTURE=0x0U,
    TAxCCTL__CM_RISING_EDGE=0x4000U,
    TAxCCTL__CM_FALLING_EDGE=0x8000U,
    TAxCCTL__CM_BOTH_EDGES=0xC000U
}TAxCCTL_CM_value;

typedef enum{
    TAxCCTL__CCIS_CCIxA=0x0U,
    TAxCCTL__CCIS_CCIxB=0x1000U,
    TAxCCTL__CCIS_GND=0x2000U,
    TAxCCTL__CCIS_VCC=0x3000U
}TAxCCTL_CCIS_value;

typedef enum{
    TAxCCTL__CAP_CAPTURE_MODE=0x0U,
    TAxCCTL__CAP_COMPARE_MODE=0x100U
}TAxCCTL_CAP_value;

typedef enum{
    TAxCCTL__OUTMOD_OUT_BIT_VALUE=0x0U,
    TAxCCTL__OUTMOD_SET=0x20U,
    TAxCCTL__OUTMOD_TOGGLE_RESET=0x40U,
    TAxCCTL__OUTMOD_SET_RESET=0x60U,
    TAxCCTL__OUTMOD_TOGGLE=0x80U,
    TAxCCTL__OUTMOD_RESET=0xA0U,
    TAxCCTL__OUTMOD_TOGGLE_SET=0xC0U,
    TAxCCTL__OUTMOD_RESET_SET=0xE0U
}TAxCCTL_OUTMOD_value;

typedef enum{
    TAxCCTL__CCIE_DISABLE_INTERRUPT=0x0U,
    TAxCCTL__CCIE_ENABLE_INTERRUPT=0x10U
}TAxCCTL_CCIE_value;

typedef enum{
    TAxCCTL__OUT_LOW=0x0U,
    TAxCCTL__OUT_HIGH=0x4U
}TAxCCTL_OUT_value;

typedef enum{
    TAxCCTL__COV_NO_COV=0x0U,
    TAxCCTL__COV_YES_COV=0x2U
}TAxCCTL_COV_value;

typedef enum{
    TAxCCTL__CCIFG_NO_INTERRUPT=0x0U,
    TAxCCTL__CCIFG_INTERRUPT_PENDING=0x1U
}TAxCCTL_CCIFG_value;

typedef struct{
    const eTimerAddress port_address;
    const TAxCTL_CLK_value clk;
    const TAxCTL_ID_value id;
    const TAxCTL_MC_value mc;
}timer_config;

#define FULL_PERIOD 27240U
#define HALF_PERIOD (FULL_PERIOD/2U)


void timer_access(const timer_config* timer_io, timer_register register_to_change, uint16_t register_mask, uint16_t timer_register_value);
void enable_timer_interrupt(const timer_config* timer_io, CCTL_register cctl);
void start_timer(const timer_config* timer_io);
void stop_timer(const timer_config* timer_io);
void timer_init(const timer_config* timer_io);
void set_timer_compare(const timer_config* timer_io, CCR_register ccr, uint16_t compare);
#endif /* TIMER_H_ */
