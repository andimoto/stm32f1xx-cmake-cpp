/**
 * File: lightCtrl.hpp
 * Initial Author: andimoto
 */
#ifndef LIGHTCTRL_H_
#define LIGHTCTRL_H_

#include <cstdint>
#include <stdint.h>

#include "stm32f1xx.h"
#include "rgb_ws2812b.hpp"
#include "color.hpp"

class lightCtrl
{
public:
	lightCtrl();

	void setNextState(void);
	void update(void);
private:
	hal_pcb::rgb_ws2812b rgb_led;

	std::uint8_t g = 0;
	std::uint8_t r = 0;
	std::uint8_t b = 0;
	std::uint32_t h = 1;

;
};


#endif /* LIGHTCTRL_H_ */
