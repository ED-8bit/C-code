#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

/*const int SIZE = 100;
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
}*/


const int SIZE = 7;
struct routes
{
    char name[80];
    char dest[80];
    int route_n;
}aeroflot[SIZE];
void aeroflot_init()
{
    int t;
    for (t = 0; t < SIZE; t++)
        *aeroflot[t].name = '\0';
}
char aeroflot_menu()
{
    char ch;
    cout << '\n';
    do
    {
        system("cls");
        cout << "(E)nter\n";
        cout << "(D)isplay\n";
        cout << "(S)elected display";
        cout << "(U)pdate\n";
        cout << "(Q)uit\n\n";
        cout << "Выберите команду: "; cin >> ch;
    } while (!strchr("eduq", tolower(ch)));
    return tolower(ch);
}

void aeroflot_input(int i)
{
    cout << "Название самолета: "; cin >> aeroflot[i].name;
    cout << "Номер рейса: "; cin >> aeroflot[i].route_n;
    cout << "Пункт назначения: "; cin >> aeroflot[i].dest;
    
}
void aeroflot_enter()
{
    int i;
    cout << '\n';
    for (i = 0; i < SIZE; i++)
        if (!*aeroflot[i].name) break;
    if (i == SIZE)
    {
        cout << "Список полон.\n"; return;
    }
    aeroflot_input(i);
}
void aeroflot_update()
{
    int i;
    char name[80];
    cout << "Введите наименование товара: ";
    cin >> name;
    for (i = 0; i < SIZE; i++)
        if (!strcmp(name, aeroflot[i].name))
            break;
    if (i == SIZE)
    {
        cout << "Товар не найден.\n"; return;
    }
    cout << "Введите новую информацию.\n";
    aeroflot_input(i);
}

void aeroflot_display()
{
    int t;

    for (t = 0; t < SIZE; t++)
    {
        if (*aeroflot[t].name)
        {
            cout << "\n\nНазвание самолета: " << aeroflot[t].name << '\n';
            cout << "Номер рейса: " << aeroflot[t].route_n << '\n';
            cout << "Пункт назначения: " << aeroflot[t].dest << '\n';
        }
    }
    system("pause");

}

void aeroflot_selected_display()
{
    int t;
    char name[80];
    cout << "Введите тип самолета: ";
    cin.ignore();
   
    for (t = 0; t < SIZE; t++)
    {
        if (*aeroflot[t].name)
        {
            cout << "\n\nНазвание самолета: " << aeroflot[t].name << '\n';
            cout << "Номер рейса: " << aeroflot[t].route_n << '\n';
            cout << "Пункт назначения: " << aeroflot[t].dest << '\n';
        }
    }
    system("pause");
}

void AEROFLOT()
{
    system("chcp 1251");
    bool quit = false;
    char choice;
    aeroflot_init();
    while(!quit)
    {
        choice = aeroflot_menu();

        switch (choice)
        {
        case 'e':
            aeroflot_enter();
            break;
        case 'd':
            aeroflot_display();
            break;
        case 's':
            aeroflot_selected_display();
            break;
        case 'u':
            aeroflot_update();
            break;
        case 'q':
            quit = true;
            break;
        }
    }
    














}

void task_2()
{

}

void task_3()
{

}

void task_4()
{

}

void task_5()
{

}

void task_6()
{

}



int menu()
{
    int choice;
    cout << "** Меню **\n";
    cout << "1. AEROFLOT\n";
    cout << "2. e\n";
    cout << "3. Функция для квадратного уравнения\n";
    cout << "4. Функция для выставления нижнего регистра строки\n";
    cout << "5. Функции для работы с дробями\n";
    cout << "6. Функция для возврата простых делителей\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
    cin >> choice;
    return choice;
}

int main()
{
    system("chcp 1251");
    int choice;
    do
    {
        system("cls");
        choice = menu();
        switch (choice)
        {
        case 1:
            system("cls");
            AEROFLOT();
            system("pause");
            break;
        case 2:
            system("cls");
            task_2();
            system("pause");
            break;
        case 3:
            system("cls");
            task_3();
            system("pause");
            break;
        case 4:
            system("cls");
            task_4();
            system("pause");
            break;
        case 5:
            system("cls");
            task_5();
            system("pause");
            break;
        case 6:
            system("cls");
            task_6();
            system("pause");
            break;
        case 0:
            system("cls");
            break;
        default:
            cout << "\n ОШИБКА";
            break;
        }
    } while (choice != 0);

    return 0;
}






    

