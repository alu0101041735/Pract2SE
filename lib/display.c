/**
 * \file display.c
 * \author David Martín Martín
 * \author Daniel Paz Marcos
 * */

#include <display.h>

display_data display;


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

  uint8_t port_data = (display.current_display << 4) | digit;

  gpio_write_port(M6812_PORTG, port_data);
  display.current_display = display.current_display << 0x01;
  ++display.current_digit;

}
