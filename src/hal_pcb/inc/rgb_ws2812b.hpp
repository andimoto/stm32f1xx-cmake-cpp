/**
 * File: rgb_ws2812b.cpp
 * Initial Author: andimoto
 */
#ifndef HAL_PCB_RGB_WS2812B_H_
#define HAL_PCB_RGB_WS2812B_H_

#include <cstdint>
#include "gpio.hpp"
#include "stm32f1xx.h"


namespace hal_pcb
{

class rgb_ws2812b
{
public:
	rgb_ws2812b();

	void toggleCtrlLed(void);
	void setRgbLed(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue);
	void resetRgb(void);

private:
	hal_uc::gpio ws2812b_din;
	hal_uc::gpio ctrl;

	void t0low(void);
	void t0high(void);
	void t1low(void);
	void t1high(void);

};


}

#endif /* HAL_PCB_RGB_WS2812B_H_ */

