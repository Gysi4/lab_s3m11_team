#ifndef LAPTOP_H
#define LAPTOP_H

class Laptop
{
public:
    Laptop();
    Laptop(bool p, bool l, bool s, int b);

    bool getPower();
    bool getLid();
    bool getSleep();
    int getBattery();
    int getState();

    void changePower();
    void changeLid();
    void changeSleep();
    void doWork(int minutes);
    void chargeBattery(int percent);

    void show();

private:
    bool power;
    bool lid;
    bool sleepMode;
    int battery;
};

#endif
