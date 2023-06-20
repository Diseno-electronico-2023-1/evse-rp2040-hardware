/*
 * Copyright (c) 2016 Intel Corporation
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM.
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));
static const struct pwm_dt_spec pwm_led1 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led1));
static const struct pwm_dt_spec pwm_led2 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led2));

#define MIN_PERIOD PWM_SEC(1U) / 128U

// El máximo/mínimo para el periodo en nsec es: 125000000/7812500
#define PERIOD PWM_NSEC(100000000U)


void main(void)
{
	uint32_t period;
	int ret;

	printk("PWM-based blinky\n");

	if (!device_is_ready(pwm_led0.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
		return;
	}
	if (!device_is_ready(pwm_led1.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led1.dev->name);
		return;
	}
	if (!device_is_ready(pwm_led2.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led2.dev->name);
		return;
	}

	printk("Calibrating for channel %d...\n", pwm_led0.channel);
	printk("Calibrating for channel %d...\n", pwm_led1.channel);
	printk("Calibrating for channel %d...\n", pwm_led2.channel);

	period = PERIOD;
	ret = pwm_set_dt(&pwm_led0, period, period / 2U);
	if (ret) {
		printk("Error %d: failed to set pulse width\n", ret);
		return;
	}

	ret = pwm_set_dt(&pwm_led1, period, period / 2U);
	if (ret) {
		printk("Error %d: failed to set pulse width\n", ret);
		return;
	}

	ret = pwm_set_dt(&pwm_led2, period, period / 2U);
	if (ret) {
		printk("Error %d: failed to set pulse width\n", ret);
		return;
	}

	
	while (1) {
		
	}
}
