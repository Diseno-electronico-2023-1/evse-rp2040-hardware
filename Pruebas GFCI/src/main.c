/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */



#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include <zephyr/drivers/pwm.h>

#include <zephyr/drivers/gpio.h>

#include <zephyr/drivers/uart.h>
#include <string.h>

#include <zephyr/drivers/display.h>
#include <zephyr/logging/log.h>


#define PIN GPIO_PIN(0, 2) // GPIO2 en la Raspberry Pi Pico

void main(void)
{
    const struct device *dev;
    int ret;

    dev = device_get_binding(DT_LABEL(DT_NODELABEL(gpio0)));
    if (dev == NULL) {
        printk("No se pudo obtener el dispositivo GPIO\n");
        return;
    }

    ret = gpio_pin_configure(dev, PIN, GPIO_INPUT);
    if (ret != 0) {
        printk("Error al configurar el pin GPIO\n");
        return;
    }

    while (1) {
        int value = gpio_pin_get(dev, PIN);
        if (value < 0) {
            printk("Error al leer el valor del pin\n");
            return;
        }

        printk("Valor del pin: %d\n", value);
        k_sleep(K_MSEC(1000));
    }
}
