#include <stdint.h>
#pragma once
#ifndef GPIO_H
#define GPIO_H

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
    uint32_t pin_number = PINNO(pin);

    gpio->MODER &= ~(3U << (pin_number * 2));
    gpio->MODER |= ((mode & 3) << (pin_number * 2));
}

#endif 