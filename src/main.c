#include <stdint.h>

// 1. 하드웨어 주소 (F401RE 데이터시트 기준 좌표)
#define RCC_AHB1ENR  (*(volatile uint32_t*)0x40023830) 
//usinged int , 32bit(4byte), _t 사용자 정의 자료형임을 나타냄.
//그냥 usinged int 라고 쓰면 메모리마다 다 달라질수 있어서 uint라고 못 박는거임
//Reset and Clock Control
#define GPIOA_MODER  (*(volatile uint32_t*)0x40020000) 
#define GPIOA_ODR    (*(volatile uint32_t*)0x40020014) 
//General Purpose Input/Output

/*
GPIOA: 0번부터 15번까지의 첫 번째 핀 묶음 (아까 LED가 연결된 PA5가 여기 속하죠.)

GPIOB: 두 번째 묶음

GPIOC: 세 번째 묶음

GPIOD: 네 번째 묶음
*/

int main(void) {
    // [STEP 1] GPIOA 포트에 클록 공급 (0번 비트를 1로)
    RCC_AHB1ENR |= (1 << 0);  

    // [STEP 2] PA5 핀(내장 LED)을 출력 모드로 설정 (10번 비트 1로)
    GPIOA_MODER &= ~(3 << 10); 
    GPIOA_MODER |= (1 << 10);  

    while (1) {
        // [STEP 3] LED 켜기 (5번 비트를 1로)
        GPIOA_ODR |= (1 << 5);
        for (volatile int i = 0; i < 500000; i++); 

        // [STEP 4] LED 끄기 (5번 비트를 0으로)
        GPIOA_ODR &= ~(1 << 5);
        for (volatile int i = 0; i < 500000; i++);
    }
}