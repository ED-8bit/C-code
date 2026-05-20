#include <iostream>
#include <Windows.h>
using namespace std;

struct int_stack {

};



void int_stack()
{

}

void brackets_check()
{

}

void brackets_check_f()
{

}













int menu()
{
    int choice;
    cout << "** Меню **";
    cout << "1. Стек простых чисел\n";
    cout << "2. Скобочная структура ()\n";
    cout << "3. Скобочная структура (){}[]\n";
    cout << "Выберите действие: "; cin >> choice;
    return choice;
}
int slt = 650;
int main()
{
    bool quit = false;
    do
    {
        int choice = menu();
        switch (choice)
        {
        case 1:
            int_stack();
            break;
        case 2:
            brackets_check();
            break;
        case 3:
            brackets_check_f();
            break;
        case 0:
            quit = true;
            break;
        default:
            cout << "\n Ошибка";
            Sleep(slt);
        }
    } while (!quit);
    return 0;
}
