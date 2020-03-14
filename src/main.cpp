/**
 * File: main.cpp
 * Initial Author: andimoto
 */

#include "main.hpp"
#include "itm_write.h"
#include "rgb_ws2812b.hpp"
#include "timer.hpp"
#include "gpio.hpp"
#include "bbGpio.hpp"
#include "color.hpp"

/* configure timer for about 1ms @APB1 Clock of 72Mhz / 4 (AHB Div) */
const hal_uc::timer::timConfig tim2Conf(
		hal_uc::timer::Instance::TIMER2,
		72-1,
		hal_uc::timer::CounterMode::UP,
		1000-1,
		hal_uc::timer::ClockDiv::DIV1,
		0
		);

static const hal_uc::bbGpio::gpioConfig led_conf(hal_uc::bbGpio::Port::PORT_C, hal_uc::bbGpio::Pin::PIN_13,
		hal_uc::bbGpio::Mode::OUT, hal_uc::bbGpio::Speed::FAST,	hal_uc::bbGpio::Type::PUSHPULL,
		hal_uc::bbGpio::PushPull::UP);

static const hal_uc::gpio::gpioConfig btnr_conf(hal_uc::gpio::Port::PORT_B, hal_uc::gpio::Pin::PIN_1,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::UP);

static const hal_uc::gpio::gpioConfig btnl_conf(hal_uc::gpio::Port::PORT_B, hal_uc::gpio::Pin::PIN_0,
		hal_uc::gpio::Mode::IN, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::DOWN);

static std::uint32_t counter = 0;
static void countUp(void)
{
	counter++;
}

int main()
{
	hal_pcb::rgb_ws2812b rgb_led;

	std::uint8_t g = 0;
	std::uint8_t r = 0;
	std::uint8_t b = 0;
	std::uint32_t h = 1;

	bool colorUp = false;
	color colorState = color::RED;

	hal_uc::gpio btnOut(btnr_conf);
	hal_uc::gpio btn(btnl_conf);
	std::uint8_t btnValPrev = 0;

	hal_uc::bbGpio led(led_conf);
	led.set();

	btnOut.set();

	hal_uc::timer tim2(tim2Conf, &countUp);
	tim2.start();

	disableSysTick();

	while(1)
	{
		if(counter > 200)
		{
			std::uint8_t btnVal = btn.get();
			if(btnVal == 0 && btnValPrev == 1)
			{
				g = colorValues[static_cast<std::uint8_t>(colorState)][static_cast<std::uint8_t>(LED::GREEN)];
				r = colorValues[static_cast<std::uint8_t>(colorState)][static_cast<std::uint8_t>(LED::RED)];
				b = colorValues[static_cast<std::uint8_t>(colorState)][static_cast<std::uint8_t>(LED::BLUE)];

//				rgb_led.calcColor(h,r,g,b);

				if(h >= 360)
					h = 1;
				else
					h++;

				printf("h%u || r%u | g%u | b%u\n",h,r,g,b);

				tim2.stop();
				led.toggle();

				rgb_led.setLightFunc2(g,r,b);
				rgb_led.runFunc();

				tim2.start();


				if(colorUp)
				{
					colorState = static_cast<color>(static_cast<std::uint8_t>(colorState)-1);
				}else{
					colorState = static_cast<color>(static_cast<std::uint8_t>(colorState)+1);
				}


				if(colorState == color::ROSE1 || colorState == color::RED)
				{
					if(colorUp == true)
						colorUp = false;
					else
						colorUp = true;
				}
			}
			btnValPrev = btnVal;

			counter = 0;

//			printf("%u\n", getSysTick());
		}
	};

	return 0;
}
