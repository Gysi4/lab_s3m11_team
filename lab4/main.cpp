#include <iostream>
#include "Laptop.h"

void action(Laptop &x)
{
    int command, value;
    std::cout << "1 - Включить/выключить" << std::endl;
    std::cout << "2 - Открыть/закрыть крышку" << std::endl;
    std::cout << "3 - Включить/выключить спящий режим" << std::endl;
    std::cout << "4 - Работать" << std::endl;
    std::cout << "5 - Зарядить" << std::endl;
    std::cout << "Введите номер действия->";
    std::cin >> command;
    switch (command)
    {
    case 1:
        x.changePower();
        break;
    case 2:
        x.changeLid();
        break;
    case 3:
        x.changeSleep();
        break;
    case 4:
        std::cout << "Сколько минут работать? ";
        std::cin >> value;
        x.doWork(value);
        break;
    case 5:
        std::cout << "На сколько процентов зарядить? ";
        std::cin >> value;
        x.chargeBattery(value);
        break;
    default:
        std::cout << "Нет такого действия" << std::endl;
    }
}

int main()
{
    int work = 1, command;
    Laptop lap;
    Laptop mas[10];
    int n = 0, k, i, number;
    int pp, ll, ss, bb;
    int working, sleeping, off, sum, maxNumber;
    double average;

    while (work)
    {
        std::cout << std::endl;
        std::cout << "Меню" << std::endl;
        std::cout << "1 - Создать ноутбук (конструктор по умолчанию)" << std::endl;
        std::cout << "2 - Создать ноутбук (конструктор с параметрами)" << std::endl;
        std::cout << "3 - Показать состояние ноутбука" << std::endl;
        std::cout << "4 - Выполнить действие над ноутбуком" << std::endl;
        std::cout << "5 - Создать массив ноутбуков" << std::endl;
        std::cout << "6 - Показать массив ноутбуков" << std::endl;
        std::cout << "7 - Выполнить действие над ноутбуком из массива" << std::endl;
        std::cout << "8 - Статистика по массиву" << std::endl;
        std::cout << "9 - Зарядить все ноутбуки массива" << std::endl;
        std::cout << "0 - Выход" << std::endl;
        std::cout << "Введите номер команды->";
        std::cin >> command;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            command = -1;
        }
        switch (command)
        {
        case 1:
            lap = Laptop();
            std::cout << "Ноутбук создан" << std::endl;
            break;
        case 2:
            std::cout << "Питание (1 - включено, 0 - выключено): ";
            std::cin >> pp;
            std::cout << "Крышка (1 - открыта, 0 - закрыта): ";
            std::cin >> ll;
            std::cout << "Спящий режим (1 - да, 0 - нет): ";
            std::cin >> ss;
            std::cout << "Заряд батареи (0-100): ";
            std::cin >> bb;
            lap = Laptop(pp == 1, ll == 1, ss == 1, bb);
            std::cout << "Ноутбук создан" << std::endl;
            break;
        case 3:
            lap.show();
            break;
        case 4:
            action(lap);
            break;
        case 5:
            std::cout << "Сколько ноутбуков создать (1-10)? ";
            std::cin >> k;
            if (k < 1 || k > 10)
                std::cout << "Неверное количество" << std::endl;
            else
            {
                n = k;
                for (i = 0; i < n; i++)
                {
                    std::cout << "Ноутбук " << i + 1 << std::endl;
                    std::cout << "Питание (1 - включено, 0 - выключено): ";
                    std::cin >> pp;
                    std::cout << "Крышка (1 - открыта, 0 - закрыта): ";
                    std::cin >> ll;
                    std::cout << "Спящий режим (1 - да, 0 - нет): ";
                    std::cin >> ss;
                    std::cout << "Заряд батареи (0-100): ";
                    std::cin >> bb;
                    mas[i] = Laptop(pp == 1, ll == 1, ss == 1, bb);
                }
                std::cout << "Массив создан" << std::endl;
            }
            break;
        case 6:
            if (n == 0)
                std::cout << "Массив пустой" << std::endl;
            else
            {
                for (i = 0; i < n; i++)
                {
                    std::cout << "Ноутбук " << i + 1 << std::endl;
                    mas[i].show();
                }
            }
            break;
        case 7:
            if (n == 0)
                std::cout << "Массив пустой" << std::endl;
            else
            {
                std::cout << "Номер ноутбука (1-" << n << "): ";
                std::cin >> number;
                if (number < 1 || number > n)
                    std::cout << "Нет такого ноутбука" << std::endl;
                else
                    action(mas[number - 1]);
            }
            break;
        case 8:
            if (n == 0)
                std::cout << "Массив пустой" << std::endl;
            else
            {
                working = 0;
                sleeping = 0;
                off = 0;
                sum = 0;
                maxNumber = 0;
                for (i = 0; i < n; i++)
                {
                    if (mas[i].getPower() == false)
                        off++;
                    else if (mas[i].getSleep() == true)
                        sleeping++;
                    else
                        working++;
                    sum = sum + mas[i].getBattery();
                    if (mas[i].getBattery() > mas[maxNumber].getBattery())
                        maxNumber = i;
                }
                average = (double)sum / n;
                std::cout << "Всего ноутбуков: " << n << std::endl;
                std::cout << "Работают: " << working << std::endl;
                std::cout << "В спящем режиме: " << sleeping << std::endl;
                std::cout << "Выключены: " << off << std::endl;
                std::cout << "Средний заряд: " << average << "%" << std::endl;
                std::cout << "Самый заряженный ноутбук: " << maxNumber + 1;
                std::cout << " (" << mas[maxNumber].getBattery() << "%)" << std::endl;
            }
            break;
        case 9:
            if (n == 0)
                std::cout << "Массив пустой" << std::endl;
            else
            {
                std::cout << "На сколько процентов зарядить? ";
                std::cin >> number;
                for (i = 0; i < n; i++)
                {
                    std::cout << "Ноутбук " << i + 1 << ": ";
                    mas[i].chargeBattery(number);
                }
            }
            break;
        case 0:
            work = 0;
            break;
        default:
            std::cout << "Нет такой команды" << std::endl;
        }
    }
    return 0;
}
