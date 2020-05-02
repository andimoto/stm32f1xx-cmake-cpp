/**
 * File: lightCtrl.cpp
 * Initial Author: andimoto
 */

#include "lightCtrl.hpp"
#include "itm_write.h"

lightCtrl::lightCtrl(void)
{

}

void lightCtrl::setNextState(void)
{
	rgb_led.calcColor(h,r,g,b);

	printf("h%u || r%u | g%u | b%u\n",h,r,g,b);

	if(h >= 360)
		h = 1;
	else
		h++;

	rgb_led.setLightFunc2(g,r,b);
}

void lightCtrl::update(void)
{
	rgb_led.runFunc();
}
