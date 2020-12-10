#include "gpio.h"
#include <timer.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>


int *readPort(uint8_t port)
{

  static int read[8];

  read[0] = gpio_read_pin(port, 0).data;
  read[1] = gpio_read_pin(port, 1).data;
  read[2] = gpio_read_pin(port, 2).data;
  read[3] = gpio_read_pin(port, 3).data;
  read[4] = gpio_read_pin(port, 4).data;
  read[5] = gpio_read_pin(port, 5).data;
  read[6] = gpio_read_pin(port, 6).data;
  read[7] = gpio_read_pin(port, 7).data;

  return read;
  
}


void setNumber(int number[8], int port, int segment, int maxsegments)
{
  int i;

  for (i = 0; i < maxsegments; i++) {
    if (i == segment) {
      gpio_write_pin(port, i, 1);
    }
    else {
      gpio_write_pin(port, i, 0);
    }
  }

  int pins[4];
  pins[0] = number[4];
  pins[1] = number[5];
  pins[2] = number[6];
  pins[3] = number[7];


  gpio_write_pin(port, 4, pins[0]);
  gpio_write_pin(port, 5, pins[1]);
  gpio_write_pin(port, 6, pins[2]);
  gpio_write_pin(port, 7, pins[3]);

}


int main() 
{
  serial_init();
  gpio_pup_disable_(M6812_PORTH);
  gpio_set_output_all_reg(SET_PIN_H);
  gpio_set_input_all_reg(SET_PIN_G);

  int segment = 0;
  int max_segment_number = 4;

  while(1) {
    int *number;
    number = readPort(M6812_PORTG);
    setNumber(number, M6812_PORTH, segment, max_segment_number);

    ++segment;

    if (segment >= max_segment_number)
      segment = 0;
  }
}
