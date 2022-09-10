#ifndef LASERCONTROLLER_H
#define LASERCONTROLLER_H

#include "Parser.h"
#include "Serial.h"
#include "retarget.h"
#include "gpio.h"
#include "tim.h"

#define MARKERFILTERFREQ 50000
#define MARKERFILTERDUTY 0.5

class LaserController
{
private:
    TIM_HandleTypeDef *pwmTimer;
    uint32_t pwmTimerFCLK = 0, pwmTimerARR = 0, pwmTimerCCR = 0, pwmTimerPSC = 0;
public:
    Serial serial;
public:
    LaserController() = default;

    LaserController(UART_HandleTypeDef *huart, uint8_t *rxBuffer, TIM_HandleTypeDef *pwmTimer,
                    uint32_t pwmTimerChannel);

    void pasteThisToRxCpltCallback();

    void pasteThisToMainLoop();

private:
    void writePWM(const uint32_t &pwmFreq, const double &dutyCycle);
    void updateTimerInfo(const bool &print= false);
    void parseSerial();
};

#endif