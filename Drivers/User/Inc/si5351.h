/**
  ******************************************************************************
  * @file    si5351.h
  * @author  K.Wang
  * @brief   Header file of si5351 module.
  ******************************************************************************
  */
#ifndef __SI5351_H
#define __SI5351_H

#include "stm32h7xx_hal.h"
#include "i2c.h"
#include "math.h"

// Crystal frequency
#define SI5351_CRYSTAL_FREQ_25MHZ 25000000
#define SI5351_CRYSTAL_FREQ_27MHZ 27000000

#define SI5351_XTAL_FREQ	SI5351_CRYSTAL_FREQ_25MHZ

#define SI5351_ADDRESS 0x60

/*  Regeister enumerate */
enum
{
  SI5351_DEVICE_STATUS = 0,
  SI5351_INTERRUPT_STATUS_STICKY = 1,
  SI5351_INTERRUPT_STATUS_MASK = 2,
  SI5351_OUTPUT_ENABLE_CONTROL = 3,
  SI5351_OEB_PIN_ENABLE_CONTROL = 9,
  SI5351_PLL_INPUT_SOURCE = 15,
  SI5351_CLK0_CONTROL = 16,
  SI5351_CLK1_CONTROL = 17,
  SI5351_CLK2_CONTROL = 18,
  SI5351_CLK3_CONTROL = 19,
  SI5351_CLK4_CONTROL = 20,
  SI5351_CLK5_CONTROL = 21,
  SI5351_CLK6_CONTROL = 22,
  SI5351_CLK7_CONTROL = 23,
  SI5351_CLK3_0_DISABLE_STATE = 24,
  SI5351_CLK7_4_DISABLE_STATE = 25,
  SI5351_MULTISYNTH_NA_PARAMETERS_1 = 26,
  SI5351_MULTISYNTH_NA_PARAMETERS_2 = 27,
  SI5351_MULTISYNTH_NA_PARAMETERS_3 = 28,
  SI5351_MULTISYNTH_NA_PARAMETERS_4 = 29,
  SI5351_MULTISYNTH_NA_PARAMETERS_5 = 30,
  SI5351_MULTISYNTH_NA_PARAMETERS_6 = 31,
  SI5351_MULTISYNTH_NA_PARAMETERS_7 = 32,
  SI5351_MULTISYNTH_NA_PARAMETERS_8 = 33,
  SI5351_MULTISYNTH_NB_PARAMETERS_1 = 34,
  SI5351_MULTISYNTH_NB_PARAMETERS_2 = 35,
  SI5351_MULTISYNTH_NB_PARAMETERS_3 = 36,
  SI5351_MULTISYNTH_NB_PARAMETERS_4 = 37,
  SI5351_MULTISYNTH_NB_PARAMETERS_5 = 38,
  SI5351_MULTISYNTH_NB_PARAMETERS_6 = 39,
  SI5351_MULTISYNTH_NB_PARAMETERS_7 = 40,
  SI5351_MULTISYNTH_NB_PARAMETERS_8 = 41,
  SI5351_MULTISYNTH0_PARAMETERS_1 = 42,
  SI5351_MULTISYNTH0_PARAMETERS_2 = 43,
  SI5351_MULTISYNTH0_PARAMETERS_3 = 44,
  SI5351_MULTISYNTH0_PARAMETERS_4 = 45,
  SI5351_MULTISYNTH0_PARAMETERS_5 = 46,
  SI5351_MULTISYNTH0_PARAMETERS_6 = 47,
  SI5351_MULTISYNTH0_PARAMETERS_7 = 48,
  SI5351_MULTISYNTH0_PARAMETERS_8 = 49,
  SI5351_MULTISYNTH1_PARAMETERS_1 = 50,
  SI5351_MULTISYNTH1_PARAMETERS_2 = 51,
  SI5351_MULTISYNTH1_PARAMETERS_3 = 52,
  SI5351_MULTISYNTH1_PARAMETERS_4 = 53,
  SI5351_MULTISYNTH1_PARAMETERS_5 = 54,
  SI5351_MULTISYNTH1_PARAMETERS_6 = 55,
  SI5351_MULTISYNTH1_PARAMETERS_7 = 56,
  SI5351_MULTISYNTH1_PARAMETERS_8 = 57,
  SI5351_MULTISYNTH2_PARAMETERS_1 = 58,
  SI5351_MULTISYNTH2_PARAMETERS_2 = 59,
  SI5351_MULTISYNTH2_PARAMETERS_3 = 60,
  SI5351_MULTISYNTH2_PARAMETERS_4 = 61,
  SI5351_MULTISYNTH2_PARAMETERS_5 = 62,
  SI5351_MULTISYNTH2_PARAMETERS_6 = 63,
  SI5351_MULTISYNTH2_PARAMETERS_7 = 64,
  SI5351_MULTISYNTH2_PARAMETERS_8 = 65,
  SI5351_MULTISYNTH3_PARAMETERS_1 = 66,
  SI5351_MULTISYNTH3_PARAMETERS_2 = 67,
  SI5351_MULTISYNTH3_PARAMETERS_3 = 68,
  SI5351_MULTISYNTH3_PARAMETERS_4 = 69,
  SI5351_MULTISYNTH3_PARAMETERS_5 = 70,
  SI5351_MULTISYNTH3_PARAMETERS_6 = 71,
  SI5351_MULTISYNTH3_PARAMETERS_7 = 72,
  SI5351_MULTISYNTH3_PARAMETERS_8 = 73,
  SI5351_MULTISYNTH4_PARAMETERS_1 = 74,
  SI5351_MULTISYNTH4_PARAMETERS_2 = 75,
  SI5351_MULTISYNTH4_PARAMETERS_3 = 76,
  SI5351_MULTISYNTH4_PARAMETERS_4 = 77,
  SI5351_MULTISYNTH4_PARAMETERS_5 = 78,
  SI5351_MULTISYNTH4_PARAMETERS_6 = 79,
  SI5351_MULTISYNTH4_PARAMETERS_7 = 80,
  SI5351_MULTISYNTH4_PARAMETERS_8 = 81,
  SI5351_MULTISYNTH5_PARAMETERS_1 = 82,
  SI5351_MULTISYNTH5_PARAMETERS_2 = 83,
  SI5351_MULTISYNTH5_PARAMETERS_3 = 84,
  SI5351_MULTISYNTH5_PARAMETERS_4 = 85,
  SI5351_MULTISYNTH5_PARAMETERS_5 = 86,
  SI5351_MULTISYNTH5_PARAMETERS_6 = 87,
  SI5351_MULTISYNTH5_PARAMETERS_7 = 88,
  SI5351_MULTISYNTH5_PARAMETERS_8 = 89,
  SI5351_MULTISYNTH6_PARAMETERS = 90,
  SI5351_MULTISYNTH7_PARAMETERS = 91,
  SI5351_CLOCK_6_7_OUTPUT_DIVIDER = 92,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_1 = 149,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_2 = 150,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_3 = 151,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_4 = 152,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_5 = 153,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_6 = 154,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_7 = 155,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_8 = 156,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_9 = 157,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_10 = 158,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_11 = 159,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_12 = 160,
  SI5351_SPREAD_SPECTRUM_PARAMETERS_13 = 161,
  SI5351_VCXO_PARAMETER = 162,
  SI5351_CLK0_INITIAL_PHASE_OFFSET = 165,
  SI5351_CLK1_INITIAL_PHASE_OFFSET = 166,
  SI5351_CLK2_INITIAL_PHASE_OFFSET = 167,
  SI5351_CLK3_INITIAL_PHASE_OFFSET = 168,
  SI5351_CLK4_INITIAL_PHASE_OFFSET = 169,
  SI5351_CLK5_INITIAL_PHASE_OFFSET = 170,
  SI5351_PLL_RESET = 177,
  SI5351_CRYSTAL_INTERNAL_LOAD_CAPACITANCE	= 183,
  SI5351_FANOUT_ENABLE = 187
};

/* Config typedef */
typedef struct SI5351
{
	I2C_HandleTypeDef interface;
	uint32_t CLK0_Control;
	uint32_t CLK1_Control;
	uint32_t CLK2_Control;
	uint32_t CLK0_Frequency;
	uint32_t CLK1_Frequency;
	uint32_t CLK2_Frequency;
}SI5351_t;

/* Register descriptions define */
/* Register 0. Device Status */
//System Initialization Status
#define SYS_INIT 0x80
//PLLB Loss Of Lock Status
#define LOL_B 0x40
//PLLA Loss Of Lock Status
#define LOL_A 0x20
//CLKIN Loss Of Signal(Si5351C)
#define LOS_CLKIN 0x10
//Crystal Loss Of Signal
#define LOS_XTAL 0x08
//Revision number of the device
#define REVID 0x03

/* Register 1. Interrupt Status Sticky */
//System Calibration Status Sticky Bit
#define SYS_INIT_STKY 0x80
//PLLB Loss Of Lock Status Sticky Bit
#define LOL_B_STKY 0x40
//PLLA Loss Of Lock Status Sticky Bit
#define LOL_A_STKY 0x20
//CLKIN Loss Of Signal Sticky Bit
#define LOS_CLKIN_STKY 0x10
//Crystal Loss Of Signal Sticky Bit
#define LOS_XTAL_STKY 0x08

/* Register 2. Interrupt Status Mask */
//System Initialization Status Mask
#define SYS_INIT_MASK 0x80
//PLLB Loss Of Lock Status Mask
#define LOL_B_MASK 0x40
//PLLA Loss Of Lock Status Mask
#define LOL_A_MASK 0x20
//CLKIN Loss Of Signal Mask(Si5351C)
#define LOS_CLKIN_MASK 0x10
//Crystal Loss Of Signal Mask
#define LOS_XTAL_MASK 0x08

/* Register 3. Output Enable Control */
//Output Disable for CLKx
#define CLK7_OEB 0x80
#define CLK6_OEB 0x40
#define CLK5_OEB 0x20
#define CLK4_OEB 0x10
#define CLK3_OEB 0x08
#define CLK2_OEB 0x04
#define CLK1_OEB 0x02
#define CLK0_OEB 0x01

/* Register 9. OEB Pin Enable Control Mask */
//OEB pin enable control of CLKx
#define OEB_CLK7 0x80
#define OEB_CLK6 0x40
#define OEB_CLK5 0x20
#define OEB_CLK4 0x10
#define OEB_CLK3 0x08
#define OEB_CLK2 0x04
#define OEB_CLK1 0x02
#define OEB_CLK0 0x01

/* Register 15. PLL Input Source */
//CLKIN Input Divider
#define CLKIN_DIV_1 0x00
#define CLKIN_DIV_2 0x40
#define CLKIN_DIV_4 0x80
#define CLKIN_DIV_8 0xC0
//Input Source Select for PLLB
#define PLLB_SRC 0x08
//Input Source Select for PLLA
#define PLLA_SRC 0x04

/* Register 16. CLK0 Control */
/* Register 17. CLK1 Control */
/* Register 18. CLK2 Control */
/* Register 19. CLK3 Control */
/* Register 20. CLK4 Control */
/* Register 21. CLK5 Control */
/* Register 22. CLK6 Control */
/* Register 23. CLK7 Control */
//Clock x Power Down
#define CLK_PDN 0x80
//MultiSynth x Integer Mode
#define MS_INT 0x40
//MultiSynth South Select for CLKx
#define MS_SRC 0x20
//Output Clock x Invert
#define CLK_INV 0x10
//Output Clock x Input Source
#define CLK_SRC_XTAL 0x00
#define CLK_SRC_CLKIN 0x04
#define CLK_SRC_MultiSynth_0 0x08
#define CLK_SRC_MultiSynth_1 0x0C
//CLKx Output Rise and Fall Time / Drive Strength Control
#define CLK_IDRV_2mA 0x00
#define CLK_IDRV_4mA 0x01
#define CLK_IDRV_6mA 0x02
#define CLK_IDRV_8mA 0x03
//FBx_INT
#define FB_MULTISYNTH_INTEGER 0x40

/* Register 24. CLK3-0 Disable State */
/* Register 25. CLK7-4 Disable State */
//Clock x Disable State
#define CLK3_DIS_STATE_LOW 0x00
#define CLK3_DIS_STATE_HIGH 0x40
#define CLK3_DIS_STATE_HIGH_IMPENDANCE 0x80
#define CLK3_DIS_STATE_NEVER_DISABLED 0xC0
#define CLK2_DIS_STATE_LOW 0x00
#define CLK2_DIS_STATE_HIGH 0x10
#define CLK2_DIS_STATE_HIGH_IMPENDANCE 0x20
#define CLK2_DIS_STATE_NEVER_DISABLED 0x30
#define CLK1_DIS_STATE_LOW 0x00
#define CLK1_DIS_STATE_HIGH 0x04
#define CLK1_DIS_STATE_HIGH_IMPENDANCE 0x08
#define CLK1_DIS_STATE_NEVER_DISABLED 0x0C
#define CLK0_DIS_STATE_LOW 0x00
#define CLK0_DIS_STATE_HIGH 0x01
#define CLK0_DIS_STATE_HIGH_IMPENDANCE 0x02
#define CLK0_DIS_STATE_NEVER_DISABLED 0x03
#define CLK7_DIS_STATE_LOW 0x00
#define CLK7_DIS_STATE_HIGH 0x40
#define CLK7_DIS_STATE_HIGH_IMPENDANCE 0x80
#define CLK7_DIS_STATE_NEVER_DISABLED 0xC0
#define CLK6_DIS_STATE_LOW 0x00
#define CLK6_DIS_STATE_HIGH 0x10
#define CLK6_DIS_STATE_HIGH_IMPENDANCE 0x20
#define CLK6_DIS_STATE_NEVER_DISABLED 0x30
#define CLK5_DIS_STATE_LOW 0x00
#define CLK5_DIS_STATE_HIGH 0x04
#define CLK5_DIS_STATE_HIGH_IMPENDANCE 0x08
#define CLK5_DIS_STATE_NEVER_DISABLED 0x0C
#define CLK4_DIS_STATE_LOW 0x00
#define CLK4_DIS_STATE_HIGH 0x01
#define CLK4_DIS_STATE_HIGH_IMPENDANCE 0x02
#define CLK4_DIS_STATE_NEVER_DISABLED 0x03

/* Register 42. - Register 49. Multisynth0 Parameters */
/* Register 50. - Register 57. Multisynth1 Parameters */
/* Register 58. - Register 65. Multisynth2 Parameters */
/* Register 66. - Register 73. Multisynth3 Parameters */
/* Register 74. - Register 81. Multisynth4 Parameters */
/* Register 82. - Register 89. Multisynth5 Parameters */
//Rx(except R6) Output Divider
#define R_DIV_1 0x00
#define R_DIV_2 0x10
#define R_DIV_4 0x20
#define R_DIV_8 0x30
#define R_DIV_16 0x40
#define R_DIV_32 0x50
#define R_DIV_64 0x60
#define R_DIV_128 0x70
//MS Divide by 4 Enable
#define MS_DIVBY4 0x0C

/* Register 92. Clock 6 and 7 Output Divider */
//R6 Output Divider
#define R6_DIV_1 0x00
#define R6_DIV_2 0x10
#define R6_DIV_4 0x20
#define R6_DIV_8 0x30
#define R6_DIV_16 0x40
#define R6_DIV_32 0x50
#define R6_DIV_64 0x60
#define R6_DIV_128 0x70

/* Register 149 - Register 161. Spread Spectrum Parameters */
//Spread Spectrum Enable
#define SSC_EN 0x80

/* Register 177. PLL Reset */
//PLLB Reset
#define PLLB_RST 0x80
#define PLLA_RST 0x20

/* Register 183. Crystal Internal Load Capacitance */
//Crystal Load Capacitance Selection
#define XTAL_CL_6pF 0x40
#define XTAL_CL_8pF 0x80
#define XTAL_CL_10pF 0xC0

/* Register 187. Fanout Enable */
//Enable fanout of CLKIN to clock output multiplexers
#define CLKIN_FANOUT_EN 0x80
//Enable fanout of XO to clock output multiplexers
#define XO_FANOUT_EN 0x40
//Enable fanout of Multisynth0 and Multisynth4 to all output multiplexers
#define MS_FANOUT_EN 0x10

void si5351_Init(SI5351_t *si5351);
void si5351_DeInit(SI5351_t *si5351);
void si5351_Config(SI5351_t *si5351);
HAL_StatusTypeDef si5351_Update(SI5351_t *si5351);
HAL_StatusTypeDef si5351_Write_Register(I2C_HandleTypeDef *hi2c, uint16_t Address, uint8_t Regsiter, uint8_t pData);

#endif
