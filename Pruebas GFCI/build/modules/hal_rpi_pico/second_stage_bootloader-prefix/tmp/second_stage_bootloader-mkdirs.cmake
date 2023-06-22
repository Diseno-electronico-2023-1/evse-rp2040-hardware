# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/jcsie/zephyrproject/zephyr/modules/hal_rpi_pico/bootloader"
  "C:/Users/jcsie/zephyrproject/evse-rp2040-hardware/GFCI/build/bootloader"
  "C:/Users/jcsie/zephyrproject/evse-rp2040-hardware/GFCI/build/modules/hal_rpi_pico/second_stage_bootloader-prefix"
  "C:/Users/jcsie/zephyrproject/evse-rp2040-hardware/GFCI/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/tmp"
  "C:/Users/jcsie/zephyrproject/evse-rp2040-hardware/GFCI/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp"
  "C:/Users/jcsie/zephyrproject/evse-rp2040-hardware/GFCI/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src"
  "C:/Users/jcsie/zephyrproject/evse-rp2040-hardware/GFCI/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/jcsie/zephyrproject/evse-rp2040-hardware/GFCI/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/jcsie/zephyrproject/evse-rp2040-hardware/GFCI/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
