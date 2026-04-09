#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;

//int main()
//{
//	int sample[10];
//	int t;
//	for (t = 0; t < 10; t++)
//	{
//		sample[t] = t;
//	}
//	for (t = 0; t < 10; t++)
//	{
//		cout << sample[t] << ' ';
//	}
//	return 0;
//}


//int main()
//{
//	int d[10];
//	srand(time(0));
//	int i;
//	int min, max;
//	for(i = 0; i < 10; i++) d[i] = rand();
//	
//	min = d[0];
//	max = d[0];
//
//	for(i = 0; i < 10; i++ )
//	{
//		if (d[i] < min)
//		{
//			min = d[i];
//		}
//		if (d[i] > max)
//		{
//			max = d[i];
//		}
//	}
//
//	cout << max << '\n';
//	cout << min << '\n';
//	return 0;
//}

//int main()
//{
//	int i, j, n, temp, min, k;
//	int list[100];
//	bool f;
//	system("chcp 1251");
//	system("cls");
//	srand(time(0));
//	cout << "Введите количество элементов массива: "; cin >> n;
//	for (i = 0; i < n; i++) list[i] = rand();
//	for (i = 0; i < n; i++) cout << list[i] << " ";
//	cout << '\n';
//	cout << "Введите индекс элемента, который нужно удалить: "; cin >> j;
//	for (i = j; i < n - 1; i++) list[i] = list[i + 1];
//	n = n - 1;
//	for (i = 0; i < n; i++) cout << list[i] << " ";
//	cout << '\n';
//	return 0;
//}

//int main()
//{
//	int i, j, n, temp, min, k;
//	int list[100];
//	bool f;
//	system("chcp 1251");
//	system("cls");
//	srand(time(0));
//	cout << "Введите количество элементов массива: "; cin >> n;
//	for (i = 0; i < n; i++) list[i] = rand();
//	for (i = 0; i < n; i++) cout << list[i] << " ";
//	cout << '\n';
//	cout << "Введите индекс для вставки: "; cin >> j;
//	cout << "Введите элемент для вставки"; cin >> temp;
//	for (i = n; i > j; i--) list[i] = list[i - 1];
//	n = n + 1;
//	list[j] = temp;
//	for (i = 0; i < n; i++) cout << list[i] << " ";
//	cout << '\n';
//	return 0;
//}


//def bubbleSort(arr):
//	n = len(arr)
//	for i in range(n):
//		swapped = False
//		for j in range(0, n - i - 1) :
//			if arr[j] > arr[j + 1]:
//arr[j], arr[j + 1] = arr[j + 1], arr[j]
//swapped = True
//if not swapped :
//	break

//int main()
//{
//	int i, j, n;
//	int list[100];
//	system("chcp 1251");
//	system("cls");
//	srand(time(0));
//	cout << "Введите количество элементов массива: "; cin >> n;
//	for (i = 0; i < n; i++) list[i] = rand();
//	cout << "[";
//	for (i = 0; i < n; i++) cout << list[i] << " ";
//	cout << "]";
//	cout << "\nОтсортированный вариант: \n";
//	bubblesort(list, n);
//}

void bubblesort(int* arr, int n);
void selectionsort(int* arr, int n);
void arrayview(int arr[], int n);
void arrayview_op(int arr[], int n);
void subqueueview(int arr[], int n);
void minmax();
void numberofmins();
void uninumber();
void temp();
void numberofnumbers();
void isgrowarray();
void abs_selectionsort();
void abs_bubblesort();
void heightofstudents();
void nechet_rand_array();
void add_13_to_array();

//Главная
int main() 
{
	int choose;
	
	//Меню функций
	while (true) 
	{
		system("chcp 1251");
		system("cls");
		cout << "** Меню **\n\n";
		cout << "1.  Номер первого отрицательного и последнего положительного\n";
		cout << "2.  Количество элементов меньше заданного\n";
		cout << "3.  Количество уникальных элементов\n";
		cout << "4.  Средняя температура за неделю\n";
		cout << "5.  Количество вхождений числа в массив\n";
		cout << "6.  Является ли последовательность возрастающей?\n";
		cout << "7.  Сортировка массива по убыванию модуля (выбором)\n";
		cout << "8.  Сортировка массива по убыванию модуля (пузырьком)\n";
		cout << "9.  Количество учеников с ростом выше среднего\n";
		cout << "10. Удаление всех четных чисел из случайного массива\n";
		cout << "11. Ввод чисел в массив, добавление частного при делении на 13\n";
		cout << "0.  Выход\n";
		cout << "\nВыберите действие: "; cin >> choose;

		switch (choose)
		{
		case 1:
			system("cls");
			minmax();
			_getch();
			break;
		case 2:
			system("cls");
			numberofmins();
			_getch();
			break;
		case 3:
			system("cls");
			uninumber();
			_getch();
			break;
		case 4:
			system("cls");
			temp();
			_getch();
			break;
		case 5:
			system("cls");
			numberofnumbers();
			_getch();
			break;
		case 6:
			system("cls");
			isgrowarray();
			_getch();
			break;
		case 7:
			system("cls");
			abs_selectionsort();
			_getch();
			break;
		case 8:
			system("cls");
			abs_bubblesort();
			_getch();
			break;
		case 9:
			system("cls");
			heightofstudents();
			_getch();
			break;
		case 10:
			system("cls");
			nechet_rand_array();
			_getch();
			break;
		case 11:
			system("cls");
			add_13_to_array();
			_getch();
			break;
		case 0:
			system("cls");
			return 0;
			break;
		default:
			cout << "Ошибка";
			_getch();
			break;
		}
	}
	
}

//Пузырьковая сортировка
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
//Сортировка выбором
void selectionsort(int* arr, int n)
{
	int i, temp, min_value, min_value_num, j;
	for (j = 0; j < n - 1; j++)
	{
		min_value = arr[j]; min_value_num = j;
		for (i = j + 1; i < n; i++)
		{
			if (min_value > arr[i])
			{
				min_value = arr[i];
				min_value_num = i;
			}
		}
		if (min_value != j)
		{
			temp = arr[j];
			arr[j] = min_value;
			arr[min_value_num] = temp;
		}
	}
	return;

}
//Вывод массива
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
// Вывод обратного массива
void arrayview_op(int arr[], int n)
{
	int i;
	cout << "\n[";
	for (i = n-1; i > -1; i--)
	{
		if (i != 0) cout << arr[i] << ',' << ' ';
		else cout << arr[i];
	}
	cout << "]\n";
}
//Вывод последовательности
void subqueueview(int arr[], int n)
{
	{
		int i;
		for (i = 0; i < n; i++)
		{
			if (i != n - 1) cout << arr[i] << ',' << ' ';
			else cout << arr[i];
		}
	}
}
//Первое отрицательное и последнее положительное
void minmax() 
{
	int i, j, n, list[100], c = 0, b;
	bool is = false;
	system("cls");
	cout << "Введите количество элементов массива: "; cin >> n;
	for (i = 0; i < n; i++)
	{
		cout << "[";
		for (j = 0; j < c; j++)
		{
			cout << list[j] << ',' << ' ';
		}
		cout << ']';
		cout << "\nВведите элемент: "; cin >> b;
		list[j] = b;
		c += 1;
		system("cls");
	}
	arrayview(list, n);

	c = 0;
	for (i = 0; i < n; i++)
	{
		if (list[i] < 0)
		{
			cout << "Номер первого отрицательного: " << i + 1 << '\n';
			is = true;
			break;
		}
	}
	if (is == false)
	{
		cout << "Нет отрицательных чисел\n";
	}
	is = false;
	for (j = n; j > 0; j--)
	{
		if (list[j] > 0)
		{
			cout << "Номер последнего положительного: " << j+1 << '\n';
			is = true;
			break;
		}
	}
	if (is == false)
	{
		cout << "Нет положительных чисел\n";
	}
}
//Количество чисел меньше заданного
void numberofmins()
{
	int i, c = 0, b, list[100], n, j;
	system("cls");
	cout << "Введите количество элементов массива: "; cin >> n;
	for (i = 0; i < n; i++)
	{
		cout << "[";
		for (j = 0; j < c; j++)
		{
			cout << list[j] << ',' << ' ';
		}
		cout << ']';
		cout << "\nВведите элемент: "; cin >> b;
		list[j] = b;
		c += 1;
		system("cls");
	}
	arrayview(list, n);

	c = 0;
	cout << "Введите число: "; cin >> b; cout << '\n';
	for (i = 0; i < n; i++)
	{
		if (list[i] < b)
		{
			cout << list[i] << ' ';
			c += 1;
		}
	}
	cout << "\nКол-во чисел меньше заданного: " << c << '\n';
}
// Количество уникальных элементов
void uninumber()
{
	int i, j, temp, c = 0, list[100], b, n;
	system("cls");
	cout << "Введите количество элементов массива: "; cin >> n;
	for (i = 0; i < n; i++)
	{
		cout << "[";
		for (j = 0; j < c; j++)
		{
			cout << list[j] << ',' << ' ';
		}
		cout << ']';
		cout << "\nВведите элемент: "; cin >> b;
		list[j] = b;
		c += 1;
		system("cls");
	}
	arrayview(list, n);

	c = 0;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (list[j] > list[j + 1])
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
	for (i = 0; i < n - 1; i++)
	{
		if ((list[i] != list[i + 1]) && (list[i] != list[i - 1]))
		{
			c += 1;
		}
	}
	cout << "Количество уникальных элементов: " << c + 1;
}
//Средняя температура
void temp()
{
	int i, c = 0;
	double sum = 0, temp;
	int daytemplist[7];
	cout << "Введите температуру воздуха за неделю:\n";
	cout << "Понедельник -> "; cin >> daytemplist[0];
	cout << "Вторник -> "; cin >> daytemplist[1];
	cout << "Среда -> "; cin >> daytemplist[2];
	cout << "Четверг -> "; cin >> daytemplist[3];
	cout << "Пятница -> "; cin >> daytemplist[4];
	cout << "Суббота -> "; cin >> daytemplist[5];
	cout << "Воскресенье -> "; cin >> daytemplist[6];
	for (i = 0; i < 7; i++)
	{
		c += 1;
		sum += daytemplist[i];
	}
	temp = sum / c;
	cout << "\nСредняя температура: " << temp << " град.";
	

}
//Количество вхождений
void numberofnumbers()
{
	int i, j, c = 0, m = 0, n, h, b;
	int list[100];
	system("cls");
	cout << "Введите количество элементов массива: "; cin >> n;
	cout << "Введите искомое число: "; cin >> h;
	
	for (i = 0; i < n; i++)
	{
		cout << "[";
		for (j = 0; j < c; j++)
		{
			cout << list[j] << ',' << ' ';
		}
		cout << ']';
		cout << "\nКоличество вхождений числа: " << m << '\n';
		cout << "\nВведите элемент: "; cin >> b;
		list[j] = b;
		c += 1;
		if (list[j] == h)
		{
			m += 1;
		}
		system("cls");
	}
	arrayview(list, n);
	cout << "\nКоличество вхождений числа: " << m << '\n';
}
// Растущая последовательность
void isgrowarray()
{
	int i, j, c = 0, n, b;
	int list[100];
	bool isgrowing = true;
	system("cls");
	cout << "Введите количество элементов последовательности: "; cin >> n;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < c; j++)
		{
			cout << list[j] << ',' << ' ';
		}
		cout << '\n';
		if (isgrowing == true && c != 0) cout << "Последовательность возрастающая";
		if (isgrowing == false) cout << "Последовательность не возрастающая";
		cout << "\nВведите элемент: "; cin >> b;
		list[j] = b;
		if (list[j] < list[j - 1] || list[j] == list[j - 1]) isgrowing = false;
		c += 1;
		system("cls");
	}
	subqueueview(list, n);
	if (isgrowing == true && c != 0) cout << "\nПоследовательность возрастающая";
	if (isgrowing == false) cout << "\nПоследовательность не возрастающая";
}
// Обратная сортировка выбором
void abs_selectionsort()
{
	int i, c = 0, b, list[100], n, j, temp, min_value, min_value_num;
	system("cls");
	cout << "Введите количество элементов массива: "; cin >> n;
	for (i = 0; i < n; i++)
	{
		cout << "[";
		for (j = 0; j < c; j++)
		{
			cout << list[j] << ',' << ' ';
		}
		cout << ']';
		cout << "\nВведите элемент: "; cin >> b;
		list[j] = b;
		c += 1;
		system("cls");
	}
	cout << "Результат: \n";

	for (j = 0; j < n - 1; j++)
	{
		min_value = list[j]; min_value_num = j;
		for (i = j + 1; i < n; i++)
		{
			if (abs(min_value) > abs(list[i]))
			{
				min_value = list[i] ;
				min_value_num = i;
			}
		}
		if (min_value != j)
		{
			temp = list[j];
			list[j] = min_value;
			list[min_value_num] = temp;
		}
	}
	
	arrayview_op(list, n);
}
// Обратная сортировка пузырьком
void abs_bubblesort()
{
	int i, c = 0, b, list[100], n, j, temp;
	system("cls");
	cout << "Введите количество элементов массива: "; cin >> n;
	for (i = 0; i < n; i++)
	{
		cout << "[";
		for (j = 0; j < c; j++)
		{
			cout << list[j] << ',' << ' ';
		}
		cout << ']';
		cout << "\nВведите элемент: "; cin >> b;
		list[j] = b;
		c += 1;
		system("cls");
	}
	cout << "Результат: \n";
	
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (abs(list[j]) > abs(list[j + 1]))
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}

	arrayview_op(list, n);
}
// Кол-во высоких учеников
void heightofstudents()
{
	int i, j, midheight = 0, list[100], n, c = 0, b, kids = 0;
	cout << "Введите количество элементов массива: "; cin >> n;
	for (i = 0; i < n; i++)
	{
		cout << "[";
		for (j = 0; j < c; j++)
		{
			cout << list[j] << ',' << ' ';
		}
		cout << ']';
		cout << "\nВведите элемент: "; cin >> b;
		list[j] = b;
		midheight += b;
		c += 1;
		system("cls");
	}
	midheight /= c;
	for (i = 0; i < n; i++)
	{
		if (list[i] > midheight)
		{
			kids += 1;
		}
	}
	cout << "Рост учеников: \n";
	arrayview(list, n);
	cout << "\nСредний рост: " << midheight << "\nКоличество учеников выше среднего роста: " << kids;


}
// Случайный массив без четных чисел
void nechet_rand_array()
{
	int list[100], i, j, n;
	cout << "Введите количество элементов для заполнения случайного массива: "; cin >> n;
	srand((time(0)));
	for (i = 0; i < n; i++) list[i] = rand();
	system("cls");
	cout << "Массив: ";
	arrayview(list, n); cout << '\n';
	cout << "Массив без четных чисел: ";
	for (i = 0; i < n; i++)
	{
		if (list[i] % 2 == 0)
		{
			for (j = i; j < n - 1; j++)
			{
				list[j] = list[j + 1];
			}	
			n = n - 1;
			i -= 1;
		}
		
	}
	arrayview(list, n);
}
// Добавление в массив частного от деления на 13
void add_13_to_array()
{
	int i, c = 0, b, list[100], banlist[52], n, j, k, s = 0;
	bool last = false, ban = false;
	system("cls");
	cout << "Введите количество элементов массива: "; cin >> n;

	for (i = 0; i < n; i++)
	{


		cout << "[";
		for (j = 0; j < c; j++)
		{
			for (k = 0; k < 51; k++)
			{
				if (j == banlist[k])
				{
					ban = true;
				}
			}
			
			if (ban != true)
			{
				cout << list[j] << ',' << ' ';
			}
			ban = false;
		}
		cout << ']';
		

		cout << "\nВведите элемент: "; cin >> b;
		if (b % 13 == 0)
		{
			if (i == n - 1) last = true;
			list[j] = b;
			list[j + 1] = b / 13;
			c += 2;
			i += 1;
			banlist[s] = j + 1;
			s += 1;
			n += 1;
			system("cls");
		}
		else
		{
			list[j] = b;
			c += 1;
			system("cls");
		}
		

	}
	arrayview(list, n);

}