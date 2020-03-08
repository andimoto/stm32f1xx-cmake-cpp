/**
 * File: rgb_ws2812b.cpp
 * Initial Author: andimoto
 */
#ifndef HAL_PCB_RGB_WS2812B_H_
#define HAL_PCB_RGB_WS2812B_H_

#include <cstdint>
#include "gpio.hpp"
#include "stmGpio.hpp"
#include "stm32f1xx.h"


namespace hal_pcb
{

class rgb_ws2812b
{
public:
	rgb_ws2812b();

	void setRgbLed(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue);
	void resetRgb(void);

	void setTestLed(void);


private:
	hal_uc::stmGpio ws2812b_din;
	hal_uc::stmGpio testPin;

	bitband_t dinSet;
	bitband_t dinReset;

	bitband_t test_dinSet;
	bitband_t test_dinReset;

	void t0low(void);
	void t0high(void);
	void t1low(void);
	void t1high(void);

	void reset(void);
};


}

#endif /* HAL_PCB_RGB_WS2812B_H_ */

