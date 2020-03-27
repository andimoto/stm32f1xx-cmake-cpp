/*
 * GpioBase.hpp
 *
 *  Created on: 27.03.2020
 *      Author: andreas
 */

#ifndef SRC_HAL_UC_INC_GPIOBASE_HPP_
#define SRC_HAL_UC_INC_GPIOBASE_HPP_

#include "PinBase.hpp"


namespace hal_uc
{

class GpioBase : public PinBase
{
public:
	void setHigh(void) const;
	void setLow(void) const;
	void togglePin(void) const;

	bool isLow(void) const;
	bool isHigh(void) const;

protected:
	GpioBase(const PortBase& portRef, const PinBase::PinInitType& pinConfig, const bool initHigh);

};



}


#endif /* SRC_HAL_UC_INC_GPIOBASE_HPP_ */
