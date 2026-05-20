#include <iostream>
#include <Windows.h>
using namespace std;
int slt = 650;
struct intST {
    int arr[10];
    int top;
    int MAXsize;
    int fill;
};

void intST_push(intST &stack, int n)
{
    if (stack.top < stack.MAXsize)
    {
        stack.top++;
        stack.arr[stack.top] = n;
        
    }
    else
    {
        cout << "Стек переполнен\n";
    }
    return;
}

void intST_pop(intST &stack)
{
    if (stack.top >= 0)
    { 
        stack.arr[stack.top] = NULL;
        stack.top--;
    }
    else
    {
        cout << "Стек уже пуст\n";
    }
    return;
}

int intST_top(intST &stack)
{
    return stack.arr[stack.top];
}

int intST_size(intST &stack)
{
    int i, c = 0;
    for (i = 0; i < stack.MAXsize; i++)
    {
        if (stack.arr[i])
            c++;
        else
            break;
    }
    return c;
}

void stacks_out(intST& s1, intST& s2)
{
    for (int i = s1.MAXsize - 1; i >= 0 ; i--)
    {
        if (s1.arr[i])
            cout << s1.arr[i];
        else
            cout << "  ";
        cout << " | ";
        if (s2.arr[i])
            cout << s2.arr[i];
        else
            cout << "  ";
        cout << '\n';
    }
}

void stacks_replace(intST& s1, intST& s2)
{
    if (s1.fill != 0 && s2.fill != 2)
    {
        int n = intST_top(s1);
        intST_push(s2, n);
        intST_pop(s1);
    }
    else if (s1.fill == 0)
    {
        cout << "\nПередающий стек пуст";
        Sleep(slt);
    }
    else if (s2.fill == 2)
    {
        cout << "\nПолучающий стек уже полон";
        Sleep(slt);
    }
       
}

void int_stack()
{
    int ch1, ch2, n;
    intST s1 = { {5, 8, 10, 34, 76, 54}, 5, 10, 1 };

    intST s2 = { {56, 43, 14, 24}, 3, 10, 1 };

    bool quit = false;
    do
    {
        system("cls");
        stacks_out(s1, s2);
        cout << "\n\n** Меню **\n";
        cout << "1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Переложить элемент\n";
        cout << "0. Назад\n";
        cout << "Выберите действие: "; cin >> ch1;
        cout << '\n';
        switch (ch1)
        {
        case 1:
            cout << "1. Левый стек\n";
            cout << "2. Правый стек\n";
            cout << "?: "; cin >> ch2;
            switch (ch2)
            {
            case 1:
                cout << "\nВведите n: "; cin >> n;
                intST_push(s1, n);
                Sleep(slt);
                break;
            case 2:
                cout << "\nВведите n: "; cin >> n;
                intST_push(s2, n);
                Sleep(slt);
                break;
            default:
                cout << "\nОтмена...";
                Sleep(slt);
            }
            break;
        case 2:
            cout << "1. Левый стек\n";
            cout << "2. Правый стек\n";
            cout << "?: "; cin >> ch2;
            switch (ch2)
            {
            case 1:
                intST_pop(s1);
                Sleep(slt);
                break;
            case 2:
                intST_pop(s2);
                Sleep(slt);
                break;
            default:
                cout << "\nОтмена...";
                Sleep(slt);
            }
            break;
        case 3:
            cout << "1. Левый стек\n";
            cout << "2. Правый стек\n";
            cout << "?: "; cin >> ch2;
            switch (ch2)
            {
            case 1:
                stacks_replace(s1, s2);
                Sleep(slt);
                break;
            case 2:
                stacks_replace(s2, s1);
                Sleep(slt);
                break;
            default:
                cout << "\nОтмена...";
                Sleep(slt);
            }
            break;
        case 0:
            quit = true;
            break;
        default:
            cout << "\nОшибка";
            Sleep(slt);
        }
    } while (!quit);
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
    cout << "** Меню **\n";
    cout << "1. Стек простых чисел\n";
    cout << "2. Скобочная структура ()\n";
    cout << "3. Скобочная структура (){}[]\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: "; cin >> choice;
    return choice;
}
int main()
{
    system("chcp 1251");
    
    bool quit = false;
    do
    {
        system("cls");
        int choice = menu();
        switch (choice)
        {
        case 1:
            system("cls");
            int_stack();
            break;
        case 2:
            system("cls");
            brackets_check();
            break;
        case 3:
            system("cls");
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
