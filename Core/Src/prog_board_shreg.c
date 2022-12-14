/*
 * prog_board_shreg.c
 *
 *  Created on: 30.8.2022
 *      Author: asethi
 *
 *      using a SPI perpheral might have been easier than bit banging that i am using
 */

#include "main.h"
#include "semphr.h"
#include <string.h>

static uint8_t g_shreg_data[BOARD_SHREG_LEN];

static void clkout_data(void) {
	GPIO_TypeDef *p_dport, *p_clkport, *p_lport;
	uint16_t dpin, clkpin, lpin;

	p_dport = SHREG_DATA_GPIO_Port;
	p_clkport = SHREG_CLK_GPIO_Port;
	p_lport = SHREG_LATCH_GPIO_Port;

	dpin = SHREG_DATA_Pin;
	clkpin = SHREG_CLK_Pin;
	lpin = SHREG_LATCH_Pin;

	for (int8_t i = BOARD_SHREG_LEN - 1; i >= 0; i--) {
		uint8_t data;

		data = g_shreg_data[i] & 0x1;

		if (data)
			HAL_GPIO_WritePin(p_dport, dpin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(p_dport, dpin, GPIO_PIN_RESET);

		for (int i = 0; i < BOARD_CLK_DELAY / 2; i++)
			;
		HAL_GPIO_WritePin(p_clkport, clkpin, GPIO_PIN_SET);
		for (int i = 0; i < BOARD_CLK_DELAY; i++)
			;
		HAL_GPIO_WritePin(p_clkport, clkpin, GPIO_PIN_RESET);
		for (int i = 0; i < BOARD_CLK_DELAY / 2; i++)
			;
	}
	// send the LE clk
	for (int i = 0; i < BOARD_CLK_DELAY / 2; i++)
		;
	HAL_GPIO_WritePin(p_lport, lpin, GPIO_PIN_SET);
	for (int i = 0; i < BOARD_CLK_DELAY; i++)
		;
	HAL_GPIO_WritePin(p_lport, lpin, GPIO_PIN_RESET);
	for (int i = 0; i < BOARD_CLK_DELAY / 2; i++)
		;

	return;
}
static void fill_def_values(void) {
	for (uint8_t i = 0; i < BOARD_SHREG_LEN; i++)
		g_shreg_data[i] = 0;

	// set active low controls to 1
	g_shreg_data[VDD_1V_R1_EN_IDX] = 1;
	g_shreg_data[VDD_1V_R2_EN_IDX] = 1;
	g_shreg_data[VDD_1V_R3_EN_IDX] = 1;
	g_shreg_data[VDD_1V_R4_EN_IDX] = 1;

	g_shreg_data[REFCLK_SYNTH1_EN_IDX] = 1;
	g_shreg_data[REFCLK_SYNTH2_EN_IDX] = 1;

	return;
}

void shreg_set_1V0_en(uint8_t en, pow_plane_t plane) {
	uint8_t idx;
	switch (plane) {
	case R1:
		idx = VDD_1V_R1_EN_IDX;
		break;
	case R2:
		idx = VDD_1V_R2_EN_IDX;
		break;
	case R3:
		idx = VDD_1V_R3_EN_IDX;
		break;
	case R4:
		idx = VDD_1V_R4_EN_IDX;
		break;

	default:
		trace_printf("invalid plane");
		Error_Handler();
		break;
	}

	if (en)
		g_shreg_data[idx] = 0;  // enable is active low
	else
		g_shreg_data[idx] = 1;

	clkout_data();
	return;
}

void shref_set_synth_refclk(uint8_t synth_id, val_gen_t val) {
	uint8_t idx;

	switch (synth_id) {
	case 1:
		idx = REFCLK_SYNTH1_EN_IDX;
		break;
	case 2:
		idx = REFCLK_SYNTH2_EN_IDX;
		break;
	default:
		trace_printf("invalid synth id");
		Error_Handler();
		break;
	}

	if (val == V_ENABLE)
		g_shreg_data[idx] = 0;  // enable is active low
	else
		g_shreg_data[idx] = 1;

	clkout_data();

	return;
}

void shreg_set_1V5_en(uint8_t en) {
	if (en)
		g_shreg_data[VDD_1V5_EN_IDX] = 1;  // enable is active high
	else
		g_shreg_data[VDD_1V5_EN_IDX] = 0;

	clkout_data();
	return;
}

void shreg_set_2V75_en(uint8_t en) {
	if (en)
		g_shreg_data[VDD_2V75_EN_IDX] = 1;  // enable is active high
	else
		g_shreg_data[VDD_2V75_EN_IDX] = 0;

	clkout_data();
	return;
}

void shreg_set_le(uint8_t ic_id) {
	uint8_t idx;
	idx = PIN_LE_IDX(ic_id);

	if (idx >= BOARD_SHREG_LEN) {
		Error_Handler();
	}
	g_shreg_data[idx] = 1;
	clkout_data();
	g_shreg_data[idx] = 0;
	clkout_data();
	return;
}

void shreg_set_iref(uint8_t ic_id, val_gen_t val) {
	uint8_t idx1, idx2;
	idx1 = IREF1_ICn_EN_IDX(ic_id);
	idx2 = IREF2_ICn_EN_IDX(ic_id);

	if (val == V_ENABLE) {
		g_shreg_data[idx1] = 1;
		g_shreg_data[idx2] = 1;
	} else {
		g_shreg_data[idx1] = 0;
		g_shreg_data[idx2] = 0;
	}
	clkout_data();
	return;
}

void shreg_set_bb_sw(uint8_t ic_id, val_gen_t val) {
	uint8_t idx1, idx2;

	switch (ic_id) {
	case 1:
		idx1 = RX_BB_SW_IC1_I_EN_IDX;
		idx2 = RX_BB_SW_IC1_Q_EN_IDX;
		break;
	case 6:
		idx1 = RX_BB_SW_IC6_I_EN_IDX;
		idx2 = RX_BB_SW_IC6_Q_EN_IDX;
		break;
	case 11:
		idx1 = RX_BB_SW_IC11_I_EN_IDX;
		idx2 = RX_BB_SW_IC11_Q_EN_IDX;
		break;
	case 16:
		idx1 = RX_BB_SW_IC16_I_EN_IDX;
		idx2 = RX_BB_SW_IC16_Q_EN_IDX;
		break;
	default:
		trace_printf("invalid ic id");
		Error_Handler();
		break;
	}

	if (val == V_ENABLE) {
		g_shreg_data[idx1] = 1;
		g_shreg_data[idx2] = 1;
	} else {
		g_shreg_data[idx1] = 0;
		g_shreg_data[idx2] = 0;
	}
	clkout_data();
	return;
}

void shreg_set_bb_amp(uint8_t ic_id, val_gen_t val) {
	uint8_t idx1, idx2;

	switch (ic_id) {
	case 1:
		idx1 = BB_AMP_IC1_I_EN_IDX;
		idx2 = BB_AMP_IC1_Q_EN_IDX;
		break;
	case 6:
		idx1 = BB_AMP_IC6_I_EN_IDX;
		idx2 = BB_AMP_IC6_Q_EN_IDX;
		break;
	case 11:
		idx1 = BB_AMP_IC11_I_EN_IDX;
		idx2 = BB_AMP_IC11_Q_EN_IDX;
		break;
	case 16:
		idx1 = BB_AMP_IC16_I_EN_IDX;
		idx2 = BB_AMP_IC16_Q_EN_IDX;
		break;
	default:
		trace_printf("invalid ic id");
		Error_Handler();
		break;
	}

	if (val == V_ENABLE) {
		g_shreg_data[idx1] = 1;
		g_shreg_data[idx2] = 1;
	} else {
		g_shreg_data[idx1] = 0;
		g_shreg_data[idx2] = 0;
	}
	clkout_data();
	return;
}

void init_shreg(void) {
	GPIO_TypeDef *p_dport, *p_clkport, *p_lport;
	uint16_t dpin, clkpin, lpin;

	p_dport = SHREG_DATA_GPIO_Port;
	p_clkport = SHREG_CLK_GPIO_Port;
	p_lport = SHREG_LATCH_GPIO_Port;

	dpin = SHREG_DATA_Pin;
	clkpin = SHREG_CLK_Pin;
	lpin = SHREG_LATCH_Pin;

	HAL_GPIO_WritePin(p_dport, dpin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(p_clkport, clkpin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(p_lport, lpin, GPIO_PIN_RESET);

	fill_def_values();
	clkout_data();
	return;
}
