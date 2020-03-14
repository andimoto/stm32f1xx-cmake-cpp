/**
 * File: main.hpp
 * Initial Author: andimoto
 */
#ifndef MAIN_H_
#define MAIN_H_

#include <cstdint>
#include <stdint.h>

#include "stm32f1xx.h"

extern void delay_ms(std::uint32_t ms);
extern std::uint32_t getSysTick(void);
extern void disableSysTick(void);
extern void enableSysTick(void);


#endif /* MAIN_H_ */
