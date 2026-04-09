#include <iostream>
#include <cmath>
using namespace std;
void bools();
void bit();
void ASI();
void del();
void circles();
void r1();
void r2();
void r3();
void r4();
void r5();
void r6();
void r7();
void r8();
void r9();
void r10();

void bools() // and, or, xor
{
	bool p, q;
	cout << "Введите P (0 или 1): "; cin >> p;
	cout << "Введите Q (0 или 1): "; cin >> q;
	cout << "P И Q:   " << bool (p && q) << '\n' << '\r';
	cout << "P ИЛИ Q: " << bool (p || q) <<'\n' << '\r';
	cout << "P XOR Q: " << bool (p != q) << '\n' << '\r';
}


void bit() // четное или нет
{
	int number;
	bool flag;
	cout << "Число четное?: ";
	cin >> number;
	flag = !(number % 2);
	cout << boolalpha << flag;
	cout << endl;
}

void ASI() // Hello ASCII
{
	unsigned char a = 72, b = 101, c = 108, d = 111;
	cout << a << b << c << c << d;

}


void del()
{
	int P, Q;
	bool del;
	cout << "Введите натуральное число P: "; cin >> P;
	cout << "Введите натуральное число Q: "; cin >> Q;
	del = !(P % Q);
	cout << boolalpha << del;

}

void circles()
{
	double x1, x2, y1, y2, x, y, r;
	bool E, C1, C2;

	x1 = 0; y1 = 0; x2 = -1; y2 = 0; r = 1;
	cout << "Введите X: "; 
	cin >> x;
	cout << "Введите Y: "; 
	cin >> y;
	
	int dist1 = (x - x1) * (x - x1) + (y - y1) * (y - y1);
	C1 = (dist1 <= r * r);

	int dist2 = (x - x2) * (x - x2) + (y - y2) * (y - y2);
	C2 = (dist2 <= r * r);

	E = C1 && C2;
	
	cout << boolalpha << E;
}

int main()
{
	system("chcp 1251");
	cout << "BOOLS: " << endl;
	bools(); cout << endl;
	bit(); cout << endl;
	cout << "Вывод ASCII" << endl;
	ASI(); cout << endl;
	cout << endl;
	cout << "P делится на Q?" << endl;
	del(); cout << endl << endl;
	cout << "Входит ли в обе окружности?" << endl;
	circles(); cout << endl << endl;
	cout << "Ответы на задачи: " << endl << endl;
	r1(); cout << endl;
	r2(); cout << endl;
	r3(); cout << endl;
	r4(); cout << endl;
	r5(); cout << endl;
	r6(); cout << endl;
	r7(); cout << endl;
	r8(); cout << endl;
	r9(); cout << endl;
	r10(); cout << endl;
	return 0;
}

void r1()
{
	double y, a = 6.84, b = 3.22, c = 4, d = 2.5;
	y = pow(((a + b) / (c + d)), 2) + b * b;
	cout << y;
}

void r2()
{
	double y, a = 4, b = 13.6;
	y = log10(sqrt(b) + tan(a));
	cout << y;
}

void r3()
{
	double y, a = 9.5, b = 1.365, c = 6.6, d = 3;
	y = (pow(sin(c), 3) * pow(cos(a), 2)) / (5 * pow(sin(b), d));
	cout << y;
}

void r4()
{
	double y, a = 8, b = 5.6;
	y = 2 * a * asin((3.14 / b));
	cout << y;
}

void r6()
{
	double y, a = 5.95, c = 3.6, d = -3;
	y = 2 * (pow(a, d) + (4 * pow(c, 2) / 3.0));
	cout << y;
}

void r5()
{
	double y, a = 5.6, b = 2.8, d = 3;
	y = ((2 * b) * log((a - b))) / (pow(d, 2));
	cout << y;
}

void r7()
{
	double y, a = 3.14, b = -1.57, c = 10.5, d = 8;
	y = 0.5 * log10((1 + sin(b)) / (1 - sin(a))) * (c - d);
	cout << y;
}

void r8()
{
	double y, a = 2.6, b = 56.6, c = 35, d = -20.3;
	y = 1 / (pow(a, 2)) * pow(((b) / 10.0), 3) * (pow((c + d), 2));
	cout << y;
}

void r9()
{
	double y, a = -6, b = 1.64, c = 0.16, d = 0.8;
	y = pow(((a / b - 1) / (c / d - 1)), 2);
	cout << y;
}

void r10()
{
	double y, a = 25, b = 8.5, c = 0.56, d = 0.01;
	y = (a + b) / (c + (d / (a + c)));
	cout << y;
}