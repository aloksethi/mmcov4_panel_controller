/*
 * board.c
 *
 *  Created on: Jan 25, 2021
 *      Author: asethi
 */

#include "main.h"

I2C_HandleTypeDef g_hi2c1;
SPI_HandleTypeDef g_hspi1;

SemaphoreHandle_t g_mutex_i2c_op;  //mutex for i2c access
SemaphoreHandle_t g_mutex_spi_op;  //mutex for spi access
/*
 * don't have i2c access functions here because of how the sensor operates.
 * sensor first needs to send data on i2c and then it can read, which means it has to hold lock after the send
 * transsaction and can release it after reading i2c.
 * it was easier to do that in the sensor handler than here
 */

static void MX_I2C1_Init(void) {

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	g_hi2c1.Instance = I2C1;
	g_hi2c1.Init.ClockSpeed = 100000;
	g_hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	g_hi2c1.Init.OwnAddress1 = 0;
	g_hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	g_hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	g_hi2c1.Init.OwnAddress2 = 0;
	g_hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	g_hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&g_hi2c1) != HAL_OK) {
		Error_Handler();
	}

	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&g_hi2c1, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		Error_Handler();
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&g_hi2c1, 0) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	g_hspi1.Instance = SPI1;
	g_hspi1.Init.Mode = SPI_MODE_MASTER;
	g_hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	g_hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	g_hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	g_hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	g_hspi1.Init.NSS = SPI_NSS_SOFT;
	g_hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
	g_hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	g_hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	g_hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	g_hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&g_hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOF,
	SYNTH_LATCH_Pin | REG1V_B1_R1_Pin | REG1V_B0_R1_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA,
			SYNTH2_LATCH_Pin | VDD2_PA_R2_EN_Pin | VDD2_PA_R2_ENA9_Pin
					| REG3V3_SYNTH_EN_Pin | REG3V3_EN_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
			LED_GREEN_Pin | REG1V_B1_R4_Pin | SHREG_LATCH_Pin | SHREG_CLK_Pin
					| LED_RED_Pin | SHREG_DATA_Pin | REG1V_B0_R4_Pin
					| LED_BLUE_Pin | REG1V_B1_R2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC,
			REG1V_B0_R3_Pin | REG1V_B1_R3_Pin | IC_DIN_Pin | REG1V_B0_R2_Pin
					| VDD2_PA_R1_EN_Pin | IC_CLK_1_2_8_Pin | VDD2_PA_R3_EN_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(IC_CLK_9_2_16_GPIO_Port, IC_CLK_9_2_16_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin : USER_Btn_Pin */
	GPIO_InitStruct.Pin = USER_Btn_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : SYNTH_LATCH_Pin REG1V_B1_R1_Pin REG1V_B0_R1_Pin */
	GPIO_InitStruct.Pin = SYNTH_LATCH_Pin | REG1V_B1_R1_Pin | REG1V_B0_R1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	/*Configure GPIO pins : SYNTH2_LATCH_Pin VDD2_PA_R2_EN_Pin VDD2_PA_R2_ENA9_Pin REG3V3_SYNTH_EN_Pin
	 REG3V3_EN_Pin */
	GPIO_InitStruct.Pin = SYNTH2_LATCH_Pin | VDD2_PA_R2_EN_Pin
			| VDD2_PA_R2_ENA9_Pin | REG3V3_SYNTH_EN_Pin | REG3V3_EN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : LED_GREEN_Pin REG1V_B1_R4_Pin SHREG_LATCH_Pin SHREG_CLK_Pin
	 LED_RED_Pin SHREG_DATA_Pin REG1V_B0_R4_Pin LED_BLUE_Pin
	 REG1V_B1_R2_Pin */
	GPIO_InitStruct.Pin = LED_GREEN_Pin | REG1V_B1_R4_Pin | SHREG_LATCH_Pin
			| SHREG_CLK_Pin | LED_RED_Pin | SHREG_DATA_Pin | REG1V_B0_R4_Pin
			| LED_BLUE_Pin | REG1V_B1_R2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  //GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : STLK_RX_Pin STLK_TX_Pin */
	GPIO_InitStruct.Pin = STLK_RX_Pin | STLK_TX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pin : USB_PowerSwitchOn_Pin */
	GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : USB_OverCurrent_Pin */
	GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : REG1V_B0_R3_Pin REG1V_B1_R3_Pin IC_DIN_Pin REG1V_B0_R2_Pin
	 VDD2_PA_R1_EN_Pin IC_CLK_1_2_8_Pin VDD2_PA_R3_EN_Pin */
	GPIO_InitStruct.Pin = REG1V_B0_R3_Pin | REG1V_B1_R3_Pin | IC_DIN_Pin
			| REG1V_B0_R2_Pin | VDD2_PA_R1_EN_Pin | IC_CLK_1_2_8_Pin
			| VDD2_PA_R3_EN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : USB_DM_Pin USB_DP_Pin */
	GPIO_InitStruct.Pin = USB_DM_Pin | USB_DP_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : IC_CLK_9_2_16_Pin */
	GPIO_InitStruct.Pin = IC_CLK_9_2_16_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(IC_CLK_9_2_16_GPIO_Port, &GPIO_InitStruct);
#if 0
	/*Configure GPIO pins : PA5, PA6, PB5 */
	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif
}

pow_plane_t board_icid_to_pow_plane(uint8_t ic_id) {
	pow_plane_t region;
	switch (ic_id) {
	case 1:
	case 2:
	case 5:
	case 6:
		region = R1;
		break;
	case 3:
	case 4:
	case 7:
	case 8:
		region = R2;
		break;
	case 9:
	case 10:
	case 13:
	case 14:
		region = R3;
		break;
	case 11:
	case 12:
	case 15:
	case 16:
		region = R4;
		break;
	default:
		trace_printf("invalid ic id\n");
	}

	return region;
}

void board_synth_write_reg(synth_config_data_t *ptr) {
	GPIO_TypeDef *p_port;
	uint16_t pin;
	uint8_t synth_id, reg;
	uint16_t val;
	HAL_StatusTypeDef ret;
	uint8_t dtx[3];

	synth_id = ptr->synth_id;
	reg = ptr->reg_num;
	val = ptr->data;

	reg = reg & 0x7f; // for writing, the msb bit A7 should be zero
	dtx[0] = reg;
	dtx[1] = (val & 0xff00) >> 8;
	dtx[2] = (val & 0x00ff);
	
	switch (synth_id) {
	case 1:
		p_port = SYNTH_LATCH_GPIO_Port;
		pin = SYNTH_LATCH_Pin;
		break;

	case 2:
		p_port = SYNTH2_LATCH_GPIO_Port;
		pin = SYNTH2_LATCH_Pin;
		break;

	default:
		Error_Handler();
	}

	HAL_GPIO_WritePin(p_port, pin, GPIO_PIN_RESET);

	ret = HAL_SPI_Transmit(&g_hspi1, dtx, sizeof(dtx), HAL_MAX_DELAY);
	if (ret == HAL_ERROR) {
		trace_printf("failed to write SPI");
		board_red_led_on();
	}
	HAL_GPIO_WritePin(p_port, pin, GPIO_PIN_SET);

	trace_printf("dtx[0]: %x dtx[1]:%x dtx[2]:%x\n", dtx[0], dtx[1], dtx[2]);
	return;
}

void board_synth_read_reg(synth_config_data_t *ptr) {
	GPIO_TypeDef *p_port;
	uint16_t pin;
	uint8_t synth_id, reg;
	uint16_t val;
	HAL_StatusTypeDef ret;
	uint8_t dtx[3], drx[3];

	synth_id = ptr->synth_id;
	reg = ptr->reg_num;
	val = ptr->data;

	reg = reg | 0x80; // for reading, the msb bit A7 should be one
	dtx[0] = reg;

	switch (synth_id) {
	case 1:
		p_port = SYNTH_LATCH_GPIO_Port;
		pin = SYNTH_LATCH_Pin;
		break;

	case 2:
		p_port = SYNTH2_LATCH_GPIO_Port;
		pin = SYNTH2_LATCH_Pin;
		break;

	default:
		Error_Handler();
	}

	HAL_GPIO_WritePin(p_port, pin, GPIO_PIN_RESET);

	ret = HAL_SPI_TransmitReceive(&g_hspi1, dtx, drx, sizeof(dtx),
			HAL_MAX_DELAY);

	if (ret == HAL_ERROR) {
		trace_printf("failed to read SPI");
		board_red_led_on();
	}
	HAL_GPIO_WritePin(p_port, pin, GPIO_PIN_SET);

//	trace_printf("dtx[0]: %x dtx[1]:%x dtx[2]:%x", dtx[0], dtx[1], dtx[2]);
	trace_printf("drx[0]: %x drx[1]:%x drx[2]:%x\n", drx[0], drx[1], drx[2]);
	return;
}

void board_green_led_off(void) {
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
	return;
}
void board_blue_led_off(void) {
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
	return;
}

void board_red_led_on(void) {
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
	return;
}
void board_red_led_toggle(void) {
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	return;
}
void board_green_led_toggle(void) {
	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	return;
}
void board_blue_led_toggle(void) {
	HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
	return;
}
void board_synth_power_on(void) {
	HAL_GPIO_WritePin(REG3V3_SYNTH_EN_GPIO_Port, REG3V3_SYNTH_EN_Pin,
			GPIO_PIN_SET);

	return;
}
void board_synth_power_off(void) {
	HAL_GPIO_WritePin(REG3V3_SYNTH_EN_GPIO_Port, REG3V3_SYNTH_EN_Pin,
			GPIO_PIN_RESET);

	return;
}
void board_3v3_power_on(void) {
	HAL_GPIO_WritePin(REG3V3_EN_GPIO_Port, REG3V3_EN_Pin, GPIO_PIN_SET);

	return;
}
void board_3v3_power_off(void) {
	HAL_GPIO_WritePin(REG3V3_EN_GPIO_Port, REG3V3_EN_Pin, GPIO_PIN_RESET);

	return;
}

void board_2v_pa_power_off(uint8_t ic_id) {
	pow_plane_t plane;
	GPIO_TypeDef *p_port;
	uint16_t pin;

	plane = board_icid_to_pow_plane(ic_id);

	switch (plane) {
	case R1:
		p_port = VDD2_PA_R1_EN_GPIO_Port;
		pin = VDD2_PA_R1_EN_Pin;
		break;
	case R2:
		p_port = VDD2_PA_R2_EN_GPIO_Port;
		pin = VDD2_PA_R2_EN_Pin;
		break;
	case R3:
		p_port = VDD2_PA_R3_EN_GPIO_Port;
		pin = VDD2_PA_R3_EN_Pin;
		break;
	case R4:
		p_port = VDD2_PA_R4_EN_GPIO_Port;
		pin = VDD2_PA_R4_EN_Pin;
		break;
	}
	HAL_GPIO_WritePin(p_port, pin, GPIO_PIN_SET);

	return;
}

void board_2v_pa_power_on(uint8_t ic_id) {
	pow_plane_t plane;
	GPIO_TypeDef *p_port;
	uint16_t pin;

	plane = board_icid_to_pow_plane(ic_id);

	switch (plane) {
	case R1:
		p_port = VDD2_PA_R1_EN_GPIO_Port;
		pin = VDD2_PA_R1_EN_Pin;
		break;
	case R2:
		p_port = VDD2_PA_R2_EN_GPIO_Port;
		pin = VDD2_PA_R2_EN_Pin;
		break;
	case R3:
		p_port = VDD2_PA_R3_EN_GPIO_Port;
		pin = VDD2_PA_R3_EN_Pin;
		break;
	case R4:
		p_port = VDD2_PA_R4_EN_GPIO_Port;
		pin = VDD2_PA_R4_EN_Pin;
		break;
	}
	HAL_GPIO_WritePin(p_port, pin, GPIO_PIN_RESET);

	return;
}

void board_1v_control(uint8_t ic_id, val_1v_t val) {
	pow_plane_t plane;
	GPIO_TypeDef *p_port_b0, *p_port_b1;
	uint16_t pin_b0, pin_b1;
	GPIO_InitTypeDef gpio_inits;

	plane = board_icid_to_pow_plane(ic_id);

	switch (plane) {
	case R1:
		p_port_b0 = REG1V_B0_R1_GPIO_Port;
		pin_b0 = REG1V_B0_R1_Pin;
		p_port_b1 = REG1V_B1_R1_GPIO_Port;
		pin_b1 = REG1V_B1_R1_Pin;
		break;
	case R2:
		p_port_b0 = REG1V_B0_R2_GPIO_Port;
		pin_b0 = REG1V_B0_R2_Pin;
		p_port_b1 = REG1V_B1_R2_GPIO_Port;
		pin_b1 = REG1V_B1_R2_Pin;

		break;
	case R3:
		p_port_b0 = REG1V_B0_R3_GPIO_Port;
		pin_b0 = REG1V_B0_R3_Pin;
		p_port_b1 = REG1V_B1_R3_GPIO_Port;
		pin_b1 = REG1V_B1_R3_Pin;
		break;
	case R4:
		p_port_b0 = REG1V_B0_R4_GPIO_Port;
		pin_b0 = REG1V_B0_R4_Pin;
		p_port_b1 = REG1V_B1_R4_GPIO_Port;
		pin_b1 = REG1V_B1_R4_Pin;
		break;
	}
// need 0,1,n Z states on the gpio pin

	gpio_inits.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_inits.Pull = GPIO_NOPULL;
	//gpio_inits.Alternate = ; no need to fill it

	gpio_inits.Mode = GPIO_MODE_INPUT;
	switch (val) {

	case V_0V00:
		shreg_set_1V0_en(0, plane);
		break;
	case V_0V80:
		gpio_inits.Pin = pin_b0;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b0, &gpio_inits);

		gpio_inits.Pin = pin_b1;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b1, &gpio_inits);

		HAL_GPIO_WritePin(p_port_b0, pin_b0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(p_port_b1, pin_b1, GPIO_PIN_RESET);

		shreg_set_1V0_en(1, plane);
		break;

	case V_0V85:
		gpio_inits.Pin = pin_b0;
		gpio_inits.Mode = GPIO_MODE_INPUT;
		HAL_GPIO_Init(p_port_b0, &gpio_inits);

		gpio_inits.Pin = pin_b1;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b1, &gpio_inits);

		HAL_GPIO_WritePin(p_port_b1, pin_b1, GPIO_PIN_RESET);

		shreg_set_1V0_en(1, plane);
		break;

	case V_0V90:
		gpio_inits.Pin = pin_b0;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b0, &gpio_inits);

		gpio_inits.Pin = pin_b1;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b1, &gpio_inits);

		HAL_GPIO_WritePin(p_port_b0, pin_b0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(p_port_b1, pin_b1, GPIO_PIN_RESET);

		shreg_set_1V0_en(1, plane);
		break;

	case V_0V95:
		gpio_inits.Pin = pin_b0;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b0, &gpio_inits);

		gpio_inits.Pin = pin_b1;
		gpio_inits.Mode = GPIO_MODE_INPUT;
		HAL_GPIO_Init(p_port_b1, &gpio_inits);

		HAL_GPIO_WritePin(p_port_b0, pin_b0, GPIO_PIN_RESET);

		shreg_set_1V0_en(1, plane);
		break;

	case V_1V00:
		gpio_inits.Pin = pin_b0;
		gpio_inits.Mode = GPIO_MODE_INPUT;
		HAL_GPIO_Init(p_port_b0, &gpio_inits);

		gpio_inits.Pin = pin_b1;
		gpio_inits.Mode = GPIO_MODE_INPUT;
		HAL_GPIO_Init(p_port_b1, &gpio_inits);

		shreg_set_1V0_en(1, plane);
		break;

	case V_1V05:
		gpio_inits.Pin = pin_b0;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b0, &gpio_inits);

		gpio_inits.Pin = pin_b1;
		gpio_inits.Mode = GPIO_MODE_INPUT;
		HAL_GPIO_Init(p_port_b1, &gpio_inits);

		HAL_GPIO_WritePin(p_port_b0, pin_b0, GPIO_PIN_SET);

		shreg_set_1V0_en(1, plane);
		break;

	case V_1V10:
		gpio_inits.Pin = pin_b0;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b0, &gpio_inits);

		gpio_inits.Pin = pin_b1;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b1, &gpio_inits);

		HAL_GPIO_WritePin(p_port_b0, pin_b0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(p_port_b1, pin_b1, GPIO_PIN_SET);

		shreg_set_1V0_en(1, plane);
		break;

	case V_1V15:
		gpio_inits.Pin = pin_b0;
		gpio_inits.Mode = GPIO_MODE_INPUT;
		HAL_GPIO_Init(p_port_b0, &gpio_inits);

		gpio_inits.Pin = pin_b1;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b1, &gpio_inits);

		HAL_GPIO_WritePin(p_port_b1, pin_b1, GPIO_PIN_SET);

		shreg_set_1V0_en(1, plane);
		break;

	case V_1V20:
		gpio_inits.Pin = pin_b0;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b0, &gpio_inits);

		gpio_inits.Pin = pin_b1;
		gpio_inits.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(p_port_b1, &gpio_inits);

		HAL_GPIO_WritePin(p_port_b0, pin_b0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(p_port_b1, pin_b1, GPIO_PIN_SET);

		shreg_set_1V0_en(1, plane);
		break;

	}
}

#if 0
void board_set_lo_switch(uint8_t val)
{
	switch (val)
	{
	case 0:
	{
		HAL_GPIO_WritePin(LO_SW1_Port, LO_SW1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LO_SW2_Port, LO_SW2_Pin, GPIO_PIN_RESET);
		break;
	}
	case 1:
	{
		HAL_GPIO_WritePin(LO_SW1_Port, LO_SW1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LO_SW2_Port, LO_SW2_Pin, GPIO_PIN_RESET);
		break;
	}
	case 2:
	{
		HAL_GPIO_WritePin(LO_SW1_Port, LO_SW1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LO_SW2_Port, LO_SW2_Pin, GPIO_PIN_SET);
		break;
	}
	}
	return;
}

#endif
void board_init(void) {
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_SPI1_Init();

	init_shreg();

	for (uint8_t ic_id=1; ic_id <= G_MAX_ICS_PER_UC; ic_id++)
	{
		board_1v_control(ic_id, V_0V00);
	}


	g_mutex_i2c_op = xSemaphoreCreateMutex();
	if (NULL == g_mutex_i2c_op) {
		trace_printf("failed to create global mutex for i2c\n");
		Error_Handler();
	}
	g_mutex_spi_op = xSemaphoreCreateMutex();
	if (NULL == g_mutex_i2c_op) {
		trace_printf("failed to create global mutex for spi\n");
		Error_Handler();
	}
	return;
}

