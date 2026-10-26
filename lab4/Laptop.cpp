#include <iostream>
#include "Laptop.h"

Laptop::Laptop()
{
    power = false;
    lid = false;
    sleepMode = false;
    battery = 50;
}

Laptop::Laptop(bool p, bool l, bool s, int b)
{
    power = p;
    lid = l;
    sleepMode = s;
    battery = b;
    if (battery < 0)
        battery = 0;
    if (battery > 100)
        battery = 100;
    if (battery == 0)
        power = false;
    if (power == false)
        sleepMode = false;
    if (power == true && lid == false)
        sleepMode = true;
}

bool Laptop::getPower()
{
    return power;
}

bool Laptop::getLid()
{
    return lid;
}

bool Laptop::getSleep()
{
    return sleepMode;
}

int Laptop::getBattery()
{
    return battery;
}

int Laptop::getState()
{
    if (power == false)
    {
        if (battery == 0)
        {
            if (lid == false)
                return 6;
            else
                return 7;
        }
        else
        {
            if (lid == false)
                return 1;
            else
                return 2;
        }
    }
    if (sleepMode == false)
        return 3;
    if (lid == true)
        return 4;
    return 5;
}

void Laptop::changePower()
{
    if (power == true)
    {
        power = false;
        sleepMode = false;
        std::cout << "Ноутбук выключен" << std::endl;
    }
    else
    {
        if (battery == 0)
            std::cout << "Батарея разряжена, включить нельзя" << std::endl;
        else if (lid == false)
            std::cout << "Крышка закрыта, сначала откройте ее" << std::endl;
        else
        {
            power = true;
            std::cout << "Ноутбук включен" << std::endl;
        }
    }
}

void Laptop::changeLid()
{
    if (lid == true)
    {
        lid = false;
        std::cout << "Крышка закрыта" << std::endl;
        if (power == true && sleepMode == false)
        {
            sleepMode = true;
            std::cout << "Ноутбук перешел в спящий режим" << std::endl;
        }
    }
    else
    {
        lid = true;
        std::cout << "Крышка открыта" << std::endl;
        if (power == true && sleepMode == true)
        {
            sleepMode = false;
            std::cout << "Ноутбук вышел из спящего режима" << std::endl;
        }
    }
}

void Laptop::changeSleep()
{
    if (power == false)
        std::cout << "Ноутбук выключен" << std::endl;
    else if (lid == false)
        std::cout << "Крышка закрыта, ноутбук спит. Откройте крышку" << std::endl;
    else if (sleepMode == true)
    {
        sleepMode = false;
        std::cout << "Ноутбук вышел из спящего режима" << std::endl;
    }
    else
    {
        sleepMode = true;
        std::cout << "Ноутбук перешел в спящий режим" << std::endl;
    }
}

void Laptop::doWork(int minutes)
{
    if (power == false || sleepMode == true)
    {
        std::cout << "Ноутбук не работает" << std::endl;
        return;
    }
    if (minutes <= 0)
    {
        std::cout << "Время должно быть больше нуля" << std::endl;
        return;
    }
    battery = battery - minutes / 3;
    if (battery <= 0)
    {
        battery = 0;
        power = false;
        sleepMode = false;
        std::cout << "Батарея разряжена, ноутбук выключился" << std::endl;
    }
    else
    {
        std::cout << "Ноутбук проработал " << minutes << " мин, ";
        std::cout << "заряд " << battery << "%" << std::endl;
    }
}

void Laptop::chargeBattery(int percent)
{
    if (percent <= 0)
    {
        std::cout << "Значение должно быть больше нуля" << std::endl;
        return;
    }
    if (percent > 100)
        percent = 100;
    battery = battery + percent;
    if (battery > 100)
        battery = 100;
    std::cout << "Заряд батареи " << battery << "%" << std::endl;
}

void Laptop::show()
{
    std::cout << "Состояние №" << getState() << ": ";
    switch (getState())
    {
    case 1:
        std::cout << "выключен, крышка закрыта";
        break;
    case 2:
        std::cout << "выключен, крышка открыта";
        break;
    case 3:
        std::cout << "включен, работает";
        break;
    case 4:
        std::cout << "спящий режим, крышка открыта";
        break;
    case 5:
        std::cout << "спящий режим, крышка закрыта";
        break;
    case 6:
        std::cout << "выключен, крышка закрыта, батарея разряжена";
        break;
    case 7:
        std::cout << "выключен, крышка открыта, батарея разряжена";
        break;
    }
    std::cout << std::endl;
    std::cout << "Питание: ";
    if (power == true)
        std::cout << "включено" << std::endl;
    else
        std::cout << "выключено" << std::endl;
    std::cout << "Крышка: ";
    if (lid == true)
        std::cout << "открыта" << std::endl;
    else
        std::cout << "закрыта" << std::endl;
    std::cout << "Спящий режим: ";
    if (sleepMode == true)
        std::cout << "да" << std::endl;
    else
        std::cout << "нет" << std::endl;
    std::cout << "Заряд батареи: " << battery << "%" << std::endl;
}
