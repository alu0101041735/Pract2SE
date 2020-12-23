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

//int *readPort(uint8_t);
//void setNumber(uint8_t number[8], uint8_t port, uint8_t segment, uint8_t axsegments);

typedef struct display_data {
  uint8_t value_array[4];
  uint8_t queued_value_array[4];
  uint8_t current_digit;
  uint8_t current_display;
  int update_queued;
} display_data;

display_data display;

void print_refresh_display() {
  serial_print("\n\rrefresh");
}
void print_update_val() {
  serial_print("\n\rupdate");
}
int main() 
{
  gpio_set_output(M6812_DDRH, 6);
  gpio_set_output(M6812_DDRH, 5);
  gpio_set_output(M6812_DDRH, 4);
  gpio_set_output(M6812_DDRH, 3);
  gpio_set_input(M6812_DDRH, 2);
  gpio_set_input(M6812_DDRH, 1);
  gpio_set_input(M6812_DDRH, 0);

  gpio_write_pin(M6812_PORTH, 6, 0);
  gpio_write_pin(M6812_PORTH, 5, 0);
  gpio_write_pin(M6812_PORTH, 4, 0);
  gpio_write_pin(M6812_PORTH, 3, 1);

  serial_init();
  timer_init(3);

  uint8_t select = 0;
  Optional pulsacion1;
  Optional pulsacion2;
  Optional pulsacion3;
  while (1) {
    timer_sleep(1000000);
    switch(select % 4) {
      case 0:
        gpio_write_pin(M6812_PORTH, 6, 0);
        gpio_write_pin(M6812_PORTH, 5, 0);
        gpio_write_pin(M6812_PORTH, 4, 0);
        gpio_write_pin(M6812_PORTH, 3, 1);
        break;
      case 1:
        gpio_write_pin(M6812_PORTH, 6, 0);
        gpio_write_pin(M6812_PORTH, 5, 0);
        gpio_write_pin(M6812_PORTH, 4, 1);
        gpio_write_pin(M6812_PORTH, 3, 0);
        break;
      case 2:
        gpio_write_pin(M6812_PORTH, 6, 0);
        gpio_write_pin(M6812_PORTH, 5, 1);
        gpio_write_pin(M6812_PORTH, 4, 0);
        gpio_write_pin(M6812_PORTH, 3, 0);
        break;
      case 3:
        gpio_write_pin(M6812_PORTH, 6, 1);
        gpio_write_pin(M6812_PORTH, 5, 0);
        gpio_write_pin(M6812_PORTH, 4, 0);
        gpio_write_pin(M6812_PORTH, 3, 0);
        break;
    }
    pulsacion1 = gpio_read_pin(M6812_PORTH, 0);
    pulsacion2 = gpio_read_pin(M6812_PORTH, 1);
    pulsacion3 = gpio_read_pin(M6812_PORTH, 2);
    if (!pulsacion1.is_valid) {
      serial_print("\n\rError de lectura");
    } else {
      serial_print("\n\rPulsacion1: ");
      serial_printbinbyte(pulsacion1.data);
      serial_print("\n\rPulsacion2: ");
      serial_printbinbyte(pulsacion2.data);
      serial_print("\n\rPulsacion3: ");
      serial_printbinbyte(pulsacion3.data);
    }
    select += 1;
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
