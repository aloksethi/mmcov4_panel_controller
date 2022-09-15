/*
 * mlab_nucleo_if.h
 *
 *  Created on: 1.2.2021
 *      Author: asethi
 */

#ifndef INC_MLAB_NUCLEO_IF_H_
#define INC_MLAB_NUCLEO_IF_H_

#define G_MAX_ICS_PER_UC					16
#define G_REGS_PER_REG						4		// upto 4 shift registers are cascaded to make one shift register
#define G_LENGTH_ONE_REG					20 		//number of bits in one shift register
#define G_MAX_NUM_REGS						63		// two older muxes were cascaded, so one address went there
#define G_STORAGE_FOR_ONE_REG_BITS			((G_REGS_PER_REG * G_LENGTH_ONE_REG))  // this is in bits
#define G_STORAGE_FOR_ONE_REG_BYTES			(G_STORAGE_FOR_ONE_REG_BITS/8)

// command code, instead of enum have made it defines, easier to integrate in matlab
#define G_UC_MIN_COMMAND_CODE				0
#define G_UC_SET_REG_CONFIG					1
#define G_UC_SAVE_DEF_REG_CONFIG		 	2
#define G_UC_SAVE_MAXI_REG_CONFIG			3
#define G_UC_SAVE_MINI_REG_CONFIG 			4
#define G_UC_APPLY_DEF_REG_CONFIG			5
#define G_UC_APPLY_MAXI_REG_CONFIG			6
#define G_UC_APPLY_MINI_REG_CONFIG 			7
#define G_UC_SET_CURR_AS_DEF_CONFIG			8
#define G_UC_SYNTH_POWER					9
#define G_UC_SYNTH_CONFIG					10
#define G_UC_3V3_POWER						11
#define G_UC_2V0_POWER						12
#define G_UC_1V5_POWER						13
#define G_UC_1V0_POWER						14
#define G_UC_REFCLK							15
#define G_UC_RX_BB_SW						16
#define G_UC_TX_BB_AMP						17
#define G_UC_IREF							18
#define G_UC_PA_GATE_BIAS					19
#define G_UC_2V75_POWER						20

#define G_UC_MAX_COMMAND_CODE				21


#define G_NUCLEO_PORT_NUM					5050

typedef enum __attribute__((__packed__))
{
	R1 = 1,
	R2 = 2,
	R3 = 3,
	R4 = 4
} pow_plane_t;

// making enum a single byte. haven't used the -fshort_enums flag
typedef enum __attribute__((__packed__))
{
	V_0V00 = 0,
	V_0V80 = 1,
	V_0V85 = 2,
	V_0V90 = 3,
	V_0V95 = 4,
	V_1V00 = 5,
	V_1V05 = 6,
	V_1V10 = 7,
	V_1V15 = 8,
	V_1V20 = 9
} val_1v_t;

typedef enum __attribute__((__packed__))
{
	V_ENABLE = 1,
	V_DISABLE = 0,
} val_gen_t;

typedef val_gen_t val_1v5_t;

typedef struct __attribute__((packed)) {
	uint8_t reg_id;		// latch id
	uint8_t cascade;	// num of shift regs in cascade, most have value 3
	uint8_t reg_val[G_STORAGE_FOR_ONE_REG_BYTES]; // value saved in bytes
} reg_t;

typedef struct __attribute__((packed)) {
	pow_plane_t plane_id;
	uint8_t sup_status;
	uint8_t pot_val;
} pot_data_t;


typedef struct __attribute__((packed)) {
//	pow_plane_t plane_id;  --> plane id is deduced from the ic id
	val_1v_t val;
} pow1_1v_data_t;

typedef uint32_t pa_regu_pln_t; // 2V PA regulator enable plane R1(1,2,5,6), R2(3,4,7,8)

typedef struct __attribute__((packed)) {
	uint32_t running_id;
	uint8_t ic_id;
	uint8_t command_code;
	uint8_t num_chunks; //number of chunks of sub data
	uint8_t data[0];	// placement for a pointer, can point to  reg_t or pot_t
} mlab_data_t;

#endif /* INC_MLAB_NUCLEO_IF_H_ */

