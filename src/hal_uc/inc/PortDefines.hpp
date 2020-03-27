/*
 * PortDefines.hpp
 *
 *  Created on: 27.03.2020
 *      Author: andreas
 */

#ifndef SRC_HAL_UC_INC_PORTDEFINES_HPP_
#define SRC_HAL_UC_INC_PORTDEFINES_HPP_

#include "PortBase.hpp"


namespace hal_uc
{


class PortA : public PortBase
{
	static PortBase& getPortInstance()
	{
		static PortA instance;
		return instance;
	}

protected:
	PortA();
};


class PortB : public PortBase
{
	static PortBase& getPortInstance()
	{
		static PortB instance;
		return instance;
	}

protected:
	PortB();
};


class PortC : public PortBase
{
	static PortBase& getPortInstance()
	{
		static PortC instance;
		return instance;
	}

protected:
	PortC();
};


}
#endif /* SRC_HAL_UC_INC_PORTDEFINES_HPP_ */
