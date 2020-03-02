/**
 * File: types.hpp
 * Initial Author: andimoto
 */

#include <cstdint>
#include <stdint.h>

#include "stm32f1xx.h"

extern void delay_ms(std::uint32_t ms);
extern std::uint32_t getSysTick(void);
