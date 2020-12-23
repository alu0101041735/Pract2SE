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
void set_rpm_pct(int8_t percentage);


