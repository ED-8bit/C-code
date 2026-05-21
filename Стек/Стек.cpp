#include <iostream>
#include <Windows.h>
using namespace std;
int slt = 650;

struct intST {
    int arr[5];
    int top = 0;
    int MAXsize = 5;
    int fill = 0;
};

void intST_push(intST &stack, int n)
{
    if (stack.top < stack.MAXsize)
    {
        stack.arr[stack.top] = n;
        stack.top++;
        if (stack.top == stack.MAXsize)
            stack.fill = 2;
        else
            stack.fill = 1;
    }
    else
    {
        cout << "Стек переполнен\n";
        Sleep(slt);
    }
    return;
}

void intST_pop(intST &stack)
{
    if (stack.top > 0)
    { 
        stack.top--;
        stack.arr[stack.top] = NULL;
        if (stack.top == 0)
            stack.fill = 0;
        else
            stack.fill = 1;
    }
    else
    {
        cout << "Стек уже пуст\n";
        Sleep(slt);
    }
    return;
}

int intST_top(intST stack)
{
    return stack.arr[stack.top - 1];
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
    intST s1 = {};

    intST s2 = {};

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
            cout << "1. В левый стек\n";
            cout << "2. В правый стек\n";
            cout << "Выбор: "; cin >> ch2;
            switch (ch2)
            {
            case 1:
                cout << "\nВведите n: "; cin >> n;
                intST_push(s1, n);
                
                break;
            case 2:
                cout << "\nВведите n: "; cin >> n;
                intST_push(s2, n);
                
                break;
            default:
                cout << "\nОтмена...";
                Sleep(slt);
            }
            break;
        case 2:
            cout << "1. Из левого стека\n";
            cout << "2. Из правого стека\n";
            cout << "Выбор: "; cin >> ch2;
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
            cout << "1. Из левого стека\n";
            cout << "2. Из правого стека\n";
            cout << "Выбор: "; cin >> ch2;
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


struct charST {
    char arr[80];
    int top = 0;
    int MAXsize = 80;
    int fill = 0;
};

void charST_push(charST& s1, char n)
{
    if (s1.top < s1.MAXsize)
    {
        s1.arr[s1.top] = n;
        s1.top++;
        if (s1.top == s1.MAXsize)
            s1.fill = 2;
        else
            s1.fill = 1;
    }
    else
    {
        cout << "Стек переполнен\n";
        Sleep(slt);
    }
    return;
}

void charST_pop(charST& s1)
{
    if (s1.top > 0)
    {
        s1.top--;
        s1.arr[s1.top] = NULL;
        if (s1.top == 0)
            s1.fill = 0;
        else
            s1.fill = 1;
    }
    else
    {
        cout << "Стек уже пуст\n";
        Sleep(slt);
    }
    return;
}

char charST_top(charST s1)
{
    return s1.arr[s1.top - 1];
}

int charST_size(charST& s1)
{
    int i, c = 0;
    for (i = 0; i < s1.MAXsize; i++)
    {
        if (s1.arr[i])
            c++;
        else
            break;
    }
    return c;
}

void charST_out(charST& s1)
{
    for (int i = 0; i < s1.MAXsize; i++)
        if (s1.arr[i])
        {
            if (i == 0)
                cout << s1.arr[i];
            else
                cout << ", " << s1.arr[i];
        }
    cout << '\n';
            
}

bool brackets(char str[])
{
    charST s1;
    int i, open = 0, close = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '(' || str[i] == ')')
            charST_push(s1, str[i]);
    }

    for (i = 0; i < s1.MAXsize; i++)
    {
        if (s1.arr[i] == '(')
            open++;
        else if (s1.arr[i] == ')')
            close++;
        if (close > open)
        {
            return false;
        }
    }
    if (close == open)
        return true;
    else
        return false;
}

void brackets_check()
{
    char str[80] = "Hello world :)\0";
    bool quit = false;
    int ch;
    do
    {
        system("cls");
        cout << "Текущая строка: " << str << "\n\n";
        cout << "1. Ввести новую строку\n";
        cout << "2. Проверить правильность скобочной структуры\n";
        cout << "0. Назад\n";
        cout << "Выбор: "; cin >> ch;
        cout << '\n';
        switch (ch)
        {
        case 1:
            cin.ignore();
            cout << "Введите строку: ";
            cin.getline(str, 80);
            break;
        case 2:
            cout << '\n';
            if (brackets(str))
                cout << "Структура правильная";
            else
                cout << "Ошибка в структуре";
            Sleep(slt);
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
