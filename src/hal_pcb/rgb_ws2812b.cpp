/**
 * File: rgb-ws2812b.cpp
 * Initial Author: andimoto
 */
#include <cstdint>
#include "rgb_ws2812b.hpp"
#include "stm32f1xx.h"


static const hal_uc::stmGpio::gpioConfig ws2812b_conf(hal_uc::stmGpio::Port::PORT_A, hal_uc::stmGpio::Pin::PIN_0,
		hal_uc::stmGpio::Mode::OUT, hal_uc::stmGpio::Speed::FAST,	hal_uc::stmGpio::Type::PUSHPULL,
		hal_uc::stmGpio::PushPull::UP);

static const hal_uc::stmGpio::gpioConfig testPin_conf(hal_uc::stmGpio::Port::PORT_A, hal_uc::stmGpio::Pin::PIN_1,
		hal_uc::stmGpio::Mode::OUT, hal_uc::stmGpio::Speed::FAST,	hal_uc::stmGpio::Type::PUSHPULL,
		hal_uc::stmGpio::PushPull::UP);


hal_pcb::rgb_ws2812b::rgb_ws2812b(void):
		ws2812b_din(ws2812b_conf),
		testPin(testPin_conf),
		dinSet(ws2812b_din.getSetPin()),
		dinReset(ws2812b_din.getResetPin()),
		test_dinSet(testPin.getSetPin()),
		test_dinReset(testPin.getResetPin())
{

}

__INLINE static void wait33percent(void)
{
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
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
	std::uint8_t bitByteR = 24;
	std::uint8_t bitByteG = 8;
	std::uint8_t bitByteB = 8;

	while(bitByteR)
	{
		*dinSet = 1;
		wait33percent();
		wait33percent();
		*dinReset = 1;
		wait33percent();
		bitByteR--;
	}

//	while(bitByteG)
//	{
//		*dinSet = 1;
//		wait33percent();
//		*dinReset = 1;
//		wait33percent();
//		bitByteG--;
//	}
//
//	while(bitByteB)
//	{
//		*dinSet = 1;
//		wait33percent();
//		*dinReset = 1;
//		wait33percent();
//		bitByteB--;
//	}
}


void hal_pcb::rgb_ws2812b::setTestLed(void)
{
	std::uint8_t bitByteR = 24;

	while(bitByteR)
	{
		*dinSet = 1;
		wait33percent();
		wait33percent();
		*dinReset = 1;
		wait33percent();
		bitByteR--;
	}

//	while(bitByteG)
//	{
//		*dinSet = 1;
//		wait33percent();
//		*dinReset = 1;
//		wait33percent();
//		bitByteG--;
//	}
//
//	while(bitByteB)
//	{
//		*dinSet = 1;
//		wait33percent();
//		*dinReset = 1;
//		wait33percent();
//		bitByteB--;
//	}

}
