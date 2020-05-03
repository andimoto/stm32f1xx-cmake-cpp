/**
 * File: main.cpp
 * Initial Author: andimoto
 */

#include "main.hpp"
#include "itm_write.h"
#include "lightCtrl.hpp"
//#include "rgb_ws2812b.hpp"
#include "buttonCtrl.hpp"
#include "timer.hpp"
#include "gpio.hpp"
#include "bbGpio.hpp"
#include "color.hpp"

#define PROC_PERIOD 100

/* configure timer for about 1ms @APB1 Clock of 72Mhz / 4 (AHB Div) */
const hal_uc::timer::timConfig tim2Conf(
		hal_uc::timer::Instance::TIMER2,
		72-1,
		hal_uc::timer::CounterMode::UP,
		1000-1,
		hal_uc::timer::ClockDiv::DIV4,
		0
		);

static const hal_uc::bbGpio::gpioConfig led_conf(hal_uc::bbGpio::Port::PORT_C, hal_uc::bbGpio::Pin::PIN_13,
		hal_uc::bbGpio::Mode::OUT, hal_uc::bbGpio::Speed::FAST,	hal_uc::bbGpio::Type::PUSHPULL,
		hal_uc::bbGpio::PushPull::UP);

static const hal_uc::gpio::gpioConfig btnl_conf(hal_uc::gpio::Port::PORT_B, hal_uc::gpio::Pin::PIN_1,
		hal_uc::gpio::Mode::IN, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::DOWN);

static std::uint32_t counter = 0;
static void countUp(void)
{
	counter++;
}

int main()
{
	disableSysTick();

	lightCtrl rgbLight;
	hal_uc::timer tim2(tim2Conf, &countUp);

	hal_pcb::buttonCtrl progButton(btnl_conf, PROC_PERIOD, 200, 1000, 2000);

	std::uint32_t tmpCnt = 0;

	hal_uc::bbGpio led(led_conf);
	led.set();

	tim2.start();

	printf("Initialized: FW %s - %s\n",__DATE__, __TIME__);

	while(1)
	{
		if(counter > PROC_PERIOD)
		{
			counter = 0;

			hal_pcb::buttonCtrl::buttonPress pressState = progButton.getButtonPress();
			if(pressState != hal_pcb::buttonCtrl::buttonPress::NO_PRESS)
				printf("%u\n", static_cast<std::uint32_t>(pressState));

			/* process button state */
			rgbLight.process(pressState);

			tim2.stop();

			rgbLight.update();

			tim2.start();

			/* Control LED on STM32F1 DevBoard */
			tmpCnt++;
			if(tmpCnt > 50)
			{
				tmpCnt = 0;
				led.toggle();
			}
		}
	}

	return 0;
}
