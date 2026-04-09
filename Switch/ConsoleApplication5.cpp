#include <iostream>
#include <cmath>
#include <cstdlib>
#include <windows.h>
using namespace std;



//int main()
//{
//	int k, s;
//	system("chcp 1251");
//	cout << "Введите количество грибов: "; cin >> k; cout << '\n' << "Мы нашли " << k << " ";
//	s = 100 * (k / 100);
//	if ((k > 10 + s) && (k < 20 + s))
//	{
//		cout << "грибов";
//	}
//	else 
//	{
//		switch (k % 10)
//		{
//		case 1:
//			cout << "гриб"; break;
//		case 2:
//		case 3:
//		case 4:
//			cout << "гриба"; break;
//		default:
//			cout << "грибов"; break;
//		}
//	}
//
//}




//int main()
//{
//	int choice;
//	system("chcp 1251");
//	cout << "Справка по темам: \n \n";
//	cout << "1. for \n";
//	cout << "2. if \n";
//	cout << "3. switch \n \n";
//	cout << "Введите номер темы (1-3): ";
//	cin >> choice;
//	cout << "\n";
//	switch (choice) {
//	case 1:
//		cout << "for - это самый универсальный цикл в C++ \n"; break;
//	case 2:
//		cout << "if - это инструкция условного ветвления \n"; break;
//	case 3:
//		cout << "switch - это инструкция многонаправленного ветвления \n"; break;
//	default:
//		cout << "Вы должны ввести число  от 1 до 3";
//	}
//	return 0;
//}




//int main()
//{
//	int mins, city;
//	system("chcp 1251");
//	cout << "Список городов: \n\n";
//	cout << "423 Владивосток \n";
//	cout << "95 Москва \n";
//	cout << "815 Мурманск \n";
//	cout << "846 Самара \n\n";
//	cout << "Введите код города: \n"; cin >> city;
//	cout << "Введите время в минутах: \n"; cin >> mins;
//	cout << "\n";
//	switch (city)
//	{
//	case 423:
//		cout << "Стоимость разговора: " << 2.2 * mins << " рублей"; break;
//	case 95:
//		cout << "Стоимость разговора: " << 1 * mins << " рублей"; break;
//	case 815:
//		cout << "Стоимость разговора: " << 1.2 * mins << " рублей"; break;
//	case 846:
//		cout << "Стоимость разговора: " << 1.4 * mins << " рублей"; break;
//	default:
//		cout << "Неверный код города (";
//	}
//}




//int main()
//{
//	int n;
//	system("chcp 1251");
//	cout << "Введите число от 0 до 10: "; cin >> n; cout << "\n\n";
//	switch (n)
//	{
//	case 1:
//		cout << "Римский вариант: I"; break;
//	case 2:
//		cout << "Римский вариант: II"; break;
//	case 3:
//		cout << "Римский вариант: III"; break;
//	case 4:
//		cout << "Римский вариант: IV"; break;
//	case 5:
//		cout << "Римский вариант: V"; break;
//	case 6:
//		cout << "Римский вариант: VI"; break;
//	case 7:
//		cout << "Римский вариант: VII"; break;
//	case 8:
//		cout << "Римский вариант: VIII"; break;
//	case 9:
//		cout << "Римский вариант: IX"; break;
//	case 10:
//		cout << "Римский вариант: X"; break;
//	case 0:
//		cout << "Римский вариант: nulla "; break;
//	default:
//		cout << "Недопустимое значение"; break;
//	}
//	return 0;
//}


//int main()
//{
//	int m;
//	system("chcp 1251");
//	cout << "Введите номер месяца: "; cin >> m; 
//	cout << "\n";
//	switch (m)
//	{
//	case 1:
//		cout << "1 квартал " << "1 полугодие"; break;
//	case 2:
//		cout << "1 квартал " << "1 полугодие"; break;
//	case 3:
//		cout << "1 квартал " << "1 полугодие"; break;
//	case 4:
//		cout << "2 квартал " << "1 полугодие"; break;
//	case 5:
//		cout << "2 квартал " << "1 полугодие"; break;
//	case 6:
//		cout << "2 квартал " << "1 полугодие"; break;
//	case 7:
//		cout << "3 квартал " << "2 полугодие"; break;
//	case 8:
//		cout << "3 квартал " << "2 полугодие"; break;
//	case 9:
//		cout << "3 квартал "  << "2 полугодие"; break;
//	case 10:
//		cout << "4 квартал " << "2 полугодие"; break;
//	case 11:
//		cout << "4 квартал " << "2 полугодие"; break;
//	case 12:
//		cout << "4 квартал" << "2 полугодие"; break;
//	default:
//		cout << "Нет такого месяца"; break;
//	}
//
//}


//int main()
//{
//	double x;
//	char choose;
//	system("chcp 1251");
//	cout << "Введите число: "; cin >> x; cout << '\n';
//	cout << "Выберете действие:\n"; 
//	cout << "1 - возвести число в квадрат\n2 — извлечь корень квадратный\n3 — вычислить синус\n4 - косинус\n# - выход\n";
//	do {
//		cin >> choose;
//		switch (choose)
//		{
//		case '1':
//			cout << "Результат: " << pow(x, 2) << "\n"; break;
//		case '2':
//			cout << "Результат: " << sqrt(x) << "\n"; break;
//		case '3':
//			cout << "Результат: " << sin(x) << "\n"; break;
//		case '4':
//			cout << "Результат: " << cos(x) << "\n"; break;
//		case '#':
//			break;
//		default:
//			cout << "ОШИБКА ввода" << "\n"; break;
//		}
//	} while (choose != '#');
//	return 0;
//}

int main()
{
	int a, b;
	double result;
	char op;
	bool exit = false;
	system("chcp 1251");
	do {
		result = 0;
		system("cls");
		cout << "** Калькулятор **\n\n";
		cout << "Введите целочисленный операнд 1: "; cin >> a;
		cout << "Введите целочисленный операнд 2: "; cin >> b;
		cout << "Выберете операцию (+, -, *, /, %)\n"; cin >> op;
		switch (op)
		{
		case'+':
			result = a + b; cout << "Результат: " << result << '\n' << '\n'; break;
		case '-':
			result = a - b; cout << "Результат: " << result << '\n' << '\n'; break;
		case '*':
			result = a * b; cout << "Результат: " << result << '\n' << '\n'; break;
		case '/':
			if (b != 0) { result = a / b; cout << "Результат: " << result << '\n' << '\n';
			}
			else cout << "ОШИБКА. Делить на ноль нельзя\n"; 
			break;
		case '%':
			if (b != 0) { result = a % b; cout << "Результат: " << result << '\n' << '\n';
			}
			else cout << "ОШИБКА. Делить на ноль нельзя\n";
			break;
		default:
			cout << "ОШИБКА"; break;
		}	
		
		cout << "1 - продолжить\n# - выход\n"; cin >> op;
		switch (op)
		{
		case '1':
			break;
		case '#':
			exit = true; break;
		}
		
	} while (exit != true);
	return 0;
}