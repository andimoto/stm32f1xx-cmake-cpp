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



static bitband_t gDinSet;
static bitband_t gDinReset;

static bitband_t gtest_dinSet;
static bitband_t gtest_dinReset;

hal_pcb::rgb_ws2812b::rgb_ws2812b(void):
		ws2812b_din(ws2812b_conf),
		testPin(testPin_conf),
		dinSet(ws2812b_din.getSetPin()),
		dinReset(ws2812b_din.getResetPin()),
		test_dinSet(testPin.getSetPin()),
		test_dinReset(testPin.getResetPin())
{
	gDinSet = dinSet;
	gDinReset = dinReset;

	gtest_dinSet = test_dinSet;
	gtest_dinReset = test_dinReset;
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

__INLINE void t1high(void)
{
	*gDinSet = 1;
	wait33percent();
	wait33percent();
}

__INLINE void t1low(void)
{
	*gDinReset = 1;
	wait33percent();
}

__INLINE void t0high(void)
{
	*gDinSet = 1;
	wait33percent();
}

__INLINE void t0low(void)
{
	*gDinReset = 1;
	wait33percent();
	wait33percent();
}


void hal_pcb::rgb_ws2812b::resetRgb(void)
{
	std::uint8_t index = 24;

	while(index){
		t0high();
		t0low();

		index--;
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
	std::uint8_t bitByteGh = 4;
	std::uint8_t bitByteGl = 4;
	std::uint8_t bitByteRh = 4;
	std::uint8_t bitByteRl = 4;
	std::uint8_t bitByteBh = 4;
	std::uint8_t bitByteBl = 4;

	while(bitByteGh)
	{
		t0high();
		t0low();

		bitByteGh--;
	}

	while(bitByteGl)
	{
		t0high();
		t0low();

		bitByteGl--;
	}
//###################################
	while(bitByteRh)
	{
		t1high();
		t1low();

		bitByteRh--;
	}

	while(bitByteRl)
	{
		t1high();
		t1low();

		bitByteRl--;
	}
//###################################
	while(bitByteBh)
	{
		t1high();
		t1low();

		bitByteBh--;
	}

	while(bitByteBl)
	{
		t1high();
		t1low();

		bitByteBl--;
	}

}



//######################################
//######################################

__INLINE void at1high(void)
{
	*gtest_dinSet = 1;
	wait33percent();
	wait33percent();
}

__INLINE void at1low(void)
{
	*gtest_dinReset = 1;
	wait33percent();
}

__INLINE void at0high(void)
{
	*gtest_dinSet = 1;
	wait33percent();
}

__INLINE void at0low(void)
{
	*gtest_dinReset = 1;
	wait33percent();
	wait33percent();
}


void hal_pcb::rgb_ws2812b::setTestLed(void)
{
	std::uint8_t bitByteGh = 4;
	std::uint8_t bitByteGl = 4;
	std::uint8_t bitByteRh = 4;
	std::uint8_t bitByteRl = 4;
	std::uint8_t bitByteBh = 4;
	std::uint8_t bitByteBl = 4;

	while(bitByteGh)
	{
		at0high();
		at0low();

		bitByteGh--;
	}

	while(bitByteGl)
	{
		at0high();
		at0low();

		bitByteGl--;
	}
//###################################
	while(bitByteRh)
	{
		at1high();
		at1low();

		bitByteRh--;
	}

	while(bitByteRl)
	{
		at1high();
		at1low();

		bitByteRl--;
	}
//###################################
	while(bitByteBh)
	{
		at1high();
		at1low();

		bitByteBh--;
	}

	while(bitByteBl)
	{
		at1high();
		at1low();

		bitByteBl--;
	}

}

void hal_pcb::rgb_ws2812b::resetTestLed(void)
{
	std::uint8_t index = 24;

	while(index){
		at0high();
		at0low();

		index--;
	}

}

void hal_pcb::rgb_ws2812b::testBreak(void)
{
	std::uint32_t index = 450;

	while(index){
		__asm__("nop\n\t");
		index--;
	}

}
