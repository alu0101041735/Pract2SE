/**
 * \file teclado.c
 * \author Daniel Paz Marcos
 * \author David Martín Martín
 * \date 21/12/20
 * */

#include <gpio.h>
#include <timer.h>
#include <teclado.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>


void teclado_init()
{

  gpio_pup_enable(M6812_PORTG);

  gpio_set_input(SET_PIN_G, 0);
  gpio_set_input(SET_PIN_G, 2);
  gpio_set_input(SET_PIN_G, 4);

  gpio_set_output(SET_PIN_G, 1);
  gpio_set_output(SET_PIN_G, 3);
  gpio_set_output(SET_PIN_G, 5);
  gpio_set_output(SET_PIN_G, 6);

  gpio_write_pin(M6812_PORTG, 1, 0);
  gpio_write_pin(M6812_PORTG, 3, 0);
  gpio_write_pin(M6812_PORTG, 5, 0);
  gpio_write_pin(M6812_PORTG, 6, 0);

}

char teclado_getch()
{

  uint8_t column = 0;

  timer_init(1);

  Optional read;
  do
  {
    read = gpio_read_pin(M6812_PORTG, 0);
    if (read.data == '0'){
    	column = 2;
    }

    read = gpio_read_pin(M6812_PORTG, 2);
    if (read.data == '0'){
    	column = 1;
    }

    read = gpio_read_pin(M6812_PORTG, 4);
    if (read.data == '0'){
    	column = 3;
    }

  } while (column == 0);


  timer_sleep(10000);
  char aux = '0';

  if (column == 1) {
    if (gpio_read_pin(M6812_PORTG, 1).data == 1)
      aux = '1';
    if (gpio_read_pin(M6812_PORTG, 6).data == 1)
      aux = '4';
    if (gpio_read_pin(M6812_PORTG, 5).data == 1)
      aux = '7';
    if (gpio_read_pin(M6812_PORTG, 3).data == 1)
      aux = '*';
  }
  else if (column == 2) {
    if (gpio_read_pin(M6812_PORTG, 1).data == 1)
      aux = '2';
    if (gpio_read_pin(M6812_PORTG, 6).data == 1)
      aux = '5';
    if (gpio_read_pin(M6812_PORTG, 5).data == 1)
      aux = '8';
    if (gpio_read_pin(M6812_PORTG, 3).data == 1)
      aux = '0';
  }
  else if (column == 3) {
    if (gpio_read_pin(M6812_PORTG, 1).data == 1)
      aux = '3';
    if (gpio_read_pin(M6812_PORTG, 6).data == 1)
      aux = '6';
    if (gpio_read_pin(M6812_PORTG, 5).data == 1)
      aux = '9';
    if (gpio_read_pin(M6812_PORTG, 3).data == 1)
      aux = '#';
  }
  else {
    aux = 'T';
  }

  return aux;

}


char teclado_getch_imeout(uint32_t milis)
{

  uint8_t column = 0;

  timer_init(1);

  do
  {
    if (gpio_read_pin(M6812_PORTG, 0).data == 0){
    	column = 2;
    }
    if (gpio_read_pin(M6812_PORTG, 2).data == 0){
    	column = 1;
    }
    if (gpio_read_pin(M6812_PORTG, 4).data == 0){
    	column = 3;
    }
  } while ((column == 0) && (milis < timer_get_mili()));


  timer_sleep(10000);
  char aux = '0';

  if (column == 1) {
    if (gpio_read_pin(M6812_PORTG, 1).data == 1)
      aux = '1';
    if (gpio_read_pin(M6812_PORTG, 6).data == 1)
      aux = '4';
    if (gpio_read_pin(M6812_PORTG, 5).data == 1)
      aux = '7';
    if (gpio_read_pin(M6812_PORTG, 3).data == 1)
      aux = '*';
  }
  else if (column == 2) {
    if (gpio_read_pin(M6812_PORTG, 1).data == 1)
      aux = '2';
    if (gpio_read_pin(M6812_PORTG, 6).data == 1)
      aux = '5';
    if (gpio_read_pin(M6812_PORTG, 5).data == 1)
      aux = '8';
    if (gpio_read_pin(M6812_PORTG, 3).data == 1)
      aux = '0';
  }
  else if (column == 3) {
    if (gpio_read_pin(M6812_PORTG, 1).data == 1)
      aux = '3';
    if (gpio_read_pin(M6812_PORTG, 6).data == 1)
      aux = '6';
    if (gpio_read_pin(M6812_PORTG, 5).data == 1)
      aux = '9';
    if (gpio_read_pin(M6812_PORTG, 3).data == 1)
      aux = '#';
  }
  else {
    aux = 'T';
  }

  return aux;
 return aux;

}
