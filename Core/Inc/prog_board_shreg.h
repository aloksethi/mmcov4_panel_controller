/*
 * prog_board_shreg.h
 *
 *  Created on: Sep 5, 2022
 *      Author: asethi
 */

#ifndef INC_PROG_BOARD_SHREG_H_
#define INC_PROG_BOARD_SHREG_H_

#define BOARD_SHREG_LEN			(80)
#define BOARD_CLK_DELAY			(100)

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
#define PIN_LE_IDX(n) 			(n>=9?(56+n-9):(64+n-1))

void shref_set_synth_refclk(uint8_t synth_id, val_gen_t val);
void shreg_set_1V0_en(uint8_t en, pow_plane_t plane);
void shreg_set_1V5_en(uint8_t en);
void shreg_set_2V75_en(uint8_t en);
void shreg_set_le(uint8_t ic_id);
void shreg_set_iref(uint8_t ic_id, val_gen_t val);
void shreg_set_bb_sw(uint8_t ic_id, val_gen_t val);
void shreg_set_bb_amp(uint8_t ic_id, val_gen_t val);
void init_shreg(void);
#endif /* INC_PROG_BOARD_SHREG_H_ */
