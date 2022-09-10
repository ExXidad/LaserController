#include "LaserController.h"

LaserController::LaserController(UART_HandleTypeDef *huart, uint8_t *rxBuffer, TIM_HandleTypeDef *pwmTimer,
                                 uint32_t pwmTimerChannel)
{
    serial = Serial(huart, rxBuffer, ';', ',');
    this->pwmTimer = pwmTimer;
    RetargetInit(huart);
    HAL_TIM_PWM_Start(pwmTimer, pwmTimerChannel);
    updateTimerInfo(true);
}

void LaserController::pasteThisToRxCpltCallback()
{
    serial.pasteThisToRxCpltCallback();
}

void LaserController::pasteThisToMainLoop()
{
    parseSerial();
}

void LaserController::writePWM(const uint32_t &pwmFreq, const double &dutyCycle)
{
    pwmTimer->Instance->ARR = pwmTimerFCLK / pwmFreq / (1 + pwmTimerPSC) - 1;
    pwmTimer->Instance->CCR1 = dutyCycle * (pwmTimerFCLK / pwmFreq / (1 + pwmTimerPSC) - 1);
    updateTimerInfo(false);
}

void LaserController::updateTimerInfo(const bool &print)
{
    pwmTimerARR = pwmTimer->Instance->ARR;
    pwmTimerCCR = pwmTimer->Instance->CCR1;
    pwmTimerPSC = pwmTimer->Instance->PSC;
    pwmTimerFCLK = HAL_RCC_GetPCLK2Freq();

    if (print)
    {
        printf("PCLK 2 freq: %lu\n", pwmTimerFCLK);
        printf("PWM timer ARR: %lu\n", pwmTimerARR);
        printf("PWM timer CCR: %lu\n", pwmTimerCCR);
        printf("PWM timer PSC: %lu\n", pwmTimerPSC);
    }
}

void LaserController::parseSerial()
{
    if (serial.readyRead())
    {
        int32_t key = serial.getInt(0);
        HAL_GPIO_WritePin(LDR_GPIO_Port, LDR_Pin | LDG_Pin | LDB_Pin, GPIO_PIN_RESET);
        switch (key)
        {
            // Disable Mode [Red]
            case 0:
                HAL_GPIO_TogglePin(LDR_GPIO_Port, LDR_Pin);
                writePWM(MARKERFILTERFREQ, 0);
                break;
                // Marker search Mode [Green]
            case 1:
                HAL_GPIO_TogglePin(LDG_GPIO_Port, LDG_Pin);
                writePWM(MARKERFILTERFREQ, MARKERFILTERDUTY);
                break;
                // CW Mode [Blue]
            case 2:
                HAL_GPIO_TogglePin(LDB_GPIO_Port, LDB_Pin);
                writePWM(MARKERFILTERFREQ, 1);
                break;
            default:
                printf("Got smth else.\n");
                break;
        }
        serial.startReceiving();
    }
}

