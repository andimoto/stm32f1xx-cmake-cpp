/*
 * PinBase.cpp
 *
 *  Created on: 27.03.2020
 *      Author: andreas
 */

#include <PinBase.hpp>

#include "stm32f1xx.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_def.h"


namespace hal_uc
{

PinBase::PinBase(const PortBase& port, const PinInitType& pinInit) :
		port(port), pinConfig(pinInit)
{
	init();
}


PinBase::init(void)
{
		uint32_t position;
	  uint32_t ioposition = 0x00;
	  uint32_t iocurrent = 0x00;
	  uint32_t temp = 0x00;
	  uint32_t config = 0x00;
	  __IO uint32_t *configregister; /* Store the address of CRL or CRH register based on pin number */
	  uint32_t registeroffset = 0; /* offset used during computation of CNF and MODE bits placement inside CRL or CRH register */

	  const PinInitType* const GPIO_Init = &pinConfig;
	  GpioType* GPIO = port.getPortPtr();

	  /* Check the parameters */
	  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
	  assert_param(IS_GPIO_PIN(GPIO_Init->Pin));
	  assert_param(IS_GPIO_MODE(GPIO_Init->Mode));

	  /* Configure the port pins */
	  for (position = 0; position < GPIO_NUMBER; position++)
	  {
		/* Get the IO position */
		ioposition = ((uint32_t)0x01) << position;

		/* Get the current IO position */
		iocurrent = (uint32_t)(GPIO_Init->Pin) & ioposition;

		if (iocurrent == ioposition)
		{
		  /* Check the Alternate function parameters */
		  assert_param(IS_GPIO_AF_INSTANCE(GPIOx));

		  /* Based on the required mode, filling config variable with MODEy[1:0] and CNFy[3:2] corresponding bits */
		  switch (GPIO_Init->Mode)
		  {
			/* If we are configuring the pin in OUTPUT push-pull mode */
			case GPIO_MODE_OUTPUT_PP:
			  /* Check the GPIO speed parameter */
			  assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
			  config = GPIO_Init->Speed + GPIO_CR_CNF_GP_OUTPUT_PP;
			  break;

			/* If we are configuring the pin in OUTPUT open-drain mode */
			case GPIO_MODE_OUTPUT_OD:
			  /* Check the GPIO speed parameter */
			  assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
			  config = GPIO_Init->Speed + GPIO_CR_CNF_GP_OUTPUT_OD;
			  break;

			/* If we are configuring the pin in ALTERNATE FUNCTION push-pull mode */
			case GPIO_MODE_AF_PP:
			  /* Check the GPIO speed parameter */
			  assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
			  config = GPIO_Init->Speed + GPIO_CR_CNF_AF_OUTPUT_PP;
			  break;

			/* If we are configuring the pin in ALTERNATE FUNCTION open-drain mode */
			case GPIO_MODE_AF_OD:
			  /* Check the GPIO speed parameter */
			  assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
			  config = GPIO_Init->Speed + GPIO_CR_CNF_AF_OUTPUT_OD;
			  break;

			/* If we are configuring the pin in INPUT (also applicable to EVENT and IT mode) */
			case GPIO_MODE_INPUT:
			case GPIO_MODE_IT_RISING:
			case GPIO_MODE_IT_FALLING:
			case GPIO_MODE_IT_RISING_FALLING:
			case GPIO_MODE_EVT_RISING:
			case GPIO_MODE_EVT_FALLING:
			case GPIO_MODE_EVT_RISING_FALLING:
			  /* Check the GPIO pull parameter */
			  assert_param(IS_GPIO_PULL(GPIO_Init->Pull));
			  if(GPIO_Init->Pull == GPIO_NOPULL)
			  {
				config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_FLOATING;
			  }
			  else if(GPIO_Init->Pull == GPIO_PULLUP)
			  {
				config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_PU_PD;

				/* Set the corresponding ODR bit */
				GPIOx->BSRR = ioposition;
			  }
			  else /* GPIO_PULLDOWN */
			  {
				config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_PU_PD;

				/* Reset the corresponding ODR bit */
				GPIOx->BRR = ioposition;
			  }
			  break;

			/* If we are configuring the pin in INPUT analog mode */
			case GPIO_MODE_ANALOG:
				config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_ANALOG;
			  break;

			/* Parameters are checked with assert_param */
			default:
			  break;
		  }

		  /* Check if the current bit belongs to first half or last half of the pin count number
		   in order to address CRH or CRL register*/
		  configregister = (iocurrent < GPIO_PIN_8) ? &GPIOx->CRL     : &GPIOx->CRH;
		  registeroffset = (iocurrent < GPIO_PIN_8) ? (position << 2) : ((position - 8) << 2);

		  /* Apply the new configuration of the pin to the register */
		  MODIFY_REG((*configregister), ((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << registeroffset ), (config << registeroffset));

		  /*--------------------- EXTI Mode Configuration ------------------------*/
		  /* Configure the External Interrupt or event for the current IO */
		  if((GPIO_Init->Mode & EXTI_MODE) == EXTI_MODE)
		  {
			/* Enable AFIO Clock */
			__HAL_RCC_AFIO_CLK_ENABLE();
			temp = AFIO->EXTICR[position >> 2];
			CLEAR_BIT(temp, ((uint32_t)0x0F) << (4 * (position & 0x03)));
			SET_BIT(temp, (GPIO_GET_INDEX(GPIOx)) << (4 * (position & 0x03)));
			AFIO->EXTICR[position >> 2] = temp;


			/* Configure the interrupt mask */
			if((GPIO_Init->Mode & GPIO_MODE_IT) == GPIO_MODE_IT)
			{
			  SET_BIT(EXTI->IMR, iocurrent);
			}
			else
			{
			  CLEAR_BIT(EXTI->IMR, iocurrent);
			}

			/* Configure the event mask */
			if((GPIO_Init->Mode & GPIO_MODE_EVT) == GPIO_MODE_EVT)
			{
			  SET_BIT(EXTI->EMR, iocurrent);
			}
			else
			{
			  CLEAR_BIT(EXTI->EMR, iocurrent);
			}

			/* Enable or disable the rising trigger */
			if((GPIO_Init->Mode & RISING_EDGE) == RISING_EDGE)
			{
			  SET_BIT(EXTI->RTSR, iocurrent);
			}
			else
			{
			  CLEAR_BIT(EXTI->RTSR, iocurrent);
			}

			/* Enable or disable the falling trigger */
			if((GPIO_Init->Mode & FALLING_EDGE) == FALLING_EDGE)
			{
			  SET_BIT(EXTI->FTSR, iocurrent);
			}
			else
			{
			  CLEAR_BIT(EXTI->FTSR, iocurrent);
			}
		  }
		}
	  }

}

}
