/**
 * File: buttonCtrl.cpp
 * Initial Author: andimoto
 */

#include "buttonCtrl.hpp"


namespace hal_pcb
{

buttonCtrl::buttonCtrl(const hal_uc::gpio::gpioConfig& buttonPinConfig, const std::uint32_t timerResolutionConf, const std::uint32_t pressDurConf,
		const std::uint32_t midPressDurConf, const std::uint32_t longPressDurConf) :
				buttonPin(buttonPinConfig), lastPinState(0), timerResolution(timerResolutionConf), timer(0),
			pressDuration(pressDurConf), pressRange(pressDurConf>>5),
			midPressDuration(midPressDurConf), midPressRange(midPressDurConf>>5),
			longPressDuration(longPressDurConf), longPressRange(longPressDurConf>>5)

{

}


hal_pcb::buttonCtrl::buttonPress buttonCtrl::getButtonPress(void)
{
	buttonPress pressState = buttonPress::NO_PRESS;
	std::uint8_t pinState = buttonPin.get();

	/* if pin is HIGH start counting timer */
	if(pinState == 1)
	{
		timer += timerResolution;

		if(timer >= longPressDuration - longPressRange)
		{
			pressState = buttonPress::LONG_PRESS;
		}

	}else{
		if(lastPinState == 1)
		{
			if(timer < pressDuration)
			{
				pressState = buttonPress::NO_PRESS;
			}
			if((timer >= pressDuration - pressRange)
					&& (timer < midPressDuration - midPressRange))
			{
				pressState = buttonPress::PRESS;
			}
			if((timer >= midPressDuration - midPressRange)
					&& (timer < longPressDuration - longPressRange))
			{
				pressState = buttonPress::MID_PRESS;
			}
			if(timer >= longPressDuration - longPressRange)
			{
				pressState = buttonPress::LONG_PRESS;
			}
		}

		timer = 0;
	}

	lastPinState = pinState;

	return pressState;
}

}
