# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/ediso/zephyrproject/zephyr/modules/hal_rpi_pico/bootloader"
  "C:/Users/ediso/zephyrproject/evse-rp2040-hardware/app/build/bootloader"
  "C:/Users/ediso/zephyrproject/evse-rp2040-hardware/app/build/modules/hal_rpi_pico/second_stage_bootloader-prefix"
  "C:/Users/ediso/zephyrproject/evse-rp2040-hardware/app/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/tmp"
  "C:/Users/ediso/zephyrproject/evse-rp2040-hardware/app/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp"
  "C:/Users/ediso/zephyrproject/evse-rp2040-hardware/app/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src"
  "C:/Users/ediso/zephyrproject/evse-rp2040-hardware/app/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/ediso/zephyrproject/evse-rp2040-hardware/app/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/ediso/zephyrproject/evse-rp2040-hardware/app/build/modules/hal_rpi_pico/second_stage_bootloader-prefix/src/second_stage_bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
