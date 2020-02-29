/**
 * Name: gpio.cpp
 * Initial Author: andimoto
 */
#include <cstdint>
#include "gpio.hpp"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_gpio.h"


static GPIO_TypeDef* gpioBase[static_cast<std::uint8_t>(hal_uc::gpio::Port::PORT_ALL)] = {
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

static std::uint32_t gpioAhb[static_cast<std::uint8_t>(hal_uc::gpio::Port::PORT_ALL)] = {
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


hal_uc::gpio::gpioConfig::gpioConfig(const Port portConf, const Pin pinConf, const Mode modeConf,
		const Speed speedConf, const Type typeConf, const PushPull ppConf) :
		gpioPort(portConf), gpioPin(pinConf), gpioMode(modeConf),
		gpioSpeed(speedConf), gpioType(typeConf), gpioPushPull(ppConf)
{

}

static void initGpio(const hal_uc::gpio::gpioConfig& gpioInitConf)
{
	GPIO_InitTypeDef initPin;

	initPin.Pin = static_cast<std::uint32_t>(gpioInitConf.gpioPin);
	initPin.Mode = static_cast<std::uint32_t>(gpioInitConf.gpioMode);
	initPin.Speed = static_cast<std::uint32_t>(gpioInitConf.gpioSpeed);
//	initPin.OType = static_cast<GPIOOType_TypeDef>(gpioInitConf.gpioType);
	initPin.Pull = static_cast<std::uint32_t>(gpioInitConf.gpioPushPull);

//	RCC_AHB1PeriphClockCmd(gpioAhb[static_cast<std::uint8_t>(gpioInitConf.gpioPort)], ENABLE);
	HAL_GPIO_Init(gpioBase[static_cast<std::uint8_t>(gpioInitConf.gpioPort)], &initPin);
}


hal_uc::gpio::gpio(const gpioConfig& gpioConfiguration) :
		gpioPort(gpioConfiguration.gpioPort),
		gpioPin(gpioConfiguration.gpioPin),
		gpioMode(gpioConfiguration.gpioMode)
{
	initGpio(gpioConfiguration);
}

void hal_uc::gpio::set(void)
{
	if(gpioMode == hal_uc::gpio::Mode::OUT)
	{
		HAL_GPIO_WritePin(gpioBase[static_cast<std::uint8_t>(gpioPort)], static_cast<std::uint16_t>(gpioPin), GPIO_PIN_SET);
	}
}

void hal_uc::gpio::reset(void)
{
	if(gpioMode == hal_uc::gpio::Mode::OUT)
	{
		HAL_GPIO_WritePin(gpioBase[static_cast<std::uint8_t>(gpioPort)], static_cast<std::uint16_t>(gpioPin), GPIO_PIN_RESET);
	}
}

void hal_uc::gpio::toggle(void)
{
	if(gpioMode == hal_uc::gpio::Mode::OUT)
	{
		HAL_GPIO_TogglePin(gpioBase[static_cast<std::uint8_t>(gpioPort)], static_cast<std::uint16_t>(gpioPin));
	}
}

std::uint8_t hal_uc::gpio::get(void) const
{
	return static_cast<std::uint8_t>(
			HAL_GPIO_ReadPin(gpioBase[static_cast<std::uint8_t>(gpioPort)],
			static_cast<std::uint16_t>(gpioPin)));
}

