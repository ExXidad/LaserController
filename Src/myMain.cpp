#include "myMain.h"

uint8_t rxBuffer[MAXMESSAGELENGTH];
LaserController laserController;

[[noreturn]] int myMain()
{
    laserController = LaserController(&huart3, rxBuffer);

    while (1)
    {
        laserController.pasteThisToMainLoop();
//        HAL_Delay();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    laserController.pasteThisToRxCpltCallback();
}