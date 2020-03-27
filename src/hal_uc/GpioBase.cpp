/*
 * GpioBase.cpp
 *
 *  Created on: 27.03.2020
 *      Author: andreas
 */

#include "GpioBase.hpp"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_gpio.h"

namespace hal_uc
{
GpioBase::GpioBase(const PortBase& portRef, const PinBase::PinInitType& pinConfig, const bool initHigh) :
		PinBase(portRef, pinConfig)
{
	if(pinConfig.Mode == GPIO_MODE_OUTPUT_PP || pinConfig.Mode == GPIO_MODE_OUTPUT_OD)
	{
		if(initHigh)
			setHigh();
		else
			setLow();
	}
}


bool GpioBase::isHigh(void)
{
	return GPIO_PIN_SET == HAL_GPIO_ReadPin(port.getPortPtr(), pinConfig.Pin);
}

bool GpioBase::isLow(void)
{
	return GPIO_PIN_RESET == HAL_GPIO_ReadPin(port.getPortPtr(), pinConfig.Pin);
}

void GpioBase::setHigh(void)
{
	HAL_GPIO_WritePin(port.getPortPtr(), pinConfig.Pin, GPIO_PIN_SET);
}

void GpioBase::setLow(void)
{
	HAL_GPIO_WritePin(port.getPortPtr(), pinConfig.Pin, GPIO_PIN_RESET);
}

void GpioBase::togglePin(void)
{
	HAL_GPIO_TogglePin(port.getPortPtr(), pinConfig.Pin);
}

}
