/*
 * PortBase.cpp
 *
 *  Created on: 27.03.2020
 *      Author: andreas
 */
#include "PortBase.hpp"

#include "stm32f1xx.h"
#include "stm32f1xx_hal_gpio.h"

namespace hal_uc
{


void PortBase::enable(void)
{
	__IO uint32_t tmpreg;
	SET_BIT(RCC->APB2ENR, rccAdd);
	/* Delay after an RCC peripheral clock enabling */
	tmpreg = READ_BIT(RCC->APB2ENR, rccAdd);
	UNUSED(tmpreg);
}


void PortBase::disable(void)
{
	CLEAR_BIT(RCC->APB2ENR, rccAdd);
}

PortBase::PortBase(GpioType* const portAddress, const std::uint32_t rccAddr) :
		portAdd(portAddress), rccAdd(rccAddr)
{
	enable();
}

}
