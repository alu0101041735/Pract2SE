/**
 * @file display.h
 * @author David Martín Martín
 * @date 23 Dec 2020 
 * @brief 
 *
 * This header defines all the functions neccesary to use the
 * 7 segment display available in the disen experiments board.
 * To use it, first call sieteSeg_init(). After that you can 
 * call either sieteSeg_digitos() to display a four element 
 * array of uint8_t or sieteSeg_valor() for an uint16_t between
 * 0 and 9999.
 * */

#ifndef DISPLAY_H
#define DISPAY_H

#include <gpio.h>
#include <timer.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>


/**
 * @brief Function to init the 7 segmen display.
 * 
 * This function should be called before trying to show
 * anything on the display.
 */
void sieteSeg_init();
/**
 * @brief Function that displays a leght 4 array of uint8_t
 * @param digits This is an array of leght 4 holding the values
 * to be printed on each 7 segmen display.
 * 
 * This array should be always of size 4 with the first element
 * being displayed on the right-most 7 segment display of the board
 * and last at the left-most.
 */
void sieteSeg_digitos(uint8_t* digits);
/**
 * @brief Function that displays a number on the displays.
 * @param Value is the number to be printed on the display.
 * 
 * Unlike sieteSeg_digitos this function displays a 0 to 4
 * digit number.
 */
void sieteSeg_valor(uint16_t value);

/**
 * @brief Function that updates the current value to be printed.
 * 
 * This function ensures that the new value is printed,
 * although it should not be used by any end user as 
 * it is automatically called every 20ms.
 */
void sieteSeg_update();

/**
 * @brief Function that refreshes the display.
 * 
 * This function ensures that the new value is printed,
 * although it should not be used by any end user as 
 * sieteSeg_init alreay calls it for us.
 */
void sieteSeg_refresh();

/**
 * @brief Structure that holds the display information
 * 
 */
typedef struct display_data {
	uint8_t value_array[4];
	uint8_t queued_value_array[4];
	uint8_t current_digit;
	uint8_t current_display;
	int update_queued;
} display_data;

#endif
