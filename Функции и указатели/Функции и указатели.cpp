#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
/*
void cube(int *n, int num);
void arrayview(int* n, int b);

int main()
{
    system("chcp 1251");
    system("cls");
    int i, nums[10];
    for (i = 0; i < 10; i++)
    {
        nums[i] = i + 1;
    }

    cout << "Исходное содержимое массива: ";
    arrayview(nums, 10);
    cout << '\n';

    cube(nums, 10);

    cout << "Измененное содержимое: ";
    arrayview(nums, 10);

    return 0;
}

void cube(int* n, int num)
{
    while (num != 0)
    {
        *n = *n * *n * *n;
        num--;
        n++;
    }
}

void arrayview(int* n, int b)
{
    int i;
    for (i = 0; i < b; i++)
    {
        cout << n[i] << " ";
    }
}

*/
/*
void stringupper(char* str);

int main()
{
    char str[80];
    cin.getline(str, 80);
    stringupper(str);
    cout << str;
    return 0;
}

void stringupper(char* str)
{
    while(*str)
    {
        *str = toupper(*str);
        str++;
    }
}

*/
/*
const char* find_substr(const char* sub, const char* str);

int main()
{
    system("chcp 1251");
    system("cls");
    const char* str;
    str = find_substr("два", "один два три четыре");
    cout << "Найденная подстрока: " << str;
    return 0;
}


const char* find_substr(const char* sub, const char* str)
{
    int t;
    const char* p, * start;
    const char* p2;
    for (t = 0; str[t]; t++)
    {
        p = &str[t]; start = p; p2 = sub;
        while (*p2 && *p2 == *p)
        {
            p++;
            p2++;
        }
        if (!*p2) return start;
    }
    return 0;

}
*/




