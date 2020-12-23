/***
 * \file test_7segments.c
 * \author Daniel Paz Marcos
 * \author David Martín Martín
 * */

#include <gpio.h>
#include <display.h>
#include <timer.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>
int main() 
{
  uint8_t digitos[4];
  sieteSeg_init();
  serial_init();
  serial_print("\n\rprueba");

  digitos[0] = 1;
  digitos[1] = 2;
  digitos[2] = 3;
  digitos[3] = 4;
  while (1) {
    static uint16_t valor = 0;
    serial_print("\r\nIntroduce un valor a mostrar");
    valor = serial_getdecword();
    if (valor > 9999)
      valor = 0;
    sieteSeg_valor(valor);
    serial_print("\r\nIntroduce cuatro digitos a mostrar: ");
    uint8_t i = 0;
    uint8_t index = 0;
    for ( i = 0; i < 4; ++i) {
	    digitos[index++] = serial_getdecbyte();
	    serial_print(" ");
    }

    sieteSeg_digitos(digitos);

  }
}


