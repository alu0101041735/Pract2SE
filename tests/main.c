#include <sys/sio.h>
#include <teclado.h>
#include <motor.h>
#include <display.h>

sieteSeg_init();
teclado_init();
motor_init();
serial_init();
uint8_t digitos[4];
uint8_t valor = 0;
int8_t i;

serial_print("\r\nIniciando programa");
for ( i = 0; i < 4; ++i) {
  digitos[i] = 0;
}

serial_print("\r\nIniciando programa");
for ( i = 0; i < 4; ++i) {
  digitos[i] = 0;
}

sieteSeg_digitos(digitos);
timer_init(3);
timer_repeat_call(10000, refresh_display);

switch (character) {
  case '#':
    if ((teclado_getch() == '#') && (valor <= 100)) {
      serial_print("\r\nPorcentaje rpm: ");
      set_rpm_pct((int8_t) valor);
      serial_printdecbyte((int8_t) valor);
    } else {
      sieteSeg_valor(0);
    }
    i = 0;
    mult = 1;
    valor = 0;
    break;
  default:
    if (i < 4) {
      uint8_t j = 0;
      for (j = 0; j < i; ++j) {
        mult *= 10;		
      }
      static uint32_t nuevo_valor;
      nuevo_valor	= valor * 10 + (character - 48);
      if (nuevo_valor <= 100) {
        valor = nuevo_valor;
        digitos[i++] = character;
        sieteSeg_valor(valor);
      } else {
        serial_print("\r\nel numero debe estar entre 0 y 100");
      }
    }
    break;
}
}
}
