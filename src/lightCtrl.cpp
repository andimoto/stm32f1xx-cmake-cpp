/**
 * File: lightCtrl.cpp
 * Initial Author: andimoto
 */

#include "lightCtrl.hpp"
#include "itm_write.h"

lightCtrl::lightCtrl(void) : lightMode(lightCtrl::Mode::OFF)
{
	rgb_led.setLightFunc2(0,0,0);
	update();
}

void lightCtrl::process(hal_pcb::buttonCtrl::buttonPress btnPress)
{
//	if(btnPress == hal_pcb::buttonCtrl::buttonPress::PRESS)
	if(btnPress == hal_pcb::buttonCtrl::buttonPress::LONG_PRESS)
	{
		setNextState();
	}
}

void lightCtrl::setNextState(void)
{
	rgb_led.calcColor(h,r,g,b);

	printf("h%u || r%u | g%u | b%u\n",h,r,g,b);

	if(h >= 359)
		h = 0;
	else
		h++;

	rgb_led.setLightFunc2(g,r,b);
}

void lightCtrl::update(void)
{
	rgb_led.runFunc();
}
