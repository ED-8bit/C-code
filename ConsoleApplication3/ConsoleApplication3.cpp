#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
/*
int main()
{
	int magic;
	int guess;
	system("chcp 1251");
	srand(time(0));
	magic = rand() % 11;
	cout << "Угадайте число от 1 до 10: " << '\n';
	cin >> guess;
	if (guess == magic) cout << "**Правильно**";
	if (magic < guess) cout << "Неправильно, ваше число больше загаданного";
	if (magic > guess) cout << "Неправильно, ваше число меньше загаданного";
	cout << '\n' << magic << '\n';
	casic();
	del();
	return 0;

}

int main()
{
	int n1, n2;
	system("chcp 1251");
	cout << "Введите два числа для того, чтобы узнать какое больше: ";
	cin >> n1 >> n2;
	if (n1 < n2) cout << n2; else if (n1 > n2) cout << n1; else if (n1 = n2) cout << "Числа равны";
}

int main()
{
	int n1, n2, n3;
	system("chcp 1251");
	cout << "Введите три числа для того, чтобы узнать какое больше: ";
	cin >> n1 >> n2 >> n3;
	if ((n1 == n2) and (n2 == n3)) cout << "Числа равны";
	else if((n1 >= n2) and (n1 >= n3)) cout << n1;
	else if((n2 >= n1) and (n2 >= n3)) cout << n2;
	else if((n3 >= n2) and (n3 >= n1)) cout << n3;
}

int main()
{
	double a, b, c, p, S;
	bool real = false;
	system("chcp 1251");
	cout << "Введите стороны треугольника: ";
	cin >> a >> b >> c;
	if ((a < (b + c)) and (b < (a + c)) and (c < (a + b))) real = true;
	p = (a + b + c) / 2;
	S = sqrt(p * (p - a) * (p - b) * (p - c));
	if (real) cout << "Площадь треугольника: " << S;
	else cout << "Такого треугольника не существует";
}



int main()
{
	int year;
	system("chcp 1251");
	cout << "Введите год, чтобы узнать вискоссный он или нет: ";
	cin >> year;
	if (((year % 4 == 0) and (year % 100 != 0)) or (year % 400 == 0)) cout << "Год високоссный"; else cout << "Год не високоссный";
}


int main()
{	
	double S;
	system("chcp 1251");
	cout << "Вычисление стоимости покупки с учетом скидки.\n";
	cout << "Введите сумму покупки  -> "; cin >> S;
	if (S >= 1000) cout << "Вам предоставляется скидка 5%\n" << "Сумма с учетом скидки: " << (S - (S / 100 * 5)) << " руб" << "\n";
	else if (S >= 500) cout << "Вам предоставляется скидка 3%\n" << "Сумма с учетом скидки: " << (S - (S / 100 * 3)) << " руб" << "\n";
	else cout << "Скидка не предоставляется\n" << "Сумма к оплате: " << S << "\n";



}




int main()
{
	int A, B, Answer, Guess;
	system("chcp 1251");
	srand(time(0));
	A = ((rand() % 10) + 1);
	B = ((rand() % 10) + 1);
	Answer = A * B;
	cout << "Экзамен 2 класс: " << A << "*" << B << "?\n";
	cin >> Guess;
	if (Guess == Answer) cout << "Молодец!";
	else cout << "Учи таблицу умножения(";
	return 0;
}




int main()
{
	int h, m, ideal_m;
	system("chcp 1251");
	cout << "Введите ваш рост (см) и текущий вес (кг), чтобы узнать идеальный вес для вашего тела: \n";
	cin >> h >> m;
	ideal_m = h - 100;
	if (ideal_m > m) cout << "Вам нужно поправиться на " << ideal_m - m << "кг\n";
	else if (ideal_m < m) cout << "Вам нужно похудеть на " << m - ideal_m << "кг\n";
	else if (ideal_m == m) cout << "У Вас идеальный вес\n";
}



int main()
{
	int d, m, y, d1, m1, y1, mdays;
	bool yvis = false;
	system("chcp 1251");
	cout << "Введите цифрами сегодняшнюю дату (число, месяц, год) -> "; // 1 3 5 7 8 10 12 - 31 день, 2 - 28/29 дней
	cin >> d >> m >> y;

	if (((y % 4 == 0) and (y % 100 != 0)) or (y % 400 == 0)) yvis = true;

	if ((m == 1) or (m == 3) or (m == 5) or (m == 7) or (m == 8) or (m == 10) or (m == 12)) mdays = 31;
	else if ((m == 4) or (m == 6) or (m == 9) or (m == 11)) mdays = 30;
	else if ((m == 2) and yvis) mdays = 29;
	else if ((m == 2) and not yvis) mdays = 28;

	d1 = d + 1;

	if (d1 > mdays) m1 = m + 1, d1 = 1;
	else m1 = m;

	if (m1 > 12) y1 = y + 1, m1 = 1, d1 = 1;
	else y1 = y;

	cout << "Завтрашняя дата: " << d1 << "." << m1 << "." << y1;



}

*/

int main()
{
	int d, m;
	system("chcp 1251");
	cout << "Введите вашу дату рождения (день, месяц), чтобы узнать знак зодиака: ";
	cin >> d >> m; cout << '\n';
	if (m == 1) { if (d >= 20) cout << "Вы Водолей"; else cout << "Вы Козерог"; }
	if (m == 2) { if (d >= 19) cout << "Вы Рыбы"; else cout << "Вы Водолей"; }
	if (m == 3) { if (d >= 21) cout << "Вы Овен"; else cout << "Вы Рыбы"; }
	if (m == 4) { if (d >= 20) cout << "Вы Телец"; else cout << "Вы Овен"; }
	if (m == 5) { if (d >= 21) cout << "Вы Близнецы"; else cout << "Вы Телец"; }
	if (m == 6) { if (d >= 21) cout << "Вы Рак"; else cout << "Вы Близнецы"; }
	if (m == 7) { if (d >= 23) cout << "Вы Лев"; else cout << "Вы Рак"; }
	if (m == 8) { if (d >= 23) cout << "Вы Дева"; else cout << "Вы Лев"; }
	if (m == 9) { if (d >= 23) cout << "Вы Весы"; else cout << "Вы Дева"; }
	if (m == 10) { if (d >= 23) cout << "Вы Скорпион"; else cout << "Вы Весы"; }
	if (m == 11) { if (d >= 22) cout << "Вы Стрелец"; else cout << "Вы Скорпион"; }
	if (m == 12) { if (d >= 22) cout << "Вы Козерог"; else cout << "Вы Стрелец"; }
																									
}