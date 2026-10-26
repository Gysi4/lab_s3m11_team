2#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const int LEN = 64;
const char* INPUT_FILE = "tours.txt";

struct Tour
{
    int id;
    char country[LEN];
    char city[LEN];
    char hotel[LEN];
    int nights;
    float price;
    double rating;
};

int readInt(int min, int max)
{
    int x;
    while (!(cin >> x) || x < min || x > max)
    {
        if (cin.eof())
            exit(0);
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ошибка ввода, повторите: ";
    }
    cin.ignore(1000, '\n');
    return x;
}

double readDouble(double min, double max)
{
    double x;
    while (!(cin >> x) || x < min || x > max)
    {
        if (cin.eof())
            exit(0);
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ошибка ввода, повторите: ";
    }
    cin.ignore(1000, '\n');
    return x;
}

void readString(char* s)
{
    cin.getline(s, LEN);
    while (strlen(s) == 0 || strchr(s, ';') != NULL)
    {
        if (cin.eof())
            exit(0);
        cin.clear();
        cout << "Ошибка ввода, повторите: ";
        cin.getline(s, LEN);
    }
}

bool readFile(Tour*& arr, int& n)
{
    ifstream fin;
    fin.open(INPUT_FILE);
    if (!fin)
    {
        cout << "Файл не найден!" << endl;
        return false;
    }

    char line[500];
    n = 0;
    while (fin.getline(line, 500))
        if (strlen(line) > 5)
            n++;
    fin.clear();
    fin.seekg(0);

    arr = new Tour[n];
    for (int i = 0; i < n; i++)
    {
        fin >> arr[i].id;
        fin.ignore();
        fin.getline(arr[i].country, LEN, ';');
        fin.getline(arr[i].city, LEN, ';');
        fin.getline(arr[i].hotel, LEN, ';');
        fin >> arr[i].nights;
        fin.ignore();
        fin >> arr[i].price;
        fin.ignore();
        fin >> arr[i].rating;
        if (fin.fail())
        {
            cout << "Ошибка в файле, строка " << i + 1 << endl;
            delete[] arr;
            arr = NULL;
            n = 0;
            fin.close();
            return false;
        }
    }
    fin.close();
    cout << "Прочитано записей: " << n << endl;
    return true;
}

int strLength(const char* s)
{
    int k = 0;
    for (int i = 0; s[i] != '\0'; i++)
        if ((s[i] & 0xC0) != 0x80)
            k++;
    return k;
}

void printStr(const char* s, int width)
{
    cout << s;
    for (int i = strLength(s); i < width; i++)
        cout << ' ';
}

void printLine()
{
    cout << "+-----+------+----------------+------------------+"
            "----------------------------+--------+--------------+---------+" << endl;
}

void showTable(Tour* arr, int n)
{
    if (n == 0)
    {
        cout << "Данных нет" << endl;
        return;
    }
    printLine();
    cout << "| "; printStr("№", 3);
    cout << " | "; printStr("ID", 4);
    cout << " | "; printStr("Страна", 14);
    cout << " | "; printStr("Город", 16);
    cout << " | "; printStr("Отель", 26);
    cout << " | "; printStr("Ночей", 6);
    cout << " | "; printStr("Цена, руб.", 12);
    cout << " | "; printStr("Рейтинг", 7);
    cout << " |" << endl;
    printLine();
    for (int i = 0; i < n; i++)
    {
        cout << "| " << left << setw(3) << i + 1 << " | " << setw(4) << arr[i].id << " | ";
        printStr(arr[i].country, 14);
        cout << " | ";
        printStr(arr[i].city, 16);
        cout << " | ";
        printStr(arr[i].hotel, 26);
        cout << " | " << setw(6) << arr[i].nights << " | ";
        cout << fixed << setprecision(2) << setw(12) << arr[i].price << " | ";
        cout << setprecision(1) << setw(7) << arr[i].rating << " |" << endl;
    }
    printLine();
}

void editRecord(Tour* arr, int n)
{
    if (n == 0)
    {
        cout << "Данных нет" << endl;
        return;
    }
    showTable(arr, n);
    cout << "Номер строки для корректировки (0 - отмена): ";
    int row = readInt(0, n);
    if (row == 0)
        return;

    int i = row - 1;
    int field = 1;
    while (field != 0)
    {
        cout << endl;
        cout << "Страна: " << arr[i].country << endl;
        cout << "Город: " << arr[i].city << endl;
        cout << "Отель: " << arr[i].hotel << endl;
        cout << "Ночей: " << arr[i].nights << endl;
        cout << "Цена: " << fixed << setprecision(2) << arr[i].price << endl;
        cout << "Рейтинг: " << setprecision(1) << arr[i].rating << endl;
        cout << endl;
        cout << "Что изменить?" << endl;
        cout << "1 - страна" << endl;
        cout << "2 - город" << endl;
        cout << "3 - отель" << endl;
        cout << "4 - количество ночей" << endl;
        cout << "5 - цена" << endl;
        cout << "6 - рейтинг" << endl;
        cout << "0 - закончить" << endl;
        cout << "Ваш выбор: ";
        field = readInt(0, 6);

        if (field == 1)
        {
            cout << "Новая страна: ";
            readString(arr[i].country);
        }
        else if (field == 2)
        {
            cout << "Новый город: ";
            readString(arr[i].city);
        }
        else if (field == 3)
        {
            cout << "Новый отель: ";
            readString(arr[i].hotel);
        }
        else if (field == 4)
        {
            cout << "Новое количество ночей: ";
            arr[i].nights = readInt(1, 365);
        }
        else if (field == 5)
        {
            cout << "Новая цена: ";
            arr[i].price = readDouble(0, 100000000);
        }
        else if (field == 6)
        {
            cout << "Новый рейтинг (0-5): ";
            arr[i].rating = readDouble(0, 5);
        }
    }
}

void addRecord(Tour*& arr, int& n)
{
    Tour* newArr = new Tour[n + 1];
    int maxId = 0;
    for (int i = 0; i < n; i++)
    {
        newArr[i] = arr[i];
        if (arr[i].id > maxId)
            maxId = arr[i].id;
    }
    newArr[n].id = maxId + 1;

    cout << "Страна: ";
    readString(newArr[n].country);
    cout << "Город: ";
    readString(newArr[n].city);
    cout << "Отель: ";
    readString(newArr[n].hotel);
    cout << "Количество ночей: ";
    newArr[n].nights = readInt(1, 365);
    cout << "Цена: ";
    newArr[n].price = readDouble(0, 100000000);
    cout << "Рейтинг (0-5): ";
    newArr[n].rating = readDouble(0, 5);

    delete[] arr;
    arr = newArr;
    n++;
    cout << "Запись добавлена, id = " << arr[n - 1].id << endl;
}

void deleteRecord(Tour*& arr, int& n)
{
    if (n == 0)
    {
        cout << "Данных нет" << endl;
        return;
    }
    showTable(arr, n);
    cout << "Номер строки для удаления (0 - отмена): ";
    int row = readInt(0, n);
    if (row == 0)
        return;
    cout << "Удалить? (1 - да, 0 - нет): ";
    if (readInt(0, 1) == 0)
        return;

    Tour* newArr = new Tour[n - 1];
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (i != row - 1)
        {
            newArr[k] = arr[i];
            k++;
        }
    }
    delete[] arr;
    arr = newArr;
    n--;
    cout << "Запись удалена" << endl;
}

void calculations(Tour* arr, int n)
{
    if (n == 0)
    {
        cout << "Данных нет" << endl;
        return;
    }
    cout << endl;
    cout << "1 - общая статистика" << endl;
    cout << "2 - статистика по стране" << endl;
    cout << "3 - подбор туров по бюджету" << endl;
    cout << "0 - назад" << endl;
    cout << "Ваш выбор: ";
    int choice = readInt(0, 3);

    if (choice == 1)
    {
        double sumPrice = 0, sumNights = 0, sumRating = 0;
        int iMin = 0, iMax = 0, iBest = 0;
        for (int i = 0; i < n; i++)
        {
            sumPrice += arr[i].price;
            sumNights += arr[i].nights;
            sumRating += arr[i].rating;
            if (arr[i].price < arr[iMin].price)
                iMin = i;
            if (arr[i].price > arr[iMax].price)
                iMax = i;
            if (arr[i].rating > arr[iBest].rating)
                iBest = i;
        }
        cout << fixed << setprecision(2);
        cout << "Количество туров: " << n << endl;
        cout << "Суммарная стоимость: " << sumPrice << " руб." << endl;
        cout << "Средняя стоимость: " << sumPrice / n << " руб." << endl;
        cout << "Средняя длительность: " << sumNights / n << " ночей" << endl;
        cout << "Средний рейтинг: " << sumRating / n << endl;
        cout << "Стоимость одной ночи: " << sumPrice / sumNights << " руб." << endl;
        cout << "Самый дешёвый тур: " << arr[iMin].country << ", " << arr[iMin].city
             << " (" << arr[iMin].price << " руб.)" << endl;
        cout << "Самый дорогой тур: " << arr[iMax].country << ", " << arr[iMax].city
             << " (" << arr[iMax].price << " руб.)" << endl;
        cout << "Лучший рейтинг: " << arr[iBest].hotel << " (" << arr[iBest].rating << ")" << endl;
    }
    else if (choice == 2)
    {
        char country[LEN];
        cout << "Введите страну: ";
        readString(country);
        int count = 0;
        double sumPrice = 0, sumNights = 0, sumRating = 0;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(arr[i].country, country) == 0)
            {
                count++;
                sumPrice += arr[i].price;
                sumNights += arr[i].nights;
                sumRating += arr[i].rating;
            }
        }
        if (count == 0)
        {
            cout << "Туры в эту страну не найдены" << endl;
            return;
        }
        cout << fixed << setprecision(2);
        cout << "Количество туров: " << count << endl;
        cout << "Средняя стоимость: " << sumPrice / count << " руб." << endl;
        cout << "Средняя длительность: " << sumNights / count << " ночей" << endl;
        cout << "Средний рейтинг: " << sumRating / count << endl;
        cout << "Стоимость одной ночи: " << sumPrice / sumNights << " руб." << endl;
    }
    else if (choice == 3)
    {
        cout << "Введите бюджет: ";
        double budget = readDouble(0, 100000000);
        int found = 0;
        cout << fixed << setprecision(2);
        for (int i = 0; i < n; i++)
        {
            if (arr[i].price <= budget)
            {
                cout << arr[i].id << ": " << arr[i].country << ", " << arr[i].city << ", "
                     << arr[i].hotel << " - " << arr[i].price << " руб." << endl;
                found++;
            }
        }
        cout << "Найдено туров: " << found << endl;
    }
}

bool saveData(Tour* arr, int n)
{
    char name[LEN];
    cout << "Введите имя нового файла (пустая строка - отмена): ";
    cin.getline(name, LEN);
    if (strlen(name) == 0)
    {
        cout << "Сохранение отменено" << endl;
        return false;
    }
    if (strcmp(name, INPUT_FILE) == 0)
    {
        cout << "Нельзя перезаписать исходный файл" << endl;
        return false;
    }

    ofstream fout;
    fout.open(name);
    if (!fout)
    {
        cout << "Не удалось создать файл!" << endl;
        return false;
    }
    for (int i = 0; i < n; i++)
    {
        fout << arr[i].id << ";" << arr[i].country << ";" << arr[i].city << ";"
             << arr[i].hotel << ";" << arr[i].nights << ";"
             << fixed << setprecision(2) << arr[i].price << ";"
             << setprecision(1) << arr[i].rating << endl;
    }
    fout.close();
    cout << "Данные сохранены в файл " << name << endl;
    return true;
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Tour* tours = NULL;
    int count = 0;
    bool loaded = false;
    int choice = -1;

    while (choice != 0)
    {
        cout << endl;
        cout << "===== ТУРИЗМ =====" << endl;
        cout << "1 - Чтение данных из файла" << endl;
        cout << "2 - Просмотр данных" << endl;
        cout << "3 - Корректировка записи" << endl;
        cout << "4 - Добавление записи" << endl;
        cout << "5 - Удаление записи" << endl;
        cout << "6 - Вычисления" << endl;
        cout << "7 - Сохранение в новый файл" << endl;
        cout << "0 - Выход" << endl;
        cout << "Ваш выбор: ";
        choice = readInt(0, 7);

        if (choice == 1)
        {
            if (loaded)
                cout << "Данные уже прочитаны" << endl;
            else
                loaded = readFile(tours, count);
        }
        else if (choice == 2)
            showTable(tours, count);
        else if (choice == 3)
            editRecord(tours, count);
        else if (choice == 4)
            addRecord(tours, count);
        else if (choice == 5)
            deleteRecord(tours, count);
        else if (choice == 6)
            calculations(tours, count);
        else if (choice == 7)
        {
            if (count == 0)
                cout << "Нет данных для сохранения" << endl;
            else
                saveData(tours, count);
        }
        else if (choice == 0 && count > 0)
        {
            cout << "Сохранение данных перед выходом" << endl;
            while (!saveData(tours, count))
            {
                cout << "Выйти без сохранения? (1 - да, 0 - нет): ";
                if (readInt(0, 1) == 1)
                    break;
            }
        }
    }

    delete[] tours;
    tours = NULL;
    return 0;
}
