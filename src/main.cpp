/**
 * File: main.cpp
 * Initial Author: andimoto
 */

#include "main.hpp"
#include "itm_write.h"
#include "rgb_ws2812b.hpp"
#include "timer.hpp"
#include "gpio.hpp"

/* configure timer for about 1ms @APB1 Clock of 72Mhz / 4 (AHB Div) */
const hal_uc::timer::timConfig tim2Conf(
		hal_uc::timer::Instance::TIMER2,
		72-1,
		hal_uc::timer::CounterMode::UP,
		1000,
		hal_uc::timer::ClockDiv::DIV1,
		0
		);

static std::uint32_t counter = 0;
static void countUp(void)
{
	counter++;
}

int main()
{
	bool rgbOn = false;
	hal_pcb::rgb_ws2812b rgb_led;

	hal_uc::timer tim2(tim2Conf, &countUp);
	tim2.start();

	for (;;)
	{
//		delay_ms(1000);
//		printf("Hello!\n");

		if(counter > 1000)
		{
			if(rgbOn == false)
			{
				rgbOn = true;
				rgb_led.setRgbLed(0,0,0);
			}else{
				rgbOn = false;
				rgb_led.resetRgb();
			}

			rgb_led.toggleCtrlLed();
			counter = 0;
			printf("%u\n", getSysTick());
		}
	};

	return 0;
}
