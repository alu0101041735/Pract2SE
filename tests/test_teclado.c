/**
 * \file test_teclado.c
 * \author David Martín Martín
 * \author Daniel Paz Marcos
 * */

#include <gpio.h>
#include <timer.h>
#include <teclado.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>


int main(void)
{

  teclado_init();

  while (1) {

    char test = teclado_getch();

    serial_send(test);
    serial_print("\r\n");
    //serial_print("test");

  }


  return 0;
}
