#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <string.h>

#include "stm32f4xx_hal.h"
UART_HandleTypeDef huart2;

void 
/*
UART 통신 (Universal Asynchronous Receiver/Transmitter)
범용 비동기 송수신 장치

Asynchronous(비동기)
비동기란?
=> 데이터를 보낼때 신호를 알려주는 별도의 클락선 없음.

TX(Transmit) : 보내기
RX(Receive) : 받기 

보드에 rx,tx 적혀있는 곳 주소값으로 받음.(전압의 변화)

UART는 0과 1을 시간과 전압으로 표현.
평상시:1
시작 신호:0
약속된 시간마다 전압을 올렸다 내렸다 8비트로 보냄
다시 1로 올려서 종료.

Baud Rate(속도)가 중요한 이유?
따로 클락선이 없기 때문에 1비트를 얼마동안 유지할지 약속해야함.
Baud Rate 115,200은 1초에 $115,200$개의 비트를 보내겠다는 뜻
**시간 맞추기 중요**
*/



#endif UART_H