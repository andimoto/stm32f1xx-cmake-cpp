/*
 * PinBase.hpp
 *
 *  Created on: 27.03.2020
 *      Author: andreas
 */

#ifndef SRC_HAL_UC_INC_PINBASE_HPP_
#define SRC_HAL_UC_INC_PINBASE_HPP_

#include <cstdint>
#include <cstddef>

#include <PortBase.hpp>


namespace hal_uc
{

class PinBase
{
public:
protected:
	struct PinInitType
	{
		std::uint32_t Pin;
		std::uint32_t Mode;
		std::uint32_t Pull;
		std::uint32_t Speed;
		std::uint32_t Alternative;
	};

	PinBase(const PortBase& port, const PinInitType& pinInit);

	const PortBase& port;
	const PinInitType& pinConfig;

	void init();
};



}



#endif /* SRC_HAL_UC_INC_PINBASE_HPP_ */
