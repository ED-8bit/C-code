#include <iostream>
#include <cstring>
#include <cctype>
#include <Windows.h>

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

const int Aeroflot_size = 7;
struct routes
{
    char name[80];
    char dest[80];
    int route_n;
};

routes aeroflot[Aeroflot_size] = {
        {"Airbus", "Stambul", 85},
        {"Boeing", "Moscow", 92},
        {"RyanAIR", "Sochi", 78},
        {"BELUGA", "Chechnya", 95},
        {"B2", "London", 88}
};


void init_routes_arr(routes *route, int size)
{
    int t;
    for (t = 0; t < size; t++)
        *route[t].name = '\0';
}
char structs_menu(int n)
{
    char ch;
    cout << '\n';
    do
    {
        system("cls");
        cout << "(E)nter\n";
        cout << "(D)isplay\n";
        cout << "(S)elected display\n";
        cout << "(U)pdate\n";
        if (n == 2)
            cout << "(R)eview\n";
        cout << "(Q)uit\n\n";
        cout << "Выберите команду: "; cin >> ch;
    } while (!strchr("edusqr", tolower(ch)));
    return tolower(ch);
}

void sort_routes_arr(routes *route, int size)
{
    int i, j, max = 0;

    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            
            if (strcmp(route[j].dest, route[j + 1].dest) > 0)
            {
                swap(route[j], route[j + 1]);
            }
        }
    }
}
void aeroflot_input(int i)
{
    cout << "Номер рейса: "; cin >> aeroflot[i].route_n;
    cout << "Тип самолета: "; cin >> aeroflot[i].name;
    cout << "Пункт назначения: "; cin >> aeroflot[i].dest;
    
}
void aeroflot_enter()
{
    int i;
    cout << '\n';
    for (i = 0; i < Aeroflot_size; i++)
        if (!*aeroflot[i].name) break;
    if (i == Aeroflot_size)
    {
        cout << "Список полон.\n"; return;
        Sleep(450);
    }
    aeroflot_input(i);
}
void aeroflot_update()
{
    int i;
    char name[80];
    cout << '\n';
    cout << "Введите тип самолета: ";
    cin >> name;
    for (i = 0; i < Aeroflot_size; i++)
        if (!strcmp(name , aeroflot[i].name))
            break;
    if (i == Aeroflot_size)
    {
        cout << "Рейс не найден.\n"; return;
        Sleep(450);
    }
    cout << "Введите новую информацию.\n";
    aeroflot_input(i);
}
void aeroflot_display()
{
    int t;
    sort_routes_arr(aeroflot, Aeroflot_size);
    cout << "\n-----------------------------------------------------------------\n";
    for (t = 0; t < Aeroflot_size; t++)
    {
        if (*aeroflot[t].name)
        {
            cout << "\nНомер рейса: " << aeroflot[t].route_n << "\n\n";
            cout << "Тип самолета: " << aeroflot[t].name << '\n';
            cout << "Пункт назначения: " << aeroflot[t].dest << "\n\n";
            cout << "-----------------------------------------------------------------\n";
        }
    }
    cout << '\n';
    
    system("pause");

}
void aeroflot_selected_display()
{
    int i;
    char name[80];
    cout << "\nВведите тип самолета: ";
    cin >> name;
   
    for (i = 0; i < Aeroflot_size; i++)
        if (!strcmp(name, aeroflot[i].name))
            break;
    if (i == Aeroflot_size)
    {
        cout << "Рейс не найден.\n"; return;
        Sleep(450);
    }
    cout << "\n-----------------------------------------------------------------\n";
    cout << "\nНомер рейса: " << aeroflot[i].route_n << '\n';
    cout << "\nТип самолета : " << aeroflot[i].name << '\n';
    cout << "Пункт назначения: " << aeroflot[i].dest << '\n';
    cout << "\n-----------------------------------------------------------------\n";
    system("pause");
}
void AEROFLOT()
{
    bool quit = false;
    char choice;
    if (!aeroflot[0].name)
        init_routes_arr(aeroflot, Aeroflot_size);
    while(!quit)
    {
        choice = structs_menu(1);

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

const int CoupleSize = 20;
struct student
{
    char family_name[80];
    char name[50];
    char surname[60];
    int group_n;
    char exams[4];
};

void sort_students_arr(student* students, int size)
{
    int i, j, max = 0;

    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {

            if (strcmp(students[j].family_name, students[j + 1].family_name) > 0)
            {
                swap(students[j], students[j + 1]);
            }
        }
    }
}
void student_input(student* students,int i)
{
    cout << "Фамилия: "; cin >> students[i].family_name;
    cout << "Имя: "; cin >> students[i].name;
    cout << "Отчество: "; cin >> students[i].surname;
    cout << "Номер группы: "; cin >> students[i].group_n;
    cout << "Оценка по математике: "; cin >> students[i].exams[0];
    cout << "Оценка по программированию: "; cin >> students[i].exams[1];
    cout << "Оценка по экономике: "; cin >> students[i].exams[2];
} // +
void init_students_arr(student* students, int CoupleSize)
{
    int t;
    for (t = 0; t < CoupleSize; t++)
        *students[t].family_name = '\0';
} 
void students_enter(student* students, int CoupleSize)
{
    int i;
    cout << '\n';
    for (i = 0; i < CoupleSize; i++)
        if (!*students[i].family_name) break;
    if (i == CoupleSize)
    {
        cout << "Список полон.\n"; return;
        Sleep(450);
    }
    student_input(students, i);
}
void students_update(student* students, int CoupleSize)
{
    int i;
    char name[80];
    char family_name[80];
    cout << '\n';
    cout << "Введите имя: ";
    cin >> name;
    cout << "\nВведите фамилию: ";
    cin >> family_name;
    for (i = 0; i < CoupleSize; i++)
        if (!strcmp(name, students[i].name) && (!strcmp(family_name, students[i].family_name)))
            break;
    if (i == CoupleSize)
    {
        cout << "Студент не найден.\n"; return;
        Sleep(450);
    }
    cout << "Введите новую информацию.\n";
    student_input(students,i);
}
void student_display(student* students, int CoupleSize)
{
    int t;
    sort_students_arr(students, CoupleSize);
    cout << "\n-----------------------------------------------------------------\n";
    for (t = 0; t < CoupleSize; t++)
    {
        if (*students[t].name)
        {
            cout << "\nСтудент: " << students[t].family_name << ' ' << students[t].name << ' ' << students[t].surname << '\n';
            cout << "Группа: " << students[t].group_n << '\n';
            cout << "Математика: " << students[t].exams[0] << "\nПрограммирование: " << students[t].exams[1] << "\nЭкономика: " << students[t].exams[2] << "\n\n";
            cout << "-----------------------------------------------------------------\n";
        }
    }
    cout << '\n';

    system("pause");

}
void student_selected_display(student* students, int CoupleSize)
{
    int i;
    char name[80];
    char family_name[80];
    cout << "Введите имя: ";
    cin >> name;
    cout << "\nВведите фамилию: ";
    cin >> family_name;
    for (i = 0; i < CoupleSize; i++)
        if (!strcmp(name, students[i].name) && (!strcmp(family_name, students[i].family_name)))
            break;
    if (i == CoupleSize)
    {
        cout << "Студент не найден\n"; return;
    }
    cout << "\n-----------------------------------------------------------------\n";
    cout << "\nСтудент: " << students[i].family_name << ' ' << students[i].name << ' ' << students[i].surname << '\n';
    cout << "Группа: " << students[i].group_n << '\n';
    cout << "Математика: " << students[i].exams[0] << "\nПрограммирование: " << students[i].exams[1] << "\nЭкономика: " << students[i].exams[2] << "\n\n";
    cout << "\n-----------------------------------------------------------------\n";
    system("pause");
}
void students_review(student* students, int CoupleSize)
{
    int i, j, c;
    double r, st = 0, best = 0;
    for (i = 0; i < CoupleSize; i++)
    {
        if (*students[i].name)
        {
            st += 1;
            c = 0;
            for (j = 0; j < 3; j++)
            { 
                if ((students[i].exams[j] == '4') || (students[i].exams[j] == '5'))
                    c += 1;
            }
            if (c == 3)
                best += 1;
        }
    }
    r = best / st * 100;
    cout << "\n4 и 5 на экзаменах получило " << r << "% студентов\n\n";
    system("pause");
}

void Session_review()
{
    char choice;
    bool quit = false;
    student students[CoupleSize] = {
    {"Safonov", "Ura", "*surname", 252, "424"},
    {"Tozlian", "Edgar", "Davidovich", 252, "354" },
    {"Starovoitov", "Ilya", "RedbuLLovich", 252, "545" },
    {"Chhaidze", "David", "*surname", 252, "432" },
    {"Grigorov", "Andrey", "*surname", 252, "555" }

    };

    if (!students[0].family_name)
        init_students_arr(students, CoupleSize);
    while (!quit)
    {
        choice = structs_menu(2);
        switch (choice)
        {
        case 'e':
            students_enter(students, CoupleSize);
            break;
        case 'd':
            student_display(students, CoupleSize);
            break;
        case 's':
            student_selected_display(students, CoupleSize);
            break;
        case 'u':
            students_update(students, CoupleSize);
            break;
        case 'r':
            students_review(students, CoupleSize);
            break;
        case 'q':
            quit = true;
            break;
        }
    }
}

struct Inum
{
    int a;
    int i;
};

void add_i(Inum a, Inum b, Inum* res)
{
    res->a = a.a + b.a;
    res->i = a.i + b.i;
}
void reduce_i(Inum a, Inum b, Inum* res)
{
    res->a = a.a - b.a;
    res->i = a.i - b.i;
}
void mult_i(Inum a, Inum b, Inum* res)
{
    res->a = a.a * b.a - a.i * b.i;
    res->i = a.a * b.i + a.i * b.a;
}
void del_i(Inum a, Inum b, Inum* res)
{
    res->a = (a.a * b.a + a.i * b.i) / (b.a * b.a + b.i * b.i);
    res->i = (a.i * b.a - a.a * b.i) / (b.a * b.a + b.i * b.i);
}
void I_numbers()
{
    Inum a, b, res;
    int choice;
    bool quit = false;
    cout << "Введите число А: ";
    cin >> a.a;
    system("cls");
    cout << "Введите число A: " << a.a << ' ';
    cin >> a.i;
    system("cls");
    cout << "Число А: " << a.a << '+' << a.i << "i\n";
    cout << "Введите число B: ";
    cin >> b.a;
    system("cls");
    cout << "Число А: " << a.a << '+' << a.i << "i\n";
    cout << "Введите число B: " << b.a << ' ';
    cin >> b.i;
    system("cls");
    cout << "Число А: " << a.a << '+' << a.i << "i\n";
    cout << "Число B: " << b.a << '+' << b.i << "i\n\n";

    cout << "** Меню **\n";
    cout << "1. +\n";
    cout << "2. -\n";
    cout << "3. *\n";
    cout << "4. /\n";
    cout << "Выберите действие: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add_i(a, b, &res);
        cout << "Результат: " << res.a << '+' << res.i << 'i';
        break;
    case 2:
        reduce_i(a, b, &res);
        cout << "Результат: " << res.a << '+' << res.i << 'i';
        break;
    case 3:
        mult_i(a, b, &res);
        cout << "Результат: " << res.a << '+' << res.i << 'i';
        break;
    case 4:
        del_i(a, b, &res);
        cout << "Результат: " << res.a << '+' << res.i << 'i';
        break;
    default:
        break;
    }
    cout << "\n\n";
    
}

struct car
{
    char brand[40];
    char model[40];
    char color[40];
    int price;
    int engine_pwr;
    double consumption;
};

void cars_display(car* cars, int size, int pricemin, int pricemax, int enginepwrmin, int enginepwrmax, double consumptionmin, double consumptionmax)
{
    int i;
    
    cout << "\n ----------------------------------------------------------------- \n";
    for (i = 0; i < size; i++)
    {
        bool price = false, pwr = false, cons = false;
        if (*cars[i].brand)
        {
            if ((cars[i].price >= pricemin) && (cars[i].price <= pricemax))
                price = true;
            if ((cars[i].engine_pwr >= enginepwrmin) && (cars[i].engine_pwr <= enginepwrmax))
                pwr = true;
            if ((cars[i].consumption >= consumptionmin) && (cars[i].consumption <= consumptionmax))
                cons = true;
            if (price && pwr && cons)
            {
                cout << "\n    Марка: " << cars[i].brand << "  Модель: " << cars[i].model << "  Цена: " << cars[i].price << " рублей" << "\n\n";
                cout << "    Цвет: " << cars[i].color << "  Мощность: " << cars[i].engine_pwr << " л. с." << "  Расход: " << cars[i].consumption << "л/100км\n\n";
                cout << " ----------------------------------------------------------------- \n";
            }
        }
    }
    cout << '\n';

    system("pause");
}
void filters(int* pricemin, int* pricemax, int* enginepwrmin, int* enginepwrmax, double* consumptionmin, double* consumptionmax)
{
    cout << "** Фильтры **";
    cout << "\nВведите минимальную цену: "; cin >> *pricemin;
    cout << "\nВведите максимальную цену: "; cin >> *pricemax;
    cout << "\nВведите минимальную мощность двигателя: "; cin >> *enginepwrmin;
    cout << "\nВведите максимальную мощность двигателя: "; cin >> *enginepwrmax;
    cout << "\nВведите минимальный расход топлива: "; cin >> *consumptionmin;
    cout << "\nВведите максимальный расход топлива: "; cin >> *consumptionmax;
}

void CarDealer()
{
    const int size = 16;
    car cars[size] = {
        {"ВАЗ", "2107","Черный", 250000, 76, 9.6},
        {"Nissan", "Sylphy","Белый", 1960000, 116, 11},
        {"Toyota", "RAV 4","Серый", 1350000, 148, 15},
        {"Changan", "LX" ,"Красный", 2960000, 120, 12},
        {"Hyundai", "Solaris","Желтый", 1195000, 94, 8.8},
        {"Opel", "Astra", "Серый",  350000, 115, 8.2},
        {"Dodge", "Charger II", "Бардовый",  50800000, 345, 22},
        {"Imponte", "Duke o`Death", "Черный", 76600000, 900, 40},
        {"RAM", "TRX", "Красный", 15000000, 702, 25}
    };
    char choice;
    bool quit = false;

    // filters
    int pricemin = 0, pricemax = 899999999;
    int enginepwrmin = 0, enginepwrmax = 99999;
    double consumptionmin = 0, consumptionmax = 99999;
    //
    do
    {
        system("cls");
        cout << "** Меню **\n";
        cout << "(D)isplay\n";
        cout << "(F)ilters\n";
        cout << "(Q)uit\n";
        cout << "Выберите действие: ";
        cin >> choice;
        choice = tolower(choice);

        switch (choice)
        {
        case 'd':
            system("cls");
            cars_display(cars, size, pricemin, pricemax, enginepwrmin, enginepwrmax, consumptionmin, consumptionmax);
            break;
        case 'f':
            system("cls");
            filters(&pricemin, &pricemax, &enginepwrmin, &enginepwrmax, &consumptionmin, &consumptionmax);
            break;
        case 'q':
            quit = true;
            break;
        }
    } while (!quit);




}

struct lesson {
    char lesson[80];
    int start_time;
    int end_time;
};

struct DaySchedule {
    lesson lessons[8]; 
};

struct AUD {
    int number;
    DaySchedule week[7]; 
};

int slt = 650;

const char* dayNames[7] = { "ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ", "ВС" };

void time_out(int time) {
    int h, m;
    h = time / 60;
    m = time % 60;
    if (h < 10)
        cout << "0" << h;
    else
        cout << h;
    cout << ':';
    if (m < 10)
        cout << "0" << m;
    else
        cout << m;
}

char AUD_menu() {
    char ch;
    cout << '\n';
    do {
        system("cls");
        cout << "** Меню управления расписанием **\n";
        cout << "(E)dit\n";
        cout << "(D)isplay\n";
        cout << "(F)ind free time\n"; 
        cout << "(Q)uit\n\n";
        cout << "Выберите команду: "; cin >> ch;
    } while (!strchr("edfq", tolower(ch)));
    return tolower(ch);
}

// Отображение расписания на конкретный день
void AUD_Day_disp(AUD* rooms, int id, int day, int Lsize) {
    cout << "Аудитория " << rooms[id].number << " (" << dayNames[day] << ")\n";
    cout << "--------------------------------------------------------------------------------------------\n";
    bool hasLessons = false;
    for (int i = 0; i < Lsize; i++) {
        if (rooms[id].week[day].lessons[i].lesson[0] != '\0') {
            hasLessons = true;
            cout << i + 1 << " | " << rooms[id].week[day].lessons[i].lesson << " | ";
            time_out(rooms[id].week[day].lessons[i].start_time);
            cout << " - ";
            time_out(rooms[id].week[day].lessons[i].end_time);
            cout << " |\n";
        }
    }
    if (!hasLessons) {
        cout << "Нет занятий\n";
    }
    cout << "--------------------------------------------------------------------------------------------\n";
}

// Отображение всего расписания 
void AUD_Week_disp(AUD* rooms, int id) {
    cout << "============================================================\n";
    cout << "Расписание аудитории " << rooms[id].number << "\n";
    cout << "============================================================\n";
    for (int day = 0; day < 7; day++) {
        AUD_Day_disp(rooms, id, day, 8);
        cout << "\n";
    }
}

// Ввод 
void AUD_lesson_input(AUD* rooms, int id, int day, int cell) {
    int h, m;
    cin.ignore();
    cout << "Аудитория " << rooms[id].number << ", " << dayNames[day] << "\n\n";
    cout << "Введите название предмета для " << cell + 1 << " пары: ";
    cin.getline(rooms[id].week[day].lessons[cell].lesson, 80);
    cout << '\n';

    cout << "Введите время начала (часы минуты): ";
    cin >> h >> m;
    rooms[id].week[day].lessons[cell].start_time = m + h * 60;
    cout << "Введите время окончания (часы минуты): ";
    cin >> h >> m;
    rooms[id].week[day].lessons[cell].end_time = m + h * 60;
}

// Удаление 
void AUD_lesson_del(AUD* rooms, int id, int day, int cell) {
    rooms[id].week[day].lessons[cell].lesson[0] = '\0';
    rooms[id].week[day].lessons[cell].start_time = 0;
    rooms[id].week[day].lessons[cell].end_time = 0;
}

// Добавление 
void AUD_add(AUD* rooms, int id, int day) {
    int cell;
    bool limit = true;
    for (cell = 0; cell < 8; cell++) {
        if (!rooms[id].week[day].lessons[cell].lesson[0]) {
            AUD_lesson_input(rooms, id, day, cell);
            limit = false;
            break;
        }
    }
    if (limit) {
        cout << "Достигнут лимит пар (8)";
        Sleep(slt);
    }
}

// Поиск свободного времени
void FindFreeTime(AUD* rooms, int id) {
    system("cls");
    cout << "Поиск свободного времени в аудитории " << rooms[id].number << "\n";
    cout << "================================================\n\n";

    int searchDay, duration;
    cout << "Введите день недели (0-ПН, 1-ВТ, 2-СР, 3-ЧТ, 4-ПТ, 5-СБ, 6-ВС): ";
    cin >> searchDay;

    if (searchDay < 0 || searchDay > 6) {
        cout << "Неверный день недели!\n";
        Sleep(slt);
        return;
    }

    cout << "Введите минимальную продолжительность свободного времени (в минутах): ";
    cin >> duration;

    cout << "\nСвободное время в " << dayNames[searchDay] << ":\n";
    cout << "----------------------------------------\n";

    lesson dayLessons[8];
    int lessonCount = 0;

    for (int i = 0; i < 8; i++) {
        if (rooms[id].week[searchDay].lessons[i].lesson[0] != '\0') {
            dayLessons[lessonCount] = rooms[id].week[searchDay].lessons[i];
            lessonCount++;
        }
    }

    // Сортируем занятия 
    for (int i = 0; i < lessonCount - 1; i++) {
        for (int j = i + 1; j < lessonCount; j++) {
            if (dayLessons[i].start_time > dayLessons[j].start_time) {
                lesson temp = dayLessons[i];
                dayLessons[i] = dayLessons[j];
                dayLessons[j] = temp;
            }
        }
    }

    int dayStart = 8 * 60;    // 8:00 - начало дня
    int dayEnd = 22 * 60;      // 22:00 - конец дня
    int lastEnd = dayStart;

    bool found = false;

    for (int i = 0; i < lessonCount; i++) {
        if (dayLessons[i].start_time - lastEnd >= duration) {
            cout << "С ";
            time_out(lastEnd);
            cout << " до ";
            time_out(dayLessons[i].start_time);
            cout << " (";
            cout << dayLessons[i].start_time - lastEnd << " мин.)\n";
            found = true;
        }
        if (dayLessons[i].end_time > lastEnd) {
            lastEnd = dayLessons[i].end_time;
        }
    }

    if (dayEnd - lastEnd >= duration) {
        cout << "С ";
        time_out(lastEnd);
        cout << " до ";
        time_out(dayEnd);
        cout << " (";
        cout << dayEnd - lastEnd << " мин.)\n";
        found = true;
    }

    if (!found) {
        cout << "Свободных окон продолжительностью " << duration << " минут не найдено\n";
    }

    cout << "\n";
    system("pause");
}

// Редактирование конкретного дня
void AUD_edit_day(AUD* rooms, int id, int day) {
    char choice, ch;
    bool quit = false;
    do {
        system("cls");
        AUD_Day_disp(rooms, id, day, 8);

        cout << "\n(A)dd\n";
        cout << "(C)hange\n";
        cout << "(D)elete\n";
        cout << "(B)ack\n";
        cout << "Введите команду: ";
        cin >> choice;
        choice = tolower(choice);
        int cell;

        switch (choice) {
        case 'a':
            system("cls");
            AUD_Day_disp(rooms, id, day, 8);
            AUD_add(rooms, id, day);
            break;
        case 'c':
            system("cls");
            AUD_Day_disp(rooms, id, day, 8);
            cout << "Введите номер ячейки для замены (1-8): ";
            cin >> cell;
            if (cell > 0 && cell < 9) {
                if (rooms[id].week[day].lessons[cell - 1].lesson[0]) {
                    system("cls");
                    AUD_Day_disp(rooms, id, day, 8);
                    AUD_lesson_input(rooms, id, day, cell - 1);
                }
                else {
                    cout << "Ячейка пуста. Добавить пару?\n";
                    cout << "Y - Да\nN - нет\n";
                    cout << "Выберите команду: ";
                    cin >> ch;
                    ch = tolower(ch);
                    if (ch == 'y') {
                        system("cls");
                        AUD_Day_disp(rooms, id, day, 8);
                        AUD_lesson_input(rooms, id, day, cell - 1);
                    }
                }
            }
            else {
                cout << "За пределами ввода";
                Sleep(slt);
            }
            break;
        case 'd':
            system("cls");
            AUD_Day_disp(rooms, id, day, 8);
            cout << "Введите номер ячейки для удаления (1-8): ";
            cin >> cell;
            if (cell > 0 && cell < 9) {
                if (rooms[id].week[day].lessons[cell - 1].lesson[0]) {
                    system("cls");
                    AUD_Day_disp(rooms, id, day, 8);
                    AUD_lesson_del(rooms, id, day, cell - 1);
                }
                else {
                    cout << "Ячейка уже пуста";
                    Sleep(slt);
                }
            }
            else {
                cout << "За пределами ввода";
                Sleep(slt);
            }
            break;
        case 'b':
            quit = true;
            break;
        default:
            break;
        }
    } while (!quit);
}

// Выбор дня 
void AUD_choose_day(AUD* rooms, int id) {
    int day;
    bool quit = false;
    do {
        system("cls");
        cout << "Выберите день недели:\n";
        for (int i = 0; i < 7; i++) {
            cout << i << " - " << dayNames[i] << "\n";
        }
        cout << "Введите номер дня (0-6): ";
        cin >> day;

        if (day >= 0 && day <= 6) {
            AUD_edit_day(rooms, id, day);
            quit = true;
        }
        else {
            cout << "Неверный номер дня!\n";
            Sleep(slt);
        }
    } while (!quit);
}

void AUD_N_disp(AUD* rooms, int size) {
    cout << "Список аудиторий:\n";
    for (int id = 0; id < size; id++) {
        if (rooms[id].number)
            cout << rooms[id].number << " аудитория\n";
    }
}

void AUD_choose(AUD* rooms, int size) {
    int id, n;
    bool f = false;
    do {
        system("cls");
        AUD_N_disp(rooms, size);
        cout << "\nВведите номер аудитории: ";
        cin >> n;
        for (id = 0; id < size; id++) {
            if (rooms[id].number == n) {
                system("cls");
                AUD_choose_day(rooms, id);
                f = true;
                break;
            }
        }
        if (!f) {
            cout << "Аудитория не найдена";
            Sleep(slt);
        }
    } while (!f);
}

// Вывод
void AUD_display(AUD* rooms, int size) {
    system("cls");
    int id, n;
    bool found = false;

    AUD_N_disp(rooms, size);
    cout << "\nВведите номер аудитории для просмотра: ";
    cin >> n;

    for (id = 0; id < size; id++) {
        if (rooms[id].number == n) {
            AUD_Week_disp(rooms, id);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Аудитория не найдена\n";
    }
    system("pause");
}

// Поиск свободного времени
void AUD_find_free(AUD* rooms, int size) {
    system("cls");
    int id, n;
    bool found = false;

    AUD_N_disp(rooms, size);
    cout << "\nВведите номер аудитории для поиска: ";
    cin >> n;

    for (id = 0; id < size; id++) {
        if (rooms[id].number == n) {
            FindFreeTime(rooms, id);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Аудитория не найдена\n";
        Sleep(slt);
    }
}

void Auditory() {
    bool quit = false;
    const int size = 10;
    char choice;

    AUD rooms1[size] = {
        {252, {
            {   // ПН
                { { "Математика", 560, 720 }, { "C++", 720, 940 } }
            },
            {   // ВТ
                { { "Физика", 540, 680 }, {} }
            },
            {   // СР
                { {} }
            },
            {   // ЧТ
                { {} }
            },
            {   // ПТ
                { {} }
            },
            {   // СБ
                { {} }
            },
            {   // ВС
                { {} }
            }
        }},
        {251, {
            {   // ПН
                { { "История дизайна", 30, 540 }, { "Английский язык", 1120, 1440 } }
            },
            {   // ВТ
                { {} }
            },
            {   // СР
                { {} }
            },
            {   // ЧТ
                { {} }
            },
            {   // ПТ
                { {} }
            },
            {   // СБ
                { {} }
            },
            {   // ВС
                { {} }
            }
        }}
    };

    do {
        system("cls");
        choice = AUD_menu();

        switch (choice) {
        case 'e':
            system("cls");
            AUD_choose(rooms1, size);
            break;
        case 'd':
            AUD_display(rooms1, size);
            break;
        case 'f':
            AUD_find_free(rooms1, size);
            break;
        case 'q':
            quit = true;
            break;
        }
    } while (!quit);
}

int menu() {
    int choice;
    cout << "** Меню **\n";
    cout << "1. AEROFLOT\n";
    cout << "2. Session review\n";
    cout << "3. Комплексные числа\n";
    cout << "4. Автосалон\n";
    cout << "5. Занятость аудитории\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
    cin >> choice;
    return choice;
}

int main() {
    system("chcp 1251");
    int choice;
    do {
        system("cls");
        choice = menu();
        switch (choice) {
        case 1:
            system("cls");
            AEROFLOT();
            system("pause");
            break;
        case 2:
            system("cls");
            Session_review();
            system("pause");
            break;
        case 3:
            system("cls");
            I_numbers();
            system("pause");
            break;
        case 4:
            system("cls");
            CarDealer();
            system("pause");
            break;
        case 5:
            system("cls");
            Auditory();
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