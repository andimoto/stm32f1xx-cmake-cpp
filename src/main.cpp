/**
 * File: main.cpp
 * Initial Author: andimoto
 */

#include "main.hpp"
#include "itm_write.h"
#include "rgb_ws2812b.hpp"
#include "timer.hpp"
#include "gpio.hpp"
#include "stmGpio.hpp"

/* configure timer for about 1ms @APB1 Clock of 72Mhz / 4 (AHB Div) */
const hal_uc::timer::timConfig tim2Conf(
		hal_uc::timer::Instance::TIMER2,
		72-1,
		hal_uc::timer::CounterMode::UP,
		1000-1,
		hal_uc::timer::ClockDiv::DIV1,
		0
		);

static const hal_uc::stmGpio::gpioConfig led_conf(hal_uc::stmGpio::Port::PORT_C, hal_uc::stmGpio::Pin::PIN_13,
		hal_uc::stmGpio::Mode::OUT, hal_uc::stmGpio::Speed::FAST,	hal_uc::stmGpio::Type::PUSHPULL,
		hal_uc::stmGpio::PushPull::UP);

static const hal_uc::gpio::gpioConfig led_conf2(hal_uc::gpio::Port::PORT_C, hal_uc::gpio::Pin::PIN_13,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::UP);

static std::uint32_t counter = 0;
static void countUp(void)
{
	counter++;
}
#define BITBAND
int main()
{
	bool rgbOn = false;
	hal_pcb::rgb_ws2812b rgb_led;

#ifdef BITBAND
	hal_uc::stmGpio led(led_conf);
#else
	hal_uc::gpio ledg(led_conf2);
#endif
	hal_uc::timer tim2(tim2Conf, &countUp);
	tim2.start();

	disableSysTick();

	while(1)
	{
		if(counter > 500)
		{
			tim2.stop();
#ifdef BITBAND
			led.toggle();
#else
			ledg.toggle();
#endif

			rgb_led.setTestLed();
			rgb_led.testBreak();
			rgb_led.setLightFunc();
//			rgb_led.testRunFunc();

			rgb_led.testBreak();
			rgb_led.resetTestLed();

			if(rgbOn == false)
			{
				rgbOn = true;
				rgb_led.setRgbLed(0,0,0);

			}else{
				rgbOn = false;
				rgb_led.resetRgb();
			}
			tim2.start();
			counter = 0;
//			printf("%u\n", getSysTick());
		}
	};

	return 0;
}
