#ifndef __STM32G4xx_HAL_CONF_H
#define __STM32G4xx_HAL_CONF_H

/* ── Clock values ────────────────────────────────────────────────────────── */
#define HSE_VALUE              8000000U   /* Not used (we use HSI) */
#define HSE_STARTUP_TIMEOUT    100U
#define HSI_VALUE              16000000U  /* G474RE internal oscillator */
#define HSI48_VALUE            48000000U
#define LSI_VALUE              32000U
#define LSE_VALUE              32768U
#define LSE_STARTUP_TIMEOUT    5000U
#define EXTERNAL_CLOCK_VALUE   12288000U

/* ── HAL tick ────────────────────────────────────────────────────────────── */
#define  TICK_INT_PRIORITY     0U
#define  USE_RTOS              0U
#define  PREFETCH_ENABLE       0U
#define  INSTRUCTION_CACHE_ENABLE 1U
#define  DATA_CACHE_ENABLE     1U

/* ── Enable only the modules we use ─────────────────────────────────────── */
#define HAL_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED

/* ── Assert (disabled for release builds) ────────────────────────────────── */
/* #define USE_FULL_ASSERT */
#define assert_param(expr) ((void)0U)

/* ── Include HAL driver headers ──────────────────────────────────────────── */
#ifdef HAL_RCC_MODULE_ENABLED
  #include "stm32g4xx_hal_rcc.h"
#endif
#ifdef HAL_GPIO_MODULE_ENABLED
  #include "stm32g4xx_hal_gpio.h"
#endif
#ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32g4xx_hal_dma.h"
#endif
#ifdef HAL_CORTEX_MODULE_ENABLED
  #include "stm32g4xx_hal_cortex.h"
#endif
#ifdef HAL_PWR_MODULE_ENABLED
  #include "stm32g4xx_hal_pwr.h"
  #include "stm32g4xx_hal_pwr_ex.h"
#endif
#ifdef HAL_FLASH_MODULE_ENABLED
  #include "stm32g4xx_hal_flash.h"
  #include "stm32g4xx_hal_flash_ex.h"
  #include "stm32g4xx_hal_flash_ramfunc.h"
#endif
#ifdef HAL_UART_MODULE_ENABLED
  #include "stm32g4xx_hal_uart.h"
  #include "stm32g4xx_hal_uart_ex.h"
#endif

#endif /* __STM32G4xx_HAL_CONF_H */
