#include "msp.h"
#include "gpio.h"
#include "ledbank.h"
#include "timer.h"
#include "state.h"


/**
 * main.c
 */

extern const gpio manchester;
extern const timer_config TIMERA;
eSM_State state;


void configure_clock(void);
void test_master_clock(void);
void error(void);
void main_program(void);

int main(void)
{
    main_program();
}

void main_program(void){
    volatile uint32_t i; // Lock CS module from unintended accesses

    /** Ramp the clock up to 48Mhz, test output on 4.3 **/
    configure_clock();
    test_master_clock();

    /** Initialize all 3 LED's on P1.0, P1.5, and P 2.1. P2.0 and P2.2 are turned off so only Green shows. **/
    led_init();


    /** Enable interrupt on rising edge to start. **/
    gpio_init(&manchester);
    NVIC_EnableIRQ(PORT2_IRQn);

//    if(gpio_read(&manchester) == ON){
        transition_idle();
        gpio_set_interrupt(&manchester, ON);
//    } else {
//        transition_collision();
//        gpio_set_interrupt(&manchester, OFF);
//    }

    /** Initialize timers **/
    timer_init(&TIMERA);
    set_timer_compare(&TIMERA, CCR0, FULL_PERIOD);
    enable_timer_interrupt(&TIMERA, CCTL0);

    while (1);
}

void error(void)
{
    volatile uint32_t i;

    while (1)
    {
        P1->OUT ^= BIT0;
        for(i = 20000; i > 0; i--);           // Blink LED forever
    }
}

void configure_clock(void){
    volatile uint32_t i;
    uint32_t currentPowerState;

    WDT_A->CTL = WDT_A_CTL_PW |
                 WDT_A_CTL_HOLD;            // Stop WDT

    P1->DIR |= BIT0;                        // P1.0 set as output

    /* NOTE: This example assumes the default power state is AM0_LDO.
     * Refer to  msp432p401x_pcm_0x code examples for more complete PCM
     * operations to exercise various power state transitions between active
     * modes.
     */

    /* Step 1: Transition to VCORE Level 1: AM0_LDO --> AM1_LDO */

    /* Get current power state, if it's not AM0_LDO, error out */
    currentPowerState = PCM->CTL0 & PCM_CTL0_CPM_MASK;
    if (currentPowerState != PCM_CTL0_CPM_0)
        error();

    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    if (PCM->IFG & PCM_IFG_AM_INVALID_TR_IFG)
        error();                            // Error if transition was not successful
    if ((PCM->CTL0 & PCM_CTL0_CPM_MASK) != PCM_CTL0_CPM_1)
        error();                            // Error if device is not in AM1_LDO mode

    /* Step 2: Configure Flash wait-state to 1 for both banks 0 & 1 */
    FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) |
            FLCTL_BANK0_RDCTL_WAIT_1;
    FLCTL->BANK1_RDCTL  = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK1_RDCTL_WAIT_MASK)) |
            FLCTL_BANK1_RDCTL_WAIT_1;

    /* Step 3: Configure DCO to 48MHz, ensure MCLK uses DCO as source*/
    CS->KEY = CS_KEY_VAL ;                  // Unlock CS module for register access
    CS->CTL0 = 0;                           // Reset tuning parameters
//    CS->CTL0 = CS_CTL0_DCORSEL_5;           // Set DCO to 48MHz
//    /* Select MCLK = DCO, no divider */
//    CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK) |
//            CS_CTL1_SELM_3;
    CS->CTL0 = CS_CTL0_DCORSEL_4;    // Set DCO to 24MHz
    CS->CTL1 = (CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK | CS_CTL1_DIVHS_MASK | CS_CTL1_DIVS_MASK | CS_CTL1_SELS_MASK)) | CS_CTL1_SELA__REFOCLK | CS_CTL1_SELS__DCOCLK | CS_CTL1_SELM__DCOCLK;

    CS->KEY = 0;
}

void test_master_clock(void){
    /* Step 4: Output MCLK to port pin to demonstrate 48MHz operation */
    P4->DIR |= BIT3;
    P4->SEL0 |=BIT3;                        // Output MCLK
    P4->SEL1 &= ~(BIT3);
}

//	/** Init GPIO **/
//	led_init();
//	gpio_init(&button);
//	//NVIC_EnableIRQ(PORT1_IRQn);
//	//gpio_set_interrupt(&button, ON);
//	while(1){
//	    P1OUT ^= 0x1;
//	}
//
//
//}
