/*
 * gpio.h
 *
 *  Created on: Oct 2, 2019
 *      Author: albrechter
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

typedef enum{
    PxIN=0x0U,
    PxOUT=0x2U,
    PxDIR=0x4U,
    PxREN=0x6U,
    PxSEL0=0xAU,
    PxSEL1=0xCU,
    PxSELC=0x16U,
    PxIES=0x18U,
    PxIE=0x1AU,
    PxIFG=0x1CU
}eRegister;

typedef enum{
    PIN0=0x1U,
    PIN1=0x2U,
    PIN2=0x4U,
    PIN3=0x8U,
    PIN4=0x10U,
    PIN5=0x20U,
    PIN6=0x40U,
    PIN7=0x80U
}ePin;

typedef enum{
    PIN0_SHIFT = 0U,
    PIN1_SHIFT=1U,
    PIN2_SHIFT=2U,
    PIN3_SHIFT=3U,
    PIN4_SHIFT=4U,
    PIN5_SHIFT=5U,
    PIN6_SHIFT=6U,
    PIN7_SHIFT=7U
}ePinShift;

typedef enum{
    PORT1_ADDR = 0x40004C00U,
    PORT2_ADDR = 0x40004C01U
}ePortAddress;

typedef enum{
    ACTIVE_LOW,
    ACTIVE_HIGH,
}eActiveConfig;

typedef enum{
    ON,
    OFF,
    TOGGLE
}eState;

typedef enum{
    RISING_EDGE=OFF,
    FALLING_EDGE=ON
}eInterruptEdge;

typedef enum{
    INPUT=OFF,
    OUTPUT=ON
}eDirection;

typedef struct{
    const ePin pin_num;
    const ePinShift pin_shift;
    const ePortAddress port_address;
    const eActiveConfig active_config;
    const eDirection direction;
}gpio;

void gpio_access(const gpio* io, eRegister io_register, eState state, eActiveConfig active_config, uint8_t register_value);
void gpio_init(const gpio* io);
void gpio_set(const gpio* io);
void gpio_clear(const gpio* io);
void gpio_set_interrupt(const gpio* io, eState state);
eState gpio_read(const gpio* io);
void gpio_toggle(const gpio* io);

#endif /* GPIO_H_ */
