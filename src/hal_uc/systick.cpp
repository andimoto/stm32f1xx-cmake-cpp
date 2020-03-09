/**
 * File: systick.cpp
 * Initial Author: andimoto
 */
#include <cstdint>
#include <stdint.h>

#include "stm32f1xx.h"

// Counts milliseconds
volatile std::uint32_t systick_count=0;

extern "C" // Interrupt handler
void SysTick_Handler(void)
{
    systick_count++;
}

void disableSysTick(void)
{
	SysTick->CTRL  = ~(SysTick_CTRL_CLKSOURCE_Msk |
	   SysTick_CTRL_TICKINT_Msk   |
	   SysTick_CTRL_ENABLE_Msk);
}

void enableSysTick(void)
{
	SysTick->CTRL  = (SysTick_CTRL_CLKSOURCE_Msk |
	   SysTick_CTRL_TICKINT_Msk   |
	   SysTick_CTRL_ENABLE_Msk);
}

std::uint32_t getSysTick(void)
{
	return systick_count;
}

// Delay some milliseconds.
// Note that effective time may be up to 1ms shorter than requested.
void delay_ms(std::uint32_t ms)
{
    std::uint32_t start=systick_count;
    while (systick_count-start<ms);
}

