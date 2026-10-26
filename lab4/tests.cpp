#include <iostream>
#include "Laptop.h"

int all = 0;
int ok = 0;

void check(int expected, int result)
{
    all++;
    std::cout << "Ожидается: " << expected << ", получено: " << result;
    if (expected == result)
    {
        ok++;
        std::cout << " - тест пройден" << std::endl;
    }
    else
        std::cout << " - ТЕСТ НЕ ПРОЙДЕН" << std::endl;
    std::cout << std::endl;
}

int main()
{
    Laptop a;

    std::cout << "Тест 1. Конструктор по умолчанию, номер состояния" << std::endl;
    check(1, a.getState());

    std::cout << "Тест 2. Конструктор по умолчанию, заряд батареи" << std::endl;
    check(50, a.getBattery());

    std::cout << "Тест 3. Конструктор с параметрами (1, 1, 0, 80), номер состояния"
              << std::endl;
    a = Laptop(true, true, false, 80);
    check(3, a.getState());

    std::cout << "Тест 4. Конструктор (1, 0, 0, 50): крышка закрыта, должен быть сон"
              << std::endl;
    a = Laptop(true, false, false, 50);
    check(5, a.getState());

    std::cout << "Тест 5. Конструктор (0, 1, 1, 50): выключен, сон сбрасывается"
              << std::endl;
    a = Laptop(false, true, true, 50);
    check(2, a.getState());

    std::cout << "Тест 6. Конструктор (1, 1, 1, 0): заряд 0, ноутбук выключен"
              << std::endl;
    a = Laptop(true, true, true, 0);
    check(7, a.getState());

    std::cout << "Тест 7. Конструктор (1, 1, 1, 150): номер состояния" << std::endl;
    a = Laptop(true, true, true, 150);
    check(4, a.getState());

    std::cout << "Тест 8. Конструктор (1, 1, 1, 150): заряд ограничивается до 100"
              << std::endl;
    check(100, a.getBattery());

    std::cout << "Тест 9. Конструктор (0, 0, 0, -10): заряд ограничивается до 0"
              << std::endl;
    a = Laptop(false, false, false, -10);
    check(0, a.getBattery());

    std::cout << "Тест 10. Переход 1 -> 2 (открыть крышку)" << std::endl;
    a = Laptop();
    a.changeLid();
    check(2, a.getState());

    std::cout << "Тест 11. Переход 2 -> 1 (закрыть крышку)" << std::endl;
    a.changeLid();
    check(1, a.getState());

    std::cout << "Тест 12. Переход 2 -> 3 (включить)" << std::endl;
    a.changeLid();
    a.changePower();
    check(3, a.getState());

    std::cout << "Тест 13. Переход 3 -> 2 (выключить)" << std::endl;
    a.changePower();
    check(2, a.getState());

    std::cout << "Тест 14. Переход 3 -> 4 (спящий режим)" << std::endl;
    a.changePower();
    a.changeSleep();
    check(4, a.getState());

    std::cout << "Тест 15. Переход 4 -> 3 (выход из спящего режима)" << std::endl;
    a.changeSleep();
    check(3, a.getState());

    std::cout << "Тест 16. Переход 3 -> 5 (закрыть крышку при работе)" << std::endl;
    a.changeLid();
    check(5, a.getState());

    std::cout << "Тест 17. Переход 5 -> 3 (открыть крышку)" << std::endl;
    a.changeLid();
    check(3, a.getState());

    std::cout << "Тест 18. Переход 4 -> 5 (закрыть крышку в спящем режиме)"
              << std::endl;
    a.changeSleep();
    a.changeLid();
    check(5, a.getState());

    std::cout << "Тест 19. Переход 5 -> 1 (выключить при закрытой крышке)" << std::endl;
    a.changePower();
    check(1, a.getState());

    std::cout << "Тест 20. Переход 4 -> 2 (выключить из спящего режима)" << std::endl;
    a = Laptop(true, true, true, 50);
    a.changePower();
    check(2, a.getState());

    std::cout << "Тест 21. Переход 3 -> 7 (батарея разрядилась при работе)"
              << std::endl;
    a = Laptop(true, true, false, 10);
    a.doWork(30);
    check(7, a.getState());

    std::cout << "Тест 22. Переход 6 -> 7 (открыть крышку)" << std::endl;
    a = Laptop(false, false, false, 0);
    a.changeLid();
    check(7, a.getState());

    std::cout << "Тест 23. Переход 7 -> 6 (закрыть крышку)" << std::endl;
    a.changeLid();
    check(6, a.getState());

    std::cout << "Тест 24. Переход 6 -> 1 (зарядить)" << std::endl;
    a.chargeBattery(20);
    check(1, a.getState());

    std::cout << "Тест 25. Переход 7 -> 2 (зарядить)" << std::endl;
    a = Laptop(false, true, false, 0);
    a.chargeBattery(20);
    check(2, a.getState());

    std::cout << "Тест 26. Состояние 1: включить при закрытой крышке нельзя"
              << std::endl;
    a = Laptop();
    a.changePower();
    check(1, a.getState());

    std::cout << "Тест 27. Состояние 6: включить при разряженной батарее нельзя"
              << std::endl;
    a = Laptop(false, false, false, 0);
    a.changePower();
    check(6, a.getState());

    std::cout << "Тест 28. Состояние 5: выйти из сна при закрытой крышке нельзя"
              << std::endl;
    a = Laptop(true, false, true, 50);
    a.changeSleep();
    check(5, a.getState());

    std::cout << "Тест 29. Состояние 2: работать выключенный ноутбук не может"
              << std::endl;
    a = Laptop(false, true, false, 50);
    a.doWork(60);
    check(50, a.getBattery());

    std::cout << "Тест 30. Состояние 4: в спящем режиме заряд не тратится" << std::endl;
    a = Laptop(true, true, true, 50);
    a.doWork(60);
    check(50, a.getBattery());

    std::cout << "Тест 31. Состояние 3: работа 30 минут, заряд 50 -> 40" << std::endl;
    a = Laptop(true, true, false, 50);
    a.doWork(30);
    check(40, a.getBattery());

    std::cout << "Тест 32. Состояние 3: после работы 30 минут состояние не изменилось"
              << std::endl;
    check(3, a.getState());

    std::cout << "Тест 33. Время работы 0 минут, заряд не меняется" << std::endl;
    a.doWork(0);
    check(40, a.getBattery());

    std::cout << "Тест 34. Зарядка 70% при заряде 50%, заряд ограничивается до 100"
              << std::endl;
    a = Laptop();
    a.chargeBattery(70);
    check(100, a.getBattery());

    std::cout << "Тест 35. Зарядка на отрицательное значение, заряд не меняется"
              << std::endl;
    a = Laptop();
    a.chargeBattery(-5);
    check(50, a.getBattery());

    std::cout << "Итого: пройдено " << ok << " из " << all << std::endl;
    return 0;
}
