#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctype.h>
#include <cctype>
#include <cmath>
#include <stdio.h>
#include <cstdlib>

using namespace std;

double pi = 3.14159;


double calculateArea(double a)
{
    return a * a;
}
double calculateArea(double a, double b, double c)
{
    double p;
    p = (a + b + c) / 2.0;
    if ((a + b > c) && (a + c > b) && (b + c > a))
        return sqrt(p * (p - a) * (p - b) * (p - c));
    else
        return 0;
}
double calculateArea(double r, bool circle)
{
    if (!circle)
        return NULL;
    else
    {
        return pi * r * r;
    }
}
void Square()
{
    double a;
    cout << "Введите размер стороны квадрата: ";
    cin >> a;
    cout << "\nРезультат: " << calculateArea(a);
    cout << "\n\n";
    system("pause");
}
void Triangle()
{
    double a, b, c, answer;
    cout << "Введите размер стороны A треугольника: ";
    cin >> a;
    cout << "\nВведите размер стороны B треугольника: ";
    cin >> b;
    cout << "\nВведите размер стороны C треугольника: ";
    cin >> c;
    answer = calculateArea(a, b, c);
    if (answer != 0)
    {
        cout << "\nРезультат: " << answer;
    }
    else
        cout << "\nТакого треугольника не существует.";

    cout << "\n\n";
    system("pause");
}
void Circle()
{
    double r;
    cout << "Введите радиус круга: ";
    cin >> r;
    cout << "\nРезультат: " << calculateArea(r, true);
    cout << "\n\n";
    system("pause");
}
void task_1()
{
    int n;
    do
    {
        system("cls");
        cout << "** Меню **\n";
        cout << "1. Квадрат\n";
        cout << "2. Треугольник\n";
        cout << "3. Круг\n";
        cout << "0. Назад\n";
        cout << "Выберите фигуру: ";
        cin >> n;
        switch (n)
        {
        case 1:
            system("cls");
            Square();
            break;
        case 2:
            system("cls");
            Triangle();
            break;
        case 3:
            system("cls");
            Circle();
            break;
        case 0:
            break;
        }
    } while (n != 0);
    
    
}

void swapValues(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void swapValues(double* a, double* b)
{
    double temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void swapValues(char *str1, char *str2)
{
    char temp[80];
    strcpy_s(temp, 80, str1);
    strcpy_s(str1, 80, str2);
    strcpy_s(str2, 80, temp);
}
void ints()
{
    int a, b;
    cout << "Введите A: ";
    cin >> a;
    cout << "\nBведите B: ";
    cin >> b;
    swapValues(&a, &b);
    cout << "\n A -> " << a;
    cout << "\n B -> " << b;
    cout << "\n\n";
    system("pause");
}
void doubles()
{
    double a, b;
    cout << "Введите A: ";
    cin >> a;
    cout << "\nBведите B: ";
    cin >> b;
    swapValues(&a, &b);
    cout << "\n A -> " << a;
    cout << "\n B -> " << b;
    cout << "\n\n";
    system("pause");
}
void Cstrings()
{
    char str1[80], str2[80];
    cin.ignore();
    cout << "Введите строку 1: ";
    cin.getline(str1, 80);
    cout << "Введите строку 2: ";
    cin.getline(str2, 80);
    swapValues(str1, str2);
    cout << "\nstr1 -> " << str1;
    cout << "\nstr2 -> " << str2;
    cout << "\n\n";
    system("pause");

}
void task_2()
{
    int n;
    do
    {
        system("cls");
        cout << "** Меню **\n";
        cout << "1. int\n";
        cout << "2. double\n";
        cout << "3. Cstrings\n";
        cout << "0. Назад\n";
        cout << "Выберите функцию: ";
        cin >> n;
        switch (n)
        {
        case 1:
            system("cls");
            ints();
            break;
        case 2:
            system("cls");
            doubles();
            break;
        case 3:
            system("cls");
            Cstrings();
            break;
        case 0:
            break;
        }
    } while (n != 0);
}

void arrayview(int arr[], int n) //Отображение массива
{
    int i;
    cout << "[";
    for (i = 0; i < n; i++)
    {
        if (i != n - 1) cout << arr[i] << ',' << ' ';
        else cout << arr[i];
    }
    cout << "]\n";
}
void analyzeArray(int* arr, int size, int& min, int& max)
{
    int i;
    min = arr[0];
    max = arr[0];
    for (i = 0; i < size; i++)
    {
        if (arr[i] >= max)
            max = arr[i];
        if (arr[i] <= min)
            min = arr[i];
    }
}
void analyzeArray(int* arr, int size, int& min, int& max, int& sum)
{
    int i;
    min = arr[0];
    max = arr[0];
    for (i = 0; i < size; i++)
    {
        if (arr[i] >= max)
            max = arr[i];
        if (arr[i] <= min)
            min = arr[i];
        sum += arr[i];
    }
}
void analyze(bool ext)
{
    system("cls");
    int arr[80];
    int i, j, c = 0, b, size, min, max, sum = 0;
    cout << "Введите размер массива: ";
    cin >> size;
    system("cls");
    for (i = 0; i < size; i++)
    {
        cout << "[";
        for (j = 0; j < c; j++)
        {
            cout << arr[j] << ',' << ' ';
        }
        cout << ']';
        cout << "\nВведите элемент: "; cin >> b;
        arr[j] = b;
        c += 1;
        system("cls");
    }
    arrayview(arr, size);
    if (ext)
        analyzeArray(arr, size, min, max, sum);
    else
        analyzeArray(arr, size, min, max);

    cout << "Минимум: " << min;
    cout << "\nМаксимум: " << max;
    if (ext)
        cout << "\nСумма: "<< sum;

    cout << "\n\n";
    system("pause");
    
}
void task_3()
{
    int n;
    do
    {
        system("cls");
        cout << "** Меню **\n";
        cout << "1. Найти экстремумы\n";
        cout << "2. Найти экстремумы и сумму элементов\n";
        cout << "0. Назад\n";
        cout << "Выберите функцию: ";
        cin >> n;
        switch (n)
        {
        case 1:
            system("cls");
            analyze(false);
            break;
        case 2:
            system("cls");
            analyze(true);
            break;
        case 0:
            break;
        }
    } while (n != 0);
}


int menu()
{
    int choice;
    cout << "** Меню **\n";
    cout << "1. Площадь фигуры\n";
    cout << "2. Обмен значений\n";
    cout << "3. Анализ массива\n";
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
            task_1();
            break;
        case 2:
            system("cls");
            task_2();
            break;
        case 3:
            system("cls");
            task_3();
            break;
        case 0:
            break;
        default:
            cout << "\n ОШИБКА";
            break;
        }
            
         
        
    } while (choice != 0);
    return 0;
}
