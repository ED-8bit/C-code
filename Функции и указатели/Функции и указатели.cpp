#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include <windows.h>
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

int menu()
{
    int choice;
    cout << "** Меню **\n";
    cout << "1. Функция Dohod\n";
    cout << "2. Функция с результатом сравнения\n";
    cout << "3. Функция для квадратного уравнения\n";
    cout << "4. Функция для выставления нижнего регистра строки\n";
    cout << "5. Функции для работы с дробями\n";
    cout << "6. Функция для возврата простых делителей\n";
    cout << "7. ИГРА в 21\n";
    cout << "8. Функция для поиска N члена Фибоначчи\n";
    cout << "9. Функция для вычисления суммы цифр целого числа\n";
    cout << "10. Функция для возврата числа в обратном порядке\n";
    cout << "11. Функция для проверки скобочной структуры в строке\n";
    cout << "12. Работа с динамическим массивом\n";
    cout << "13. Сумма элементов делящихся на 5\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
    cin >> choice;
    return choice;
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
int countnums(int number)
{
    if (number == 0) return 1;
    int count = 0;

    number = abs(number);
    while (number > 0) {
        number /= 10;
        count++;
    }
    return count;
}

double Dohod(double bank, double bet, int days)
{
    int i;
    for (i = 0; i < days; i++)
    {
        bank += bank * ((bet / 365)/100.0);
    }
    return bank;
}
void task_1()
{
    double bank, bet;
    int days;
    cout << "Введите сумму: ";
    cin >> bank;
    cout << "\n\nВведите годовую ставку: ";
    cin >> bet;
    cout << "\n\nВведите кол-во дней: ";
    cin >> days;
    cout << "\n\n" << Dohod(bank, bet, days);

}

char match(int a, int b)
{
    if (a > b)
    {
        return '>';
    }
    if (a < b)
    {
        return '<';
    }
    if (a == b)
    {
        return '=';
    }

}
void task_2()
{
    int A, B;
    cout << "Введите число A: ";
    cin >> A;
    cout << "Введите число B: ";
    cin >> B;
    system("cls");
    cout << 'A' << match(A, B) << 'B' << "\n\n";
}

int uravnenie(int a, int b, int c)
{
    if (a == 0)
        return -1;
    else
    {
        int D = (b * b - 4 * a * c);
        if (D > 0)
            return 2;
        if (D == 0)
            return 1;
        if (D < 0)
            return 0;
    }

}
void task_3() 
{
    int a, b, c;
    cout << "Введите коэффиценты квадратного уравнения: \n";
    cout << "A*x^2 + B*x + C = 0\n";
    cout << "Введите коэффициент A: ";
    cin >> a;
    cout << "Введите коэффициент B: ";
    cin >> b;
    cout << "Введите коэффициент C: ";
    cin >> c;

    system("cls");

    cout << a << "*x^2 +" << '(' << b << ')' << "*x +" << '(' << c << ')' << " = 0\n\n";

    cout << "'2' - 2 разных корня\n";
    cout << "'1' - 2 одинаковых корня\n";
    cout << "'0' - Уравнение не имеет решений\n";
    cout << "'-1' - Исходные данные неверны\n\n";
    cout << "Результат: " << uravnenie(a, b, c) << "\n\n";
    
}

void str_tolower(char *str)
{
    int i;
    for  (i = 0; str[i]!= '\0'; i++)
    {
        *str = tolower(*str);
        str++;
    }
}
void task_4()
{
    char str[80];
    cin.ignore();
    cin.getline(str, 80);
    str_tolower(str);
    cout << '\n' << str << '\n' << '\n';
}

void dr_del(int* dr1, int* dr2, int* res)
{
    dr2++;
    *res = (*dr1) * (*dr2);
    *res++;
    *dr1++;
    *dr2--;
    *res = (*dr1) * (*dr2);
}
void dr_mult(int* dr1, int* dr2, int* res)
{
    *res = (*dr1) * (*dr2);
    *res++;
    *dr1++;
    *dr2++;
    *res = (*dr1) * (*dr2);
}
void dr_sum(int *dr1, int *dr2, int *res)
{
    int temp;
    dr1++;
    dr2++;

    if (*dr1 == *dr2)
    {
        dr1--;
        dr2--;
        *res = *dr1 + *dr2;
        res++;
        dr1++;
        *res = *dr1;
    }
    else
    {
        if ((*dr1 > *dr2) && (*dr1 % *dr2 == 0))
        {        
            temp = *dr1 / *dr2;
            *dr2 = temp;
            dr2--;
            dr1--;
            *dr2 *= temp;
            *res = *dr1 + *dr2;
            res++;
            dr1++;
            *res = *dr1;
        }
        else if ((*dr2 > *dr1) && (*dr2 % *dr1 == 0))
        {
            temp = *dr2 / *dr1;
            *dr1 = temp;
            dr1--;
            dr2--;
            *dr1 *= temp;
            *res = *dr1 + *dr2;
            res++;
            dr2++;
            *res = *dr2;
        }
        else
        {
            temp = *dr1;

            *dr1 *= *dr2;
            dr1--;
            *dr1 *= *dr2;
            dr1++;

            *dr2 *= temp;
            dr2--;
            *dr2 *= temp;
            dr2++;
   
            *res = *dr1 + *dr2;
            *res++;
            dr1++;
            *res = *dr1;
        }
    }
}
void dr_compact(int* drc)
{
    int* drz;
    int i;
    drz = drc;
    drz++;

    if (*drc > *drz)
    {
        for (i = *drz; *drc % *drz != 0; i--)
        {
            if (i == 0)
                break;
        }
        *drz /= i;
        *drc /= i;
    }
    else if (*drc < *drz)
    {
        for (i = *drc; *drz % *drc != 0; i--)
        {
            if (i == 0)
                break;
        }
        *drz /= i;
        *drc /= i;
    }
    else if (*drc == *drz)
    {
        *drc = 1;
        *drz = 1;
    }
        
    
}
void dr_ch_enter(int* dr)
{
    int a;
    cout << "Введите числитель: ";
    cin >> a;
    *dr = a;
}
void dr_zn_enter(int* dr)
{
    int a;
    cout << "Введите знаменатель: ";
    cin >> a;
    dr++;
    *dr = a;
}
void dr_view(int dr[2])
{
    if (dr[0] == dr[1])
    {
        cout << dr[0];
    }
    else
    {
        if (dr[1] != 1)
            cout << '(' << dr[0] << '/' << dr[1] << ')';
        else
            cout << dr[0];
    }
    
}
void task_5()
{
    int dr1[2], dr2[2], res[2];
    cout << "Первая дробь: \n";
    dr_ch_enter(dr1);
    dr_zn_enter(dr1);
    cout << '\n';
    cout << "Вторая дробь: \n";
    dr_ch_enter(dr2);
    dr_zn_enter(dr2);
    cout << '\n';
    dr_view(dr1);
    cout << '\n';
    dr_view(dr2);
    cout << '\n' << '\n' << "Результат: \n";
    
    dr_del(dr1, dr2, res);
    dr_compact(res);
    dr_view(res);
    cout << "\n\n";
    
}


bool is_prime(int num)
{
    int i;
    if (num < 2)
        return false;
    for (i = 2; i < sqrt(num); i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}
int prime_dels(int num, int* arr)
{
    int i = 2, c = 0;
    do
    {
        if (is_prime(i) && (num % i == 0))
        {
            *arr = i;
            num /= i;
            arr++;
            c++;
        }
        i++;
    } while (num != 1);
    return c;
}
void task_6()
{
    int num, arr[20], c;
    cout << "Введите число: ";
    cin >> num;
    c = prime_dels(num, arr);
    "\nПростые множители числа: ";
    arrayview(arr, c);

}

bool takecard(int hand[], int &j, int cards[], int &k)
{
    if (k > 0)
    {
        hand[j] = cards[k - 1];
        j++;
        k--;
        return true;
    }
    else
        return false;
}
int arrsum(int arr[], int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += arr[i];
    }
    return sum;
}
void shake(int *arr, int len)
{
    int i, j;
    for (i = len - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }



}
void game(int *player1_bank, int bet, int *dealer_bank)
{
    int game_bank = 0;
    bool dealer_win = false, player1_win = false, game_end = false;
    int cards[36] = { 2, 3, 4, 6, 7, 8, 9, 10, 11,    2, 3, 4, 6, 7, 8, 9, 10, 11,    2, 3, 4, 6, 7, 8, 9, 10, 11,    2, 3, 4, 6, 7, 8, 9, 10, 11 };
    int player1_hand[15], dealer_hand[15];
    int i = 0, j = 0, k = 36, choice;
    
    *player1_bank -= bet;
    *dealer_bank -= bet;
    game_bank += 2*bet;

    

    shake(cards, 36);
    takecard(player1_hand, i, cards, k);
    takecard(dealer_hand, j, cards, k);
    
    do
    {
        system("cls");
        cout << "Ваш баланс: " << *player1_bank << '$' << "   Банк игры: " << game_bank << '$' << "\n\n";
        cout << "У вас на руке " << arrsum(player1_hand, i) << " очков\n";
        cout << "У дилера на руке " << arrsum(dealer_hand, j) << " очков\n\n";
        
        cout << "1. Взять ещё карту\n";
        cout << "2. Хватит\n";
        cout << "CHOICE? : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            takecard(player1_hand, i, cards, k);
            if (arrsum(player1_hand, i) > 21)
            {
                system("cls");
                cout << "Ваш баланс: " << *player1_bank << '$' << "   Банк игры: " << game_bank << '$' << "\n\n";
                cout << "У вас на руке " << arrsum(player1_hand, i) << " очков\n";
                cout << "У дилера на руке " << arrsum(dealer_hand, j) << " очков\n\n";
                game_end = true;
                dealer_win = true;
            }
            
            break;
        case 2:  
            while ((arrsum(dealer_hand, j) < arrsum(player1_hand, i)) || (arrsum(dealer_hand, j) < 17))
            {
                Sleep(1500);
                takecard(dealer_hand, j, cards, k);
                system("cls");
                cout << "Ваш баланс: " << *player1_bank << '$' << "   Банк игры: " << game_bank << '$' << "\n\n";
                cout << "У вас на руке " << arrsum(player1_hand, i) << " очков\n";
                cout << "У дилера на руке " << arrsum(dealer_hand, j) << " очков\n\n";

                cout << "Дилер берет карту...\n";

                if (arrsum(dealer_hand, j) > 21)
                    break;
                
            }
            if (arrsum(dealer_hand, j) > 21)
            {
                game_end = true;
                player1_win = true;
            }
            else if (arrsum(dealer_hand, j) == arrsum(player1_hand, i))
            {
                game_end = true;
                dealer_win = true;
                player1_win = true;

            }
            else if (arrsum(dealer_hand, j) > arrsum(player1_hand, i))
            {
                game_end = true;
                dealer_win = true;
                
            }
            
            
            break;
        }


        
        
    } while (game_end != true);

    if (dealer_win && !player1_win)
    {
        cout << "Вы проиграли...\n\n";
        *dealer_bank += 2*bet;
    } 
    else if (player1_win && !dealer_win)
    {
        cout << "Вы победили! \n\n";
        *player1_bank += 2 * bet;
    }
    else if (player1_win && dealer_win)
    {
        cout << "Ничья. \n\n";
        *player1_bank += bet;
        *dealer_bank += bet;
    }
        

    system("pause");
}
void task_7()
{
    int player1_bank = 2000, dealer_bank = 50000, min_bet = 100, max_bet = 10000, bet = 1000, bet_step = 100;
    int choice;

    cout << "** Игра в '21' **\n\n";

    system("pause");
    srand(time(0));
    do
    {
        system("cls");
        cout << "Ваш баланс: " << player1_bank << '$' << "   Ваша ставка: " << bet << '$' << "   Шаг ставки: " << bet_step << "$\n\n" << "Минимальная ставка: " << min_bet << '$' << "   Максимальная ставка: " << max_bet << '$' << "\n\n";
        cout << "1. Увеличить ставку\n";
        cout << "2. Уменьшить ставку\n";
        cout << "3. Изменить шаг ставки\n";
        cout << "4. Сбросить ставку\n";
        cout << "5. Начать игру\n";
        cout << "0. Выйти\n";
        cout << "CHOICE? : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            if (bet <= max_bet - bet_step)
            {
                bet += bet_step;
                break;
            }
            else
            {
                cout << "\nДостигнут верхний предел ставки\n";
                system("pause");
                break;
            }
                
        case 2:
            if (bet >= min_bet + bet_step)
            {
                bet -= bet_step;
                break;
            }
            else
            {
                cout << "\nДостигнут нижний предел ставки\n";
                system("pause");
                break;
            }
        case 3:
            system("cls");
            cout << "Введите размер шага ставки: ";
            cin >> bet_step;
            break;
        case 4:
            bet = 500;
            break;
        case 5:
            if (bet <= player1_bank &&  bet <= dealer_bank)
                game(&player1_bank, bet, &dealer_bank);
            else
            {
                if (bet > player1_bank)
                {
                    cout << "Ваш кошелек исхудал";
                    Sleep(1000);
                }
                else
                {
                    cout << "У Дилера не хватает денег на ставку(";
                    Sleep(1000);
                }
                
            }
                
        }




    } while (choice != 0);
    

   







}

int Fib_n(int n)
{
    if (n - 1 > 1)
    {
        int i, answer;
        int* fibs = new int[n];
        fibs[0] = 0;
        fibs[1] = 1;
        for (i = 2; i < n; i++)
            fibs[i] = fibs[i - 1] + fibs[i - 2];
        answer = fibs[n - 1];
        delete fibs;
        return answer;
    }
    else
    {
        if (n - 1 == 0)
            return 0;
        else if
            (n - 1 == 1)
            return 1;
    }
    

}
void task_8()
{
    int i;
    cout << "Введите номер члена последовательности Фибоначчи: ";
    cin >> i;
    cout << "Он равен " << Fib_n(i) << "\n\n";
}

int SumOfNums(int n)
{
    int answer = 0, del_k = 1, i;
    n = abs(n);
    for (i = 0; i < countnums(n) - 1 ; i++)
        del_k *= 10;
    answer = n % 10;
    n = n / 10;
    if (del_k == 1)
    {
        return answer;
    }
    else
        answer += SumOfNums(n);
    

    // 29343 / 10000 = 2 --> 9343 / 1000 = 9 --> 343 / 100 = 3 --> 43 / 10 = 4 --> 3 / 1 = 3


}
void task_9()
{
    int n;
    cout << "Введите целое число: ";
    cin >> n;
    cout << "Сумма его цифр: " << SumOfNums(n) << "\n\n";
}


int int_reverse(int n)
{

    if ((n >= -9) && (n <= 9))
        return n;
    else
    { 
        int sign, last_digit = abs(n) % 10, remaining = abs(n) / 10, power = 1;

        sign = (n < 0) ? -1 : 1;
        
        for (int i = 0; i < countnums(remaining); i++) {
            power *= 10;
        }

        return sign * (last_digit * power + int_reverse(remaining));

    }
}
void task_10()
{
    int n;
    cout << "Введите целое число: ";
    cin >> n;
    cout << "Число в обратном порядке: " << int_reverse(n) << "\n\n";
}

bool brackets_check(const char* str, int balance)
{
    if (*str == '.')
    {
        return !balance;
    }
    else
    {
        if (*str == '(')
            balance++;
        else if (*str == ')')
        {
            balance--;
            if (balance < 0)
                return 0;
        }

        return brackets_check(str + 1, balance);

    }
}
void task_11()
{
    char str[80];
    cout << "Введите строку для проверки, конец обозначьте точкой: ";
    cin.ignore();
    cin.getline(str, 80);
    if (brackets_check(str, 0))
        cout << "Корректно\n";
    else
        cout << "Ошибка в структуре\n";
    

}


int* arr = nullptr;
int arr_size = 0;
bool initialized = false;

int* arr_init(int size)
{
    int* arr = (int*)malloc(size * sizeof(int));

    if (arr == NULL)
    {
        cout << "Ошибка инициализации\n";
        return NULL;
    }

    return arr;


}
void arr_delete(int *arr)
{ 
    if (arr != NULL)
    {
        free(arr);
        cout << "Память очищена\n";
    }
    else
    {
        cout << "Массив не был инициализирован\n";
    }
}
void arr_enter(int *arr, int id, int size)
{
    if (arr == NULL)
    {
        cout << "Массив не инициализирован\n";
        return;
    }

    if (id < 0 || id >= size)
    {
        cout << "Ошибка: индекс вне диапазона (0-" << size - 1 << ")\n";
        return;
    }

    int value;
    cout << "Введите значение для элемента [" << id << "]: ";
    cin >> value;
    arr[id] = value;
    cout << "Значение установлено\n";
}
void arr_output(int* arr, int size)
{
    if (arr == NULL)
    {
        cout << "Массив не инициализирован\n";
        return;
    }

    cout << "\nСодержимое массива:\n";
    for (int i = 0; i < size; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << "\n";
    }
    cout << endl;
}
void task_12()
{
    bool exit = false;
    int choice, size, n;
    int *arr;
    do
    {
        system("cls");
        cout << "\n** Редактор массива **\n\n";
        cout << "1. Инициализация\n";
        cout << "2. Заполнение массива\n";
        cout << "3. Вывод данных\n";
        cout << "4. Очистка памяти\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            if (initialized)
            {
                cout << "Массив уже инициализирован. Очистите память перед повторной инициализацией.\n";
                break;
            }
            cout << "Введите размер массива: ";
            cin >> size;
            if (size <= 0)
            {
                cout << "Размер должен быть положительным числом\n";
                break;
            }
            arr = arr_init(size);
            if (arr != NULL)
            {
                arr_size = size;
                initialized = true;
                cout << "Массив успешно инициализирован размером " << size << "\n";
            }
            break;
        case 2:
            system("cls");
            if (!initialized)
            {
                cout << "Сначала инициализируйте массив (пункт 1)\n";
                break;
            }
            cout << "Введите номер элемента (1-" << arr_size << "): ";
            cin >> n;
            arr_enter(arr, n - 1, arr_size);
            break;
        case 3:
            system("cls");
            if (!initialized)
            {
                cout << "Сначала инициализируйте массив (пункт 1)\n";
                break;
            }
            arr_output(arr, arr_size);
            break;
        case 4:
            system("cls");
            if (initialized && arr != NULL)
            {
                arr_delete(arr);
                arr = NULL;
                arr_size = 0;
                initialized = false;
            }
            else
            {
                cout << "Массив не был инициализирован\n";
            }
            break;
        case 0:
            if (initialized && arr != NULL)
            {
                arr_delete(arr);
                arr = NULL;
            }
            exit = true;
            break;
        default:
            cout << "Ошибка";
            break;
        }
    } while (!exit);
    
}



void task_13()
{

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
        case 7:
            system("cls");
            task_7();
            system("pause");
            break;
        case 8:
            system("cls");
            task_8();
            system("pause");
            break;
        case 9:
            system("cls");
            task_9();
            system("pause");
            break;
        case 10:
            system("cls");
            task_10();
            system("pause");
            break;
        case 11:
            system("cls");
            task_11();
            system("pause");
            break;
        case 12:
            system("cls");
            task_12();
            system("pause");
            break;    
        case 13:
            system("cls");
            task_13();
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




