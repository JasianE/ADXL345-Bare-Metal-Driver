#include <stdint.h>
#include "gpio.h"

/* INTERFACING WITH GPIO */
/*
GPIOA: 0x4202 0000 - 03FF -- Start of GPIO peripherals
*/

int main(void);

/* MAIN SUPERLOOP */

int main(void){
    uint16_t pin = PIN('A', 3);
    gpio_set_mode(pin, GPIO_MODE_OUTPUT);

    while (1) {

    }
    return 0;
}
