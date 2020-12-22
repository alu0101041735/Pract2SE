#include <teclado.h>
#include <motor.h>
#include <display.h>
int main() {
	sieteSeg_init();
	teclado_init();
	motor_init();
	uint8_t digitos[4];
	uint8_t valor;
	int8_t i;
	
	for ( i = 0; i < 4; ++i) {
		digitos[i] = 0;
	}

	sieteSeg_digitos(digitos);

	i = 0;
	while (1) {
		uint8_t caracter = teclado_getch();
		switch (character) {
			case '#':
				if ((teclado_getch() == '#') && (valor < 100)) {
					set_rpm_pct(valor);
				} else {
					for ( i = 0; i < 4; ++i) {
						digitos[i] = 0;
						sieteSeg_valor(0);
					}
				}
				i = 0;
				break;
			case '':
				i = 0;
				break;
			default:
				if (i < 4) {
					uint8_t j = 0;
					uint8_t mult = 1;
					for (j = 0; j < i; ++j) {
						mult *= 10;		
					}
					valor += (character - 48) * mult;
					if (valor <= 100) {
						digitos[i++] = character;
						sieteSeg_digitos(digitos);
					}
				}
				break;
		}
	}
}
