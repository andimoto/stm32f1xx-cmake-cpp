/**
 * File: buttonCtrl.hpp
 * Initial Author: andimoto
 */

#ifndef SRC_HAL_PCB_INC_BUTTONCTRL_HPP_
#define SRC_HAL_PCB_INC_BUTTONCTRL_HPP_
#include <cstdint>
#include "gpio.hpp"

namespace hal_pcb
{


class buttonCtrl
{
public:
	enum class buttonPress
	{
		NO_PRESS,
		PRESS,
		MID_PRESS,
		LONG_PRESS
	};

	buttonCtrl(const hal_uc::gpio::gpioConfig& buttonPinConf, const std::uint32_t timerResolutionConf, const std::uint32_t pressDurConf,
			const std::uint32_t midPressDurConf, const std::uint32_t longPressDurConf);

	buttonPress getButtonPress(void);

private:

	hal_uc::gpio buttonPin;
	std::uint8_t lastPinState;

	const std::uint32_t timerResolution;
	std::uint32_t timer;

	const std::uint32_t pressDuration;
	const std::uint32_t pressRange;

	const std::uint32_t midPressDuration;
	const std::uint32_t midPressRange;

	const std::uint32_t longPressDuration;
	const std::uint32_t longPressRange;



};


}

#endif /* SRC_HAL_PCB_INC_BUTTONCTRL_HPP_ */
