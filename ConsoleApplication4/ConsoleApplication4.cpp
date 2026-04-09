#include <iostream>
#include <cmath>
#include <cstdlib>
#include <conio.h>
using namespace std;

//int main()
//{
//	int num;
//	double sq_root;
//	for (num = 1; num < 100; num++)
//	{
//		sq_root = sqrt((double)num);
//		cout << num << " " << sq_root << '\n';
//	}
//	return 0;
//}



//int main()
//{
//	int magic;
//	int guess;
//	int n,count, i, success;
//	srand(time(0));
//	system("chcp 1251");
//	cout << "Введите диапозон: "; cin >> n;
//	cout << "Введите количество попыток: "; cin >> count;
//	success = 0;
//	for (i = 0; i < count; i++) 
//	{
//		magic = rand() % (n + 1);
//		cout << "Введите свой вариант магического числа: ";
//		cin >> guess;
//		if (guess == magic) { cout << "** Правильно **\n"; success = success + 1; }
//		else cout << "** Очень жаль, но Вы ошиблись **\n";
//	}
//	cout << "Вы угадали " << success << " раз";
//	return 0;
//}

//int main()
//{
//	int i;
//	system("chcp 1251");
//	for (i = 0; !_kbhit(); i++) cout << i << '\n';
//	return 0;
//}


//int main()
//{
//	system("chcp 1251");
//	int N;
//	int i;
//	cout << "Введите размер таблицы квадратов: \n"; cin >> N;
//	
//	for (i = 1; i <= N; i++)
//	{
//		cout << i*i << '\n';
//	}
//	return 0;
//}

//int main()
//{
//	int N, i, sum;
//	system("chcp 1251");
//	cout << "Введите число четных чисел: "; cin >> N; cout << '\n';
//	sum = 0;
//	for(i = 2; i <= N*2; i += 2) 
//	{ 
//		sum += i;
//	}
//	cout << "Сумма чисел: " << sum;
//	return 0;
//}

//int main()
//{
//	int N, i;
//	double sum;
//	system("chcp 1251");
//	cout << "Введите число членов последовательности: "; cin >> N; cout << '\n';
//	sum = 0;
//	for (i = 1; i <= N; i++)
//	{
//		sum += 1.0 / i;
//	}
//	cout << "Сумма чисел: " << sum;
//	return 0;
//}

//int main()
//{
//	int N, i;
//	double sum;
//	system("chcp 1251");
//	cout << "Введите число для вичисления факториала: "; cin >> N; cout << '\n';
//	sum = 1;
//	for (i = 1; i <= N; i++)
//	{
//		sum *= i;
//	}
//	cout << "Факториал: " << sum;
//	return 0;
//}

//int main()
//{
//	double y, x;
//	system("chcp 1251");
//	for (x = -4; x <= 4; x += 0.5)
//	{
//		y = fabs(x - 2) + fabs(x + 1);
//		cout << "(" << x << ", " << y << ")" << '\n';
//	}
//}

//int main()
//{
//	int i, a, b, res, Trues;
//	system("chcp 1251");
//	srand(time(0));
//	Trues = 0;
//
//	for (i = 1; i <= 10; i++) 
//	{
//		a = (rand() % 9) + 1;
//		b = (rand() % 9) + 1;
//		cout << i << ")  " << a << "*" << b << "?" << '\n';
//		cin >> res;
//		if (res == a * b) Trues += 1;
//	}
//
//	cout << "\n" << "Ваша оценка: ";
//	if (Trues == 10) cout << "Отлично";
//	else if (Trues < 10 && Trues > 7) cout << "Хорошо";
//	else if (Trues < 8 && Trues > 5) cout << "Удовлетворительно";
//	else if (Trues < 7) cout << "Плохо";
//	cout << '\n';
//	
//	return 0;
//}

//int main()
//{
//	int i;
//	double res;
//	system("chcp 1251");
//	res = 0;
//
//	for (i = 99; i != 3; i -= 3)
//	{
//		res = sqrt( i + res);
//	}
//
//	cout << res;
//  return 0;
//}

//int main()
//{
//	int magic;
//	int guess;
//	int n,count, i;
//	srand(time(0));
//	system("chcp 1251");
//	cout << "У Вас будет 5 попыток, чтобы угадать число. Введите диапозон: "; cin >> n;
//	count = 5;
//	magic = rand() % (n + 1);
//	for (i = 0; i < count; i++) 
//	{
//		cout << "\nВведите свой вариант магического числа: ";
//		cin >> guess;
//		if (guess == magic) { cout << "** Правильно **\n"; break; }
//		else if (guess < magic) cout << "** Вы ошиблись. Ваше число меньше загаданного **\n";
//		else if (guess > magic) cout << "** Вы ошиблись. Ваше число больше загаданного **\n";
//	}
//	if (guess != magic) cout << "\nВы проиграли\n" << "Загаданное число: " << magic;
//	return 0;
//}

int main()
{
	int i, c;
	system("chcp 1251");
	cout << "  1 2 3 4 5 6 7 8 9 10 \n";
	for (i = 1; i < 11; i++)
	{
		cout << i << " ";
		for (c = 1; c < 11; c++)
		{
			cout << i * c << ' ';
		}
		cout << '\n';
	}
	return 0;
}



