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

  gpio_pup_enable(M6812_PORTH);

  gpio_set_input(SET_PIN_H, 0);
  gpio_set_input(SET_PIN_H, 2);
  gpio_set_input(SET_PIN_H, 4);

  gpio_set_output(SET_PIN_H, 1);
  gpio_set_output(SET_PIN_H, 3);
  gpio_set_output(SET_PIN_H, 5);
  gpio_set_output(SET_PIN_H, 6);

  gpio_write_pin(M6812_PORTH, 1, 0);
  gpio_write_pin(M6812_PORTH, 3, 0);
  gpio_write_pin(M6812_PORTH, 5, 0);
  gpio_write_pin(M6812_PORTH, 6, 0);

}

char teclado_getch()
{

  uint8_t column = 0;

  timer_init(2);

  Optional read;
  do
  {
    if (gpio_read_pin(M6812_PORTH, 0).data == '0'){
      column = 2;
    }

    read = gpio_read_pin(M6812_PORTH, 2);
    if (gpio_read_pin(M6812_PORTH, 2).data == '0'){
      column = 1;
    }

    if (gpio_read_pin(M6812_PORTH, 4).data == '0'){
      column = 3;
    }

  } while (column == 0);


  timer_sleep(200);
  char aux = '0';

  gpio_write_pin(M6812_PORTH, 1, 1);
  gpio_write_pin(M6812_PORTH, 3, 1);
  gpio_write_pin(M6812_PORTH, 5, 1);
  gpio_write_pin(M6812_PORTH, 6, 1);

  if (column == 1) {
    gpio_write_pin(M6812_PORTH, 1, 0);
    if (gpio_read_pin(M6812_PORTH, 2).data == '0')
      aux = '1';
    gpio_write_pin(M6812_PORTH, 6, 0);
    if (gpio_read_pin(M6812_PORTH, 2).data == '0')
      aux = '4';
    gpio_write_pin(M6812_PORTH, 5, 0);
    if (gpio_read_pin(M6812_PORTH, 2).data == '0')
      aux = '7';
    gpio_write_pin(M6812_PORTH, 3, 0);
    if (gpio_read_pin(M6812_PORTH, 2).data == '0')
      aux = '*';
  }

  else if (column == 2) {
    gpio_write_pin(M6812_PORTH, 1, 0);
    if (gpio_read_pin(M6812_PORTH, 0).data == '0')
      aux = '2';
    gpio_write_pin(M6812_PORTH, 6, 0);
    if (gpio_read_pin(M6812_PORTH, 0).data == '0')
      aux = '5';
    gpio_write_pin(M6812_PORTH, 5, 0);
    if (gpio_read_pin(M6812_PORTH, 0).data == '0')
      aux = '8';
    gpio_write_pin(M6812_PORTH, 3, 0);
    if (gpio_read_pin(M6812_PORTH, 0).data == '0')
      aux = '0';
  }


  else if (column == 3) {
    gpio_write_pin(M6812_PORTH, 1, 0);
    if (gpio_read_pin(M6812_PORTH, 4).data == '0')
      aux = '1';
    gpio_write_pin(M6812_PORTH, 6, 0);
    if (gpio_read_pin(M6812_PORTH, 4).data == '0')
      aux = '4';
    gpio_write_pin(M6812_PORTH, 5, 0);
    if (gpio_read_pin(M6812_PORTH, 4).data == '0')
      aux = '7';
    gpio_write_pin(M6812_PORTH, 3, 0);
    if (gpio_read_pin(M6812_PORTH, 4).data == '0')
      aux = '*';
  }
  else {
    aux = 'T';
  }
  gpio_write_pin(M6812_PORTH, 1, 0);
  gpio_write_pin(M6812_PORTH, 3, 0);
  gpio_write_pin(M6812_PORTH, 5, 0);
  gpio_write_pin(M6812_PORTH, 6, 0);

  return aux;

}


char teclado_getch_imeout(uint32_t milis)
{

  uint8_t column = 0;

  timer_init(1);

  do
  {
    if (gpio_read_pin(M6812_PORTH, 0).data == 0){
    	column = 2;
    }
    if (gpio_read_pin(M6812_PORTH, 2).data == 0){
    	column = 1;
    }
    if (gpio_read_pin(M6812_PORTH, 4).data == 0){
    	column = 3;
    }
  } while ((column == 0) && (milis < timer_get_mili()));


  timer_sleep(10000);
  char aux = '0';

  if (column == 1) {
    if (gpio_read_pin(M6812_PORTH, 1).data == 1)
      aux = '1';
    if (gpio_read_pin(M6812_PORTH, 6).data == 1)
      aux = '4';
    if (gpio_read_pin(M6812_PORTH, 5).data == 1)
      aux = '7';
    if (gpio_read_pin(M6812_PORTH, 3).data == 1)
      aux = '*';
  }
  else if (column == 2) {
    if (gpio_read_pin(M6812_PORTH, 1).data == 1)
      aux = '2';
    if (gpio_read_pin(M6812_PORTH, 6).data == 1)
      aux = '5';
    if (gpio_read_pin(M6812_PORTH, 5).data == 1)
      aux = '8';
    if (gpio_read_pin(M6812_PORTH, 3).data == 1)
      aux = '0';
  }
  else if (column == 3) {
    if (gpio_read_pin(M6812_PORTH, 1).data == 1)
      aux = '3';
    if (gpio_read_pin(M6812_PORTH, 6).data == 1)
      aux = '6';
    if (gpio_read_pin(M6812_PORTH, 5).data == 1)
      aux = '9';
    if (gpio_read_pin(M6812_PORTH, 3).data == 1)
      aux = '#';
  }
  else {
    aux = 'T';
  }

  return aux;
 return aux;
