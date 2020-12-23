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

/**
 * \fn teclado_init
 * \brief Function That initializes the Keyboard
 * Configures port H to act as the keyboard input.
 * */
 void teclado_init();

 /**
  * \fn teclado_getch
  * \brief Function that returns a character read
  * */
uint8_t teclado_getch();

/**
 * \fn teclado_getch_timeout
 * \brief Function that returns a character read.
 * It has timeout
 * */
uint8_t teclado_getch_timeout(uint16_t milis);


#endif
