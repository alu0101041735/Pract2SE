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

  char caracter;
  while (1) {

    serial_print("\n\rPulse una tecla");
    serial_print("\r\n");
    caracter = teclado_getch();

    serial_print("\r\nHa pulsado la tecla: ");
    serial_send(caracter);
    serial_print("\r\n");

    serial_print("\r\nPulse una tecla para indicar el tiempo de espera");
    caracter = teclado_getch();
    serial_print("\r\n");
    caracter = teclado_getch_timeout((caracter - 48) * 1000);
    serial_send(caracter);
    serial_print("\r\n");

  }


  return 0;
}
