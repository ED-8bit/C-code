#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <ctype.h>
#include <conio.h>
#include <cstdlib>
using namespace std;

//Введите строку

//int main()
//{
//	system("chcp 1251");
//	system("cls");
//	char str[80];
//	cout << "Введите строку: ";
//	fgets(str, sizeof(str), stdin); //Считываем строку с клавиатуры
//	cout << "Вот ваша строка: " << str;
//}

//Вставить в строку

//int main()
//{
//	system("chcp 1251");
//	system("cls");
//	char str[80];
//	strcpy_s(str, "Привет");
//	cout << str;
//	return 0;
//}

//Соединить строки

//int main()
//{
//	system("chcp 1251");
//	system("cls");
//	char s1[20], s2[10];
//	strcpy_s(s1, "Привет");
//	strcpy_s(s2, " всем!");
//	strcat_s(s1, s2);
//	cout << s1;
//	return 0;
//}

//Сравнение строк по символам. Пароль

//bool password();
//
//int main()
//{
//	system("chcp 1251");
//	system("cls");
//	if (password()) cout << "Вход разрешен. \n"; else cout << "В доступе отказано. \n";
//	return 0;
//}
//
//bool password()
//{
//	char s[80];
//	cout << "Введите пароль: "; 
//	fgets(s, sizeof(s), stdin);
//	s[strlen(s) - 1] = '\0';
//	if (strcmp(s, "password"))
//	{
//		cout << "Пароль недействителен\n";
//		return false;
//	}
//	else
//	{
//		cout << "Пароль верный\n";
//		return true;
//	}
//}

//Поиск длины строки

//int main()
//{
//	system("chcp 1251");
//	system("cls");
//	char str[80];
//	int i;
//	cout << "Введите строку: "; fgets(str, sizeof(str), stdin);
//	for (i = strnlen(str, sizeof(str)) - 1; i >= 0; i--)
//	{
//		cout << str[i];
//	}
//	return 0;
//}

// Изменение строки

//int main()
//{
//	system("chcp 1251");
//	system("cls");
//	char str[80];
//	int i;
//	strcpy_s(str, "test");
//	for (i = 0; str[i]; i++)
//	{
//		str[i] = toupper(str[i]); //tolower //isalpha //islight // 
//		
//	}
//	cout << str;
//	return 0;
//}

void palindrom_eng();
void one_space(char* str, int n);
void char_bubblesort(char* str, int n);
void words(char str[]);
void words_reverse(char str[]);
void isanagrams(char str[], char str2[]);
unsigned char toupper_goida(unsigned char r);
void winrar(char str[]);
void palindrom_goida(char str1[]);

int main()
{
	system("chcp 1251");
	int choose;
	char str1[80];
	char str2[80];
	

	while (true)
	{
		system("cls");
		str1[0] = '\0';
		str2[0] = '\0';
		cout << "** Меню **\n\n";
		cout << "1. Проверка на палиндром на английском\n";
		cout << "2. Строку с пробелами преобразовать в один пробел\n";
		cout << "3. Вывести отдельные слова из предложения\n";
		cout << "4. Перевернуть порядок слов в строке\n";
		cout << "5. Проверка на Анаграммы\n";
		cout << "6. Алгоритм сжатия строк\n";
		cout << "7. Проверка на палиндром на русском\n";
		cout << "0. Выход\n";
		cout << "Выберите действие: "; cin >> choose;
		switch (choose)
		{
		case 1:
			system("cls");
			palindrom_eng();
			_getch();
			break;
		case 2:
			system("cls");
			cout << "Введите строку: ";
			cin.ignore();
			cin.getline(str1, 80);
			one_space(str1, 80);
			cout << str1;
			_getch();
			break;
		case 3:
			system("cls");
			cout << "Введите строку: ";
			cin.ignore();
			cin.getline(str1, 80);
			words(str1);
			_getch();
			break;
		case 4:
			system("cls");
			cout << "Введите строку: ";
			cin.ignore();
			cin.getline(str1, 80);
			words_reverse(str1);
			_getch();
			break;
		case 5:
			system("cls");
			cout << "Введите первое слово: ";
			cin.ignore();
			cin.getline(str1, 80);
			cout << "Введите второе слово: ";
			cin.getline(str2, 80);
			isanagrams(str1, str2);
			_getch();
		case 6:
			system("cls");
			cout << "Введите строку: ";
			cin.ignore();
			cin.getline(str1, 80);
			winrar(str1);
			_getch();
			break;
		case 7:
			system("cls");
			cout << "Введите строку: ";
			cin.ignore();
			cin.getline(str1, 80);
			palindrom_goida(str1);
			_getch();
			break;


		case 0:
			exit(0);
			break;
		default:
			cout << "Ошибка";
						}

	}
	return 0;
}

// strcpy_s(str, "test"); / присвоение
// strnlen(str, sizeof(str)); / длина
// strcmp(s, "password"); / сравнение (количество отличий)
// strcat_s(s1, s2); / соединить строки
// toupper(str[i]); изменение

void palindrom_eng()
{
	char str[80], str_op[80];
	int i, n;
	cin.ignore();
	cout << "Введите строку: ";
	cin.getline(str, 80);
	strcpy_s(str_op, str);
	n = strnlen(str, sizeof(str)) - 1;
	for (i = n; i >= 0; i--)
	{
		str_op[i] = toupper(str[(abs(i - n))]);
		str[i] = toupper(str[i]);
	}
	//cout << '\n' << str << '\n' << str_op << '\n';
	if (strcmp(str_op, str))
	{
		cout << "Не палиндром";
	}
	else
	{
		cout << "Палиндром";
	}


}

unsigned char toupper_goida(unsigned char r)
{
	if ((r > 223) && (r < 255))
	{
		r -= 32;
	}
	if (r == 184)
	{
		r = 168;
	}
	return r;
}

void one_space(char* str, int n)
{
	//system("chcp 1251");
	//system("cls");
	int i, d;

	for (i = 0; str[i]; i++)
	{
		if (isspace(str[i]) && isspace(str[i + 1]))
		{
			for (d = i+1; d < strlen(str) - 1; d++)
			{
				str[d] = str[d + 1];
			}
			i -= 1;
			
		}
	}
}

void char_bubblesort(char* str, int n)
{
	int i, j;
	char temp;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (str[j] > str[j + 1])
			{
				temp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = temp;
			}
		}
	}
	return;
}

void words(char str[])
{
	int i, n = 1;
	one_space(str, 80);

	for (i = 0; i < strlen(str); i++)
	{
		cout << n <<") ";
		do {
			if (isspace(str[i]) == 0)
			{
				cout << str[i];
			}
			i += 1;
		} while (isspace(str[i]) == false && ispunct(str[i]) == false && str[i] != 0);
		cout << '\n';
		n += 1;
	}

}

void words_reverse(char str[])
{
	int i = 0, n = 0, w = 0, j, k;
	char words[20][60];
	one_space(str, 80);

	while (str[i] != '\0')
	{
		if (isspace(str[i]) == false && ispunct(str[i]) == false)
		{
			words[n][w] = str[i];
			w += 1;

			if (isspace(str[i + 1]) || str[i + 1] == '\0')
			{
				words[n][w] = '\0';
				n++;
				w = 0;
			}
		}
		i++;
	}
	k = n - 1;

	for (k; k >= 0; k--)
	{
		for (j = 0; words[k][j] != '\0'; j++)
		{
			cout << words[k][j];
		}
		if (k > 0) cout << ' ';
	}
	
}

void isanagrams(char str1[], char str2[])
{
	int i;
	
	for (i = 0; str1[i] != '\0'; i++)
	{
		str1[i] = toupper(str1[i]);
		str1[i] = toupper_goida(str1[i]);
	}
	for (i = 0; str2[i] != '\0'; i++)
	{
		str2[i] = toupper(str2[i]);
		str2[i] = toupper_goida(str2[i]);
	}
	char_bubblesort(str1, strlen(str1));
	char_bubblesort(str2, strlen(str2));
	
	if (strcmp(str1, str2))
	{
		cout << "Не анаграммы" << '\n';
	}
	else cout << "Анаграммы";

}

void winrar(char str[])
{
	int i, c = 0, j, n = strlen(str), nc, e = 0;
	char r = str[0];
	char strcompact[80];
	strcompact[0] = '\0';
	for (i = 0; str[i - 1] != '\0'; i++)
	{
		if (str[i] == r)
		{
			c += 1;
		}
		if ((str[i] != r) || str[i] == '\0')
		{
			nc = strlen(strcompact) + 2;
			for (j = e; j < nc; j += 2)
			{
				strcompact[j] = r;
				if (c != 1)
				{
					strcompact[j + 1] = c + '0';
					strcompact[j + 2] = '\0';
					e += 2;
				}
				else
				{
					strcompact[j + 1] = '\0';
					e += 1;
				}
			}
			r = str[i];
			c = 1;
		}
	}
	cout << strcompact;
}

void palindrom_goida(char str1[])
{
	char str_op[80];
	int i, n;
	strcpy_s(str_op, str1);
	n = strnlen(str1, sizeof(str1)) - 1;
	for (i = n; i >= 0; i--)
	{
		str_op[i] = toupper_goida(str1[(abs(i - n))]);
		str1[i] = toupper_goida(str1[i]);
	}
	//cout << '\n' << str1 << '\n' << str_op << '\n';
	if (strcmp(str_op, str1))
	{
		cout << "Не палиндром";
	}
	else
	{
		cout << "Палиндром";
	}
}
