/**
 * Name: stmGpio.hpp
 * Initial Author: andimoto
 */
#ifndef HAL_UC_STM_GPIO_H_
#define HAL_UC_STM_GPIO_H_

#include <cstdint>


typedef volatile uint32_t * bitband_t;

/* base address for bit banding */
#define BITBAND_SRAM_REF              (0x20000000)
/* base address for bit banding */
#define BITBAND_SRAM_BASE             (0x22000000)
/* base address for bit banding */
#define BITBAND_PERIPH_REF            (0x40000000)
/* base address for bit banding */
#define BITBAND_PERIPH_BASE           (0x42000000)

/* sram bit band */
#define BITBAND_SRAM(address, bit)     ((void*)(BITBAND_SRAM_BASE +   \
                (((uint32_t)address) - BITBAND_SRAM_REF) * 32 + (bit) * 4))

/* periph bit band */
#define BITBAND_PERIPH(address, bit)   ((void *)(BITBAND_PERIPH_BASE + \
                (((uint32_t)address) - BITBAND_PERIPH_REF) * 32 + (bit) * 4))

namespace hal_uc
{

class stmGpio
{
public:
	enum class Port
	{
		PORT_A,
		PORT_B,
		PORT_C,
		PORT_D,
		PORT_E,
//		PORT_F,
//		PORT_G,
//		PORT_H,
//		PORT_I,
//		PORT_J,
//		PORT_K,
		PORT_ALL
	};

	enum class Pin : std::uint32_t
	{
		PIN_0 =	0,
		PIN_1 = 1,
		PIN_2 = 2,
		PIN_3 = 3,
		PIN_4 = 4,
		PIN_5 = 5,
		PIN_6 = 6,
		PIN_7 = 7,
		PIN_8 = 8,
		PIN_9 = 9,
		PIN_10 = 10,
		PIN_11 = 11,
		PIN_12 = 12,
		PIN_13 = 13,
		PIN_14 = 14,
		PIN_15 = 15,
		PIN_ALL
	};

	enum class Mode
	{
		IN = 0x00,
		OUT = 0x01,
		AF = 0x02,
		AN = 0x03
	};

	enum class Speed
	{
		LOW     = 0x00, /*!< Low speed    */
		MEDIUM  = 0x01, /*!< Medium speed */
		FAST    = 0x02, /*!< Fast speed   */
		HIGH    = 0x03  /*!< High speed   */
	};

	enum class Type
	{
		PUSHPULL,
		OPENDRAIN
	};

	enum class PushPull
	{
		NONE,
		UP,
		DOWN
	};

	struct gpioConfig
	{
	public:
		Port			gpioPort;
		Pin			    gpioPin;
		Mode 			gpioMode;
		Speed 			gpioSpeed;
		Type 			gpioType;
		PushPull		gpioPushPull;

		gpioConfig(const Port portConf, const Pin pinConf, const Mode modeConf,
				const Speed speedConf, const Type typeConf, const PushPull ppConf);
	};

	stmGpio(const gpioConfig& gpioConfiguration);

	void set(void);
	void reset(void);
	void toggle(void);

	std::uint8_t get(void) const;

	bitband_t getSetPin(void);
	bitband_t getResetPin(void);

private:

	const Port gpioPort;
	const Pin gpioPin;
	const Mode gpioMode;

	bitband_t pinRead;
	bitband_t pinSet;
	bitband_t pinReset;
};


}
#endif /* HAL_UC_STM_GPIO_H_ */
