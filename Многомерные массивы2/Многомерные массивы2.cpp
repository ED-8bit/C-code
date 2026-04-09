#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;

int menu();
void DoubleArrayview(int array[100][100]);
void DoubleArrayCreate();
int countchar(int number);
void task_1();
void task_2();
void task_3();
void task_4();
void task_5();
void task_6();
void task_7();
void task_8();


int main()
{
	system("chcp 1251");
	system("cls");
	int choose;
	int arr1[100][100];
	do
	{
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
		case 0:
			system("cls");
			break;
		default:
			system("cls");
			cout << "Ошибка\n\n";
			system("pause");
			break;
		}
	} while (choose != 0);

	return 0;
}

int menu()
{
	int choose;
	system("cls");
	cout << "** Меню **\n";
	cout << "1. Массив 10х10. Вывести числа больше k\n";
	cout << "2. Массив 10х10. Сумма элементов выше главной диагонали\n";
	cout << "3. Транспонирование матрицы 10х10\n";
	cout << "4. Умножение двух матриц\n";
	cout << "5. Номер строки квадратной матрицы с максимальной суммой\n";
	cout << "6. Является ли матрица магическим квадратом\n";
	cout << "7. Отсортировать массив строк в алфавитном порядке\n";
	cout << "8. Посчитать сколько раз каждая строка встречается в массиве строк\n";
	cout << "0. Выход\n";
	cout << "Выберите действие: ";
	cin >> choose;
	return choose;
}

int countchar(int number)
{

	if (number == 0) return 1;
	int count = 0;
	if (number < 0) count++;

	number = abs(number);
	while (number > 0) {
		number /= 10;
		count++;
	}
	return count;

}
void DoubleArrayCreate()
{

	//Создание массива
	int i, j, n, rows, cols;
	int arr[10][10];
	cout << "Введите количество строк до 10: ";
	cin >> rows;
	cout << "Введите количество столбцов до 10: ";
	cin >> cols;
	

	for (i = 0; i < rows; i++)
	{
		cout << "[";
		for (j = 0; j < cols; j++)
		{
			cout << "\033[s";
			cin >> n;
			cout << "\033[u";

			cout << "\033[" << countchar(n) << "C";
			

			if (j+1 != cols)
			cout << ", ";

			arr[i][j] = n;
		}
		cout << "]\n";
	  
	}
	cout << "Продолжить... ";
	_getch();

	//Вывод
	system("cls");
	cout << "Ваш массив: \n";

	for (i = 0; i < rows; i++)
	{
		cout << "[";
		for (j = 0; j < cols; j++)
		{
			
			if (j + 1 != rows)
				cout << arr[i][j] << ", ";
			else
				cout << arr[i][j];
			
		}
		cout << "]\n";
	}
	return;
}
void DoubleArrayview(int arr[100][100])
{
	int i, j;
	
	for (i = 0; i < sizeof(arr); i++)
	{
		cout << "[";
		for (j = 0; j < sizeof(arr[i]); j++)
		{
			if (j + 1 != sizeof(arr[i]))
				cout << arr[i][j] << ", ";
			else
				cout << arr[i][j];
			
		}
		cout << "]\n";
	}
}

void task_1()
{
	int i, j, k, n, c = 0, rows = 10, cols = 10;
	int arr[10][10];
	int positive;
	srand(time(0));

	for (i = 0; i < rows; i++)
	{
		cout << "[";
		for (j = 0; j < cols; j++)
		{
			cout << "\033[s";

			
			n = rand() % 101;
			if (n > 50)
			{
				positive = 1;
			}
			else
				positive = -1;
			
			n = (((rand() % 10)+ 1) * positive);

			cout << "\033[u";

			cout << "\033[" << countchar(n) << "C";

			if (j + 1 != cols)
				cout << ", ";

			arr[i][j] = n;
		}
		cout << "]\n";
   
	}

	
	system("cls");
	cout << "Ваш массив: \n";

	for (i = 0; i < rows; i++)
	{
		cout << "[";
		for (j = 0; j < cols; j++)
		{

			if (j + 1 != rows)
				cout << arr[i][j] << ", ";
			else
				cout << arr[i][j];

		}
		cout << "]\n";
	}

	cout << "Введите число k: ";
	cin >> k;

	cout << "Элементы больше " << k << ':' << '\n';
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (arr[i][j] > k)
			{
				cout << arr[i][j] << " ";
				c += 1;
			}
		}
	}
	cout << '\n' << "Кол-во элементов: " << c << '\n';


	return;
}
void task_2()
{
	int i, j, n, sum = 0, rows = 10, cols = 10;
	int arr[10][10];
	srand(time(0));

	//Генерация массива
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			n = (rand() % 100) + 1;
			arr[i][j] = n;
		}

	}

	//Вывод массива
	system("cls");
	cout << "Ваш массив: \n";
	
	for (i = 0; i < rows; i++)
	{
		cout << "[";
		for (j = 0; j < cols; j++)
		{

			if (j + 1 != rows)
				cout << arr[i][j] << ", ";
			else
				cout << arr[i][j];

		}
		cout << "]\n";
	}

	//Сумма над диагональю
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (j > i)
			{
				sum += arr[i][j];
			}
		}
	}
	cout << "Сумма элементов над главной диагональю: " << sum << '\n' << '\n';

}
void task_3()
{
	int choice, i, j, n, temp, rows, cols;
	int arr[10][10];
	
	do
	{
		system("cls");
		cout << "** Меню **\n" << "1. Создать матрицу\n" << "2. Сгенерировать матрицу\n" << "0. Выход\n" << "Выберите действие: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			cout << "Введите количество строк до 10: ";
			cin >> rows;
			cout << "Введите количество столбцов до 10: ";
			cin >> cols;
			cout << "Заполните матрицу: \n";
			for (i = 0; i < rows; i++)
			{
				cout << "[";
				for (j = 0; j < cols; j++)
				{
					cout << "\033[s";
					cin >> n;
					cout << "\033[u";

					cout << "\033[" << countchar(n) << "C";


					if (j + 1 != cols)
						cout << ", ";

					arr[i][j] = n;
				}
				cout << "]\n";

			}
			break;
		case 2:
			srand(time(0));
			system("cls");
			cout << "Введите количество строк до 10: ";
			cin >> rows;
			cout << "Введите количество столбцов до 10: ";
			cin >> cols;
			//Генерация массива
			for (i = 0; i < rows; i++)
			{
				for (j = 0; j < cols; j++)
				{
					n = (rand() % 100) + 1;
					arr[i][j] = n;
				}

			}
			system("cls");
			cout << "\nМатрица: \n";
			for (i = 0; i < rows; i++)
			{
				cout << "[";
				for (j = 0; j < cols; j++)
				{

					if (j + 1 != rows)
						cout << arr[i][j] << ", ";
					else
						cout << arr[i][j];

				}
				cout << "]\n";
			}
			break;
		case 0:
			return;
			break;
		default:
			cout << "\nОшибка";
		}

		cout << "\nЧтобы транспонировать, нажмите любую клавишу, ... ";
		_getch();

		//Транспонирование матрицы

		for (i = 0; i < rows; i++)
		{
			for (j = i + 1; j < cols; j++)
			{
				temp = arr[i][j];
				arr[i][j] = arr[j][i];
				arr[j][i] = temp;
			}
		}

		//Вывод матрицы
		
		cout << "\n\nВаша транспонированная матрица: \n\n";

		for (i = 0; i < rows; i++)
		{
			cout << "[";
			for (j = 0; j < cols; j++)
			{

				if (j + 1 != rows)
					cout << arr[i][j] << ", ";
				else
					cout << arr[i][j];

			}
			cout << "]\n";
		}
		cout << '\n';
		_getch();
	} while (choice != 0);

}
void task_4()
{
	int choice, i, j, k, g, n, temp, rows1, cols1, rows2, cols2;
	int arr1[10][10], arr2[10][10], arr3[10][10];
	bool possibility = true;

	cout << "** Матрица 1 **\n\n";
	cout << "Введите количество строк до 10: ";
	cin >> rows1;
	cout << "Введите количество столбцов до 10: ";
	cin >> cols1;
	cout << "Заполните матрицу: \n";
	for (i = 0; i < rows1; i++)
	{
		cout << "[";
		for (j = 0; j < cols1; j++)
		{
			cout << "\033[s";
			cin >> n;
			cout << "\033[u";

			cout << "\033[" << countchar(n) << "C";


			if (j + 1 != cols1)
				cout << ", ";

			arr1[i][j] = n;
		}
		cout << "]\n";

	}
	_getch();
	
	system("cls");

	cout << "** Матрица 2 **\n\n";
	cout << "Введите количество строк до 10: ";
	cin >> rows2;
	cout << "Введите количество столбцов до 10: ";
	cin >> cols2;
	cout << "Заполните матрицу: \n";
	for (i = 0; i < rows2; i++)
	{
		cout << "[";
		for (j = 0; j < cols2; j++)
		{
			cout << "\033[s";
			cin >> n;
			cout << "\033[u";

			cout << "\033[" << countchar(n) << "C";


			if (j + 1 != cols2)
				cout << ", ";

			arr2[i][j] = n;
		}
		cout << "]\n";

	}
	_getch();

	if (cols1 != rows2) possibility = false;

	if (possibility == true)
	{
		
		for (i = 0; i < rows1; i++)
			for (j = 0; j < cols2; j++)
				arr3[i][j] = 0;
		
		
		for (i = 0; i < rows1; i++)
		{
			for (j = 0; j < cols2; j++)
			{               
				for (k = 0; k < cols1; k++)
				{
					arr3[i][j] += arr1[i][k] * arr2[k][j];
				}
			}
		}


		cout << "\nРезультат: \n";
		for (i = 0; i < rows1; i++)
		{
			cout << "[";
			for (j = 0; j < cols2; j++)
			{

				if (j + 1 != cols2)
					cout << arr3[i][j] << ", ";
				else
					cout << arr3[i][j];

			}
			cout << "]\n";
		}

	}
	else cout << "\nУмножение невозможно! Количество столбцов первой матрицы должно равняться количеству строк второй.\n\n";

	
}
void task_5()
{
	int choice, i, j, n, temp, rows, cols;
	int arr[10][10];

	do
	{
		system("cls");
		cout << "** Меню **\n" << "1. Создать матрицу\n" << "2. Сгенерировать матрицу\n" << "0. Выход\n" << "Выберите действие: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			cout << "Введите размер до 10: ";
			cin >> rows;
			cols = rows;
			cout << "Заполните матрицу: \n";
			for (i = 0; i < rows; i++)
			{
				cout << "[";
				for (j = 0; j < cols; j++)
				{
					cout << "\033[s";
					cin >> n;
					cout << "\033[u";

					cout << "\033[" << countchar(n) << "C";


					if (j + 1 != cols)
						cout << ", ";

					arr[i][j] = n;
				}
				cout << "]\n";

			}
			break;
		case 2:
			srand(time(0));
			system("cls");
			cout << "Введите количество строк до 10: ";
			cin >> rows;
			cols = rows;

			//Генерация массива
			for (i = 0; i < rows; i++)
			{
				for (j = 0; j < cols; j++)
				{
					n = (rand() % 100) + 1;
					arr[i][j] = n;
				}

			}
			system("cls");
			cout << "\nМатрица: \n";
			for (i = 0; i < rows; i++)
			{
				cout << "[";
				for (j = 0; j < cols; j++)
				{

					if (j + 1 != rows)
						cout << arr[i][j] << ", ";
					else
						cout << arr[i][j];

				}
				cout << "]\n";
			}
			break;
		case 0:
			return;
			break;
		default:
			cout << "\nОшибка";
		}

		cout << "\nЧтобы определить номер наибольшей строки, нажмите любую клавишу, ... ";
		_getch();

		//Поиск наибольшей строки

		int row_n = 1, sum_n = 0, sum_n0 = 0;

		for (i = 0; i < rows; i++)
		{
			for (j = 0; j < cols; j++)
			{
				sum_n0 += arr[i][j];
			}

			if (sum_n0 > sum_n)
			{
				sum_n = sum_n0;
				row_n = i + 1;
			}
			sum_n0 = 0;
		}

		cout << "\n\nНаибольшая строка: " << row_n;

		



		_getch();
	} while (choice != 0);

}
void task_6()
{
	int choice, i, j, n, temp, rows, cols;
	int arr[10][10];

do
{
	system("cls");
	cout << "** Меню **\n" << "1. Создать матрицу\n" << "2. Сгенерировать матрицу\n" << "0. Выход\n" << "Выберите действие: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		system("cls");
		cout << "Введите размер до 10: ";
		cin >> rows;
		cols = rows;
		cout << "Заполните матрицу: \n";
		for (i = 0; i < rows; i++)
		{
			cout << "[";
			for (j = 0; j < cols; j++)
			{
				cout << "\033[s";
				cin >> n;
				cout << "\033[u";

				cout << "\033[" << countchar(n) << "C";


				if (j + 1 != cols)
					cout << ", ";

				arr[i][j] = n;
			}
			cout << "]\n";

		}
		break;
	case 2:
		srand(time(0));
		system("cls");
		cout << "Введите количество строк до 10: ";
		cin >> rows;
		cols = rows;

		//Генерация массива
		for (i = 0; i < rows; i++)
		{
			for (j = 0; j < cols; j++)
			{
				n = (rand() % 100) + 1;
				arr[i][j] = n;
			}

		}
		system("cls");
		cout << "\nМатрица: \n";
		for (i = 0; i < rows; i++)
		{
			cout << "[";
			for (j = 0; j < cols; j++)
			{

				if (j + 1 != rows)
					cout << arr[i][j] << ", ";
				else
					cout << arr[i][j];

			}
			cout << "]\n";
		}
		break;
	case 0:
		return;
		break;
	default:
		cout << "\nОшибка";
	}

	cout << "\nЧтобы узнать является ли магическим квадратом, нажмите любую клавишу, ... ";
	_getch();

	int sum_n = 0, sum_n0 = 0;
	bool square = true;
		
	//Горизонтальность
	for (i = 0; i < rows; i++)
	{
		sum_n = 0;
		for (j = 0; j < cols; j++)
		{
			sum_n += arr[i][j];
		}
		if (i == 0)
		{
			sum_n0 = sum_n;  
		}
		else
		{
			if (sum_n != sum_n0)
			{
				square = false;
			}
		}
	}

	//Вертикальность
		
	if (square)  
	{
		for (j = 0; j < cols; j++)
		{
			sum_n = 0;
			for (i = 0; i < rows; i++)
			{
				sum_n += arr[i][j];
			}
			if (sum_n != sum_n0)
			{
				square = false;
				break;
			}
		}
	}

	//Диагональность

	if (square)
	{
		sum_n = 0;
		for (i = 0; i < rows; i++)
		{
			sum_n += arr[i][i];
		}
		if (sum_n != sum_n0)
		{
			square = false;
		}
	}

		
	if (square)
	{
		sum_n = 0;
		for (i = 0; i < rows; i++)
		{
			sum_n += arr[i][rows - 1 - i];
		}
		if (sum_n != sum_n0)
		{
			square = false;
		}
	}



	if (square)
	{
		cout << "\n\nМагический квадрат";
	}
	else
	{
		cout << "\n\nНе магический квадрат";
	}


	_getch();
} while (choice != 0);
return;
}
void task_7()
{
	char strs[10][80], temp[80];
	int n, i, j;
	cout << "Введите количество строк до 10: ";
	cin >> n;
	cin.ignore();
	for (i = 0; i < n; i++)
	{
		cin.getline(strs[i], 80);
	}

 
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (strs[j][0] > strs[j + 1][0])
			{
				strcpy_s(temp, strs[j]);
				strcpy_s(strs[j], strs[j + 1]);
				strcpy_s(strs[j + 1], temp);
			}
		}
	}

	cout << "Ваш массив строк: \n";
	for (i = 0; i < n; i++)
	{
		cout << strs[i] << '\n';
	}

}
void task_8()
{
	char strs[10][80], temp[80];
	int n, i, j, c, k;

	//Заполнение массива строк
	cout << "Введите количество строк до 10: ";
	cin >> n;
	cin.ignore();
	for (i = 0; i < n; i++)
	{
		cin.getline(strs[i], 80);
	}
	
	cout << "\nЧтобы получить готовый массив строк, нажмите любую клавишу, ... ";
	_getch();
	cout << '\n' << '\n';

	//Подсчет повторов строк и вывод

	for (i = 0; i < n; i++)
	{
		c = 1;
		strcpy_s(temp, strs[i]);
		for (j = i + 1; j < n; j++)
		{
			if (strcmp(temp, strs[j])) continue;
			else
			{
				c += 1;
				for (k = j; k < n - 1; k++)
				{
					strcpy_s(strs[k], strs[k + 1]);
				}
				n -= 1;
			}
		}
		cout << strs[i] << " | строк: " << c << "\n";
	}


}