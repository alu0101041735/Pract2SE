/**
 * \file teclado.c
 * \author Daniel Paz Marcos
 * \author David Martín Martín
 * \date 21/12/20
 * */

#include <gpio.h>
#include <timer.h>
#include <teclado.h>
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

uint8_t set_and_read(uint8_t port, uint8_t pin, uint8_t port2, uint8_t pin2) {

  gpio_write_pin(port, pin, 0);
  Optional opt;
  opt = gpio_read_pin(port2, pin2);
  gpio_write_pin(port, pin, 1);
  if (opt.is_valid) 
    return !opt.data;
  else return 0;
}

uint8_t teclado_getch()
{

  //timer_sleep(20000);

  uint8_t column = 0;

  timer_init(3);

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

  } while (column == 0);


  timer_sleep(20000);
  uint8_t aux = '0';

  gpio_write_pin(M6812_PORTH, 1, 1);
  gpio_write_pin(M6812_PORTH, 3, 1);
  gpio_write_pin(M6812_PORTH, 5, 1);
  gpio_write_pin(M6812_PORTH, 6, 1);

  uint8_t port = M6812_PORTH;
  if (column == 1) {
    if (set_and_read(port, 1, port, 2)) {
      aux = '1';
    }
    else if (set_and_read(port, 6, port, 2)) {
      aux = '4';
    }
    else if (set_and_read(port, 5, port, 2)) {
      aux = '7';
    }
    else if (set_and_read(port, 3, port, 2)) {
      aux = '*';
    }
    gpio_write_pin(port, 1, 0);
    gpio_write_pin(port, 6, 0);
    gpio_write_pin(port, 5, 0);
    gpio_write_pin(port, 3, 0);
    while (gpio_read_pin(M6812_PORTH, 2).data == 0);
  }

  else if (column == 2) {
    if (set_and_read(port, 1, port, 0)) {
      aux = '2';
    }
    else if (set_and_read(port, 6, port, 0)) {
      aux = '5';
    }
    else if (set_and_read(port, 5, port, 0)) {
      aux = '8';
    }
    else if (set_and_read(port, 3, port, 0)) {
      aux = '0';
    }
    gpio_write_pin(port, 1, 0);
    gpio_write_pin(port, 6, 0);
    gpio_write_pin(port, 5, 0);
    gpio_write_pin(port, 3, 0);
    while (gpio_read_pin(M6812_PORTH, 0).data == 0);
  }


  else if (column == 3) {
    if (set_and_read(port, 1, port, 4)) {
      aux = '3';
    }
    else if (set_and_read(port, 6, port, 4)) {
      aux = '6';
    }
    else if (set_and_read(port, 5, port, 4)) {
      aux = '9';
    }
    else if (set_and_read(port, 3, port, 4)) {
      aux = '#';
    }
    gpio_write_pin(port, 1, 0);
    gpio_write_pin(port, 6, 0);
    gpio_write_pin(port, 5, 0);
    gpio_write_pin(port, 3, 0);
    while (gpio_read_pin(M6812_PORTH, 4).data == 0);
  }
  else {
    aux = 'T';
  }

  return aux;

}


uint8_t teclado_getch_timeout(uint16_t milis)
{

  while ((gpio_read_pin(M6812_PORTH, 2).data == 0) ||
      (gpio_read_pin(M6812_PORTH, 0).data == 0) ||
      (gpio_read_pin(M6812_PORTH, 4).data == 0)) {


  }
  timer_sleep(20000);

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


  timer_sleep(20000);
  uint8_t aux = '0';

  gpio_write_pin(M6812_PORTH, 1, 1);
  gpio_write_pin(M6812_PORTH, 3, 1);
  gpio_write_pin(M6812_PORTH, 5, 1);
  gpio_write_pin(M6812_PORTH, 6, 1);

  if (column == 1) {
    gpio_write_pin(M6812_PORTH, 1, 0);
    if (gpio_read_pin(M6812_PORTH, 2).data == 0)
      aux = '1';
    gpio_write_pin(M6812_PORTH, 6, 0);
    if (gpio_read_pin(M6812_PORTH, 2).data == 0)
      aux = '4';
    gpio_write_pin(M6812_PORTH, 5, 0);
    if (gpio_read_pin(M6812_PORTH, 2).data == 0)
      aux = '7';
    gpio_write_pin(M6812_PORTH, 3, 0);
    if (gpio_read_pin(M6812_PORTH, 2).data == 0)
      aux = '*';
  }

  else if (column == 2) {
    gpio_write_pin(M6812_PORTH, 1, 0);
    if (gpio_read_pin(M6812_PORTH, 0).data == 0)
      aux = '2';
    gpio_write_pin(M6812_PORTH, 6, 0);
    if (gpio_read_pin(M6812_PORTH, 0).data == 0)
      aux = '5';
    gpio_write_pin(M6812_PORTH, 5, 0);
    if (gpio_read_pin(M6812_PORTH, 0).data == 0)
      aux = '8';
    gpio_write_pin(M6812_PORTH, 3, 0);
    if (gpio_read_pin(M6812_PORTH, 0).data == 0)
      aux = '0';
  }


  else if (column == 3) {
    gpio_write_pin(M6812_PORTH, 1, 0);
    if (gpio_read_pin(M6812_PORTH, 4).data == 0)
      aux = '1';
    gpio_write_pin(M6812_PORTH, 6, 0);
    if (gpio_read_pin(M6812_PORTH, 4).data == 0)
      aux = '4';
    gpio_write_pin(M6812_PORTH, 5, 0);
    if (gpio_read_pin(M6812_PORTH, 4).data == 0)
      aux = '7';
    gpio_write_pin(M6812_PORTH, 3, 0);
    if (gpio_read_pin(M6812_PORTH, 4).data == 0)
      aux = '*';
  }
  else {
    aux = 'T';
  }
  gpio_write_pin(M6812_PORTH, 1, 1);
  gpio_write_pin(M6812_PORTH, 3, 1);
  gpio_write_pin(M6812_PORTH, 5, 1);
  gpio_write_pin(M6812_PORTH, 6, 1);

  return aux;
}
