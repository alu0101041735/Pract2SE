/**
 * \file test_potentiometer.c
 * \author David Martín Martín
 * \author Daniel Paz Marcos
 * */

#include <timer.h>
#include <ad.h>
#include <timer.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>
#include <display.h>
#include <teclado.h>

int main() 
{
  uint16_t*  valor;

  sieteSeg_init();
  serial_init();
	char digitos[4];	
	serial_print("\r\nIniciando programa");
	digitos[0] = 0;
	digitos[1] = 0;
	digitos[2] = 0;
	digitos[3] = 0;
	sieteSeg_digitos(digitos);

  ad_pin_inicio(0,0);
  serial_print("\n\r");
  ad_modulo(0,0);
  serial_print("\n\r");
  ad_ocho_o_diez_bits(1,0);
  serial_print("\n\r");
  ad_ciclos_muestreo(4,0);
  serial_print("\n\r");
  ad_scanMode(1,0);
  serial_print("\n\r");
  ad_cantidadConversiones(4,0);
  serial_print("\n\r");



  ad_activarInterrupMode(0);
  ad_setUserFunction(NULL);
  ad_start();

  while (1)
  {
    valor = ad_wait_for_data();
    sieteSeg_valor(*valor);

  }

}
