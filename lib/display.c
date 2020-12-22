#include <display.h>

display_data display;

void print_refresh_display() {
	serial_print("\n\rrefresh");
}
void print_update_val() {
	serial_print("\n\rupdate");
}
int main() 
{
	uint8_t digitos[4];
	sieteSeg_init();
	serial_init();
	//init timer
	timer_init(3);
	//refresh every 10ms
	timer_repeat_call(10000, refresh_display);
	//timer_repeat_call(1000, print_refresh_display);
	//update value every 2ms
	//timer_repeat_call(100, update_val);
	//timer_repeat_call(1000, print_update_val);
	serial_print("\n\rprueba");

	digitos[0] = 1;
	digitos[1] = 2;
	digitos[2] = 3;
	digitos[3] = 4;
	while (1) {
		static uint16_t valor = 0;
		if (valor > 9999)
			valor = 0;
		//leer teclado y pedir numero
		//digitos[0] += 1;
		//if (digitos[0] > 8)
		//	digitos[0] = 0;
		//digitos[1] = 2;
		//digitos[2] = 3;
		//digitos[3] = 4;
		//sieteSeg_digitos(digitos);
		//serial_print("\n\rprueba");
		//valor += 1;
		sieteSeg_valor(valor);
	}
}


void sieteSeg_init() {
	display.value_array[0] = 1;
	display.value_array[1] = 2;
	display.value_array[2] = 3;
	display.value_array[3] = 4;
	display.queued_value_array[0] = 1;
	display.queued_value_array[1] = 2;
	display.queued_value_array[2] = 3;
	display.queued_value_array[3] = 4;
	display.current_display = 0x01;
	display.update_queued = 0;

	gpio_pup_disable_(M6812_PORTG);
	gpio_set_output_all_reg(M6812_DDRG);
}


void sieteSeg_digitos(uint8_t* new_digits) {
	uint8_t mask = 0x0F;
	display.queued_value_array[0] = new_digits[0] & mask;
	display.queued_value_array[1] = new_digits[1] & mask;
	display.queued_value_array[2] = new_digits[2] & mask;
	display.queued_value_array[3] = new_digits[3] & mask;
	display.update_queued = 1;
}

void sieteSeg_valor(uint16_t newValue) {
	uint16_t temp = newValue;
	uint8_t index = 0;
	while (temp >= 0 && index < 4) {
		display.queued_value_array[index] = temp % 10;
		++index;
		temp /= 10;
	}
	display.update_queued = 1;
}


void update_val() {
	if (display.update_queued) {
		//uint8_t *aux_ptr = display.value_array;
		//*display.value_array = *display.queued_value_array;
		//*display.queued_value_array = aux_ptr;
		uint8_t size = 4;
		uint8_t i;
		for (i = 0 ; i < size; ++i) {
			display.value_array[i] = display.queued_value_array[i];
		}
		display.update_queued = 0;
	}
}


void refresh_display() {
	update_val();
	if (display.current_display > 8) {
		display.current_display = 0x01;
		display.current_digit = 0;
	}

	/* The port_data variable will hold the 7 segment
	 * display to be enabled on it's 4 most significant bits
	 * and the number to display on the other 4 bits.
	 * 			       selected 
	 *				 		 display  digit
	 * port_data = xxxx     xxxx
	 */

	uint8_t digit = display.value_array[display.current_digit];
	digit &= 0x0F;
	serial_print("\n\rdigito: ");
	serial_printdecbyte(digit);

	uint8_t port_data = (display.current_display << 4) | digit;
	serial_print("\n\rdisplay: ");
	serial_printbinbyte(display.current_display);

	gpio_write_port(M6812_PORTG, port_data);
	display.current_display = display.current_display << 0x01;
	++display.current_digit;

}