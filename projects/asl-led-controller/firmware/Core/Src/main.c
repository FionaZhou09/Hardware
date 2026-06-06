/**
 * ASL LED Controller — STM32 Nucleo-G474RE
 *
 * Receives 'L' or 'R' over USART2 (USB serial via ST-Link VCP).
 * 'L' → PA5 (built-in LD2) on,  PB5 off
 * 'R' → PB5 (external LED D4) on, PA5 off
 * Replies "OK\n" after every command.
 */

#include "main.h"
#include <string.h>

UART_HandleTypeDef huart2;

static void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

static void UART_Print(const char *msg)
{
    HAL_UART_Transmit(&huart2, (const uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    HAL_GPIO_WritePin(LED_L_PORT, LED_L_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_R_PORT, LED_R_PIN, GPIO_PIN_RESET);

    uint8_t rx;

    while (1)
    {
        if (HAL_UART_Receive(&huart2, &rx, 1, HAL_MAX_DELAY) == HAL_OK)
        {
            if (rx == 'A')
            {
                /* A sign — orange LED (D7) on, blue off */
                HAL_GPIO_WritePin(LED_L_PORT, LED_L_PIN, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LED_R_PORT, LED_R_PIN, GPIO_PIN_RESET);
            }
            else if (rx == 'C')
            {
                /* C sign — blue LED (D4) on, orange off */
                HAL_GPIO_WritePin(LED_L_PORT, LED_L_PIN, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(LED_R_PORT, LED_R_PIN, GPIO_PIN_SET);
            }
            else if (rx == 'O')
            {
                /* No hand — both off */
                HAL_GPIO_WritePin(LED_L_PORT, LED_L_PIN, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(LED_R_PORT, LED_R_PIN, GPIO_PIN_RESET);
            }
            UART_Print("OK\n");
        }
    }
}

/* ── GPIO ────────────────────────────────────────────────────────────────── */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef cfg = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    cfg.Mode  = GPIO_MODE_OUTPUT_PP;
    cfg.Pull  = GPIO_NOPULL;
    cfg.Speed = GPIO_SPEED_FREQ_LOW;

    cfg.Pin = LED_L_PIN;
    HAL_GPIO_Init(LED_L_PORT, &cfg);

    cfg.Pin = LED_R_PIN;
    HAL_GPIO_Init(LED_R_PORT, &cfg);
}

/* ── USART2 — 115200 8N1 ─────────────────────────────────────────────────── */
static void MX_USART2_UART_Init(void)
{
    huart2.Instance          = USART2;
    huart2.Init.BaudRate     = 115200;
    huart2.Init.WordLength   = UART_WORDLENGTH_8B;
    huart2.Init.StopBits     = UART_STOPBITS_1;
    huart2.Init.Parity       = UART_PARITY_NONE;
    huart2.Init.Mode         = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK)
        Error_Handler();
}

/* ── Clock — 170 MHz from HSI via PLL ───────────────────────────────────── */
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

    osc.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
    osc.HSIState            = RCC_HSI_ON;
    osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    osc.PLL.PLLState        = RCC_PLL_ON;
    osc.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
    osc.PLL.PLLM            = RCC_PLLM_DIV4;
    osc.PLL.PLLN            = 85;
    osc.PLL.PLLP            = RCC_PLLP_DIV2;
    osc.PLL.PLLQ            = RCC_PLLQ_DIV2;
    osc.PLL.PLLR            = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&osc) != HAL_OK)
        Error_Handler();

    clk.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                       | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    clk.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV1;
    clk.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_4) != HAL_OK)
        Error_Handler();
}

void Error_Handler(void)
{
    __disable_irq();
    while (1) {}
}
