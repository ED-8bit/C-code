#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <cmath>
using namespace std;

//int main()
//{
//	system("chcp 1251");
//	system("cls");
//	double n, sum = 0, mid;
//	int s = 0;
//	cout << "Вводите числа последовательности. Введите 0, чтобы закончить\n\n";
//	do
//	{
//		cin >> n;
//		sum = sum + n;
//		s += 1;
//	} while (n != 0);
//		mid = sum / (s - 1);
//		cout << '\n' << "Сумма: " << sum << " " << "Среднее арифметическое: " << mid << '\n' << '\n';
//	return 0;
//}

//int main()
//{
//	system("chcp 1251");
//	system("cls");
//	double n, max = 0, min = 0;
//	cout << "Вводите числа последовательности. Введите 0, чтобы закончить\n\n";
//	cin >> n;
//	max = n;
//	min = n;
//	do
//	{
//		cin >> n;
//
//		if (max < n)
//		{
//			max = n;
//		}
//
//		if ((min > n) && (n != 0))
//		{
//			min = n;
//		}
//
//	} while (n != 0);
//	cout << '\n' << "Максимальное число: " << max << " " << "Минимальное число: " << min << '\n' << '\n';
//	return 0;
//}

//int main()
//{
//	int maxs = 0, s = 0;
//	double n0 = 0, n1 = 0, n;
//	system("chcp 1251");
//	system("cls");
//	cout << "Вводите числа последовательности. Введите 0, чтобы закончить\n\n";
//	do
//	{
//		cin >> n;
//		if (s >= 2)
//		{
//			if ((n1 > n) && (n1 > n0))
//			{
//				maxs += 1;
//			}
//		}
//		n0 = n1;
//		n1 = n;
//		s += 1;
//	} while (n != 0);
//	cout << "\nКол-во локальных максимумов: " << maxs;
//	return 0;
//}

/*

long long fact(int n);

int main()
{	
	double x, res = 0, e = 0.001, s;
	int i = 0;
	system("chcp 1251");
	system("cls");
	cout << "Введите X: "; cin >> x;
	do
	{
		s = (pow(x, 2 * i)) / (fact(2 * i));
		res += s;
		i += 1;

		if (i > 50)
		{  // максимум 50 итераций
			cout << "Достигнут лимит итераций\n";

			break;
		}
	} while (abs(s) >= e);
	cout << "\n" << "Результат: " << res;
	return 0;
}

long long fact(int n)
{
	int s = 1, res = 1;
	while (s <= n)
	{
		res = res * s;
		s += 1;
	}
	return res;
}

*/


//int main()
//{
//	int a, b, min, max, ost, nod = 0;
//	system("chcp 1251");
//	system("cls");
//	cout << "** НОД чисел: **\n\n";
//	cout << "A: "; cin >> a;
//	cout << "\nB: "; cin >> b;
//	if (a == 0 || b == 0)
//	{
//		cout << "На ноль делить нельзя";
//		return 0;
//	}
//	if (a > b)
//	{
//		max = a;
//		min = b;
//	}
//	else if (b > a)
//	{
//		max = b;
//		min = a;
//	}
//	else if (a == b)
//	{
//		cout << "\n\nНОД: " << a;
//		return 0;
//	}
//
//	do
//	{
//		if (max % min == 0)
//		{
//			nod = min;
//		}
//		else
//		{
//			ost = max % min;
//			max = min;
//			min = ost;
//		}
//	} while (nod == 0);
//	cout << "\nНОД: " << nod;
//	return 0;
//}
//



//int main()
//{
//	int k, s1, i, b;
//	double s;
//	bool iflag;
//	system("chcp 1251");
//	system("cls");
//	cout << "** Поиск простых чисел **\n";
//	cout << "Введите диапозон чисел: "; cin >> k; cout << "\n";
//	for (i = 2; i <= k; i++)
//	{
//		iflag = true;
//		s = sqrt(i);
//		s1 = int(s);
//		for (b = 2; b <= s1; b++)
//		{
//			if (i % b == 0)
//			{
//				iflag = false;
//			}
//			
//		}
//		if (iflag == true)
//		{
//			cout << i << " ";
//		}
//	}
//}


//int main()
//{
//	int d = 1;
//	double x, y;
//	system("chcp 1251");
//	system("cls");
//	cout << "** Марафон **\n\n";
//	cout << "Пробежал км: "; cin >> x;
//	cout << "\nНужно пробежать км: "; cin >> y;
//	while (x < y)
//	{
//		x *= 1.1;
//		d += 1;
//	} 
//	cout << "\nДостигнет цели в " << d << " день";
//
//}



/*
int r(int n);
int t(int n);
bool ts(int n, int a);

int main()
{
	int a, b;
	bool delim;
	system("chcp 1251");
	system("cls");
	cout << "** Раздвоитель **\n\n";
	cout << "Введите числа A > B: \n"; cin >> a >> b;
	if (a <= b)
	{
		cout << "Ошибка. Некорректные данные";
	}
	else
	{
		do
		{
			delim = ts(a, b);
			if (delim == true)
			{
				a = t(a);
			}
			if (delim == false)
			{
				a = r(a);
			}
		} while (a != b);
	}
}


int r(int n)
{
	n -= 1;
	cout << "-1\n";
	cout << "[" << n << "]" << "\n";
	return n;
}

bool ts(int n, int a)
{
	int d;
	if (n % 2 == 0)
	{
		n = n / 2;
	}
	else
	{
		n -= 1;
		n = n / 2;
	}
	if (n < a) return false;
	else return true;
}

int t(int n)
{
	if (n % 2 == 0)
	{
		n = n / 2;
	}
	else
	{
		n -= 1;
		n = n / 2;
	}
	cout << ":2\n";
	cout << "[" << n << "]" << "\n";
	return n;
}

*/

double f(double n);

int main()
{
	double a, b, e, c, x;
	system("chcp 1251");
	system("cls");
	a = 2;
	b = 4.7;
	cout << "tgx-x = 0 [" << a << "," << b << "]\n\n";
	
	e = 0.001;
	if ((f(a) * f(b)) >= 0)
	{
		cout << "ОШИБКА";
	}
	else
	{
		while ((b - a) > e)
		{
			c = (a + b) / 2;
			if (abs(f(c)) < e)
			{
				x = (a + b) / 2;
				cout << "x = " << x;
				return 0;
			}

			if (f(a) * f(c) < 0)
			{
				b = c;
			}
			else
			{
				a = c;
			}

			
		}
		x = (a + b) / 2;
		cout << "x = " << x;
		
	}
	return 0;
}

double f(double x)
{
	return (tan(x) - x);
}