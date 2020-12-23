#include <motor.h>
#include <pwm.h>

void motor_init() {
	timer_init(3);
	pwm_set_clock(RELOJ_A, 7, GRANO_FINO, 24);
	pwm_set_polarity(0, ALTA);
	pwm_aling(ALINEAMIENTO_IZQ, 0);
	pwm_period(200,0);
	pwm_habilitacion_canal(0);
}

void set_rpm_pct(int8_t pct) {
	if (pct > 100) {
		pct = 100;
	} else if (pct < 0) {
		pct = 0;
	}
	
	pwm_modificar_porcentaje(pct,0);
}
