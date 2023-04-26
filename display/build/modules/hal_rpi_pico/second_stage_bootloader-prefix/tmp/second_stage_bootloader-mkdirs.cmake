# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/afrodri/zephyrproject/zephyr/modules/hal_rpi_pico/bootloader"
  "/home/afrodri/zephyrproject/evse-rp2040-hardware/display/build/bootloader"
  "/home/afrodri/zephyrproject/evse-rp2040-hardware/display/build/modules/hal_rpi_pico/second_stage_bootloader-prefix"
  "/home/afrodri/zephyrproject/evse-rp2040-hardware/display/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/tmp"
  "/home/afrodri/zephyrproject/evse-rp2040-hardware/display/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp"
  "/home/afrodri/zephyrproject/evse-rp2040-hardware/display/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src"
  "/home/afrodri/zephyrproject/evse-rp2040-hardware/display/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/afrodri/zephyrproject/evse-rp2040-hardware/display/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/afrodri/zephyrproject/evse-rp2040-hardware/display/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
