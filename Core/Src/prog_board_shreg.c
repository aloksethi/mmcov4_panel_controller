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
#define BOARD_SHREG_LEN			(80)

#define IREF1_ICn_EN_IDX(n) 	(2*n-2) /*offset by -1*/
#define IREF2_ICn_EN_IDX(n) 	(2*n-1)
#define BB_AMP_IC6_I_EN_IDX		(32)
#define BB_AMP_IC1_I_EN_IDX 	(33)
#define BB_AMP_IC16_I_EN_IDX	(34)
#define BB_AMP_IC11_I_EN_IDX 	(35)
#define BB_AMP_IC6_Q_EN_IDX		(36)
#define BB_AMP_IC1_Q_EN_IDX 	(37)
#define BB_AMP_IC16_Q_EN_IDX 	(38)
#define BB_AMP_IC11_Q_EN_IDX 	(39)
#define RX_BB_SW_IC1_I_EN_IDX	(40)
#define RX_BB_SW_IC6_I_EN_IDX 	(41)
#define RX_BB_SW_IC11_I_EN_IDX  (42)
#define RX_BB_SW_IC16_I_EN_IDX  (43)
#define RX_BB_SW_IC1_Q_EN_IDX  	(44)
#define RX_BB_SW_IC6_Q_EN_IDX  	(45)
#define RX_BB_SW_IC11_Q_EN_IDX  (46)
#define RX_BB_SW_IC16_Q_EN_IDX 	(47)
#define VDD_1V5_EN_IDX 			(48)
#define VDD_1V_R1_EN_IDX		(49)
#define VDD_1V_R2_EN_IDX		(50)
#define VDD_1V_R3_EN_IDX		(51)
#define VDD_1V_R4_EN_IDX		(52)
#define VDD_2V75_EN_IDX			(53)
#define REFCLK_SYNTH1_EN_IDX	(54)
#define REFCLK_SYNTH2_EN_IDX	(55)
#define PIN_LE_IDX(n) 			(n>=9?(56+n-9):(65+n))

static uint8_t g_shreg_data[BOARD_SHREG_LEN];

void fill_def_values(void)
{
	for (uint8_t i=0;i<BOARD_SHREG_LEN;i++)
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

void init_shreg(void)
{
	GPIO_TypeDef *p_dport, *p_clkport, *p_lport;
		uint16_t dpin, clkpin, lpin;

		p_dport = SHREG_DATA_GPIO_Port;
		p_clkport = SHREG_CLK_GPIO_Port;
		p_lport = SHREG_LATCH_GPIO_Port;

		dpin = SHREG_DATA_Pin;
		clkpin = SHREG_CLK_Pin;
		lpin = SHREG_LATCH_Pin;

	for (int8_t i=BOARD_SHREG_LEN-1;i>0; i--)
	{
		uint8_t data;

		data = g_shreg_data[i] & 0x1;

//		HAL_GPIO_WritePin(p_port, pin, GPIO_PIN_RESET);


	}
}
