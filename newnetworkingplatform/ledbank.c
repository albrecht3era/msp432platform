/*
 * ledbank.c
 *
 *  Created on: Oct 2, 2019
 *      Author: albrechter
 */
#include "gpio.h"
#include "ledbank.h"

extern const gpio redLED;
extern const gpio greenLED;
extern const gpio yellowLED;
extern const gpio LEDTURNOFF_R;
extern const gpio LEDTURNOFF_B;

void led_init(void){
    gpio_init(&greenLED);
    gpio_init(&redLED);
    gpio_init(&yellowLED);
    gpio_init(&LEDTURNOFF_R);
    gpio_init(&LEDTURNOFF_B);
    gpio_clear(&LEDTURNOFF_R);
    gpio_clear(&LEDTURNOFF_B);
    gpio_clear(&greenLED);
    gpio_clear(&redLED);
    gpio_clear(&yellowLED);
}

void led_idle_mode(void){
    gpio_set(&greenLED);
    gpio_clear(&redLED);
    gpio_clear(&yellowLED);
}

void led_busy_mode(void){
    gpio_set(&yellowLED);
    gpio_clear(&redLED);
    gpio_clear(&greenLED);
}

void led_collision_mode(void){
    gpio_set(&redLED);
    gpio_clear(&yellowLED);
    gpio_clear(&greenLED);
}
