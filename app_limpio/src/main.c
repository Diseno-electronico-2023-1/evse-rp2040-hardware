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



// ############# GPIO ###############

#define LED0_NODE DT_ALIAS(led0)
#define GFCI_test_NODE DT_ALIAS(led1)
#define GFCI_fault_NODE DT_ALIAS(led2)

// ############# PWM ###############

#define PERIOD PWM_NSEC(100000000U)


// ############# GPIO ###############

static const struct gpio_dt_spec led_placa = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec GFCI_test = GPIO_DT_SPEC_GET(GFCI_test_NODE, gpios);
static const struct gpio_dt_spec GFCI_fault = GPIO_DT_SPEC_GET(GFCI_fault_NODE, gpios);

// ############# PWM ###############

static const struct pwm_dt_spec pwm_rele1 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led1));
static const struct pwm_dt_spec pwm_rele2 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led2));
static const struct pwm_dt_spec pwm_pilot_out = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led3));


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



	// ############# INICIO DEL PROGRAMA ###############

	//RELÉS OFF
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

	ret = pwm_set_dt(&pwm_pilot_out, period, period / 2U);
		if (ret) {
			printk("Error %d: failed to set pulse width\n", ret);
			return;
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