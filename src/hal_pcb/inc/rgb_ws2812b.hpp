/**
 * File: rgb_ws2812b.cpp
 * Initial Author: andimoto
 */
#ifndef HAL_PCB_RGB_WS2812B_H_
#define HAL_PCB_RGB_WS2812B_H_

#include <cstdint>

#include "bbGpio.hpp"
#include "gpio.hpp"
#include "stm32f1xx.h"


namespace hal_pcb
{

class rgb_ws2812b
{
public:
	rgb_ws2812b();

	void setLightFunc(void);
	void setLightFunc2(std::uint8_t g, std::uint8_t r, std::uint8_t b);
	void setTurnOff(void);
	void runFunc(void);

	void resetRgb(void);

private:
	hal_uc::bbGpio ws2812b_din;
	hal_uc::bbGpio testPin;

	bitband_t dinSet;
	bitband_t dinReset;

	bitband_t test_dinSet;
	bitband_t test_dinReset;

	void reset(void);
};


}

#endif /* HAL_PCB_RGB_WS2812B_H_ */

