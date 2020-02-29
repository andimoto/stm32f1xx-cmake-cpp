set(sources ${sources}
    src/stm32f1xx_hal_adc.c
    src/stm32f1xx_hal_adc_ex.c
    src/stm32f1xx_hal.c
    src/stm32f1xx_hal_can.c
    src/stm32f1xx_hal_cec.c
    src/stm32f1xx_hal_cortex.c
    src/stm32f1xx_hal_crc.c
    src/stm32f1xx_hal_dac.c
    src/stm32f1xx_hal_dac_ex.c
    src/stm32f1xx_hal_dma.c
    src/stm32f1xx_hal_eth.c
    src/stm32f1xx_hal_flash.c
    src/stm32f1xx_hal_flash_ex.c
    src/stm32f1xx_hal_gpio.c
    src/stm32f1xx_hal_gpio_ex.c
    src/stm32f1xx_hal_hcd.c
    src/stm32f1xx_hal_i2c.c
    src/stm32f1xx_hal_i2s.c
    src/stm32f1xx_hal_irda.c
    src/stm32f1xx_hal_iwdg.c
    src/stm32f1xx_hal_msp_template.c
    src/stm32f1xx_hal_nand.c
    src/stm32f1xx_hal_nor.c
    src/stm32f1xx_hal_pccard.c
    src/stm32f1xx_hal_pcd.c
    src/stm32f1xx_hal_pcd_ex.c
    src/stm32f1xx_hal_pwr.c
    src/stm32f1xx_hal_rcc.c
    src/stm32f1xx_hal_rcc_ex.c
    src/stm32f1xx_hal_rtc.c
    src/stm32f1xx_hal_rtc_ex.c
    src/stm32f1xx_hal_sd.c
    src/stm32f1xx_hal_smartcard.c
    src/stm32f1xx_hal_spi.c
    src/stm32f1xx_hal_spi_ex.c
    src/stm32f1xx_hal_sram.c
    src/stm32f1xx_hal_tim.c
    src/stm32f1xx_hal_tim_ex.c
    src/stm32f1xx_hal_uart.c
    src/stm32f1xx_hal_usart.c
    src/stm32f1xx_hal_wwdg.c
    src/stm32f1xx_ll_fsmc.c
    src/stm32f1xx_ll_sdmmc.c
    src/stm32f1xx_ll_usb.c
    ../pure_virtual.c            # this is needed for CPP size optimization
)

#set debug functions to source
set(sources ${sources} 
	../tools/itm_write.c)

#set system init functions to source
set(sources ${sources} 
	../startup/system_stm32f1xx.c)

if (DEVICE_FAMILY STREQUAL STM32F100xB) 
	set(sources ${sources} ../startup/startup_stm32f100xb.s)
elseif (DEVICE_FAMILY STREQUAL STM32F100xE) 
	set(sources ${sources} ../startup/startup_stm32f100xe.s)
elseif (DEVICE_FAMILY STREQUAL STM32F101x6) 
	set(sources ${sources} ../startup/startup_stm32f101x6.s)
elseif (DEVICE_FAMILY STREQUAL STM32F101xB) 
	set(sources ${sources} ../startup/startup_stm32f101xb.s)
elseif (DEVICE_FAMILY STREQUAL STM32F102x6) 
	set(sources ${sources} ../startup/startup_stm32f102x6.s)
elseif (DEVICE_FAMILY STREQUAL STM32F102xB ) 
	set(sources ${sources} ../startup/startup_stm32f102xb.s)
elseif (DEVICE_FAMILY STREQUAL STM32F103x6) 
	set(sources ${sources} ../startup/startup_stm32f103x6.s)
elseif (DEVICE_FAMILY STREQUAL STM32F103xB) 
	set(sources ${sources} ../startup/startup_stm32f103xb.s)
elseif (DEVICE_FAMILY STREQUAL STM32F105xC) 
	set(sources ${sources} ../startup/startup_stm32f105xc.s)
elseif (DEVICE_FAMILY STREQUAL STM32F107xC) 
	set(sources ${sources} ../startup/startup_stm32f107xc.s)
elseif (DEVICE_FAMILY STREQUAL STM32F101xE) 
	set(sources ${sources} ../startup/startup_stm32f101xe.s)
elseif (DEVICE_FAMILY STREQUAL STM32F101xG) 
	set(sources ${sources} ../startup/startup_stm32f101xg.s)
elseif (DEVICE_FAMILY STREQUAL STM32F103xE) 
	set(sources ${sources} ../startup/startup_stm32f103xe.s)
elseif (DEVICE_FAMILY STREQUAL STM32F103xG) 
	set(sources ${sources} ../startup/startup_stm32f103xg.s)
endif()


# FMC/FSMC only defined for some F4 families
#if (DEVICE_FAMILY STREQUAL STM32F427_437xx OR \
#	DEVICE_FAMILY STREQUAL STM32F429_439xx OR \
#	DEVICE_FAMILY STREQUAL STM32F446xx OR \
#	DEVICE_FAMILY STREQUAL STM32F469_479xx)
#  set(sources ${sources} src/stm32f4xx_fmc.c)
#else()
#  set(sources ${sources} src/stm32f4xx_fsmc.c)
#endif()

add_library(stm32f1xx ${sources})

# add include directories for StdPeriph library and CMSIS
target_include_directories(stm32f1xx PUBLIC inc)
target_include_directories(stm32f1xx PUBLIC inc/cmsis)
target_include_directories(stm32f1xx PUBLIC ../tools)

# set up some defines for the StdPeriph library
target_compile_definitions(stm32f1xx PUBLIC USE_STDPERIPH_DRIVER)
target_compile_definitions(stm32f1xx PUBLIC ${DEVICE_FAMILY})
target_compile_definitions(stm32f1xx PUBLIC HSE_VALUE=${HSE_VALUE})

# additional compiler options: use size-optimized version of library in release build, use -O0 in debug build
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(additional_flags -O0)
else()
  set(additional_flags -Os)
endif()

target_compile_options(stm32f1xx PRIVATE ${additional_flags})
