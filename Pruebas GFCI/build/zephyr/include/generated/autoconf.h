#define CONFIG_GPIO_INIT_PRIORITY 40
#define CONFIG_UART_INTERRUPT_DRIVEN 1
#define CONFIG_BOARD "rpi_pico"
#define CONFIG_RP2_FLASH_W25Q080 1
#define CONFIG_SOC "rp2040"
#define CONFIG_SOC_SERIES "rp2"
#define CONFIG_NUM_IRQS 26
#define CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC 125000000
#define CONFIG_FLASH_SIZE 2048
#define CONFIG_FLASH_BASE_ADDRESS 0x10000000
#define CONFIG_ICACHE_LINE_SIZE 32
#define CONFIG_DCACHE_LINE_SIZE 32
#define CONFIG_HEAP_MEM_POOL_SIZE 0
#define CONFIG_ROM_START_OFFSET 0x0
#define CONFIG_PINCTRL 1
#define CONFIG_RESET 1
#define CONFIG_GPIO 1
#define CONFIG_CORTEX_M_SYSTICK 1
#define CONFIG_SYS_CLOCK_TICKS_PER_SEC 10000
#define CONFIG_BUILD_OUTPUT_HEX 1
#define CONFIG_SERIAL_INIT_PRIORITY 55
#define CONFIG_SERIAL 1
#define CONFIG_MAIN_STACK_SIZE 1024
#define CONFIG_BUILD_OUTPUT_UF2_USE_FLASH_BASE 1
#define CONFIG_MP_MAX_NUM_CPUS 1
#define CONFIG_HAS_DTS 1
#define CONFIG_DT_HAS_ARM_ARMV6M_SYSTICK_ENABLED 1
#define CONFIG_DT_HAS_ARM_CORTEX_M0__ENABLED 1
#define CONFIG_DT_HAS_ARM_PL022_ENABLED 1
#define CONFIG_DT_HAS_ARM_V6M_NVIC_ENABLED 1
#define CONFIG_DT_HAS_FIXED_CLOCK_ENABLED 1
#define CONFIG_DT_HAS_FIXED_PARTITIONS_ENABLED 1
#define CONFIG_DT_HAS_GPIO_KEYS_ENABLED 1
#define CONFIG_DT_HAS_GPIO_LEDS_ENABLED 1
#define CONFIG_DT_HAS_MMIO_SRAM_ENABLED 1
#define CONFIG_DT_HAS_RASPBERRYPI_CORE_SUPPLY_REGULATOR_ENABLED 1
#define CONFIG_DT_HAS_RASPBERRYPI_PICO_ADC_ENABLED 1
#define CONFIG_DT_HAS_RASPBERRYPI_PICO_FLASH_CONTROLLER_ENABLED 1
#define CONFIG_DT_HAS_RASPBERRYPI_PICO_GPIO_ENABLED 1
#define CONFIG_DT_HAS_RASPBERRYPI_PICO_PINCTRL_ENABLED 1
#define CONFIG_DT_HAS_RASPBERRYPI_PICO_PWM_ENABLED 1
#define CONFIG_DT_HAS_RASPBERRYPI_PICO_RESET_ENABLED 1
#define CONFIG_DT_HAS_RASPBERRYPI_PICO_SPI_ENABLED 1
#define CONFIG_DT_HAS_RASPBERRYPI_PICO_UART_ENABLED 1
#define CONFIG_DT_HAS_RASPBERRYPI_PICO_USBD_ENABLED 1
#define CONFIG_DT_HAS_RASPBERRYPI_PICO_WATCHDOG_ENABLED 1
#define CONFIG_DT_HAS_SNPS_DESIGNWARE_I2C_ENABLED 1
#define CONFIG_DT_HAS_SOC_NV_FLASH_ENABLED 1
#define CONFIG_ZEPHYR_CANOPENNODE_MODULE 1
#define CONFIG_ZEPHYR_CHRE_MODULE 1
#define CONFIG_ZEPHYR_FATFS_MODULE 1
#define CONFIG_ZEPHYR_HAL_ESPRESSIF_MODULE 1
#define CONFIG_ZEPHYR_HAL_ETHOS_U_MODULE 1
#define CONFIG_ZEPHYR_HAL_GIGADEVICE_MODULE 1
#define CONFIG_ZEPHYR_HAL_INFINEON_MODULE 1
#define CONFIG_ZEPHYR_HAL_NORDIC_MODULE 1
#define CONFIG_ZEPHYR_HAL_NXP_MODULE 1
#define CONFIG_HAS_RPI_PICO 1
#define CONFIG_PICOSDK_USE_UART 1
#define CONFIG_PICOSDK_USE_GPIO 1
#define CONFIG_ZEPHYR_HAL_RPI_PICO_MODULE 1
#define CONFIG_ZEPHYR_SILABS_MODULE 1
#define CONFIG_ZEPHYR_HAL_TELINK_MODULE 1
#define CONFIG_ZEPHYR_LIBLC3_MODULE 1
#define CONFIG_ZEPHYR_LITTLEFS_MODULE 1
#define CONFIG_ZEPHYR_LORAMAC_NODE_MODULE 1
#define CONFIG_ZEPHYR_LVGL_MODULE 1
#define CONFIG_ZEPHYR_LZ4_MODULE 1
#define CONFIG_ZEPHYR_MBEDTLS_MODULE 1
#define CONFIG_ZEPHYR_NANOPB_MODULE 1
#define CONFIG_ZEPHYR_OPENTHREAD_MODULE 1
#define CONFIG_ZEPHYR_PICOLIBC_MODULE 1
#define CONFIG_ZEPHYR_SEGGER_MODULE 1
#define CONFIG_HAS_SEGGER_RTT 1
#define CONFIG_ZEPHYR_SOF_MODULE 1
#define CONFIG_ZEPHYR_TFLITE_MICRO_MODULE 1
#define CONFIG_ZEPHYR_TRACERECORDER_MODULE 1
#define CONFIG_ZEPHYR_TRUSTED_FIRMWARE_M_MODULE 1
#define CONFIG_ZEPHYR_TRUSTED_FIRMWARE_A_MODULE 1
#define CONFIG_ZEPHYR_UOSCORE_UEDHOC_MODULE 1
#define CONFIG_ZEPHYR_ZCBOR_MODULE 1
#define CONFIG_ZEPHYR_ZSCILIB_MODULE 1
#define CONFIG_ZEPHYR_THRIFT_MODULE 1
#define CONFIG_HAS_CMSIS_CORE 1
#define CONFIG_HAS_CMSIS_CORE_M 1
#define CONFIG_BOARD_REVISION "$BOARD_REVISION"
#define CONFIG_BOARD_RPI_PICO 1
#define CONFIG_SOC_SERIES_RP2XXX 1
#define CONFIG_CPU_HAS_ARM_MPU 1
#define CONFIG_SOC_FAMILY "rpi_pico"
#define CONFIG_SOC_FAMILY_RPI_PICO 1
#define CONFIG_SOC_RP2040 1
#define CONFIG_RP2_REQUIRES_SECOND_STAGE_BOOT 1
#define CONFIG_ARCH "arm"
#define CONFIG_CPU_CORTEX 1
#define CONFIG_CPU_CORTEX_M 1
#define CONFIG_ISA_THUMB2 1
#define CONFIG_ASSEMBLER_ISA_THUMB2 1
#define CONFIG_COMPILER_ISA_THUMB2 1
#define CONFIG_STACK_ALIGN_DOUBLE_WORD 1
#define CONFIG_FAULT_DUMP 2
#define CONFIG_FP16 1
#define CONFIG_FP16_IEEE 1
#define CONFIG_CPU_CORTEX_M0PLUS 1
#define CONFIG_CPU_CORTEX_M_HAS_SYSTICK 1
#define CONFIG_CPU_CORTEX_M_HAS_VTOR 1
#define CONFIG_ARMV6_M_ARMV8_M_BASELINE 1
#define CONFIG_GEN_ISR_TABLES 1
#define CONFIG_NULL_POINTER_EXCEPTION_DETECTION_NONE 1
#define CONFIG_GEN_IRQ_VECTOR_TABLE 1
#define CONFIG_ARM_MPU_REGION_MIN_ALIGN_AND_SIZE 4
#define CONFIG_ARM 1
#define CONFIG_ARCH_IS_SET 1
#define CONFIG_LITTLE_ENDIAN 1
#define CONFIG_SRAM_SIZE 264
#define CONFIG_SRAM_BASE_ADDRESS 0x20000000
#define CONFIG_GEN_PRIV_STACKS 1
#define CONFIG_ARCH_IRQ_VECTOR_TABLE_ALIGN 4
#define CONFIG_IRQ_VECTOR_TABLE_JUMP_BY_ADDRESS 1
#define CONFIG_GEN_SW_ISR_TABLE 1
#define CONFIG_ARCH_SW_ISR_TABLE_ALIGN 4
#define CONFIG_GEN_IRQ_START_VECTOR 0
#define CONFIG_ARCH_HAS_SINGLE_THREAD_SUPPORT 1
#define CONFIG_ARCH_HAS_RAMFUNC_SUPPORT 1
#define CONFIG_ARCH_HAS_NESTED_EXCEPTION_DETECTION 1
#define CONFIG_ARCH_SUPPORTS_COREDUMP 1
#define CONFIG_ARCH_SUPPORTS_ARCH_HW_INIT 1
#define CONFIG_ARCH_HAS_EXTRA_EXCEPTION_INFO 1
#define CONFIG_ARCH_HAS_THREAD_LOCAL_STORAGE 1
#define CONFIG_ARCH_HAS_SUSPEND_TO_RAM 1
#define CONFIG_ARCH_HAS_THREAD_ABORT 1
#define CONFIG_ARCH_HAS_CODE_DATA_RELOCATION 1
#define CONFIG_CPU_HAS_MPU 1
#define CONFIG_TOOLCHAIN_HAS_BUILTIN_FFS 1
#define CONFIG_MULTITHREADING 1
#define CONFIG_NUM_COOP_PRIORITIES 16
#define CONFIG_NUM_PREEMPT_PRIORITIES 15
#define CONFIG_MAIN_THREAD_PRIORITY 0
#define CONFIG_COOP_ENABLED 1
#define CONFIG_PREEMPT_ENABLED 1
#define CONFIG_PRIORITY_CEILING -127
#define CONFIG_NUM_METAIRQ_PRIORITIES 0
#define CONFIG_IDLE_STACK_SIZE 256
#define CONFIG_ISR_STACK_SIZE 2048
#define CONFIG_ERRNO 1
#define CONFIG_SCHED_DUMB 1
#define CONFIG_WAITQ_DUMB 1
#define CONFIG_BOOT_BANNER 1
#define CONFIG_BOOT_DELAY 0
#define CONFIG_SYSTEM_WORKQUEUE_STACK_SIZE 1024
#define CONFIG_SYSTEM_WORKQUEUE_PRIORITY -1
#define CONFIG_ATOMIC_OPERATIONS_C 1
#define CONFIG_TIMESLICING 1
#define CONFIG_TIMESLICE_SIZE 0
#define CONFIG_TIMESLICE_PRIORITY 0
#define CONFIG_NUM_MBOX_ASYNC_MSGS 10
#define CONFIG_KERNEL_MEM_POOL 1
#define CONFIG_ARCH_HAS_CUSTOM_SWAP_TO_MAIN 1
#define CONFIG_SWAP_NONATOMIC 1
#define CONFIG_SYS_CLOCK_EXISTS 1
#define CONFIG_TIMEOUT_64BIT 1
#define CONFIG_SYS_CLOCK_MAX_TIMEOUT_DAYS 365
#define CONFIG_XIP 1
#define CONFIG_KERNEL_INIT_PRIORITY_OBJECTS 30
#define CONFIG_KERNEL_INIT_PRIORITY_DEFAULT 40
#define CONFIG_KERNEL_INIT_PRIORITY_DEVICE 50
#define CONFIG_APPLICATION_INIT_PRIORITY 90
#define CONFIG_MP_NUM_CPUS 1
#define CONFIG_TICKLESS_KERNEL 1
#define CONFIG_TOOLCHAIN_SUPPORTS_THREAD_LOCAL_STORAGE 1
#define CONFIG_CONSOLE 1
#define CONFIG_CONSOLE_INPUT_MAX_LINE_LEN 128
#define CONFIG_CONSOLE_HAS_DRIVER 1
#define CONFIG_CONSOLE_INIT_PRIORITY 60
#define CONFIG_UART_CONSOLE 1
#define CONFIG_GPIO_RPI_PICO 1
#define CONFIG_INTC_INIT_PRIORITY 40
#define CONFIG_PINCTRL_RPI_PICO 1
#define CONFIG_RESET_INIT_PRIORITY 40
#define CONFIG_RESET_RPI_PICO 1
#define CONFIG_SERIAL_HAS_DRIVER 1
#define CONFIG_SERIAL_SUPPORT_INTERRUPT 1
#define CONFIG_UART_USE_RUNTIME_CONFIGURE 1
#define CONFIG_UART_RPI_PICO 1
#define CONFIG_SYSTEM_CLOCK_INIT_PRIORITY 0
#define CONFIG_TICKLESS_CAPABLE 1
#define CONFIG_SYSTEM_TIMER_HAS_DISABLE_SUPPORT 1
#define CONFIG_CORTEX_M_SYSTICK_INSTALL_ISR 1
#define CONFIG_FULL_LIBC_SUPPORTED 1
#define CONFIG_MINIMAL_LIBC_SUPPORTED 1
#define CONFIG_NEWLIB_LIBC_SUPPORTED 1
#define CONFIG_PICOLIBC_SUPPORTED 1
#define CONFIG_MINIMAL_LIBC 1
#define CONFIG_HAS_NEWLIB_LIBC_NANO 1
#define CONFIG_COMMON_LIBC_ABORT 1
#define CONFIG_COMMON_LIBC_MALLOC 1
#define CONFIG_COMMON_LIBC_MALLOC_ARENA_SIZE 0
#define CONFIG_COMMON_LIBC_CALLOC 1
#define CONFIG_COMMON_LIBC_REALLOCARRAY 1
#define CONFIG_COMMON_LIBC_STRNLEN 1
#define CONFIG_MINIMAL_LIBC_NON_REENTRANT_FUNCTIONS 1
#define CONFIG_MINIMAL_LIBC_MALLOC 1
#define CONFIG_MINIMAL_LIBC_MALLOC_ARENA_SIZE -2
#define CONFIG_MINIMAL_LIBC_CALLOC 1
#define CONFIG_MINIMAL_LIBC_REALLOCARRAY 1
#define CONFIG_MINIMAL_LIBC_OPTIMIZE_STRING_FOR_SIZE 1
#define CONFIG_MINIMAL_LIBC_TIME 1
#define CONFIG_STDOUT_CONSOLE 1
#define CONFIG_NEED_LIBC_MEM_PARTITION 1
#define CONFIG_CRC 1
#define CONFIG_CBPRINTF_COMPLETE 1
#define CONFIG_CBPRINTF_FULL_INTEGRAL 1
#define CONFIG_CBPRINTF_N_SPECIFIER 1
#define CONFIG_SYS_HEAP_ALLOC_LOOPS 3
#define CONFIG_SYS_HEAP_AUTO 1
#define CONFIG_POSIX_MAX_FDS 4
#define CONFIG_MAX_TIMER_COUNT 5
#define CONFIG_TIMER_CREATE_WAIT 100
#define CONFIG_PRINTK 1
#define CONFIG_EARLY_CONSOLE 1
#define CONFIG_ASSERT_VERBOSE 1
#define CONFIG_COVERAGE_GCOV_HEAP_SIZE 16384
#define CONFIG_TOOLCHAIN_ZEPHYR_0_15 1
#define CONFIG_TOOLCHAIN_ZEPHYR_SUPPORTS_THREAD_LOCAL_STORAGE 1
#define CONFIG_LINKER_ORPHAN_SECTION_WARN 1
#define CONFIG_HAS_FLASH_LOAD_OFFSET 1
#define CONFIG_USE_DT_CODE_PARTITION 1
#define CONFIG_FLASH_LOAD_OFFSET 0x100
#define CONFIG_FLASH_LOAD_SIZE 0x1fff00
#define CONFIG_LD_LINKER_SCRIPT_SUPPORTED 1
#define CONFIG_LD_LINKER_TEMPLATE 1
#define CONFIG_KERNEL_ENTRY "__start"
#define CONFIG_LINKER_SORT_BY_ALIGNMENT 1
#define CONFIG_SRAM_OFFSET 0x0
#define CONFIG_LINKER_GENERIC_SECTIONS_PRESENT_AT_BOOT 1
#define CONFIG_LINKER_LAST_SECTION_ID 1
#define CONFIG_LINKER_LAST_SECTION_ID_PATTERN 0xE015E015
#define CONFIG_LINKER_USE_RELAX 1
#define CONFIG_COMPILER_FREESTANDING 1
#define CONFIG_SIZE_OPTIMIZATIONS 1
#define CONFIG_COMPILER_TRACK_MACRO_EXPANSION 1
#define CONFIG_COMPILER_COLOR_DIAGNOSTICS 1
#define CONFIG_FORTIFY_SOURCE_NONE 1
#define CONFIG_COMPILER_OPT ""
#define CONFIG_RUNTIME_ERROR_CHECKS 1
#define CONFIG_KERNEL_BIN_NAME "zephyr"
#define CONFIG_OUTPUT_STAT 1
#define CONFIG_OUTPUT_DISASSEMBLY 1
#define CONFIG_OUTPUT_PRINT_MEMORY_USAGE 1
#define CONFIG_BUILD_OUTPUT_BIN 1
#define CONFIG_BUILD_OUTPUT_UF2 1
#define CONFIG_BUILD_OUTPUT_UF2_FAMILY_ID "0xe48bff56"
#define CONFIG_BUILD_OUTPUT_STRIP_PATHS 1
#define CONFIG_WARN_DEPRECATED 1
#define CONFIG_ENFORCE_ZEPHYR_STDINT 1
#define CONFIG_COMPAT_INCLUDES 1