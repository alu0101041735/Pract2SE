#include <gpio.h>
#include <timer.h>
#include <teclado.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>


int main()
{

  teclado_init();

  while (1) {

    char test = teclado_getch();

    serial_send(test);
    serial_print("\n\n");

  }


  return 0;
}
