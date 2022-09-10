#ifndef LASERCONTROLLER_H
#define LASERCONTROLLER_H

#include "Parser.h"
#include "Serial.h"
#include "retarget.h"
#include "gpio.h"

class LaserController
{
private:

public:
    Serial serial;
public:
    LaserController() = default;

    LaserController(UART_HandleTypeDef *huart, uint8_t *rxBuffer);

    void pasteThisToRxCpltCallback();

    void pasteThisToMainLoop();

private:
};

#endif