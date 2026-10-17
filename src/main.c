#include <stdint.h>

/* INTERFACING WITH GPIO */
/*
GPIOA: 0x4202 0000 - 03FF -- Start of GPIO peripherals
*/

int main(void);

/* PERIPHERAL DEFINITIONS */

// Create GPIO struct to represent the GPIO peripheral

struct gpio {
    volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFR[2];
};

#define GPIO(bank) ((struct gpio *) (0x42020000 + 0x400 * (bank)))
#define PIN(bank, num) ((((bank) - 'A') << 8) | (num))
#define PINNO(pin) (pin & 255)
#define PINBANK(pin) (pin >> 8)

enum {GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG};

static inline void gpio_set_mode(uint16_t pin, uint16_t mode){
    struct gpio *gpio = GPIO(PINBANK(pin));
    uint8_t pin_number = GPIO(PINNO(pin));

    gpio->MODER &= ~(3U << (pin_number * 2));
    gpio->MODER |= ((mode & 3) << (pin_number * 2));
}

/* VECTOR TABLE DEFINITION AND RESET HANDLER */

__attribute__((naked, noreturn)) void _reset(void){
    extern long _sbss, _ebss, _sdata, _edata, _sidata;
    for (long *dst = &_sbss; dst < _ebss; dst++) *dst = 0;
    for (long *dst = &_sdata, *src = &_sidata; dst < _edata; dst++) *dst++ = *src++;
}

extern void _estack(void); // Trick compiler into thinking this is a function, actually the SP

__attribute__((section(".vectors"))) void (*const tab[16 + 91])(void) = {_estack, _reset};

/* MAIN SUPERLOOP */

int main(void){
    uint16_t pin = PIN('A', 3);
    gpio_set_mode(pin, GPIO_MODE_OUTPUT);

    while (1) {

    }
    return 0;
}
