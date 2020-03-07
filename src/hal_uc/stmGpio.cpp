/**
 * File: gpio.cpp
 * Initial Author: andimoto
 */
#include <cstdint>
#include "stmGpio.hpp"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_gpio.h"


static GPIO_TypeDef* gpioBase[static_cast<std::uint8_t>(hal_uc::stmGpio::Port::PORT_ALL)] = {
		GPIOA,
		GPIOB,
		GPIOC,
		GPIOD,
		GPIOE
//		,
//		GPIOF,
//		GPIOG,
//		GPIOH,
//		GPIOI,
//		GPIOJ,
//		GPIOK
};

static std::uint32_t gpioAhb[static_cast<std::uint8_t>(hal_uc::stmGpio::Port::PORT_ALL)] = {
		RCC_APB2ENR_IOPAEN,
		RCC_APB2ENR_IOPBEN,
		RCC_APB2ENR_IOPCEN,
		RCC_APB2ENR_IOPDEN,
		RCC_APB2ENR_IOPEEN
//		,
//		RCC_AHB1Periph_GPIOF,
//		RCC_AHB1Periph_GPIOG,
//		RCC_AHB1Periph_GPIOH,
//		RCC_AHB1Periph_GPIOI,
//		RCC_AHB1Periph_GPIOJ,
//		RCC_AHB1Periph_GPIOK
};


hal_uc::stmGpio::gpioConfig::gpioConfig(const Port portConf, const Pin pinConf, const Mode modeConf,
		const Speed speedConf, const Type typeConf, const PushPull ppConf) :
		gpioPort(portConf), gpioPin(pinConf), gpioMode(modeConf),
		gpioSpeed(speedConf), gpioType(typeConf), gpioPushPull(ppConf)
{

}

static void initGpio(const hal_uc::stmGpio::gpioConfig& gpioInitConf)
{
	GPIO_InitTypeDef initPin;

	initPin.Pin = 0x1<<static_cast<std::uint32_t>(gpioInitConf.gpioPin);
	initPin.Mode = static_cast<std::uint32_t>(gpioInitConf.gpioMode);
	initPin.Speed = static_cast<std::uint32_t>(gpioInitConf.gpioSpeed);
//	initPin.OType = static_cast<GPIOOType_TypeDef>(gpioInitConf.gpioType);
	initPin.Pull = static_cast<std::uint32_t>(gpioInitConf.gpioPushPull);

	do {
		__IO uint32_t tmpreg;
		SET_BIT(RCC->APB2ENR, gpioAhb[static_cast<std::uint32_t>(gpioInitConf.gpioPort)]);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);
		UNUSED(tmpreg);
	} while(0);
	GPIO_TypeDef* portBase = (GPIO_TypeDef*)gpioBase[static_cast<std::uint8_t>(gpioInitConf.gpioPort)];
	HAL_GPIO_Init(portBase, &initPin);
}


hal_uc::stmGpio::stmGpio(const gpioConfig& gpioConfiguration) :
		gpioPort(gpioConfiguration.gpioPort),
		gpioPin(gpioConfiguration.gpioPin),
		gpioMode(gpioConfiguration.gpioMode)
{
	initGpio(gpioConfiguration);

	pinRead = (uint32_t*)BITBAND_PERIPH(
			&gpioBase[static_cast<std::uint8_t>(gpioConfiguration.gpioPort)]->IDR,
			static_cast<std::uint32_t>(gpioConfiguration.gpioPin));
	pinSet = (uint32_t*)BITBAND_PERIPH(
			&gpioBase[static_cast<std::uint8_t>(gpioConfiguration.gpioPort)]->BSRR,
			static_cast<std::uint32_t>(gpioConfiguration.gpioPin));
	pinReset = ((uint32_t*)BITBAND_PERIPH(
			&gpioBase[static_cast<std::uint8_t>(gpioConfiguration.gpioPort)]->BSRR,
			static_cast<std::uint32_t>(gpioConfiguration.gpioPin))+16);
}

void hal_uc::stmGpio::set(void)
{
	*pinSet = 1;
}

void hal_uc::stmGpio::reset(void)
{
	*pinReset = 1;
}

void hal_uc::stmGpio::toggle(void)
{
	if(*pinRead)
		*pinReset = 1;
	else
		*pinSet = 1;
}

std::uint8_t hal_uc::stmGpio::get(void) const
{
	return *pinRead;
}

