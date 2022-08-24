/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
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
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
