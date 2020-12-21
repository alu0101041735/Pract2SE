#include <gpio.h>
#include <timer.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>

#define F1 0x01000000
#define F2 0x00000010
#define F3 0x00000100
#define F4 0x00010000

#define C1 0x00100000
#define C2 0x10000000
#define C3 0x00001000



void teclado_init()
{

  gpio_pup_disable_(M6812_PORTG);
  gpio_set_input_all_reg(SET_PIN_G);

}

char teclado_getch()
{

  uint8_t number = 0x00000000;
  do
  {
    number |=  0 << gpio_read_pin(M6812_PORTG, 0).data;
    number |=  1 << gpio_read_pin(M6812_PORTG, 1).data;
    number |=  2 << gpio_read_pin(M6812_PORTG, 2).data;
    number |=  3 << gpio_read_pin(M6812_PORTG, 3).data;
    number |=  4 << gpio_read_pin(M6812_PORTG, 4).data;
    number |=  5 << gpio_read_pin(M6812_PORTG, 5).data;
    number |=  6 << gpio_read_pin(M6812_PORTG, 6).data;
    number |=  7 << 0x00000000;

  } while (!number);

  char aux;

  if (number == (uint8_t)(F1 | C1))
	  aux = '1';
  else if (number == (uint8_t)(F1 | C2))
	  aux = '2';
  else if (number == (uint8_t)(F1 | C3))
	  aux = '3';
  else if (number == (uint8_t)(F2 | C1))
	  aux = '4';
  else if (number == (uint8_t)(F2 | C2))
	  aux = '5';
  else if (number == (uint8_t)(F2 | C3))
	  aux = '6';
  else if (number == (uint8_t)(F3 | C1))
	  aux = '7';
  else if (number == (uint8_t)(F3 | C2))
	  aux = '8';
  else if (number == (uint8_t)(F3 | C3))
	  aux = '9';
  else if (number == (uint8_t)(F4 | C1))
	  aux = '*';
  else if (number == (uint8_t)(F4 | C2))
	  aux = '0';
  else if (number == (uint8_t)(F4 | C3))
	  aux = '#';

  return aux;

}


char teclado_getch_imeout(uint32_t milis)
{

  timer_init(1);
  uint8_t number = 0x00000000;

  do {

    number |=  0 << gpio_read_pin(M6812_PORTG, 0).data;
    number |=  1 << gpio_read_pin(M6812_PORTG, 1).data;
    number |=  2 << gpio_read_pin(M6812_PORTG, 2).data;
    number |=  3 << gpio_read_pin(M6812_PORTG, 3).data;
    number |=  4 << gpio_read_pin(M6812_PORTG, 4).data;
    number |=  5 << gpio_read_pin(M6812_PORTG, 5).data;
    number |=  6 << gpio_read_pin(M6812_PORTG, 6).data;
    number |=  7 << 0x00000000;

  } while ((milis < timer_get_cycle()) && (!number));

  char aux;

  if (number == (uint8_t)(F1 | C1))
	  aux = '1';
  else if (number == (uint8_t)(F1 | C2))
	  aux = '2';
  else if (number == (uint8_t)(F1 | C3))
	  aux = '3';
  else if (number == (uint8_t)(F2 | C1))
	  aux = '4';
  else if (number == (uint8_t)(F2 | C2))
	  aux = '5';
  else if (number == (uint8_t)(F2 | C3))
	  aux = '6';
  else if (number == (uint8_t)(F3 | C1))
	  aux = '7';
  else if (number == (uint8_t)(F3 | C2))
	  aux = '8';
  else if (number == (uint8_t)(F3 | C3))
	  aux = '9';
  else if (number == (uint8_t)(F4 | C1))
	  aux = '*';
  else if (number == (uint8_t)(F4 | C2))
	  aux = '0';
  else if (number == (uint8_t)(F4 | C3))
	  aux = '#';

  return aux;

}


int main() 
{
  serial_init();

  while(1) {
    teclado_init();

    char test = teclado_getch();


    serial_print(test);
    serial_print("\n\n");
  }
}
