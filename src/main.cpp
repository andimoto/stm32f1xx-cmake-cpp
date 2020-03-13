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

	std::uint8_t countColor = 0x01;
	std::uint8_t g = 0;
	std::uint8_t r = 0;
	std::uint8_t b = 0;


#ifdef BITBAND
	hal_uc::stmGpio led(led_conf);
	led.set();
#else
	hal_uc::gpio ledg(led_conf2);
#endif
	hal_uc::timer tim2(tim2Conf, &countUp);
	tim2.start();

	disableSysTick();

	while(1)
	{
		if(counter > 400)
		{
			if( (countColor&0x01) == 0x01)
			{
				g++;
			}
			if( (countColor&0x03) == 0x02)
			{
				r++;
			}
			if( (countColor&0x04) == 0x04)
			{
				b++;
			}
			countColor++;

//			g++;
//			r++;
//			b--;


			tim2.stop();
#ifdef BITBAND
			led.toggle();
#else
			ledg.toggle();
#endif



			if(rgbOn == false)
			{
				rgbOn = true;
				rgb_led.setLightFunc2(g,r,b);
				rgb_led.runFunc();

			}else{
				rgbOn = false;
				rgb_led.setTurnOff();
				rgb_led.runFunc();

			}
			tim2.start();
			counter = 0;
//			printf("%u\n", getSysTick());
		}
	};

	return 0;
}
