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


constexpr std::uint32_t bitsG = 8*2;
constexpr std::uint32_t bitsR = 8*2;
constexpr std::uint32_t bitsB = 8*2;
static void (*led01_hl[bitsG+bitsR+bitsB])(void);


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




//****************************
void t1high(void)
{
	*gDinSet = 1;
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

void t1low(void)
{
	*gDinReset = 1;
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");

	__asm__("nop\n\t");

}

void t0high(void)
{
	*gDinSet = 1;
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");

}

//****************************
void t0low(void)
{
	*gDinReset = 1;
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t"); //416ns

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
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");
	__asm__("nop\n\t");

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




void hal_pcb::rgb_ws2812b::setLightFunc(void)
{
	std::uint32_t index = 0;
	std::uint8_t g = 0x0F;
	std::uint8_t r = 0x3C;
	std::uint8_t b = 0xF0;

	index = 0;
	while(index < bitsG){
		led01_hl[index] = t1high;
		led01_hl[index+1] = t1low;
		index = index + 2;
	}

	index = 0;
	while(index < bitsR){
		led01_hl[index+bitsG] = t1high;
		led01_hl[index+bitsG+1] = t1low;
		index = index + 2;
	}

	index = 0;
	while(index < bitsB){
		led01_hl[index+bitsG+bitsB] = t0high;
		led01_hl[index+bitsG+bitsB+1] = t0low;
		index = index + 2;
	}

}



void hal_pcb::rgb_ws2812b::setTurnOff(void)
{
	std::uint32_t index = 0;

	index = 0;
	while(index < bitsG){
		led01_hl[index] = t0high;
		led01_hl[index+1] = t0low;
		index = index + 2;
	}

	index = 0;
	while(index < bitsR){
		led01_hl[index+bitsG] = t0high;
		led01_hl[index+bitsG+1] = t0low;
		index = index + 2;
	}

	index = 0;
	while(index < bitsB){
		led01_hl[index+bitsG+bitsB] = t0high;
		led01_hl[index+bitsG+bitsB+1] = t0low;
		index = index + 2;
	}
}


void hal_pcb::rgb_ws2812b::runFunc(void)
{
	std::uint8_t index=0;
	/* LED Green */
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();

	/* LED Red */
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();

	/* LED Blue */
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
	led01_hl[index++]();
}






__INLINE static void nwait33percent(void)
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
__INLINE void it1high(void)
{
	*gDinSet = 1;
	nwait33percent();
	nwait33percent();
}

__INLINE void it1low(void)
{
	*gDinReset = 1;
	nwait33percent();
}

__INLINE void it0high(void)
{
	*gDinSet = 1;
	nwait33percent();
}

__INLINE void it0low(void)
{
	*gDinReset = 1;
	nwait33percent();
	nwait33percent();
}



void hal_pcb::rgb_ws2812b::resetRgb(void)
{
	std::uint8_t index = 24;

	while(index){
		it0high();
		it0low();

		index--;
	}

}



