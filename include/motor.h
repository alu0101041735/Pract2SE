
/**
 * @file motor.h
 * @author David Martin Martin
 * @date 23 Dec 2020
 * @brief These are some comfort functions for sendig a
 * pwm signal from the first port of the first pwm module
 * of the M6812HC.
 */

#include <gpio.h>
#include <timer.h>
#include <types.h>
#include <sys/ports.h>
#include <sys/sio.h>

#define UP 1
#define DOWN 0

/**
 * @brief Initializes the necesary signals to send a pwm signal.
 */
void motor_init();
/**
 * @brief Sets the pwm duty cycle to the specified percentage.
 * @param percentage This is how much the signal will be on on
 * every cycle.
 */
void set_rpm_pct(int8_t percentage);


