/*
 * board.h
 *
 *  Created on: Jan 25, 2021
 *      Author: asethi
 */

#ifndef INC_BOARD_H_
#define INC_BOARD_H_

#include "FreeRTOS.h"
#include "semphr.h"

extern I2C_HandleTypeDef g_hi2c1;
extern SPI_HandleTypeDef g_hspi1;

extern SemaphoreHandle_t g_mutex_i2c_op;
extern SemaphoreHandle_t g_mutex_spi_op;

#define CHIP_CLK_DELAY				500
//nss pin is under software control, rest are configed in HAL_SPI_MspInit
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define SYNTH_LATCH_Pin GPIO_PIN_5
#define SYNTH_LATCH_GPIO_Port GPIOF
#define REG1V_B1_R1_Pin GPIO_PIN_6
#define REG1V_B1_R1_GPIO_Port GPIOF
#define REG1V_B0_R1_Pin GPIO_PIN_7
#define REG1V_B0_R1_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define SYNTH2_LATCH_Pin GPIO_PIN_4
#define SYNTH2_LATCH_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LED_GREEN_Pin GPIO_PIN_0
#define LED_GREEN_GPIO_Port GPIOB
#define REG1V_B1_R4_Pin GPIO_PIN_10
#define REG1V_B1_R4_GPIO_Port GPIOB
#define SHREG_LATCH_Pin GPIO_PIN_11
#define SHREG_LATCH_GPIO_Port GPIOB
#define SHREG_CLK_Pin GPIO_PIN_12
#define SHREG_CLK_GPIO_Port GPIOB
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_14
#define LED_RED_GPIO_Port GPIOB
#define SHREG_DATA_Pin GPIO_PIN_15
#define SHREG_DATA_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define REG1V_B0_R3_Pin GPIO_PIN_6
#define REG1V_B0_R3_GPIO_Port GPIOC
#define REG1V_B1_R3_Pin GPIO_PIN_7
#define REG1V_B1_R3_GPIO_Port GPIOC
#define IC_DIN_Pin GPIO_PIN_8
#define IC_DIN_GPIO_Port GPIOC
#define REG1V_B0_R2_Pin GPIO_PIN_9
#define REG1V_B0_R2_GPIO_Port GPIOC
#define VDD2_PA_R2_EN_Pin GPIO_PIN_8
#define VDD2_PA_R2_EN_GPIO_Port GPIOA
#define VDD2_PA_R2_ENA9_Pin GPIO_PIN_9
#define VDD2_PA_R2_ENA9_GPIO_Port GPIOA
#define REG3V3_SYNTH_EN_Pin GPIO_PIN_10
#define REG3V3_SYNTH_EN_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define REG3V3_EN_Pin GPIO_PIN_15
#define REG3V3_EN_GPIO_Port GPIOA
#define VDD2_PA_R1_EN_Pin GPIO_PIN_10
#define VDD2_PA_R1_EN_GPIO_Port GPIOC
#define IC_CLK_1_2_8_Pin GPIO_PIN_11
#define IC_CLK_1_2_8_GPIO_Port GPIOC
#define VDD2_PA_R3_EN_Pin GPIO_PIN_12
#define VDD2_PA_R3_EN_GPIO_Port GPIOC
#define IC_CLK_9_2_16_Pin GPIO_PIN_2
#define IC_CLK_9_2_16_GPIO_Port GPIOD
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define REG1V_B0_R4_Pin GPIO_PIN_4
#define REG1V_B0_R4_GPIO_Port GPIOB
#define LED_BLUE_Pin GPIO_PIN_7
#define LED_BLUE_GPIO_Port GPIOB
#define REG1V_B1_R2_Pin GPIO_PIN_8
#define REG1V_B1_R2_GPIO_Port GPIOB


void board_red_led_toggle(void);
void board_green_led_toggle(void);
void board_blue_led_toggle(void);

void board_synth_power_on(void);
void board_synth_power_off(void);
void board_3v3_power_on(void);
void board_3v3_power_off(void);

void board_set_lo_switch(uint8_t);

void board_pb_sup1_en(void);
void board_pb_sup1_dis(void);
void board_pb_sup2_en(void);
void board_pb_sup2_dis(void);
void board_pb_sup3_en(void);
void board_pb_sup3_dis(void);
void board_pb_sup4_en(void);
void board_pb_sup4_dis(void);
void board_pb_sup5_en(void);
void board_pb_sup5_dis(void);
void board_pb_lcl5v_en(void);
void board_pb_lcl5v_dis(void);

void board_init(void);

#endif /* INC_BOARD_H_ */
