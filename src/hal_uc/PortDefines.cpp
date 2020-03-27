/*
 * PortDefines.cpp
 *
 *  Created on: 27.03.2020
 *      Author: andreas
 */

#include "PortDefines.hpp"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_gpio.h"

namespace hal_uc
{
PortA::PortA():
		PortBase(GPIOA, RCC_APB2ENR_IOPAEN)
{

}


PortB::PortB():
		PortBase(GPIOB, RCC_APB2ENR_IOPBEN)
{

}


PortC::PortC():
		PortBase(GPIOC, RCC_APB2ENR_IOPCEN)
{

}





}
