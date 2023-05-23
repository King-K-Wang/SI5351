/**
  ******************************************************************************
  * @file    si5351.c
  * @author  K.Wang
  * @brief   Si5351 clock generator driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Si5351 clock gengerator.
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *
  ******************************************************************************
  */
	
#include "si5351.h"


void si5351_Init(SI5351_t *si5351)
{
	//Disable outputs
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_OUTPUT_ENABLE_CONTROL, 0xff);
	//Powerdown all output drivers
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_CLK0_CONTROL, CLK_PDN);
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_CLK1_CONTROL, CLK_PDN);
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_CLK2_CONTROL, CLK_PDN);
	//Set interrupt masks
	//default
	
	//Set PLL source
	//default(XTAL)

	//Control CLKx
	//customize!
	
	//Disable state
	
	//Output no-divede
	
	//PLL reset
	
	//Init, skip enable output
	
	return;
}

void si5351_DeInit(SI5351_t *si5351)
{
	//Disable outputs
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_OUTPUT_ENABLE_CONTROL, 0xff);
	//Powerdown all output drivers
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_CLK0_CONTROL, CLK_PDN);
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_CLK1_CONTROL, CLK_PDN);
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_CLK2_CONTROL, CLK_PDN);
	
	return;
}

void si5351_Config(SI5351_t *si5351)
{
	uint32_t a, b, c;
	a = 900000000/SI5351_XTAL_FREQ;
	c = 0xfffff;
	b = (900000000%SI5351_XTAL_FREQ)*c/SI5351_XTAL_FREQ;
	
	//Set PLLA
	uint32_t MSNA_P1, MSNA_P2, MSNA_P3;
	MSNA_P1 = 128*a + floor(128*b/c) - 512;
	MSNA_P2 = 128*b - c*floor(128*b/c);
	MSNA_P3 = c;
	
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH_NA_PARAMETERS_1, (uint8_t)(MSNA_P3>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH_NA_PARAMETERS_2, (uint8_t)(MSNA_P3));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH_NA_PARAMETERS_3, (uint8_t)(0x03 & (MSNA_P1>>16)));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH_NA_PARAMETERS_4, (uint8_t)(MSNA_P1>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH_NA_PARAMETERS_5, (uint8_t)(MSNA_P1));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH_NA_PARAMETERS_6, (uint8_t)(((MSNA_P3>>12) & 0xf0) | ((MSNA_P2>>16) & 0x0f)));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH_NA_PARAMETERS_7, (uint8_t)(MSNA_P2>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH_NA_PARAMETERS_8, (uint8_t)(MSNA_P2));
	
	//Set frequency
	a = 128*(900000000/si5351->CLK0_Frequency) - 512;
	c = 0xfffff;
	b = (900000000%a)*c/si5351->CLK0_Frequency;
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH0_PARAMETERS_1, (uint8_t)(c>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH0_PARAMETERS_2, (uint8_t)(c));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH0_PARAMETERS_3, (uint8_t)(0x03 & (a>>16)));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH0_PARAMETERS_4, (uint8_t)(a>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH0_PARAMETERS_5, (uint8_t)(a>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH0_PARAMETERS_6, (uint8_t)(((c>>12) & 0xf0) | ((b>>16) & 0x0f)));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH0_PARAMETERS_7, (uint8_t)(b>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH0_PARAMETERS_8, (uint8_t)(b));
	
	a = 128*(900000000/si5351->CLK1_Frequency) - 512;
	c = 0xfffff;
	b = (900000000%a)*c/si5351->CLK1_Frequency;
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH1_PARAMETERS_1, (uint8_t)(c>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH1_PARAMETERS_2, (uint8_t)(c));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH1_PARAMETERS_3, (uint8_t)(0x03 & (a>>16)));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH1_PARAMETERS_4, (uint8_t)(a>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH1_PARAMETERS_5, (uint8_t)(a>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH1_PARAMETERS_6, (uint8_t)(((c>>12) & 0xf0) | ((b>>16) & 0x0f)));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH1_PARAMETERS_7, (uint8_t)(b>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH1_PARAMETERS_8, (uint8_t)(b));
	
	a = 128*(900000000/si5351->CLK2_Frequency) - 512;
	c = 0xfffff;
	b = (900000000%a)*c/si5351->CLK2_Frequency;
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH2_PARAMETERS_1, (uint8_t)(c>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH2_PARAMETERS_2, (uint8_t)(c));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH2_PARAMETERS_3, (uint8_t)(0x03 & (a>>16)));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH2_PARAMETERS_4, (uint8_t)(a>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH2_PARAMETERS_5, (uint8_t)(a>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH2_PARAMETERS_6, (uint8_t)(((c>>12) & 0xf0) | ((b>>16) & 0x0f)));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH2_PARAMETERS_7, (uint8_t)(b>>8));
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_MULTISYNTH2_PARAMETERS_8, (uint8_t)(b));
	
	//Config output
	si5351->CLK0_Control = (MS_INT | CLK_SRC_MultiSynth_1 | CLK_IDRV_8mA);
	si5351->CLK1_Control = (MS_INT | CLK_SRC_MultiSynth_1 | CLK_IDRV_8mA);
	si5351->CLK2_Control = (MS_INT | CLK_SRC_MultiSynth_1 | CLK_IDRV_8mA);
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_CLK0_CONTROL, si5351->CLK0_Control);
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_CLK1_CONTROL, si5351->CLK1_Control);
	si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_CLK2_CONTROL, si5351->CLK2_Control);
	
	return;
}

HAL_StatusTypeDef si5351_Update(SI5351_t *si5351)
{
	HAL_StatusTypeDef ret = HAL_OK;
	//Reset PLL
	ret = si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_PLL_RESET, 0xA0);
	if(ret != HAL_OK)
	{
		return ret;
	}
	//Enable output
	ret = si5351_Write_Register(&si5351->interface, SI5351_ADDRESS, SI5351_OUTPUT_ENABLE_CONTROL, 0x00);
	if(ret != HAL_OK)
	{
		return ret;
	}
	
	return ret;
}

HAL_StatusTypeDef si5351_Write_Register(I2C_HandleTypeDef *hi2c, uint16_t Address, uint8_t Regsiter, uint8_t pData)
{
	uint8_t data[2] = {Regsiter, pData};
	HAL_StatusTypeDef ret = HAL_OK;
	
	ret = HAL_I2C_Master_Transmit(hi2c, ((Address << 1) | 0), data, 2, HAL_MAX_DELAY);
	
	return ret;
}
