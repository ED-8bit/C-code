#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const int SIZE = 100;
struct inv_type 
{
    char item[40];
    double cost;
    double retail;
    int on_hand;
    int lead_time;
} invtry[SIZE];

void init_list()
{
    int t;
    for (t = 0; t < SIZE; t++)
        *invtry[t].item = '\0';
}

char menu()
{
    char ch;
    cout << '\n';
    do
    {
        system("cls");
        cout << "(E)nter\n";
        cout << "(D)isplay\n";
        cout << "(U)pdate\n";
        cout << "(Q)uit\n\n";
        cout << "Выберите команду: "; cin >> ch;
    } while (!strchr("eduq", tolower(ch)));
    return tolower(ch);
}

void input( int i)
{
    cout << "Товар: "; cin >> invtry[i].item;
    cout << "Стоимость: "; cin >> invtry[i].cost;
    cout << "Розничная цена: "; cin >> invtry[i].retail;
    cout << "В наличии: "; cin >> invtry[i].on_hand;
    cout << "Время до пополнения запасов (в днях): "; cin >> invtry[i].lead_time;
}
void enter()
{
    int i;
    cout << '\n';
    for (i = 0; i < SIZE; i++)
        if (!*invtry[i].item) break;
    if (i == SIZE)
    {
        cout << "Список полон.\n"; return;
    }
    input(i);
}

void update()
{
    int i;
    char name[80];
    cout << "Введите наименование товара: ";
    cin >> name;
    for (i = 0; i < SIZE; i++)
        if (!strcmp(name, invtry[i].item)) 
            break;
    if (i == SIZE)
    {
        cout << "Товар не найден.\n"; return;
    }
    cout << "Введите новую информацию.\n";
    input(i);
}

void display()
{
    int t;

    for (t = 0; t < SIZE; t++)
    {
        if (*invtry[t].item)
        {
            cout << "\n\nНаименование: " << invtry[t].item << '\n';
            cout << "Стоимость: " << invtry[t].cost << '\n';
            cout << "В розницу: " << invtry[t].retail << '\n';
            cout << "В наличии: " << invtry[t].on_hand << '\n';
            cout << "До пополнения осталось: " << invtry[t].lead_time << " дней" << '\n' << '\n';
        }
    }
    system("pause");

}

int main()
{
    system("chcp 1251");
    char choice;
    init_list();
    for (;;)
    {
        choice = menu();

        switch (choice)
        {
        case 'e':
            enter();
            break;
        case 'd':
            display();
            break;
        case 'u':
            update();
            break;
        case 'q':
            return 0;
        }

    }
}

    

