#include "LaserController.h"

LaserController::LaserController(UART_HandleTypeDef *huart, uint8_t *rxBuffer)
{
    serial = Serial(huart, rxBuffer, ';', ',');
    RetargetInit(huart);
}

void LaserController::pasteThisToRxCpltCallback()
{
    serial.pasteThisToRxCpltCallback();
}

void LaserController::pasteThisToMainLoop()
{
    if (serial.readyRead())
    {
        int32_t key = serial.getInt(0);
        switch (key)
        {
            case 0:
                HAL_GPIO_TogglePin(LDR_GPIO_Port, LDR_Pin);
                break;
            case 1:
                HAL_GPIO_TogglePin(LDG_GPIO_Port, LDG_Pin);
                break;
            case 2:
                HAL_GPIO_TogglePin(LDB_GPIO_Port, LDB_Pin);
                break;
            default:
                printf("Got smth else.\n");
                break;
        }
        serial.startReceiving();
    }
}
