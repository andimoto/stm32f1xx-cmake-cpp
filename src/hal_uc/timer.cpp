/**
 * File: timer.cpp
 * Initial Author: andimoto
 */

#include "timer.hpp"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_tim.h"
#include "core_cm3.h"

static TIM_TypeDef* timerBase[static_cast<std::uint8_t>(hal_uc::timer::Instance::ALL)] = {
		TIM2,
		TIM3,
		TIM4
//		,
//		TIM5,
//		TIM6,
//		TIM7,
//		TIM9,
//		TIM10,
//		TIM11,
//		TIM12,
//		TIM13,
//		TIM14
};

static std::uint32_t rccTimers[static_cast<std::uint8_t>(hal_uc::timer::Instance::ALL)] = {
		RCC_APB1ENR_TIM2EN,
		RCC_APB1ENR_TIM3EN,
		RCC_APB1ENR_TIM4EN
//		,
//		RCC_APB1Periph_TIM5,
//		RCC_APB1Periph_TIM6,
//		RCC_APB1Periph_TIM7,
//		RCC_APB2Periph_TIM9,
//		RCC_APB2Periph_TIM10,
//		RCC_APB2Periph_TIM11,
//		RCC_APB1Periph_TIM12,
//		RCC_APB1Periph_TIM13,
//		RCC_APB1Periph_TIM14
};


static IRQn_Type nvicIrqMap[static_cast<std::uint8_t>(hal_uc::timer::Instance::ALL)] = {
		TIM2_IRQn,
		TIM3_IRQn,
		TIM4_IRQn
//		,
//		TIM5_IRQn,
//		TIM6_DAC_IRQn,
//		TIM7_IRQn,
//		TIM1_BRK_TIM9_IRQn,
//		TIM1_UP_TIM10_IRQn,
//		TIM1_TRG_COM_TIM11_IRQn,
//		TIM8_BRK_TIM12_IRQn,
//		TIM8_UP_TIM13_IRQn,
//		TIM8_TRG_COM_TIM14_IRQn
};

static void startTimerCtrl(const hal_uc::timer::Instance tim)
{
	timerBase[static_cast<std::uint8_t>(tim)]->CR1 |= static_cast<std::uint16_t>(TIM_CR1_CEN);
	timerBase[static_cast<std::uint8_t>(tim)]->DIER |= static_cast<std::uint16_t>(TIM_IT_UPDATE);
}

static void stopTimerCtrl(const hal_uc::timer::Instance tim)
{
	timerBase[static_cast<std::uint8_t>(tim)]->CR1 &= static_cast<std::uint16_t>(~TIM_CR1_CEN);
	timerBase[static_cast<std::uint8_t>(tim)]->DIER &= static_cast<std::uint16_t>(~TIM_IT_UPDATE);
}

static void enableTimerIrq(const hal_uc::timer::Instance tim)
{
///**/	timerBase[static_cast<std::uint8_t>(tim)]->DIER |= static_cast<std::uint16_t>(TIM_IT_UPDATE);
	NVIC_EnableIRQ(nvicIrqMap[static_cast<std::uint8_t>(tim)]);
}

static void disableTimerIrq(const hal_uc::timer::Instance tim)
{
///**/	timerBase[static_cast<std::uint8_t>(tim)]->DIER &= static_cast<std::uint16_t>(~TIM_IT_UPDATE);
	NVIC_DisableIRQ(nvicIrqMap[static_cast<std::uint8_t>(tim)]);
}


hal_uc::timer::timConfig::timConfig(const Instance instConf, const std::uint16_t prescalerConf, const CounterMode counterModeConf,
				const std::uint32_t periodConf, const ClockDiv clockDivConf, const std::uint8_t repetitionConf) :
		timInstance(instConf), prescaler(prescalerConf), counterMode(counterModeConf),
		period(periodConf), clockDiv(clockDivConf), repetitionCnt(repetitionConf)
{

}

static void registerTimerObject(hal_uc::timer* timerObj, const hal_uc::timer::Instance timerObjInstance);

static void initTimer(const hal_uc::timer::timConfig& timerConfigInit)
{
	TIM_HandleTypeDef TimerInit;

	TimerInit.Instance = timerBase[static_cast<std::uint8_t>(timerConfigInit.timInstance)];
	TimerInit.Init.Prescaler = static_cast<std::uint16_t>(timerConfigInit.prescaler);
	TimerInit.Init.CounterMode = static_cast<std::uint16_t>(timerConfigInit.counterMode);
	TimerInit.Init.Period = static_cast<std::uint32_t>(timerConfigInit.period);
	TimerInit.Init.ClockDivision = static_cast<std::uint16_t>(timerConfigInit.clockDiv);
	TimerInit.Init.RepetitionCounter = static_cast<std::uint16_t>(timerConfigInit.repetitionCnt);


	/* enable RCC Clock for selected Timer */
	do {
		__IO uint32_t tmpreg;
		SET_BIT(RCC->APB1ENR, rccTimers[static_cast<std::uint8_t>(timerConfigInit.timInstance)]);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->APB1ENR, rccTimers[static_cast<std::uint8_t>(timerConfigInit.timInstance)]);
		UNUSED(tmpreg);
	} while(0);

	HAL_TIM_Base_Init(&TimerInit);
}

hal_uc::timer::timer(const timConfig timerConf, simplePointer timerIrqFuncConfig) :
		timInstance(timerConf.timInstance),
		timerIrqFunc(timerIrqFuncConfig)
{
	initTimer(timerConf);
	enableTimerIrq(timInstance); /* enable NVIC Irq */
	/* register this timer object for usage in TIMx_IRQHandler */
	registerTimerObject(this, timInstance);
}

std::uint32_t hal_uc::timer::get(void) const
{
	return static_cast<std::uint32_t>( timerBase[static_cast<std::uint8_t>(timInstance)]->CNT );
}

void hal_uc::timer::start(void)
{
	/* enable irq only if an irq handler function has been provided */
	if(timerIrqFunc != nullptr)
	{
//		enableTimerIrq(timInstance); /* enable NVIC Irq */
	}
	startTimerCtrl(timInstance); /* start timer */
}

void hal_uc::timer::stop(void)
{
	/* enable irq only if an irq handler function has been provided */
	if(timerIrqFunc != nullptr)
	{
//		disableTimerIrq(timInstance); /* disable NVIC Irq */
	}
	stopTimerCtrl(timInstance); /* stop timer */
}

void hal_uc::timer::irqHandler(void)
{
	/* clear TIM UPDATE FLAG */
	timerBase[static_cast<std::uint8_t>(timInstance)]->SR &= static_cast<std::uint16_t>(~TIM_FLAG_UPDATE);

	/* call given irq function if not nullptr */
	if(timerIrqFunc != nullptr)
	{
		timerIrqFunc();
	}
}


/*******************************/
/* * * * * IRQ Handler * * * * */
/*******************************/

/* timer object pointers for using in TIMx_IRQ_Handler functions */
static hal_uc::timer* tim2ref = nullptr;
static hal_uc::timer* tim3ref = nullptr;
static hal_uc::timer* tim4ref = nullptr;



static void registerTimerObject(hal_uc::timer* timerObj, const hal_uc::timer::Instance timerObjInstance)
{
	switch(timerObjInstance)
	{
	case hal_uc::timer::Instance::TIMER2: tim2ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER3: tim3ref = timerObj; break;
	case hal_uc::timer::Instance::TIMER4: tim4ref = timerObj; break;
//	case hal_uc::timer::Instance::TIMER5: tim5ref = timerObj; break;
//	case hal_uc::timer::Instance::TIMER6: tim6ref = timerObj; break;
//	case hal_uc::timer::Instance::TIMER7: tim7ref = timerObj; break;
//	case hal_uc::timer::Instance::TIMER9: tim9ref = timerObj; break;
//	case hal_uc::timer::Instance::TIMER10: tim10ref = timerObj; break;
//	case hal_uc::timer::Instance::TIMER11: tim11ref = timerObj; break;
//	case hal_uc::timer::Instance::TIMER12: tim12ref = timerObj; break;
//	case hal_uc::timer::Instance::TIMER13: tim13ref = timerObj; break;
//	case hal_uc::timer::Instance::TIMER14: tim14ref = timerObj; break;
	case hal_uc::timer::Instance::ALL:
		while(1){
			/* fail config! run into endless loop */
		};
		break;
	}
}

extern "C" void TIM2_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(nvicIrqMap[static_cast<std::uint8_t>(hal_uc::timer::Instance::TIMER2)]);
	if(tim2ref != nullptr)
	{
		tim2ref->irqHandler();
	}
}

extern "C" void TIM3_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(nvicIrqMap[static_cast<std::uint8_t>(hal_uc::timer::Instance::TIMER3)]);
	if(tim3ref != nullptr)
	{
		tim3ref->irqHandler();
	}
}

extern "C" void TIM4_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(nvicIrqMap[static_cast<std::uint8_t>(hal_uc::timer::Instance::TIMER4)]);
	if(tim4ref != nullptr)
	{
		tim4ref->irqHandler();
	}
}
