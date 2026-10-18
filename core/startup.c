#include <stdint.h>

/* VECTOR TABLE DEFINITION AND RESET HANDLER */

__attribute__((naked, noreturn)) void _reset(void){
    extern long _sbss, _ebss, _sdata, _edata, _sidata;
    for (long *dst = &_sbss; dst < &_ebss; dst++) *dst = 0;
    for (long *dst = &_sdata, *src = &_sidata; dst < &_edata; dst++) *dst++ = *src++;
}

extern void _estack(void); // Trick compiler into thinking this is a function, actually the SP

__attribute__((section(".vectors"))) void (*const tab[16 + 91])(void) = {_estack, _reset};
