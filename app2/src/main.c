/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */



#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>

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
#include <zephyr/display/cfb.h>
#include <zephyr/logging/log.h>



// ############# GPIO ###############

#define LED0_NODE DT_ALIAS(led0)
#define GFCI_test_NODE DT_ALIAS(led1)
#define GFCI_fault_NODE DT_ALIAS(led2)

// ############# PWM ###############

#define PERIOD PWM_NSEC(100000000U)

// ############# ADC ###############

#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

double tempC; 
double R2 = 100000;
double A = 0.7768951640E-3;
double B = 2.068786810E-4;
double C = 1.280087096E-7;
double KELVINCONSTANT = 273.15;

double AdcToCelsius(uint32_t rawValue);

// ############# UART ###############

//Command for PZEM
uint8_t cmd_read[8] = {0xF8, 0x04, 0x00, 0x00, 0x00, 0x0A, 0x64, 0x64};

//Reception variables
#define BUFFER_SIZE 25
uint8_t buffer[BUFFER_SIZE];
size_t buffer_len = 0;
uint8_t rx_data;
float voltage, current;

//Processing of data obtained
void pzem_reading(uint8_t *data, size_t length)
{
    // Check if the received data matches the expected response format
    if (length == 24 && data[0] == 0x04 && data[1] == 0x14) {
        // Extract the relevant information from the received data
        voltage = (data[2] << 8 | data[3]) / 10.0;
		current = (data[4] << 8 | data[5] | data[6] << 24 | data[7] << 16) / 1000.0;

        // Print the extracted values
        printf("Voltage: %.1f V\n", voltage);
        printf("Current: %.2f A\n", current);
    }
}

// ############# I2C DISPLAY ###############
#include "Chargers.h"
#include "Logo_b.h"
#define DISPLAY_BUFFER_PITCH 128
LOG_MODULE_REGISTER(display);


// ############# GPIO ###############

static const struct gpio_dt_spec led_placa = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec GFCI_test = GPIO_DT_SPEC_GET(GFCI_test_NODE, gpios);
static const struct gpio_dt_spec GFCI_fault = GPIO_DT_SPEC_GET(GFCI_fault_NODE, gpios);

// ############# BUTTONS ###############

#define SW3_NODE	DT_ALIAS(sw3)
#define SW0_NODE	DT_ALIAS(sw0)
#define SW1_NODE	DT_ALIAS(sw1)
#define SW2_NODE	DT_ALIAS(sw2)

#if !DT_NODE_HAS_STATUS(SW0_NODE, okay)
#error "Unsupported board: sw devicetree alias is not defined"
#endif
#if !DT_NODE_HAS_STATUS(SW1_NODE, okay)
#error "Unsupported board: sw devicetree alias is not defined"
#endif
#if !DT_NODE_HAS_STATUS(SW2_NODE, okay)
#error "Unsupported board: sw devicetree alias is not defined"
#endif
#if !DT_NODE_HAS_STATUS(SW3_NODE, okay)
#error "Unsupported board: sw devicetree alias is not defined"
#endif

static const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET_OR(SW0_NODE, gpios,
							      {0});
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET_OR(SW1_NODE, gpios,
							      {0});
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET_OR(SW2_NODE, gpios,
							      {0});
static const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET_OR(SW3_NODE, gpios,
							      {0});

static struct gpio_callback button0_cb_data;
static struct gpio_callback button1_cb_data;
static struct gpio_callback button2_cb_data;
static struct gpio_callback button3_cb_data;

void button0_pressed(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
	printk("Button0 pressed at %" PRIu32 "\n", k_cycle_get_32());
}
void button1_pressed(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
	printk("Button1 pressed at %" PRIu32 "\n", k_cycle_get_32());
}
void button2_pressed(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
	printk("Button2 pressed at %" PRIu32 "\n", k_cycle_get_32());
}
void button3_pressed(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
	printk("Button3 pressed at %" PRIu32 "\n", k_cycle_get_32());
}

// ############# PWM ###############

static const struct pwm_dt_spec pwm_rele1 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led1));
static const struct pwm_dt_spec pwm_rele2 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led2));
static const struct pwm_dt_spec pwm_pilot_out = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led3));

// ############# ADC ###############

static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
			     DT_SPEC_AND_COMMA)
};

// ############# UART ###############
const struct device *uart_pzem = DEVICE_DT_GET(DT_NODELABEL(pio1_uart0));

// ############# I2C DISPLAY ###############
static const struct device *display = DEVICE_DT_GET(DT_NODELABEL(ssd1306));

void main(void)
{
	printk("ingresa a 1\n");
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
	uint32_t rawValue;
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

	// ############# UART ###############
	if (!device_is_ready(uart_pzem)) {
		printk("UART device not found!");
		return 0;
	}

	// ############# PWM ###############
	uint32_t period;
	period = PERIOD;

	if (!device_is_ready(pwm_rele1.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_rele1.dev->name);
		return;
	}

	if (!device_is_ready(pwm_rele2.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_rele2.dev->name);
		return;
	}

	if (!device_is_ready(pwm_pilot_out.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_pilot_out.dev->name);
		return;
	}

	printk("PWMs configurados correctamente\n");

	// // ############# I2C DISPLAY ###############
	if (display == NULL) {
    LOG_ERR("device pointer is NULL");
    return;
	}

	if (!device_is_ready(display)) {
		LOG_ERR("display device is not ready");
		return;
	}

	struct display_capabilities capabilities;
	display_get_capabilities(display, &capabilities);

	const uint16_t x_res = capabilities.x_resolution;
	const uint16_t y_res = capabilities.y_resolution;

	LOG_INF("x_resolution: %d", x_res);
	LOG_INF("y_resolution: %d", y_res);
	LOG_INF("supported pixel formats: %d", capabilities.supported_pixel_formats);
	LOG_INF("screen_info: %d", capabilities.screen_info);
	LOG_INF("current_pixel_format: %d", capabilities.current_pixel_format);
	LOG_INF("current_orientation: %d", capabilities.current_orientation);
		
	const struct display_buffer_descriptor buf_desc = {
		.width = x_res,
		.height = y_res,
		.buf_size = x_res * y_res,
		.pitch = DISPLAY_BUFFER_PITCH
	};

	// ############# BUTTON ###############

	// Button 0
	if (!gpio_is_ready_dt(&button0)) {
		printk("Error: button3 device %s is not ready\n",
		       button0.port->name);
		return;
	}
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
		       ret, button0.port->name, button0.pin);
		return;
	}
	gpio_init_callback(&button0_cb_data, button0_pressed, BIT(button0.pin));
	gpio_add_callback(button0.port, &button0_cb_data);
	printk("Set up button0 at %s pin %d\n", button0.port->name, button0.pin);
	// Button 1
	if (!gpio_is_ready_dt(&button1)) {
		printk("Error: button1 device %s is not ready\n",
		       button1.port->name);
		return;
	}
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
		       ret, button1.port->name, button1.pin);
		return;
	}
	gpio_init_callback(&button1_cb_data, button1_pressed, BIT(button1.pin));
	gpio_add_callback(button1.port, &button1_cb_data);
	printk("Set up button1 at %s pin %d\n", button1.port->name, button1.pin);
	// Button 2
	if (!gpio_is_ready_dt(&button2)) {
		printk("Error: button2 device %s is not ready\n",
		       button2.port->name);
		return;
	}
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
		       ret, button2.port->name, button2.pin);
		return;
	}
	gpio_init_callback(&button2_cb_data, button2_pressed, BIT(button2.pin));
	gpio_add_callback(button2.port, &button2_cb_data);
	printk("Set up button2 at %s pin %d\n", button2.port->name, button2.pin);
	// Button 3
	if (!gpio_is_ready_dt(&button3)) {
		printk("Error: button3 device %s is not ready\n",
		       button3.port->name);
		return;
	}
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
		       ret, button3.port->name, button3.pin);
		return;
	}
	gpio_init_callback(&button3_cb_data, button3_pressed, BIT(button3.pin));
	gpio_add_callback(button3.port, &button3_cb_data);
	printk("Set up button3 at %s pin %d\n", button3.port->name, button3.pin);
	

	// ############# INICIO DEL PROGRAMA ###############
	printk("Press the button\n"); 
	//RELÉS OFF
	int izquierda_bt;
	int derecha_bt;
	int aceptar_bt;
	int atras_bt;
	ret = pwm_set_dt(&pwm_rele1, period, period / 2U);
		if (ret) {
			printk("Error %d: failed to set pulse width\n", ret);
			return;
		}

	ret = pwm_set_dt(&pwm_rele2, period, period / 2U);
		if (ret) {
			printk("Error %d: failed to set pulse width\n", ret);
			return;
		}

	// ret = pwm_set_dt(&pwm_pilot_out, period, period / 2U);
	// 	if (ret) {
	// 		printk("Error %d: failed to set pulse width\n", ret);
	// 		return;
	// 	}
	
	int fase_programa = 0;
	const uint8_t *current_image = buff;

	while (1)
	{

		//LECTURA DE CORRIENTE DE ENTRADA (SENSORES)
		//LECTURA DE VOLTAJE DE ENTRADA (SENSORES)
		//Send command
		for (size_t i = 0; i < sizeof(cmd_read); i++) {
        	uart_poll_out(uart_pzem, cmd_read[i]);
    	}

		//Receive an answer
		int len = uart_poll_in(uart_pzem, &rx_data);

		//Verification of the reception status
		if (len == -1)
		{
			printk("No data to receive!\n");
		}else if (len == 0)
		{
			printk("Successful data reception!\n"); 
		}else
		{
			printk("Failure to receive data!\n"); 
		}

		//Read data until the end of the answer
		while (len == 0)
		{
			uart_poll_in(uart_pzem, &rx_data);
			buffer[buffer_len] = rx_data;
            buffer_len++;

			if (buffer_len == 24)
			{
				len = -1; 
			}
		}

		//Processing of read data
		pzem_reading(buffer, buffer_len);

		//Reset buffer for the next packet
		buffer_len = 0; 
		k_sleep(K_MSEC(1000));

		//LECTURA DE TEMPERATURA (SENSORES)
		for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
			printk("- %s, channel %d: ",
			    	adc_channels[i].dev->name,
			    	adc_channels[i].channel_id);

			(void)adc_sequence_init_dt(&adc_channels[i], &sequence);


			err = adc_read(adc_channels[i].dev, &sequence);
			if (err < 0) {
				printk("Could not read (%d)\n", err);
				continue;
			} else {
				printk("RawValue %"PRIu16, buf);
			}

			rawValue = buf; 
			//Esta es la variable que contiene el valor de la temperatura
			tempC = AdcToCelsius(rawValue);
			printf(" = Temperature %.2f\n", tempC);
			k_sleep(K_MSEC(1000));
		}
		k_sleep(K_MSEC(1000));	
		

		display_write(display, 0, 0, &buf_desc, current_image);

		// Definimos las diferentes secciones que hay dentro del programa
		// Inicio, Selecciona corriente, ya esta cargando el carro?, carga, finalización
		
		izquierda_bt = gpio_pin_get_dt(&button0);
		derecha_bt = gpio_pin_get_dt(&button1);
		aceptar_bt = gpio_pin_get_dt(&button2);
		atras_bt = gpio_pin_get_dt(&button3);
		
		// Máquina de estados
		switch(fase_programa) {
			//case inicio:
			case 0:
				printk("inicio");
				current_image = buff;
				//:-) imprimir pantalla de inicio
				k_msleep(10000);
				fase_programa = 1;
			break;

			//case selecciona_corriente_6A:
			case 1:
				current_image = Char6;
				//:-) imprimir pantalla de selección corriente con 6A seleccionado

				if (aceptar_bt != 0) {
					// :-P asignar el valor a la variable corriente
					printk("Corriente 6A seleccionada\n");
					fase_programa = 3;

					k_msleep(10);
				}
				if (derecha_bt != 0){
					fase_programa = 2;

					k_msleep(10);
				}
			break;

			//case selecciona_corriente_16A:
			case 2:

				//:-) imprimir pantalla de selección corriente con 16A seleccionado
				current_image = Char16;
				if (aceptar_bt != 0) {
					printk("Corriente 16A seleccionada\n");
					// :-P asignar el valor a la variable corriente
					fase_programa = 3;

					k_msleep(10);
				}
				if (izquierda_bt != 0){
					fase_programa = 1;

					k_msleep(10);
				}
			break;

			// case comprobar si el carro esta conectado
			case 3:
				//:-) imprimir pantalla de mostrar que el carro esté conectado
				current_image = Char0;
				// :-P condicional para ver si el carro esta conectado y proceder a la carga
				if (aceptar_bt != 0) {
					printk("Caarga aceptada\n");
					// :-P asignar el valor a la variable corriente
					fase_programa = 4;

					k_msleep(10);
				}
				if (atras_bt != 0){
					fase_programa = 1;

					k_msleep(10);
				}
			break;

			//case cargando
			case 4:
				//:-) imprimir pantalla de cargando
				current_image = Char50;
				// :-P condicional para ver si el carro ya está full carga
				if (atras_bt != 0){
					fase_programa = 5;
					k_msleep(10);
				}
			break;

			// case carga completada
			case 5:
				//:-) imprimir pantalla de carga completada
				current_image = Char100;
			break;

			default:
				printk("error no esta en inguna fase del programa");
				//:-) mostrar pantalla de error que diga que conecte y desconecte el cargador a la toma
		}

	}
	

// 	//REVISIÓN DE FALLAS: (SENSORES)
// 		//LECTURA DE CORRIENTE DE ENTRADA (SENSORES)
// 		//LECTURA DE VOLTAJE DE ENTRADA (SENSORES)
// 		//LECTURA DE TEMPERATURA (SENSORES)
// 		//LECTURA GFCI (SENSORES)
// 	//EN CASO DE FALLA: (PANTALLA)
// 		//MOSTRAR PANTALLA DE FALLA POR 5 SEGUNDOS
// 		//TERMINAR PROGRAMA 
// 	//MOSTRAR PANTALLA DE INICIO POR 2 SEGUNDOS (PANTALLA)
// 	//REVISAR SI SE APAGÓ CORRECTAMENTE (MICRO)
// 	//SI SE APAGÓ CORRECTAMENTE:
// 		//SE MUESTRA PANTALLA DE SELECCIÓN DE CORRIENTE 8A (PANTALLA)
// 		int aceptar = gpio_pin_get_dt(&button0);
// 		int izquierda = gpio_pin_get_dt(&button1);
// 		int derecha = gpio_pin_get_dt(&button2);
// 		int seleccionando_corriente = 1;
// 		int corriente_A = 16;
// 		int counter=0;
// 		while(seleccionando_corriente){
// 			if(izquierda){
// 				//SE MUESTRA PANTALLA DE SELECCIÓN DE CORRIENTE 8A (PANTALLA)
// 				corriente_A = 8;
// 			}
// 			if(derecha){
// 				//SE MUESTRA PANTALLA DE SELECCIÓN DE CORRIENTE 16A (PANTALLA)
// 				corriente_A = 16;
// 			}
// 			if(aceptar){
// 				seleccionando_corriente = 0;
// 			}
// 			if(counter > 200){
// 				seleccionando_corriente = 0;
// 			}
// 			counter = counter + 1;

// 			k_sleep(K_MSEC(700U));
// 		}
		
// 		//SE MUESTRA PANTALLA DE SOLICITUD DE CONEXIÓN DEL CARRO (PANTALLA)
// 		//vERIFICACIÓN DE CONEXIÓN CON EL CARRO %%%%%(CONECTOR)%%%%%%%%%
// 		//SI NO ESTÁ CONECTADO, SE REINICIA EL PROGRAMA CON EL REGISTRO DE APAGADO CORRECTAMENTE EN 1
// 	//%%%%%%%% INICIA CARGA %%%%%%%%%
// //RELÉS ENCENDIDOS (PROTOCOLO CONECTOR)
// 	ret = pwm_set_dt(&pwm_rele1, period, period);
// 		if (ret) {
// 			printk("Error %d: failed to set pulse width\n", ret);
// 			return;
// 		}

// 	ret = pwm_set_dt(&pwm_rele2, period, period);
// 		if (ret) {
// 			printk("Error %d: failed to set pulse width\n", ret);
// 			return;
// 		}

//  bool Carga_Completa = false;
// // INICIO DE WHILE

// 	while (1) {
	
// 	//LECTURA DE CORRIENTE DE ENTRADA (SENSORES)
// 	//LECTURA DE VOLTAJE DE ENTRADA (SENSORES)
// 	//LECTURA DE TEMPERATURA (SENSORES)
// 	//LECTURA DE CONEXIÓN CON EL CARRO (CONECTOR)
// 	//LECTURA GFCI (SENSORES)
// 	//ESTADO DE CARGA (CONECTOR)
// 		//SI NO ESTÁ LLENA:
// 			//MOSTRAR PANTALLA CARGANDO (PANTALLA)
// 		//SI ESTÁ LLENA:

// 			if (Carga_Completa == true)
// 			{
// 			//MOSTRAR PANTALLA CARGADO (PANTALLA)
// 			//APAGA RELÉS (MICRO)
// 				ret = pwm_set_dt(&pwm_rele1, period, 0);
// 				if (ret) {
// 				printk("Error %d: failed to set pulse width\n", ret);
// 				return;
// 				}

// 			ret = pwm_set_dt(&pwm_rele2, period, 0);
// 			if (ret) {
// 			printk("Error %d: failed to set pulse width\n", ret);
// 			return;
// 			}
// 			//FINALIZA PROGRAMA
// 			return 0;
// 			}
			

// 	//SI SE CANCELA CARGA: 
		

// 	//FALLO (CORRIENTE, TENSIÓN, TEMPERATURA, GFCI,) (SENSORES)
// 		//ABRE RELÉS
// 		//MUESTRA PANTALLA DE ERROR POR 5 SEGUNDOS (PANTALLA)
// 		//FINALIZA PROGRAMA

// 		ret = gpio_pin_toggle_dt(&led_placa);
// 		if (ret < 0) {
// 			return;
// 		}
// 		k_msleep(SLEEP_TIME_MS);

// 		if (k_msgq_get(&uart_msgq, &tx_buf, K_FOREVER) == 0) {
// 			print_uart("Echo: ");
// 			print_uart(tx_buf);
// 			print_uart("\r\n");
// 		}
		
// 	}
}

double AdcToCelsius(uint32_t rawValue){ 
    double resistanceNTC = (R2 * (1350 - rawValue)) / rawValue;
    double logNTC = log(resistanceNTC); 
    double temp = (1 / (A + (B * logNTC) + (C * logNTC * logNTC * logNTC))) - KELVINCONSTANT; 

    return temp; 
}