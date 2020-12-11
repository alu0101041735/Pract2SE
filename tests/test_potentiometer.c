
#include <timer.h>
#include <ad.h>
//#include "7Segmentos.c"
#include <timer.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>

int main() 
{
  uint16_t * valores;

  ad_pin_inicio(3,0);

  ad_modulo(0,0);

  ad_ocho_o_diez_bits(8,0);

  ad_ciclos_muestreo(2,0);

  ad_scanMode(1,0);

  ad_cantidadConversiones(1,0);

  ///Hasta aquí se han recogido todos los datos en modo interactivo, para poder hacer las pruebas más fácilmente.

  ad_activarInterrupMode(0); ///Me aseguro de desactivar las interrupciones
  ad_setUserFunction(0);
  ad_start(); ///se inicia el proceso
  timer_init(1);

  while (1)
  {
    valores = ad_wait_for_data(); ///espero a una lectura total de la secuencia. También se ejecutaría la rutina de usuario en caso de definirla.

    //sieteSeg_valor(valores[0]);

    //timer_repeat_call(100000, sieteSeg_valor(valores[0]));

  }

}
