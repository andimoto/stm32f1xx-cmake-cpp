/**
 * File: rgb-ws2812b.cpp
 * Initial Author: andimoto
 */
#include <cstdint>
#include "rgb_ws2812b.hpp"
#include "stm32f1xx.h"


static const hal_uc::gpio::gpioConfig ws2812b_conf(hal_uc::gpio::Port::PORT_A, hal_uc::gpio::Pin::PIN_0,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::UP);

static const hal_uc::gpio::gpioConfig testPin_conf(hal_uc::gpio::Port::PORT_A, hal_uc::gpio::Pin::PIN_1,
		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
		hal_uc::gpio::PushPull::UP);

//static const hal_uc::gpio::gpioConfig led_conf(hal_uc::gpio::Port::PORT_C, hal_uc::gpio::Pin::PIN_13,
//		hal_uc::gpio::Mode::OUT, hal_uc::gpio::Speed::FAST,	hal_uc::gpio::Type::PUSHPULL,
//		hal_uc::gpio::PushPull::UP);

hal_pcb::rgb_ws2812b::rgb_ws2812b(void):
		ws2812b_din(ws2812b_conf),
		testPin(testPin_conf)
//,
//		ctrl(led_conf)
{
	/* initialize rgb led pin to high */
	ws2812b_din.set();
}

static void wait33percent(void)
{
	for(std::uint32_t index = 0; index<12/4;index++) /*14*0,028us*/
	{
		__asm__("nop\n\t");
	}
}

static void wait50percent(void)
{
	for(std::uint32_t index = 0; index<20/4;index++) /*22*0,028us*/
	{
		__asm__("nop\n\t");
	}
}

void hal_pcb::rgb_ws2812b::t1high(void)
{
	ws2812b_din.set();
	wait33percent();
	wait33percent();
}

void hal_pcb::rgb_ws2812b::t1low(void)
{
	ws2812b_din.reset();
	wait33percent();
}

void hal_pcb::rgb_ws2812b::t0high(void)
{
	ws2812b_din.set();
	wait33percent();
}

void hal_pcb::rgb_ws2812b::t0low(void)
{
	ws2812b_din.reset();
	wait33percent();
	wait33percent();
}


void hal_pcb::rgb_ws2812b::resetRgb(void)
{
	std::uint8_t index = 0;
	std::uint8_t tmp = 0;

	for(index=0; index < 24;index++)
	{
		t0high();
		t0low();
	}
	reset();
}

void hal_pcb::rgb_ws2812b::reset(void)
{
	std::uint16_t index = 0;

	ws2812b_din.reset();
	for(index=0; index < 260; index++)
	{
		__asm__("nop\n\t");
	}

	ws2812b_din.set();
}

void hal_pcb::rgb_ws2812b::setRgbLed(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue)
{
	const std::uint8_t bitByte = 8;
	std::uint8_t index = 0;
	std::uint8_t tmp = 0;

	for(index=0; index < 24; index++)
	{
		t1high();
		t1low();
	}
//	ws2812b_din.set();

	reset();

}

//####################################################################
//####################################################################
//####################################################################
//####################################################################

static void test33percent(void)
{
//	for(std::uint32_t index = 0; index<2;index++) /*14*0,028us*/
//	{
		__asm__("nop\n\t");
		__asm__("nop\n\t");
//	}
}

void hal_pcb::rgb_ws2812b::test1high(void)
{
	testPin.set();
	test33percent();
	test33percent();
}

void hal_pcb::rgb_ws2812b::test1low(void)
{
	testPin.reset();
	test33percent();
}

void hal_pcb::rgb_ws2812b::test0high(void)
{
	testPin.set();
	test33percent();
}

void hal_pcb::rgb_ws2812b::test0low(void)
{
	testPin.reset();
	test33percent();
	test33percent();
}


void hal_pcb::rgb_ws2812b::testReset(void)
{
	std::uint16_t index = 0;

	testPin.reset();
	for(index=0; index < 260; index++)
	{
		__asm__("nop\n\t");
	}

	testPin.set();
}

void hal_pcb::rgb_ws2812b::setTestLed(void)
{
	const std::uint8_t bitByte = 24;
	std::uint8_t index = 0;
	std::uint8_t tmp = 0;

//	for(index=0; index < bitByte; index++)
//	{
//		test1high();
//		test1low();
//	}

	testPin.set();
//	__asm__("nop\n\t");
//	__asm__("nop\n\t");
	testPin.reset();

//	test1high();
//	test1low();
//	test1high();
//	test1low();

//	reset();

}

//####################################################################
//####################################################################
//####################################################################


void hal_pcb::rgb_ws2812b::toggleCtrlLed(void)
{
//	ctrl.toggle();
}
