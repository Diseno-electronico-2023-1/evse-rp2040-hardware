#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/display/cfb.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(display);

static const struct device *display = DEVICE_DT_GET(DT_NODELABEL(ssd1306));

void main(void)
{
	if(display == NULL){
		LOG_ERR("device pointer is NULL");
		return;
	}

	if(!device_is_ready(display)){
		LOG_ERR("display device is not ready");
		return;
	}

	int ret;
	ret = cfb_framebuffer_init(display);
	if(ret != 0){
		LOG_ERR("could not initialize display");
		return;
	}

	ret = cfb_print(display, "fasilito el tutorial", 0, 0);
	if(ret != 0) {
		LOG_ERR("could not print to display");
		return;
	}

	ret = cfb_framebuffer_finalize(display);
	if(ret != 0) {
		LOG_ERR("could not finalize to display");
		return;
	}
}
