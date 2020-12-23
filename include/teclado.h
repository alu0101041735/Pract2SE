/**
 * \file teclado.h
 * \author Daniel Paz Marcos
 * \author David Martín Martín
 * */

#ifndef TECLADO_H
#define TECLADO_H

#include <types.h>

#define F1 0x01000000
#define F2 0x00000010
#define F3 0x00000100
#define F4 0x00010000

#define C1 0x00100000
#define C2 0x10000000
#define C3 0x00001000

void teclado_init();

uint8_t teclado_getch();

uint8_t teclado_getch_timeout(uint16_t milis);


#endif
