/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    octospi.c
  * @brief   This file provides code for the configuration
  *          of the OCTOSPI instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "octospi.h"

/* USER CODE BEGIN 0 */
#include "usart.h"



#define PSRAM_ENTER_QUAD_MODE     0x35
#define PSRAM_QUAD_WRITE          0x38
#define PSRAM_FAST_READ_QUAD_IO   0xEB
#define PSRAM_READ_DUMMY_CYCLES   6



/* USER CODE END 0 */

OSPI_HandleTypeDef hospi1;

/* OCTOSPI1 init function */
void MX_OCTOSPI1_Init(void)
{

  /* USER CODE BEGIN OCTOSPI1_Init 0 */

  /* USER CODE END OCTOSPI1_Init 0 */

  OSPIM_CfgTypeDef OSPIM_Cfg_Struct = {0};

  /* USER CODE BEGIN OCTOSPI1_Init 1 */

  /* USER CODE END OCTOSPI1_Init 1 */
  hospi1.Instance = OCTOSPI1;
  hospi1.Init.FifoThreshold = 1;
  hospi1.Init.DualQuad = HAL_OSPI_DUALQUAD_DISABLE;
  hospi1.Init.MemoryType = HAL_OSPI_MEMTYPE_APMEMORY;
  hospi1.Init.DeviceSize = 23;
  hospi1.Init.ChipSelectHighTime = 4;
  hospi1.Init.FreeRunningClock = HAL_OSPI_FREERUNCLK_DISABLE;
  hospi1.Init.ClockMode = HAL_OSPI_CLOCK_MODE_0;
  hospi1.Init.ClockPrescaler = 64;
  hospi1.Init.SampleShifting = HAL_OSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hospi1.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_DISABLE;
  hospi1.Init.ChipSelectBoundary = 0;
  hospi1.Init.DelayBlockBypass = HAL_OSPI_DELAY_BLOCK_BYPASSED;
  hospi1.Init.Refresh = 0;
  if (HAL_OSPI_Init(&hospi1) != HAL_OK)
  {
    Error_Handler();
  }
  OSPIM_Cfg_Struct.ClkPort = 1;
  OSPIM_Cfg_Struct.NCSPort = 1;
  OSPIM_Cfg_Struct.IOLowPort = HAL_OSPIM_IOPORT_1_LOW;
  if (HAL_OSPIM_Config(&hospi1, &OSPIM_Cfg_Struct, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OCTOSPI1_Init 2 */

  /* USER CODE END OCTOSPI1_Init 2 */

}

void HAL_OSPI_MspInit(OSPI_HandleTypeDef* ospiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(ospiHandle->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspInit 0 */

  /* USER CODE END OCTOSPI1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_OSPI;
    PeriphClkInit.OspiClockSelection = RCC_OSPICLKSOURCE_SYSCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* OCTOSPI1 clock enable */
    __HAL_RCC_OSPIM_CLK_ENABLE();
    __HAL_RCC_OSPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**OCTOSPI1 GPIO Configuration
    PA2     ------> OCTOSPIM_P1_NCS
    PA3     ------> OCTOSPIM_P1_CLK
    PA6     ------> OCTOSPIM_P1_IO3
    PA7     ------> OCTOSPIM_P1_IO2
    PB0     ------> OCTOSPIM_P1_IO1
    PB1     ------> OCTOSPIM_P1_IO0
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN OCTOSPI1_MspInit 1 */

  /* USER CODE END OCTOSPI1_MspInit 1 */
  }
}

void HAL_OSPI_MspDeInit(OSPI_HandleTypeDef* ospiHandle)
{

  if(ospiHandle->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspDeInit 0 */

  /* USER CODE END OCTOSPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_OSPIM_CLK_DISABLE();
    __HAL_RCC_OSPI1_CLK_DISABLE();

    /**OCTOSPI1 GPIO Configuration
    PA2     ------> OCTOSPIM_P1_NCS
    PA3     ------> OCTOSPIM_P1_CLK
    PA6     ------> OCTOSPIM_P1_IO3
    PA7     ------> OCTOSPIM_P1_IO2
    PB0     ------> OCTOSPIM_P1_IO1
    PB1     ------> OCTOSPIM_P1_IO0
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_1);

  /* USER CODE BEGIN OCTOSPI1_MspDeInit 1 */

  /* USER CODE END OCTOSPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */






void PSRAM_ResetReadID_Print(void)
{
    OSPI_RegularCmdTypeDef cmd = {0};
    uint8_t id[3] = {0};
    char msg[80];

    // ---------- Reset Enable (0x66) ----------
    cmd.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
    cmd.FlashId            = HAL_OSPI_FLASH_ID_1;

    cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_1_LINE;
    cmd.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    cmd.Instruction        = 0x66;

    cmd.AddressMode        = HAL_OSPI_ADDRESS_NONE;
    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    cmd.DataMode           = HAL_OSPI_DATA_NONE;
    cmd.DummyCycles        = 0;
    cmd.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);

    // ---------- Reset (0x99) ----------
    cmd.Instruction = 0x99;
    HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);

    HAL_Delay(1);

    // ---------- Read ID (0x9F + 24-bit address) ----------
    cmd.Instruction = 0x9F;

    cmd.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
    cmd.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
    cmd.Address     = 0x000000;

    cmd.DataMode    = HAL_OSPI_DATA_1_LINE;
    cmd.NbData      = 3;

    HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);
    HAL_OSPI_Receive(&hospi1, id, HAL_MAX_DELAY);

    // ---------- Print to UART ----------
    int n = sprintf(msg,
                    "PSRAM ID: %02X %02X %02X\r\n",
                    id[0], id[1], id[2]);

    HAL_UART_Transmit(&huart1,
                      (uint8_t*)msg,
                      n,
                      HAL_MAX_DELAY);
}






void PSRAM_EnterQuadMode(void)
{
    OSPI_RegularCmdTypeDef cmd = {0};

    cmd.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
    cmd.FlashId            = HAL_OSPI_FLASH_ID_1;

    cmd.Instruction        = 0x35; // Enter Quad Mode
    cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_1_LINE;
    cmd.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;

    cmd.AddressMode        = HAL_OSPI_ADDRESS_NONE;
    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    cmd.DataMode           = HAL_OSPI_DATA_NONE;
    cmd.DummyCycles        = 0;
    cmd.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;



    HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);
}




void PSRAM_Reset(void)
{
    OSPI_RegularCmdTypeDef cmd = {0};

    // ---------- Reset Enable (0x66) ----------
    cmd.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
    cmd.FlashId            = HAL_OSPI_FLASH_ID_1;

    cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_1_LINE;
    cmd.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    cmd.Instruction        = 0x66;

    cmd.AddressMode        = HAL_OSPI_ADDRESS_NONE;
    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    cmd.DataMode           = HAL_OSPI_DATA_NONE;
    cmd.DummyCycles        = 0;
    cmd.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);

    // ---------- Reset (0x99) ----------
    cmd.Instruction = 0x99;
    HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY);

    HAL_Delay(1);
}









void PSRAM_EnableMemMapped_Quad444(void)
{
    OSPI_RegularCmdTypeDef cmd = {0};
    OSPI_MemoryMappedTypeDef mm = {0};

    PSRAM_Reset();
    HAL_Delay(1);
    PSRAM_EnterQuadMode();
    HAL_Delay(1);

    // Common
    cmd.FlashId            = HAL_OSPI_FLASH_ID_1;
    cmd.InstructionMode    = HAL_OSPI_INSTRUCTION_4_LINES;
    cmd.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    cmd.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;

    cmd.AddressMode        = HAL_OSPI_ADDRESS_4_LINES;
    cmd.AddressSize        = HAL_OSPI_ADDRESS_24_BITS;
    cmd.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;

    cmd.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;

    cmd.DataMode           = HAL_OSPI_DATA_4_LINES;
    cmd.DataDtrMode        = HAL_OSPI_DATA_DTR_DISABLE;

    cmd.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    cmd.Address            = 0;
    cmd.NbData             = 0;   // IMPORTANT for *_CFG templates

    // -------- WRITE_CFG (memory-mapped writes use this) --------
    cmd.OperationType      = HAL_OSPI_OPTYPE_WRITE_CFG;
    cmd.Instruction        = 0x38;                 // Quad Write
    cmd.DummyCycles        = 0;
    cmd.DQSMode            = HAL_OSPI_DQS_ENABLE; // L4 usually no DQS pin

    if (HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
        Error_Handler();

    // -------- READ_CFG (memory-mapped reads use this) --------
    cmd.OperationType      = HAL_OSPI_OPTYPE_READ_CFG;
    cmd.Instruction        = 0xEB;                 // Fast Read Quad I/O (QPI style)
    cmd.DummyCycles        = 6;
    cmd.DQSMode            = HAL_OSPI_DQS_DISABLE;

    if (HAL_OSPI_Command(&hospi1, &cmd, HAL_MAX_DELAY) != HAL_OK)
        Error_Handler();

    // -------- Memory-mapped enable --------
    mm.TimeOutActivation   = HAL_OSPI_TIMEOUT_COUNTER_ENABLE;
    mm.TimeOutPeriod       = 1;   // release nCS quickly

    if (HAL_OSPI_MemoryMapped(&hospi1, &mm) != HAL_OK)
        Error_Handler();
}



/* USER CODE END 1 */
