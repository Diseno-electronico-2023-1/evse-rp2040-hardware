#include <zephyr/device.h>
#include <zephyr/toolchain.h>

/* 1 : /soc/reset-controller@4000c000:
 * Supported:
 *    - /soc/uart@40034000
 *    - /soc/adc@4004c000
 *    - /soc/pwm@40050000
 */
extern const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2"))) __devicehdl_dts_ord_7[6];
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_7[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, 2, 4, 5, DEVICE_HANDLE_ENDS };

/* 2 : /soc/uart@40034000:
 * Direct Dependencies:
 *    - /soc/reset-controller@4000c000
 */
extern const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2"))) __devicehdl_dts_ord_53[4];
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_53[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 3 : /soc/gpio@40014000:
 */
extern const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2"))) __devicehdl_dts_ord_12[3];
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_12[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 4 : /soc/adc@4004c000:
 * Direct Dependencies:
 *    - /soc/reset-controller@4000c000
 */
extern const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2"))) __devicehdl_dts_ord_8[4];
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_8[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 5 : /soc/pwm@40050000:
 * Direct Dependencies:
 *    - /soc/reset-controller@4000c000
 */
extern const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2"))) __devicehdl_dts_ord_38[4];
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_38[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };
