#include <gpio.h>
#include <timer.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>

#define UP 1
#define DOWN 0

void motor_init();
void set_rpm_max();
void set_rpm_min();
void set_rpm_pct(uint8_t percentage);
uint8_t set_cycle(uint16_t hertz);
void set_direction(uint8_t);
void get_direction();


