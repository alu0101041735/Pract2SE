
#include <gpio.h>
#include <timer.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>


void sieteSeg_init();
void sieteSeg_digitos(uint8_t*);
void sieteSeg_valor(uint16_t);
void update_val();
void refresh_display();

typedef struct display_data {
	uint8_t value_array[4];
	uint8_t queued_value_array[4];
	uint8_t current_digit;
	uint8_t current_display;
	int update_queued;
} display_data;
