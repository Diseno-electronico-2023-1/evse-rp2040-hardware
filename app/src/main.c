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



/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000


// ############# GPIO ###############

#define LED0_NODE DT_ALIAS(led0)
#define GFCI_test_NODE DT_ALIAS(led1)
#define GFCI_fault_NODE DT_ALIAS(led2)

// ############# PWM ###############

#define PERIOD PWM_SEC(1U)

// ############# ADC ###############

	#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

// ############# UART ###############

	#define UART_DEVICE_NODE DT_CHOSEN(zephyr_shell_uart)
	#define MSG_SIZE 32
	K_MSGQ_DEFINE(uart_msgq, MSG_SIZE, 10, 4);

// ############# I2C DISPLAY ###############
// #include "logo_image.h"
// #define DISPLAY_BUFFER_PITCH 128
// LOG_MODULE_REGISTER(display);

// ############# BOTONES ###############
#define SW0_NODE	DT_ALIAS(sw0)
#define SW1_NODE	DT_ALIAS(sw1)
#define SW2_NODE	DT_ALIAS(sw2)
#define SW3_NODE	DT_ALIAS(sw3)
#define SW4_NODE	DT_ALIAS(sw4)


// ############# GPIO ###############

static const struct gpio_dt_spec led_placa = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec GFCI_test = GPIO_DT_SPEC_GET(GFCI_test_NODE, gpios);
static const struct gpio_dt_spec GFCI_fault = GPIO_DT_SPEC_GET(GFCI_fault_NODE, gpios);

// ############# PWM ###############

static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));

// ############# ADC ###############

static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
			     DT_SPEC_AND_COMMA)
};

// ############# UART ###############
static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);
static char rx_buf[MSG_SIZE];
static int rx_buf_pos;


void serial_cb(const struct device *dev, void *user_data)
{
	uint8_t c;

	if (!uart_irq_update(uart_dev)) {
		return;
	}

	if (!uart_irq_rx_ready(uart_dev)) {
		return;
	}

	/* read until FIFO empty */
	while (uart_fifo_read(uart_dev, &c, 1) == 1) {
		if ((c == '\n' || c == '\r') && rx_buf_pos > 0) {
			/* terminate string */
			rx_buf[rx_buf_pos] = '\0';

			/* if queue is full, message is silently dropped */
			k_msgq_put(&uart_msgq, &rx_buf, K_NO_WAIT);

			/* reset the buffer (it was copied to the msgq) */
			rx_buf_pos = 0;
		} else if (rx_buf_pos < (sizeof(rx_buf) - 1)) {
			rx_buf[rx_buf_pos++] = c;
		}
		/* else: characters beyond buffer size are dropped */
	}
}

/*
 * Print a null-terminated string character by character to the UART interface
 */
void print_uart(char *buf)
{
	int msg_len = strlen(buf);

	for (int i = 0; i < msg_len; i++) {
		uart_poll_out(uart_dev, buf[i]);
	}
}

// ############# I2C DISPLAY ###############
// static const struct device *display = DEVICE_DT_GET(DT_NODELABEL(ssd1306));


// void print_uart(char *buf)
// {
// 	int msg_len = strlen(buf);

// 	for (int i = 0; i < msg_len; i++) {
// 		uart_poll_out(uart_dev, buf[i]);
// 	}
// }

// ############# BOTONES ###############
// static const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET_OR(SW0_NODE, gpios,
// 							      {0});
// static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET_OR(SW1_NODE, gpios,
// 							      {0});
// static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET_OR(SW2_NODE, gpios,
// 							      {0});
// static const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET_OR(SW3_NODE, gpios,
// 							      {0});
// static const struct gpio_dt_spec button4 = GPIO_DT_SPEC_GET_OR(SW4_NODE, gpios,
// 							      {0});

// static struct gpio_callback button_cb_data;

// /*
//  * The led0 devicetree alias is optional. If present, we'll use it
//  * to turn on the LED whenever the button is pressed.
//  */
// static struct gpio_dt_spec led = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led2), gpios,
// 						     {0});

// void button_pressed(const struct device *dev, struct gpio_callback *cb,
// 		    uint32_t pins)
// {
// 	printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
// }


void main(void)
{
	int ret;

	// ############# GPIO ###############

	// inicializar led placa
	if (!gpio_is_ready_dt(&led_placa)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led_placa, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	// inicializar GFCI_test
	if (!gpio_is_ready_dt(&GFCI_test)) {
		return;
	}

	ret = gpio_pin_configure_dt(&GFCI_test, GPIO_INPUT);
	if (ret < 0) {
		return;
	}

	// inicializar GFCI_fault
	if (!gpio_is_ready_dt(&GFCI_fault)) {
		return;
	}

	ret = gpio_pin_configure_dt(&GFCI_fault, GPIO_INPUT);
	if (ret < 0) {
		return;
	}

	printk("GPIOs configurados correctamente\n");


	// ############# ADC ###############
	
	int err;
	uint16_t buf;
	struct adc_sequence sequence = {
		.buffer = &buf,
		/* buffer size in bytes, not number of samples */
		.buffer_size = sizeof(buf),
	};
	/* Configure channels individually prior to sampling. */
	for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
		if (!device_is_ready(adc_channels[i].dev)) {
			printk("ADC controller device not ready\n");
			return;
		}

		err = adc_channel_setup_dt(&adc_channels[i]);
		if (err < 0) {
			printk("Could not setup channel #%d (%d)\n", i, err);
			return;
		}
	}

	printk("ADCs configurados correctamente\n");

	// ############# PWM ###############
	uint32_t period;
	uint8_t dir = 0U;
	int T;

	if (!device_is_ready(pwm_led0.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
		return;
	}

	printk("PWMs configurados correctamente\n");

	// ############# UART ###############
	char tx_buf[MSG_SIZE];

	if (!device_is_ready(uart_dev)) {
		printk("UART device not found!");
		return;
	}

	/* configure interrupt and callback to receive data */
	ret = uart_irq_callback_user_data_set(uart_dev, serial_cb, NULL);

	if (ret < 0) {
		if (ret == -ENOTSUP) {
			printk("Interrupt-driven UART API support not enabled\n");
		} else if (ret == -ENOSYS) {
			printk("UART device does not support interrupt-driven API\n");
		} else {
			printk("Error setting UART callback: %d\n", ret);
		}
		return;
	}
	uart_irq_rx_enable(uart_dev);

	printk("UART configurado correctamente\n");


	print_uart("Hello! I'm your echo bot.\r\n");
	print_uart("Tell me something and press enter:\r\n");

	// // ############# I2C DISPLAY ###############
	// if (display == NULL) {
    // LOG_ERR("device pointer is NULL");
    // return;
	// }

	// if (!device_is_ready(display)) {
	// 	LOG_ERR("display device is not ready");
	// 	return;
	// }

	// struct display_capabilities capabilities;
	// display_get_capabilities(display, &capabilities);

	// const uint16_t x_res = capabilities.x_resolution;
	// const uint16_t y_res = capabilities.y_resolution;

	// LOG_INF("x_resolution: %d", x_res);
	// LOG_INF("y_resolution: %d", y_res);
	// LOG_INF("supported pixel formats: %d", capabilities.supported_pixel_formats);
	// LOG_INF("screen_info: %d", capabilities.screen_info);
	// LOG_INF("current_pixel_format: %d", capabilities.current_pixel_format);
	// LOG_INF("current_orientation: %d", capabilities.current_orientation);
		
	// const struct display_buffer_descriptor buf_desc = {
	// 	.width = x_res,
	// 	.height = y_res,
	// 	.buf_size = x_res * y_res,
	// 	.pitch = DISPLAY_BUFFER_PITCH
	// };

	// if (display_write(display, 0, 0, &buf_desc, buf) != 0) {
	// 	LOG_ERR("could not write to display");
	// }

	// if (display_set_contrast(display, 0) != 0) {
	// 	LOG_ERR("could not set display contrast");
	// }
	// size_t ms_sleep = 5;

	// printk("I2C display configurado correctamente\n");


	// ############# BOTONES ###############








	// ############# INICIO DEL WHILE ###############

	while (1) {
		ret = gpio_pin_toggle_dt(&led_placa);
		if (ret < 0) {
			return;
		}
		k_msleep(SLEEP_TIME_MS);

		if (k_msgq_get(&uart_msgq, &tx_buf, K_FOREVER) == 0) {
			print_uart("Echo: ");
			print_uart(tx_buf);
			print_uart("\r\n");
		}
		
	}
	return 0;
}