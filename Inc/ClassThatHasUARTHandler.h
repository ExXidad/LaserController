//
// Created by Ivan Kalesnikau on 10.09.2022.
//

#ifndef CLASSTHATHASUARTHANDLER_H
#define CLASSTHATHASUARTHANDLER_H


class ClassThatHasUARTHandler
{
public:
    ClassThatHasUARTHandler() = default;

    virtual void handleUART() = 0;
};

#endif
