#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
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
    int i, num, arr[20], c;
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
    int i = 0, j = 0, k = 36, n, choice;
    
    *player1_bank -= bet;
    *dealer_bank -= bet;
    game_bank += 2*bet;

    

    shake(cards, 36);
    takecard(player1_hand, i, cards, k);
    takecard(dealer_hand, j, cards, k);
    
    do
    {
        system("cls");
        cout << "Ваш баланс: " << *player1_bank << "   Банк игры: " << game_bank << "\n\n";
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
                cout << "Ваш баланс: " << *player1_bank << "   Банк игры: " << game_bank << "\n\n";
                cout << "У вас на руке " << arrsum(player1_hand, i) << " очков\n";
                cout << "У дилера на руке " << arrsum(dealer_hand, j) << " очков\n\n";
                game_end = true;
                dealer_win = true;
            }
            //if (arrsum(player1_hand, i) == 21)
            //{
            //    game_end = true;
            //    player1_win = true;
            //}
            break;
        case 2:  
            while ((arrsum(dealer_hand, j) < arrsum(player1_hand, i)) || (arrsum(dealer_hand, j) < 17))
            {
                Sleep(1500);
                takecard(dealer_hand, j, cards, k);
                system("cls");
                cout << "Ваш баланс: " << *player1_bank << "   Банк игры: " << game_bank << "\n\n";
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
        cout << "Вы проиграли...\n\n";
    else if (player1_win && !dealer_win)
    {
        cout << "Вы победили! \n\n";
        *player1_bank += 2 * bet;
    }
    else if (player1_win && dealer_win)
    {
        cout << "Ничья. \n\n";
        *player1_bank += bet;
    }
        

    system("pause");
}
void task_7()
{
    int player1_bank = 2000, dealer_bank = 2000000, min_bet = 100, max_bet = 10000, bet = 1000;
    int choice;

    cout << "** Игра в '21' **\n\n";

    system("pause");
    srand(time(0));
    do
    {
        system("cls");
        cout << "Ваш баланс: " << player1_bank << "   Ваша ставка: " << bet << "   Минимальная ставка: " << min_bet << "   Максимальная ставка: " << max_bet << "\n\n";
        cout << "1. Увеличить ставку\n";
        cout << "2. Уменьшить ставку\n";
        cout << "3. Сбросить ставку\n";
        cout << "4. Начать игру\n";
        cout << "0. Выйти\n";
        cout << "CHOICE? : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            if (bet <= max_bet - 100)
            {
                bet += 100;
                break;
            }
            else
            {
                cout << "\nДостигнут верхний предел ставки\n";
                system("pause");
                break;
            }
                
        case 2:
            if (bet >= min_bet + 100)
            {
                bet -= 100;
                break;
            }
            else
            {
                cout << "\nДостигнут нижний предел ставки\n";
                system("pause");
                break;
            }
        case 3:
            bet = 500;
            break;
        case 4:
            if (bet <= player1_bank)
                game(&player1_bank, bet, &dealer_bank);
            else
            {
                cout << "Кошелек исхудал";
                Sleep(1000);
            }
                
        }




    } while (choice != 0);
    

   







}

void task_8()
{

}
void task_9()
{

}
void task_10()
{

}
void task_11()
{

}
void task_12()
{

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




