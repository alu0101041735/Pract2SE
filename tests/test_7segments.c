#include "gpio.h"
#include <timer.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>

void sieteSeg_init();
void sieteSeg_digitos(uint8_t*);
void sieteSeg_valor(uint16_t);
void update_val();
void refresh_display();

//int *readPort(uint8_t);
//void setNumber(uint8_t number[8], uint8_t port, uint8_t segment, uint8_t axsegments);

typedef struct display_data {
	uint8_t value_array[4];
	uint8_t queued_value_array[4];
	uint8_t current_digit;
	uint8_t current_display;
} display_data;

display_data display;

int main() 
{
	uint8_t digitos[4];
	sieteSeg_init();
	//init timer
	timer_init(3);
	//refresh every 10ms
	timer_schelude_call(10000, refresh_display);
	//update value every 2ms
	timer_schedule_call(500000, update_val);

	while (1) {
		//leer teclado y pedir numero
		digitos[0] = 1;
		digitos[1] = 2;
		digitos[2] = 3;
		digitos[3] = 4;
		sieteSeg_digitos(digitos);
	}
}


void sieteSeg_init() {
	display.current_value = 0;
	display.queued_value = 0;
	display.current_display = 0x01;

	gpio_pup_disable(M6812_PORTG);
	gpio_set_output_all_reg(M6812_PORTG);
}


void sieteSeg_digitos(uint8_t* new_digits) {
	uint8_t mask = 0x0F;
	display.queued_value_array[0] = new_digits[0] & mask;
	display.queued_value_array[1] = new_digits[1] & mask;
	display.queued_value_array[2] = new_digits[2] & mask;
	display.queued_value_array[3] = new_digits[3] & mask;
}

void sieteSeg_valor(uint16_t newValue) {
	uint16_t temp = newValue;
	uint8_t index = 0;
	while (temp > 0 && index < 4) {
		display.queued_value_array[index] = temp % 10;
		++index;
		temp /= 10;
	}
}


void update_val() {
	display.queued_value =  newValue;
	uint8_t* aux_ptr = display.value_array;
	display.value_array = display.queued_value_array;
	display.queued_value_array = aux_ptr;
}


void refresh_display() {
	if (current_display > 8) {
		current_display = 0x01;
		display.current_digit = 0;
	}

	/* The port_data variable will hold the 7segment
	 * display to ve enabled on it's 4 most significant bits
	 * and the number to display on the other 4 bits.
	 * 			       selected 
	 *				 		 display  digit
	 * port_data = xxxx     xxxx
	 */
	uint8_t digit = display.value_array[display.current_digit];
	digit &= 0x0F;

	uint8_t port_data = (current_display << 4) | digit;

	gpio_write_port(port_data);
	display.current_display = display.current_display << 0x01;
	++display.current_digit;

}
