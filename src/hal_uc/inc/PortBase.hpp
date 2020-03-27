/*
 * PortBase.hpp
 *
 *  Created on: 27.03.2020
 *      Author: andreas
 */

#ifndef SRC_HAL_UC_INC_PORTBASE_HPP_
#define SRC_HAL_UC_INC_PORTBASE_HPP_

#include <cstdint>
#include <cstddef>

struct GpioType;

namespace hal_uc
{

class PortBase
{
public:
	void enable(void);
	void disable(void);

	GpioType* getPortPtr() const
	{
		return portAdd;
	}

protected:
	PortBase(GpioType* const portAddress, const std::uint32_t rccAddr);

private:

	GpioType* const portAdd;
	const std::uint32_t rccAdd;
};

}



#endif /* SRC_HAL_UC_INC_PORTBASE_HPP_ */
