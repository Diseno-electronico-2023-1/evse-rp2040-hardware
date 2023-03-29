#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>


void main(void)
{
    const struct device *dev_led;
    int ret;

    dev_led = device_get_binding((char*) DT_ALIAS_LED_GPIO_PIN);
    if (dev_led == NULL) {
        return;
    }

    ret = gpio_pin_configure(dev_led, DT_ALIAS_LED_GPIO_PIN, GPIO_OUTPUT_ACTIVE | DT_ALIAS_LED_GPIO_PIN);
    if (ret < 0) {
        return;
    }

    while (1) {
        gpio_pin_toggle(dev_led, DT_ALIAS_LED_GPIO_PIN);
        k_msleep(500);
    }
}
