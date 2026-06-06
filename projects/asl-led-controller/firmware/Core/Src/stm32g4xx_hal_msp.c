/**
 * HAL MSP (MCU Support Package)
 * Low-level peripheral pin and clock init called by HAL_XXX_Init() functions.
 */

#include "main.h"

/* Called by HAL_Init() */
void HAL_MspInit(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
}

/* Called by HAL_UART_Init() — configures PA2 (TX) and PA3 (RX) for USART2 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef cfg = {0};

    if (huart->Instance == USART2)
    {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /* PA2 = USART2_TX, PA3 = USART2_RX  (AF7) */
        cfg.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
        cfg.Mode      = GPIO_MODE_AF_PP;
        cfg.Pull      = GPIO_NOPULL;
        cfg.Speed     = GPIO_SPEED_FREQ_LOW;
        cfg.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &cfg);
    }
}

/* Called by HAL_UART_DeInit() */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        __HAL_RCC_USART2_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
    }
}
