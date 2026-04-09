#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES

using namespace std;
void sphere();
void KMtoML();
void MLtoKM();
void coord_dec();
void coord_pol();
void falltime();
void bazar();
const double PI = 3.14159265358979323846;
// Функции и константы

int main()
{ double gallons, liters;
	system("chcp 1251");
	cout << "Введите количество галлонов: ";
	cin >> gallons;
	liters = gallons * 4.55;
	cout << "Литров:" << liters;
	cout << endl << endl;
	KMtoML();
	cout << endl << endl;
	MLtoKM();
	cout << endl << endl;
	sphere();
	cout << endl << endl;
	coord_dec();
	cout << endl << endl;
	coord_pol();
	cout << endl << endl;
	falltime();
	cout << endl << endl;
	bazar();
	return 0;
}

void KMtoML()
{	double ml, km;
	cout << "Введите количество километров: ";
	cin >> km;
	ml = km / 1.609;
	cout << "Миль: " << ml;
}

void MLtoKM()
{
	double ml, km;
	cout << "Введите количество миль: ";
	cin >> ml;
	km = ml * 1.609;
	cout << "Километров: " << km;
	
}

void sphere()

{
	double S, V, Radius;
	cout << "Введите радиус сферы: ";
	cin >> Radius;
	S = 4 * PI * Radius * Radius;
	V = 4.0 / 3.0 * PI * Radius * Radius * Radius;
	cout << "Площадь сферы: " << S;
	cout << endl;
	cout << "Объем сферы: " << V;
}


void coord_dec()
{
	double X, Y, r, ang;
	cout << "Введите радиус: ";
	cin >> r;
	cout << "Введите угол: ";
	cin >> ang;
	X = r * cos(ang);
	Y = r * sin(ang);
	cout << "Декартовые координаты: " << '(' << X << ',' << Y << ')';
}

void coord_pol()
{
	double x, y, r, ang;
	cout << "Введите X: ";
	cin >> x;
	cout << "Введите Y: ";
	cin >> y;
	r = sqrt((x * x + y * y));
	ang = atan2(y, x);
	cout << "Полярные координаты: " << '(' << r << ',' << ang << ')';
}

void falltime()
{
	double t, h, g;
	cout << "Введите высоту: ";
	cin >> h;
	g = 9.8;
	t = sqrt((2 * h) / g);
	cout << "Время падения: " << t << 'c';
}

void bazar()
{
	double pom_col, pom_cost, og_col, og_cost, ucr_col, ucr_cost, sum;
	cout << "Введите количество помидоров и их цену за штуку: ";
	cin >> pom_col >> pom_cost;
	cout << "Введите количество огурцов и их цену за штуку: ";
	cin >> og_col >> og_cost;
	cout << "Введите количество пучков укропа и их цену за штуку: ";
	cin >> ucr_col >> ucr_cost;

	sum = pom_col * pom_cost + og_col * og_cost + ucr_col * ucr_cost;
	cout << "Итого: " << sum;
}