#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
using namespace std;
/*
int main()
{
	system("chcp 1251");
	system("cls");
	int balance = 3200;
	int balance1 = 5000;
	int* balptr;
	int value;

	balptr = &balance;
	value = *balptr;
	cout << "Баланс равен: " << value << '\n';

	balptr = &balance1;
	value = *balptr;
	cout << "Баланс равен: " << value << '\n';

	return 0;
}



int main()
{
	int* p, num;
	p = &num;
	*p = 100;
	cout << num << ' ';
	(*p)++;
	cout << num << ' ';
	(*p)--;
	cout << num << ' ';
	return 0;
}


int main()
{
	system("chcp 1251");
	system("cls");
	char str[80];
	char token[80];
	char* p, * q;
	cout << "Введите предложение: ";
	cin.getline(str, 30);
	p = str;

	while (*p)
	{
		q = token;
		while (*p != ' ' && *p)
		{
			*q = *p;
			q++;
			p++;
		}
		if (*p) p++;
		*q = '\0';
		cout << token << '\n';
	}
	return 0;
}

*/
/*int main()
{
	const char* fortunes[] = { "Удача\n", "Процветание\n", "Счастье\n", "Доброта\n", "Тепло\n" };
	int chance;
	system("chcp 1251");
	system("cls");
	srand(time(0));
	cout << "Чтобы узнать ваше предсказание нажмите любую клавишу: ";

	while (!_kbhit()) rand();
	cout << '\n';
	chance = rand();
	chance = chance % 5;
	cout << fortunes[chance];
	return 0;
}*/

// *P - обратиться по адресу P
// 
// &P - получить адрес P

int menu()
{
	int choice;
	cout << "** Меню **\n";
	cout << "1. Найти указатель строки. Вывести через него строку\n";
	cout << "2. В массиве из 5 чисел обратиться к 3 и 4 через арифметику указателей\n";
	cout << "3. Сортировка массива указателей по их значениям\n";
	cout << "4. Найти удвоенную разность квадратов через ссылки\n";
	cout << "5. Увеличить значение переменных через ссылку и указатель\n";
	cout << "6. Написать викторину на 5 слуайных вопросов\n";
	cout << "7. Объявить массив указателями. Поменять значения четных и нечетных ячеек.\n";
	cout << "8. Заданный массив с квадратами и их суммой\n";
	cout << "9. Таблица умножения\n";
	cout << "0. Выход\n";
	cout << "Выберите действие: ";
	cin >> choice;
	return choice;
}
void arrayview(int arr[], int n)
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
void bubblesort(int* arr, int n)
{
	int i, j, temp;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return;
}
void task_1()
{
	char str[]{ "Hello, world" };
	char* s;

	s = str;

	while (*s)
	{
		cout << *s;
		*s++;
	}
	cout << '\n';

}
void task_2()
{
	int i, arr[5];
	int* n;
	srand(time(0));

	for (i = 0; i < 5; i++)
	{
		arr[i] = (rand() % 100) + 1;
	}
	cout << "Массив: ";
	arrayview(arr, 5);

	n = arr;

	cout << "3 элемент: " << *(n + 2) << '\n';
	cout << "4 элемент: " << *(n + 3) << '\n';
}
void task_3()
{
	int* arrptr[10];
	int arr[10], i, j;
	int* temp;

	srand(time(0));
	for (i = 0; i < 10; i++)
	{
		arr[i] = (rand() % 100) + 1;
	}

	for (i = 0; i < 10; i++)
	{
		arrptr[i] = &arr[i];
	}
	cout << "Массив значений: \n\n";
	arrayview(arr, 10);

	cout << "\n\nМассив указателей: \n\n";
	cout << "[";
	for (i = 0; i < 10; i++)
	{
		if (i !=  9) cout << arrptr[i] << ',' << ' ';
		else cout << arrptr[i];
	}
	cout << "]\n\n";

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9 - i; j++)
		{
			if (*arrptr[j] > *arrptr[j + 1])
			{
				temp = arrptr[j];
				arrptr[j] = arrptr[j + 1];
				arrptr[j + 1] = temp;
			}
		}
	}

	cout << "Отсортированный массив значений: \n\n";
	bubblesort(arr, 10);
	arrayview(arr, 10);
	cout << "\n\n";

	cout << "Отсортированный массив указателей: \n\n";
	cout << "[";
	for (i = 0; i < 10; i++)
	{
		if (i != 9) cout << arrptr[i] << ',' << ' ';
		else cout << arrptr[i];
	}
	cout << "]\n\n";

}
void task_4()
{
	int A = 0, B = 0, C = 0;
	int& f = A;
	int& s = B;
	int& t = C;

	cout << "Введите первое число: ";
	cin >> f;
	cout << "Введите второе число: ";
	cin >> s;
	t = 2 * (f*f - s*s);
	cout << "Удвоенная разность квадратов: " << C << "\n\n";

}
void task_5()
{
	int A, B;
	int* i = &A;
	int& j = B;
	cout << "Введите первое число: ";
	cin >> *i;
	cout << "Введите второе число: ";
	cin >> j;

	j = j * 2;
	*i = (*i) * 2;

	cout << "\nУдвоенные числа: " << *i << ", " << j << "\n\n";

}
void task_6()
{
	const char* questions[] = { "DOTA 2 является достойной игрой?\n\n A) Да\n В) Скорее да, чем нет\n C) Скорее нет, чем да\n D) Нет\n\n Ваш вариант ответа: ","С", "Какой кофе больше бодрит?\n\n A) Американо\n B) Эспрессо\n С) Капучино\n D) Латте\n\n Ваш вариант ответа: ", "B", "Столица США?\n\n A) Вашингтон\n B) Нью-Йорк\n C) Лас-Вегас\n D) Лос-Анджелес\n\n Ваш вариант ответа: ", "A", "Какая гора самая высокая?\n\n A) Килиманджаро\n B) Эльбрус\n C) Фудзияма\n D) Джомолунгма\n\n", "D", "Для какой еды родиной является Япония?\n\n A) Суп-лапша\n B) Удон\n C) Суп ФО-БО\n D) Кимчи\n\n", "B" };
	char answer[30];
	int i, j, q, score = 0, len = 5;
	int num[5];
	srand(time(0));
	cout << "** Викторина! **\n\n Ответьте на 5 вопросов\n\n";
	system("pause");
	cin.ignore();

	for (i = 0; i < len; i++)
	{
		num[i] = i * 2;
	}

	for (i = len - 1; i > 0; i--) 
	{
		j = rand() % (i + 1);
		swap(num[i], num[j]);
	}


	for (i = 0; i < len; i++)
	{

		cout << questions[num[i]];
		cin.getline(answer, 30);

		answer[0] = toupper(answer[0]);

		if (strcmp(questions[num[i] + 1], answer) == 0)
		{
			score += 1;
		}


	}
	cout << "\n\nРезультат: " << score << "/" << len<< "\n\n";
	score = 0;
}
void task_7()
{
	int* nums = new int[12];
	int i, temp;
	srand(time(0));

	for (i = 0; i < 12; i++)
	{
		nums[i] = rand() % 11;
	}

	cout << "Массив: \n\n";

	cout << "[";
	for (i = 0; i < 12; i++)
	{
		if (i != 11) cout << nums[i] << ',' << ' ';
		else cout << nums[i];
	}
	cout << "]\n\n";


	for (i = 0; i < 12; i += 2)
	{
		temp = nums[i];
		nums[i] = nums[i + 1];
		nums[i + 1] = temp;
	}
	cout << "Массив с поменявшимися четными и нечетными: \n\n";
	cout << "[";
	for (i = 0; i < 12; i++)
	{
		if (i != 11) cout << nums[i] << ',' << ' ';
		else cout << nums[i];
	}
	cout << "]\n";

	delete[] nums;

}
void task_8()
{
	int i, len, sum = 0;
	cout << "Введите размер массива: ";
	cin >> len;
	int* nums = new int[len];

	for (i = 0; i < len; i++)
	{
		nums[i] = i * i;
		sum += nums[i];
	}
	cout << "Ваш массив: \n\n";
	arrayview(nums, len);
	cout << "\n\nСумма элементов: " << sum << "\n\n";

	delete[] nums;
	
}
void task_9()
{
	int i, n, j, m;
	
	cout << "Введите размер таблицы: ";
	cin >> n;
	m = n;
	int **nums = new int*[n];
	for (i = 0; i < n; i++)
	{
		nums[i] = new int[m];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			nums[i][j] = (i+1) * (j+1);
		}
	}

	cout << "\n\n";

	for (i = 0; i < n; i++)
	{
		cout << "[";
		for (j = 0; j < n; j++)
		{
			if (j + 1 != m)
				cout << nums[i][j] << ", ";
			else
				cout << nums[i][j];
		}
		cout << "]\n";
	}


	for (i = 0; i < n; i++)
	{
		delete[] nums[i];
	}
	delete[] nums;
}

int main()
{
	int choose;
	system("chcp 1251");
	do
	{
		system("cls");
		choose = menu();
		switch (choose)
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
			break;
		default:
			cout << "Ошибка";
			break;

		}
	} while (choose != 0);

	return 0;
}







