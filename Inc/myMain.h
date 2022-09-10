#ifndef MYMAIN_H
#define MYMAIN_H

#include "usart.h"
#include <cstring>
#include <stdio.h>
#include "LaserController.h"

[[noreturn]] int myMain();

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif