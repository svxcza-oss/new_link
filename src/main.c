#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"

UART_HandleTypeDef huart2;

// 함수 선언
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);

int main(void) {
    HAL_Init();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    uint8_t rx_data;
    uint8_t msg[] = "Received!\r\n";

    while (1) {
        // UART 수신 대기 (에러 방지용으로 10ms만 대기)
        HAL_StatusTypeDef status = HAL_UART_Receive(&huart2, &rx_data, 1, 10);

        if (status == HAL_OK) {
            // 데이터 받으면 맥북으로 다시 쏘고 LED 반전
            HAL_UART_Transmit(&huart2, msg, 11, 100);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        } 
        else if (status == HAL_ERROR) {
            // ⭐️ 중요: 오버런 에러(ORE) 발생 시 강제 초기화 ⭐️
            __HAL_UART_CLEAR_OREFLAG(&huart2);
            HAL_UART_Receive(&huart2, &rx_data, 1, 0); 
        }
    }
}

// 1. GPIO 초기화 (LED 핀 설정)
void MX_GPIO_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// 2. UART 초기화 (통로 개방 및 핀 설정)
void MX_USART2_UART_Init(void) {
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // ⭐️ 님을 괴롭힌 범인: 핀을 'UART 모드(AF7)'로 설정해야 함 ⭐️
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2; // 이게 핵심!
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart2);
}