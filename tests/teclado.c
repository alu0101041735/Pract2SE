#include <gpio.h>
#include <timer.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>


uint8_t readPort(uint8_t port)
{

  uint8_t read;

  read |=  0 << gpio_read_pin(port, 0).data;
  read |=  1 << gpio_read_pin(port, 1).data;
  read |=  2 << gpio_read_pin(port, 2).data;
  read |=  3 << gpio_read_pin(port, 3).data;
  read |=  4 << gpio_read_pin(port, 4).data;
  read |=  5 << gpio_read_pin(port, 5).data;
  read |=  6 << gpio_read_pin(port, 6).data;
  read |=  7 << gpio_read_pin(port, 7).data;

  return read;
  
}


uint8_t processInput(uint8_t number) {

  uint8_t aux;


  switch(number) {
    case(0x01100000):
      aux = 0x00000001;
      break;
    case(0x11000000):
      aux = 0x00000010;
      break;
    case(0x01001000):
      break;
    case(0x00000000):
      break;
    case(0x00000000):
      break;
    case(0x00000000):
      break;
    case(0x00000000):
      break;
    case(0x00000000):
      break;
    case(0x00000000):
      break;
    case(0x00000000):
      break;
    case(0x00000000):
      break;
    case(0x00000000):
      break;
    default:
      break;
  }
}


int main() 
{
  serial_init();
  gpio_pup_disable_(M6812_PORTH);
  gpio_set_input_all_reg(SET_PIN_G);

  uint8_t number;
  uint8_t value;

  while(1) {
    number = readPort(M6812_PORTG);

    value = processinput(number);

    serial_printbinbyte(number);
    serial_print("\n\n");
  }

}
