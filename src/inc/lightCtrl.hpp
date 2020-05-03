/**
 * File: lightCtrl.hpp
 * Initial Author: andimoto
 */
#ifndef LIGHTCTRL_H_
#define LIGHTCTRL_H_

#include <cstdint>
#include <stdint.h>

#include "stm32f1xx.h"
#include "buttonCtrl.hpp"
#include "rgb_ws2812b.hpp"
#include "color.hpp"

class lightCtrl
{
public:
	enum class Mode{
		OFF,
		STATIC,
		PULSE,
		RAINBOW,
		FIRE,
		ALL_ON
	};


	lightCtrl();
	void process(const hal_pcb::buttonCtrl::buttonPress btnPress);
	void setNextState(void);
	void update(void);
private:
	hal_pcb::rgb_ws2812b rgb_led;

	Mode lightMode;

	std::uint8_t g = 0;
	std::uint8_t r = 0;
	std::uint8_t b = 0;
	std::uint32_t h = 0;

;
};


#endif /* LIGHTCTRL_H_ */
